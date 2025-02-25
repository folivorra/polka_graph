#ifndef POLISH_H
#define POLISH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"

#define PLUS "+"
#define MINUS "-"
#define MULT "*"
#define DIV "/"
#define ASIN "asin"
#define SIN "sin"
#define COS "cos"
#define ACOS "acos"
#define LN "ln"
#define TG "tg"
#define CTG "ctg"
#define SQ "sqrt"
#define UN_MINUS "~"
#define X "x"

char* to_polish(char* formula, int count);
int priority(char* operator);
double from_polish(double x, char* polish);

#endif