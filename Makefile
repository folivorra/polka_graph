GCC=gcc
FLAGS=-Wall -Wextra -Werror

all: src/calculator.c src/polish_notation.c src/stack.c

	$(GCC) $^ -lm -o build/calc.out
	build/calc.out

clean:

	@rm -f build/*.out build/*.o