SRC=$(wildcard lectures/*/*.c)
OUT=$(patsubst %.c,%,$(SRC))

all: $(OUT)
clean:
	rm $(OUT) || true
recompile: clean $(OUT)

%: %.c | $(SRC)
	gcc -o $@ $^ -Wall -pedantic