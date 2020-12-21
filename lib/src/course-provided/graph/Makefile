target:
	mkdir -p out
	mkdir -p ../../../bin/course-provided
	mkdir -p ../../../hdr/course-provided

	gcc -Wall -pedantic -lm -ggdb -I ../../../hdr -c -o out/graph.o graph.c

	ar rcs ../../../bin/course-provided/libgraph.a out/graph.o

	cp graph.h ../../../hdr/course-provided/

clean:
	rm -rf out
	rm -rf ../../../bin/course-provided/libgraph.a
	rm -rf ../../../hdr/course-provided/graph.h
