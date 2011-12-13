#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "cma.h"
#include "debug.h"
#define NXT(e) ((void*)e+e->size+sizeof(struct MemNode))
#define ITEMNOTFOUND ((void *)-1)

static void *class_membase = NULL;
static void *class_limit = NULL;
static MNode class_inuse = NULL;
static MNode class_nouse = NULL;

static struct {
    unsigned long malloc, calloc, realloc, free, gc, nomem;
} class_counters = {
0, 0, 0, 0, 0, 0};

static MNode class_AddToList(MNode list, MNode item)
{
    ENTER;
    item->next = list;
//return item;
    RETURN(item);
}

static MNode class_RemoveFromList(MNode list, MNode item)
{
    ENTER;
    MNode p, prev;

    prev = NULL;
    for (p = list; p != NULL; p = p->next) {
	if (p == item) {
	    if (prev == NULL)
		list = p->next;
	    else
		prev->next = p->next;
//      return list;
	    RETURN(list);
	}
	prev = p;
    }
    //not in list..
//  return ITEMNOTFOUND;
    RETURN(ITEMNOTFOUND);
}


static void class_printList(MNode list)
{
    ENTER;
    if (!list) {
	EXIT;
	return;
    }
    printf("Node %p, %ld\n", list, list->size);
    class_printList(list->next);
    EXIT;
}

int class_memory(void *mem, size_t size)
{
    ENTER;
    MNode item;
    if (class_membase) {
//      return FALSE;
	RETURN(FALSE);
    }

    class_membase = mem;
    class_limit = mem + size;

    //setup initial list item
    item = (MNode) mem;
    item->size = size - sizeof(struct MemNode);
    item->next = NULL;

    class_nouse = class_AddToList(class_nouse, item);
    EXIT;
}

void *class_calloc(size_t nmemb, size_t size)
{
    ENTER;
    void *mem;

    mem = class_malloc(nmemb * size);
    memset(mem, 0, nmemb * size);
//    return mem;
    RETURN(mem);
}

static MNode class_findNoUse(size_t target)
{
    ENTER;
    size_t closeness = LONG_MAX;
    size_t c;
    MNode best = NULL;
    MNode p;

    for (p = class_nouse; p != NULL; p = p->next) {
	c = p->size - target;
	if (c >= 0 && c < closeness) {
	    best = p;
	    closeness = c;
	}
    }
//    return best;
    RETURN(best);
}

MNode class_splitNode(MNode org, size_t size)
{
    ENTER;
    MNode extra = NULL;
    size_t orgsz = org->size;

    //we need room for a new header
    if ((orgsz - size - sizeof(struct MemNode)) > 0) {
	org->size = size;
	extra = (MNode) ((void *) org + size + sizeof(struct MemNode));
	extra->next = 0;
	extra->size = orgsz - sizeof(struct MemNode) - size;
    }
//    return extra;
    RETURN(extra);
}

void *class_malloc(size_t size)
{
    ENTER;
    MNode newnode, extra;

    newnode = class_findNoUse(size);

    if (newnode) {
	class_nouse = class_RemoveFromList(class_nouse, newnode);	//assume it is there since we just found it there

	//split the node..
	extra = class_splitNode(newnode, size);
	if (extra)
	    class_nouse = class_AddToList(class_nouse, extra);

	newnode->next = NULL;
	class_inuse = class_AddToList(class_inuse, newnode);
//      return (void *) newnode + sizeof(struct MemNode);
	RETURN((void *) newnode + sizeof(struct MemNode));
    } else {
//      return NULL;
	RETURN(NULL);
    }
}

//attempt to find adjacent unused nodes and collapse them.
static void class_garbage()
{
//  ENTER;
//  MNode here, there;
//  here = class_nouse;
//  while (here->next != NULL)
//  {
//      there = here->next;
//      if (NXT(here)==there)
//      {
//        here->next = there->next;
//        here->size = sizeof(struct MemNode) + there->size;
//        class_counters.gc++;
//        return;
//      }
//      else
//      here->next = there->next;
//  }
// EXIT;
}


void class_free(void *ptr)
{
    ENTER;
    MNode cur = NULL;
    if (!ptr) {
	EXIT;
	return;
    }
    cur = class_RemoveFromList(class_inuse, PTRTOMNODE(ptr));
    if (cur == ITEMNOTFOUND) {	//not our pointer       
	EXIT;
	return;
    }
    class_inuse = cur;
    class_nouse = class_AddToList(class_nouse, PTRTOMNODE(ptr));
    class_garbage();
    EXIT;
}

void *class_realloc(void *ptr, size_t size)
{
    ENTER;
    void *mem;
    size_t oldsize;

    mem = class_malloc(size);
    if (!mem)
//      return NULL;
	RETURN(NULL);

    oldsize = PTRTOMNODE(ptr)->size;
    memcpy(mem, ptr, oldsize);

    class_free(ptr);
//    return mem;
    RETURN(mem);
}

void class_stats()
{
    ENTER;
    printf("InUse\n");
    class_printList(class_inuse);

    printf("NoUse\n");
    class_printList(class_nouse);

    printf("Counters:\n");
#define DUMPC(x) printf(" %10s : %d\n",#x,class_counters.x)
    DUMPC(malloc);
    DUMPC(calloc);
    DUMPC(realloc);
    DUMPC(free);
    DUMPC(gc);
    DUMPC(nomem);
#undef DUMPC
    EXIT;
}
