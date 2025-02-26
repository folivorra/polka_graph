GCC=gcc
FLAGS=-Wall -Wextra -Werror
EXENAME=build/calc.out
SRCS=src/*.c

all: $(EXENAME)

clean:

	@rm -rf $(EXENAME) build

$(EXENAME): $(SRCS)

	mkdir build
	$(GCC) $^ -lm -o $(EXENAME)
	$(EXENAME)

rebuild: clean $(EXENAME)