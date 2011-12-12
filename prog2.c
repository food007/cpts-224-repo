#include "stdio.h"
#include "cma.c"
#include "stdlib.h"
//#include "math.h"
#define MULT 2  
#define MSIZE 1024*16
unsigned long mem[MSIZE];

int main (int argc, char *argv[])
{
  if (argc == 2)
    {
      unsigned long i = 0;
      unsigned long j = 0;
  	  unsigned long k = 0;
      class_memory (mem, MSIZE);	// give it memory allocator
      i = strtoul (argv[1], NULL, 10);
      if (i != 0)
	{
	  unsigned long *t = NULL;
	  do
	    {
		  k = i;
	      t = (unsigned long *) class_malloc (k);
	      if (t != NULL)
			{
			  class_free (t);
		 	  j = k;
			  i *= MULT;
			}
	    }
	  while (t != NULL);
	  printf ("Largest memory block allocated was: %lu\n", j);
	  printf("Next requested block(failed): %lu\n", k);
	}
      else
	{
	  printf ("Invalid argument, must be a positive non-zero number.");
	}
    }
  else
    {
      printf ("Invalid argument, must be a positive non-zero number");
    }
}
