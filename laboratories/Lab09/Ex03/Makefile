all: clean targetInt
default: clean targetInt

targetInt:
	cp dataInt.c data.c
	cp dataInt.h data.h
	gcc -Wall -g -I. -o main data.c tree.c client.c treeAddition.c -lm

targetStr:
	cp dataStr.c data.c
	cp dataStr.h data.h
	gcc -Wall -g -I. -o main data.c tree.c client.c treeAddition.c -lm

clean:
	rm -f main
	rm -f data.c
	rm -f data.h
