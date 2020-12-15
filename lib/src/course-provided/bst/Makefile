default:
	mkdir -p out
	mkdir -p ../../../bin/course-provided
	mkdir -p ../../../hdr/course-provided

	# Compile for integers
	cp dataInt.c data.c
	cp dataInt.h data.h

	gcc -Wall -pedantic -lm -ggdb -c -o out/tree.o tree.c
	gcc -Wall -pedantic -lm -ggdb -c -o out/data.o data.c

	ar rcs ../../../bin/course-provided/libbst-int.a out/data.o
	ar rcs ../../../bin/course-provided/libbst-int.a out/tree.o

	cat data.h treePublic.h | sed '/#include "dataInt.h"/d' | sed '/#include "data.h"/d' > ../../../hdr/course-provided/bst-int.h

	# Compile for strings
	cp dataStr.c data.c
	cp dataStr.h data.h

	gcc -Wall -pedantic -lm -ggdb -c -o out/tree.o tree.c
	gcc -Wall -pedantic -lm -ggdb -c -o out/data.o data.c

	ar rcs ../../../bin/course-provided/libbst-str.a out/data.o
	ar rcs ../../../bin/course-provided/libbst-str.a out/tree.o

	cat data.h treePublic.h | sed '/#include "dataStr.h"/d' | sed '/#include "data.h"/d' > ../../../hdr/course-provided/bst-str.h

	# Compile for structures
	cp dataStruct.c data.c
	cp dataStruct.h data.h

	gcc -Wall -pedantic -lm -ggdb -c -o out/tree.o tree.c
	gcc -Wall -pedantic -lm -ggdb -c -o out/data.o data.c

	ar rcs ../../../bin/course-provided/libbst-struct.a out/data.o
	ar rcs ../../../bin/course-provided/libbst-struct.a out/tree.o

	cat data.h treePublic.h | sed '/#include "dataStruct.h"/d' | sed '/#include "data.h"/d' > ../../../hdr/course-provided/bst-struct.h

clean:
	rm -rf data.c
	rm -rf data.h

	rm -rf ../../../bin/course-provided/libbst-int.a
	rm -rf ../../../bin/course-provided/libbst-str.a
	rm -rf ../../../bin/course-provided/libbst-struct.a
	
	rm -rf ../../../hdr/course-provided/bst-int.h
	rm -rf ../../../hdr/course-provided/bst-str.h
	rm -rf ../../../hdr/course-provided/bst-struct.h
	
	rm -rf out
