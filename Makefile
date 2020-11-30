DIRECTORIES=$(shell find . -type f -name '*.c' -printf '%h\n' | sort | uniq)

all: compile
default: compile

clean:
	for PROJECT in $(DIRECTORIES); do \
		if [ ! -f $$PROJECT/Makefile ]; then \
			rm -f "$$PROJECT/main"; \
		else \
			make -C $$PROJECT clean; \
		fi \
	done

recompile: clean compile

compile:
	for PROJECT in $(DIRECTORIES); do \
		if [ ! -f $$PROJECT/Makefile ]; then \
			SOURCES=$$(find $$PROJECT -type f -name '*.c' -printf '%p '); \
			gcc -o $$PROJECT/main $$SOURCES -Wall -pedantic -ggdb -lm; \
		else \
			make -C $$PROJECT; \
		fi \
	done

%/main: %
	if [ ! -f $^/Makefile ]; then \
			SOURCES=$$(find $^ -type f -name '*.c' -printf '%p '); \
			gcc -o $@ $$SOURCES -Wall -pedantic -ggdb -lm; \
		else \
			make -C $^; \
		fi \