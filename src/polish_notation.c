#include "../include/polish_notation.h"

char* to_polish(char* sep_formula, int count) {
    char* polish = malloc(strlen(sep_formula));
    stack* top = NULL;
    char* tmp = strtok(sep_formula, " ");
    int i = 1, bracket_counter = 0;
    if ((tmp[0] > 47 && tmp[0] < 58) || tmp[0] == 'x') {
        polish = strcpy(polish, tmp);
        polish[strlen(polish)] = ' ';
    } else {
        top = push(top, tmp);
    }
    while (i < count) {
        char* temp = strtok(NULL, " ");
        if ((temp[0] > 47 && temp[0] < 58) || temp[0] == 'x') {
            polish = strcat(polish, temp);
            polish[strlen(polish)] = ' ';
        } else if (temp[0] == ')') {
            bracket_counter--;
            while (top != NULL && top->data[0] != '(') {
                polish = strcat(polish, top->data);
                polish[strlen(polish)] = ' ';
                top = pop(top);
            }
            if (top != NULL) top = pop(top);
        } else if (top != NULL && priority(temp) <= priority(top->data) && top->data[0] != '(') {
            polish = strcat(polish, top->data);
            polish[strlen(polish)] = ' ';
            top = pop(top);
            top = push(top, temp);
        } else if (temp[0] == '(') {
            bracket_counter++;
            top = push(top, temp);
        } else {
            top = push(top, temp);
        }
        i++;
    }
    while (top != NULL) {
        polish = strcat(polish, top->data);
        polish[strlen(polish)] = ' ';
        top = pop(top);
    }
    return polish;
}

int priority(char* operator) {
    int prior = -1;
    if (strlen(operator) == 1) {
        char op_1 = operator[0];
        if (op_1 == '+' || op_1 == '-') {
            prior = 0;
        } else if (op_1 == '*' || op_1 == '/') {
            prior = 1;
        } else if (op_1 == '~') {
            prior = 2;
        } else if (op_1 == '(' || op_1 == ')') {
            prior = 3;
        }
    } else {
        prior = 2;
    }
    return prior;
}

double from_polish(double x, char* polish) {
    double result = 0;
    char* cp_pol = malloc(256);
    strcpy(cp_pol, polish);
    char* lexema = strtok(cp_pol, " ");
    stack_d* top = NULL;

    while (lexema != NULL) {
        if (lexema[0] != '0' && atof(lexema) != 0) {
            top = push_d(top, atof(lexema));
        } else if (lexema[0] == '0') {
            top = push_d(top, 0);
        } else if (!strcmp(lexema, X)) {
            top = push_d(top, x);
        } else if (!strcmp(lexema, PLUS)) {
            result = top->data + top->next->data;
            top = pop_d(top);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, MINUS)) {
            result = top->next->data - top->data;
            top = pop_d(top);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, MULT)) {
            result = top->data * top->next->data;
            top = pop_d(top);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, DIV)) {
            result = top->next->data / top->data;
            top = pop_d(top);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, ASIN)) {
            result = asin(top->data);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, SIN)) {
            result = sin(top->data);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, ACOS)) {
            result = acos(top->data);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, COS)) {
            result = cos(top->data);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, TG)) {
            result = tan(top->data);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, CTG)) {
            result = 1/tan(top->data);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, LN)) {
            result = log(top->data);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, SQ)) {
            result = sqrt(top->data);
            top = pop_d(top);
            top = push_d(top, result);
        } else if (!strcmp(lexema, UN_MINUS)) {
            result = -1 * top->data;
            top = pop_d(top);
            top = push_d(top, result);
        }
        lexema = strtok(NULL, " ");
    }

    free(cp_pol);

    result = top->data;
    top = pop_d(top);

    return result;
}