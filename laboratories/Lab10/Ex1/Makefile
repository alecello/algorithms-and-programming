default:
	mkdir -p out

	gcc -Wall -pedantic -ggdb -c -o out/main.o main.c
	gcc -Wall -pedantic -ggdb -c -o out/data.o data.c
	gcc -Wall -pedantic -ggdb -c -o out/tree.o tree.c

	gcc -Wall -pedantic -ggdb -o main out/main.o out/data.o out/tree.o

clean:	
	rm -rf out