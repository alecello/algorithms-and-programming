target:
	mkdir -p out
	mkdir -p ../../../bin/course-provided
	mkdir -p ../../../hdr/course-provided

	gcc -Wall -pedantic -lm -ggdb -I ../../../hdr -c -o out/util.o util.c

	ar rcs ../../../bin/course-provided/libgraph.a out/util.o

	cp util.h ../../../hdr/course-provided/

clean:
	rm -rf out
	rm -rf ../../../bin/course-provided/libutil.a
	rm -rf ../../../hdr/course-provided/util.h
