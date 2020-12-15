DIRECTORIES=$(shell find . -type f -name '*.c' -printf '%h\n' | sort | uniq)

all: compile
default: compile

clean:
	python build.py clean all

recompile: clean compile

compile:
	python build.py build all

%/main: % %/*.c
	python build.py build $<