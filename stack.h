#ifndef STACK
#define STACK
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    char *data;
    struct stack *next;
} stack;

typedef struct stack_d {
    double data;
    struct stack_d *next;
} stack_d;

stack* push(stack* top, char* str);

stack* pop(stack* top);

stack_d* push_d(stack_d *top, double lexema);

stack_d* pop_d(stack_d *top);

#endif