#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"
#include "polish_notation.h"

#define WIDTH 80
#define HEIGHT 25
#define PI 3.14159265359

void bracket_val(char* str, char* to_free);
int separator(const char *str, int i, int len);
void freee(char* str, char* str1);
void field(char matrix[][WIDTH]);
void print_graph(char matrix[][WIDTH]);

int main() {
    char graph[HEIGHT][WIDTH];
    field(graph);
    char* input = malloc(256); fgets(input, 256, stdin); input[strlen(input) - 1] = '\0';
    char* sep_in = malloc(256); int len = 0, error = 0, count = 0;
    if (strlen(input) == 0) {
        printf("Пустая строк\n");
        freee(input, sep_in);
        return 1;
    }
    bracket_val(input, sep_in);
    int i = 0;
    while (i < (int)strlen(input)) {
        int val_res = separator(input, i, (int)strlen(input));
        if (val_res == -1) {
            error = 1;
            printf("Некорректное выражение\n");
            freee(input, sep_in);
            return 1;
        } else {
            for (int k = i; k < i + val_res; k++) {
                if (val_res == 123) {
                    sep_in[len] = '~';
                    val_res = 1;
                } else {
                    sep_in[len] = input[k];
                }
                len++;
            }
            sep_in[len] = ' ';
            len++;
            i += val_res;
            count++;
        }
    }
    char* polish = to_polish(sep_in, count);

    int count_col = 0;

    for (double x = 0; x <= 4.0 * PI; x += 4.0 * PI / 79) {
        double res = from_polish(x, polish);
        int y = round(res * 12); 
        
        if (y <= 12 && y >= -12) {
            int row = 12 - y; 
            graph[row][count_col] = '*';  
        }
        count_col++;
    }

    print_graph(graph);

    return 0;
}

void bracket_val(char* str, char* to_free) {
    unsigned int bracket_count = 0;
    int len = 0;
    int count_of_digit = 0;
    int count_of_ops = 0;
    while(str[len]) {
        if (str[len] == '(') {
            bracket_count++;
        } else if (str[len] == ')' && bracket_count > 0) {
            bracket_count--;
        } else if (str[len] == ')') {
            printf("Скобки расставлены неправильно\n");
            freee(str, to_free);
            exit(1);
        }
        if (isdigit(str[len]) != 0 || strstr(str, X) != NULL)
            count_of_digit++;
        len++;
    }
    if (bracket_count != 0) {
        printf("Скобки расставлены неправильно\n");
        freee(str, to_free);
        exit(1);
    }
    if (count_of_digit == 0) {
        printf("Выражение только из скобок\n");
        freee(str, to_free);
        exit(1);
    }
}

int separator(const char *str, int i, int len) {
    int flag = -1;
    if (str[i] > 47 && str[i] < 58) {
        flag = 0;
        for (int j = i;
             (str[j] > 47 && str[j] < 58) || (str[j] == '.' && (str[j + 1] > 47 && str[j + 1] < 58)); j++) {
            flag++;
        }
    } else if (i + 4 < len + 1 && str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' && str[i+3] == 'n') {
        flag = 4;
    } else if (i + 4 < len + 1 && str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' && str[i+3] == 's') {
        flag = 4;
    } else if (i + 3 < len + 1 && str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
        flag = 3;
    } else if (i + 4 < len + 1 && str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
        flag = 3;
    } else if (i + 2 < len + 1 && str[i] == 't' && str[i + 1] == 'g') {
        flag = 2;
    } else if (i + 3 < len + 1 && str[i] == 'c' && str[i + 1] == 't' && str[i + 2] == 'g') {
        flag = 3;
    } else if (i + 2 < len + 1 && str[i] == 'l' && str[i + 1] == 'n') {
        flag = 2;
    } else if (i + 4 < len + 1 && str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' && str[i+3] == 't') {
        flag = 4;
    } else if (str[i] == 'x') {
        flag = 1;
    } else if ((i != 0) && (i != len) && ((str[i] > 41 && str[i] < 44) || str[i] == '/' || str[i] == '-') &&
               ((str[i + 1] > 47 && str[i + 1] < 58) || str[i + 1] == 'a' || str[i + 1] == 'c' || str[i + 1] == 'x' || 
               str[i + 1] == 's' || str[i + 1] == 'l' || str[i + 1] == 't' || str[i + 1] == '(') &&
               ((str[i - 1] > 47 && str[i - 1] < 58) || str[i - 1] == 'n' || str[i - 1] == 's' || str[i - 1] == 'x' ||
               str[i - 1] == 'g' || str[i - 1] == 't' || str[i - 1] == ')') &&
               str[i + 1] != ')' && str[i - 1] != '(') {
        flag = 1;
    } else if (i != 0 && str[i] == '(' && (str[i - 1] > 57 || str[i - 1] < 48) && str[i-1] != ')') {
        flag = 1;
    } else if (i == 0 && str[i] == '(') {
        flag = 1;
    } else if (i != strlen(str) && str[i] == ')' && (str[i + 1] > 57 || str[i + 1] < 48) && str[i + 1] != '(') {
        flag = 1;
    } else if (i == strlen(str) && str[i] == ')') {
        flag = 1;
    } else if (str[i] == '-' && (i == 0 || str[i - 1] == '(')) {
        flag = 123;
    }
    return flag;
}

void freee(char* str, char* str1) {
    free(str);
    free(str1);
}

void field(char matrix[][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++) {
            matrix[i][j] = (int)'.';
        }
}

void print_graph(char matrix[][WIDTH]) {
    for (int rows = 0; rows < HEIGHT; rows++) {
        for (int cols = 0; cols < WIDTH; cols++) {
            printf("%c", matrix[rows][cols]);
        }
        printf("\n");
    }
}