#include "calculator.h"

double s21Calculate(char *postfix) {
  int length = strlen(postfix);
  char string[length + 1];
  strcpy(string, postfix);

  double stack[255];
  int stack_size = 0;
  int counter = 0;

  for (int i = 0; i < length; i++) {
    char c = string[i];

    if (isdigit(c) || c == '.') {
      double num = get_double_number(string, &i);
      stack[stack_size++] = num;
    } else if (s21Prior(c) != 0) {
      counter += 1;

      if (c == '~') {
        double last = stack_size > 0 ? stack[--stack_size] : 0;
        stack[stack_size++] = execute('-', 0, last);
        continue;
      } else if (c != '#') {
        double second = stack_size > 0 ? stack[--stack_size] : 0,
               first = stack_size > 0 ? stack[--stack_size] : 0;
        stack[stack_size++] = execute(c, first, second);
      }
    }
  }

  return stack[--stack_size];
}

double get_double_number(char *expr, int *i) {
  char str_num[255];
  int str_num_index = 0;

  for (; expr[*i] != '\0'; (*i)++) {
    char num = expr[*i];

    if (isdigit(num) || num == '.') {
      str_num[str_num_index++] = num;
    } else {
      (*i)--;
      break;
    }
  }

  str_num[str_num_index] = '\0';

  return atof(str_num);
}

double execute(char op, double num1, double num2) {
  double result = 0;
  switch (op) {
  case '+':
    result = num1 + num2;
    break;
  case '-':
    result = num1 - num2;
    break;
  case '*':
    result = num1 * num2;
    break;
  case '/':
    result = num1 / num2;
    break;
  case '^':
    result = pow(num1, num2);
    break;
  case '%':
    result = fmod(num1, num2);
    break;
  }
  return result;
}

double start(char *infix) {
  char postfix[255] = "\0";
  double result = 0;

  s21Parcer(infix, postfix);
  result = s21Calculate(postfix);
  return result;
}
