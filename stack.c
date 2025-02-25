#include "stack.h"

stack *push(stack *top, char *str) {
    stack *newnode = malloc(sizeof(stack));
    newnode->next = top;
    newnode->data = str;
    return newnode;
}

stack *pop(stack *top) {
    if (top == NULL) 
        return top;
    stack *tmp = top->next;
    free(top);
    return tmp;
}

stack_d* push_d(stack_d *top, double lexema) {
    stack_d *newnode = malloc(sizeof(stack_d));
    newnode->next = top;
    newnode->data = lexema;
    return newnode;
}

stack_d* pop_d(stack_d *top) {
    if (top == NULL) 
        return top;
    stack_d *tmp = top->next;
    free(top);
    return tmp;
}