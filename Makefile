GCC=gcc
FLAGS=-Wall -Wextra -Werror
EXENAME=build/calc.out
SRCS=src/*.c

all: $(EXENAME)

clean:

	@rm -rf $(EXENAME) build

$(EXENAME): $(SRCS)

	mkdir -p build
	$(GCC) $^ -lm -o $(EXENAME)

rebuild: clean $(EXENAME)