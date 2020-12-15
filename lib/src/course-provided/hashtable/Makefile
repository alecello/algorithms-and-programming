target:
	mkdir -p out
	mkdir -p ../../../bin/course-provided
	mkdir -p ../../../hdr/course-provided

	# Compile for integers
	cp itemInt.c item.c
	cp itemInt.h item.h

	gcc -Wall -pedantic -lm -ggdb -c -o out/st.o st.c
	gcc -Wall -pedantic -lm -ggdb -c -o out/item.o item.c

	ar rcs ../../../bin/course-provided/libhashtable-int.a out/st.o
	ar rcs ../../../bin/course-provided/libhashtable-int.a out/item.o

	cat item.h st.h > ../../../hdr/course-provided/hashtable-int.h

	# Compile for structures
	cp itemStruct.c item.c
	cp itemStruct.h item.h

	gcc -Wall -pedantic -lm -ggdb -c -o out/st.o st.c
	gcc -Wall -pedantic -lm -ggdb -c -o out/item.o item.c

	ar rcs ../../../bin/course-provided/libhashtable-struct.a out/st.o
	ar rcs ../../../bin/course-provided/libhashtable-struct.a out/item.o

	cat item.h st.h > ../../../hdr/course-provided/hashtable-struct.h

clean:
	rm -rf item.c
	rm -rf item.h

	rm -rf ../../../bin/course-provided/libhashtable-int.a
	rm -rf ../../../bin/course-provided/libhashtable-struct.a

	rm -rf ../../../hdr/course-provided/hashtable-int.h
	rm -rf ../../../hdr/course-provided/hashtable-struct.h
	
	rm -rf out
