DIRECTORIES=$(shell find . -type f -name '*.c' -printf '%h\n' | sort | uniq)
SRC=$(shell find . -type f -name "*.c" -print)
OUT=$(patsubst %.c,%,$(SRC))

all: $(OUT)
clean:
	@rm $(OUT) || true
recompile: clean $(OUT)

%: %.c | $(SRC)
	gcc -o $@ $^ -Wall -pedantic -ggdb -lm

compile:
	for PROJECT in $(DIRECTORIES); do \
		SOURCES=$$(find $$PROJECT -type f -name '*.c' -printf '%p '); \
		gcc -o $$PROJECT/main $$SOURCES -Wall -pedantic -ggdb -lm; \
	done