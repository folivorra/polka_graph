GCC=gcc
FLAGS=-Wall -Wextra -Werror

all: calculatorAsin.c polish_notation.c stack.c

	$(GCC) $^ -lm
	./a.out

clean:
	@rm -f *.out *.o