.PHONY: all
.PHONY: clean
.SILENT: clean
all: prog2 ma
prog2: prog2.o libcma.so
	gcc -o prog2 prog2.o
prog2.o: prog2.c
	gcc -o prog2.o -c prog2.c
ma: libcma.so ma.o
	export LD_LIBRARY_PATH=.
	gcc ma.o libcma.so -o ma -L.
ma.o: ma.c
	gcc -fPIC -o ma.o -c ma.c

libcma.so: cma.c cma.h
	gcc -fPIC -c cma.c -o libcma.so

dist:
	tar -czvf ostrom-hw6.tar.gz cma.c cma.h ma.c prog2.c makefile
clean:
	rm -f *.o *.s ma prog2 *.so*
