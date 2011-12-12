.PHONY: all
.PHONY: clean
.SILENT: clean
all: ma
test: prog2 ma
	make prog2
	make ma
prog2:p2.c libcma.so
	gcc -o prog2 p2.c libcma.so
ma: libcma.so ma.o
	export LD_LIBRARY_PATH=.
	gcc ma.o -lcma -o ma -L.
ma.o: ma.c
	gcc -fPIC -o ma.o -c ma.c

libcma.so: cma.c cma.h
	gcc -fPIC -c cma.c -o cma.o
	gcc -shared -Wl,-soname,libcma.so.1 -o libcma.so.1 cma.o
dist:
	tar -czvf ostrom-hw6.tar.gz cma.c cma.h ma.c prog2.c makefile
clean:
	rm -f *.o *.s ma prog2 *.so*
