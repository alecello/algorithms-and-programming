all: clean stack-int
default: clean stack-int

stack-int:
	cp -R item-int.h ./item.h
	cp -R item-int.c ./item.c
	gcc -Wall -g -o main \
	    client.c stack.c util.c item.c -lm

stack-string:
	cp -R item-string.h ./item.h
	cp -R item-string.c ./item.c
	gcc -Wall -g -o main \
	    client.c stack.c util.c item.c -lm

stack-struct:
	cp -R item-struct.h ./item.h
	cp -R item-struct.c ./item.c
	gcc -Wall -g -o main \
	    client.c stack.c util.c item.c -lm

clean:
	rm -f main
	rm -f item.h
	rm -f item.c
