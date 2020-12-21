target:
	mkdir -p out
	mkdir -p ../../../bin/course-provided
	mkdir -p ../../../hdr/course-provided

	gcc -Wall -pedantic -lm -ggdb -I ../../../hdr  -c -o out/queue.o queue.c

	ar rcs ../../../bin/course-provided/libqueue.a out/queue.o

	cp queuePublic.h ../../../hdr/course-provided/queue.h

clean:
	rm -rf out
	rm -rf ../../../bin/course-provided/libqueue.a
	rm -rf ../../../hdr/course-provided/queue.h
