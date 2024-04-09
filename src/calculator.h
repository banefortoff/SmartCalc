#ifdef __cplusplus

extern "C" {

#endif

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
  char elem[255];
  int top;
};

//ФУНКЦИИ СТЕКА
void init(struct stack *stk);
void push(struct stack *stk, char c);
char pop(struct stack *stk);
char stkTop(struct stack *stk);

//ФУНКЦИИ ОПН
void s21Parcer(char str[], char *result);
int s21FunctionExpression(char str[], int i, char tmpstr[], int value);
int s21Prior(char a);
int find_trig(char *e, int i);
int find_trig_value(int trig);

//ФУНКЦИИ ВЫЧИСЛЕНИЯ
double s21Calculate(char *postfix);
double execute(char op, double num1, double num2);
double get_double_number(char *expr, int *i);

//ФУНКЦИЯ ДЛЯ ТЕСТОВ
double start(char *infix);

#ifdef __cplusplus
}

#endif
