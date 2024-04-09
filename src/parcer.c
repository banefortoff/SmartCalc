#include "calculator.h"

void s21Parcer(char str[], char *result) {
  char e[255];
  strcpy(e, str);

  struct stack *stk;
  stk = (struct stack *)malloc(sizeof(struct stack));
  init(stk);
  char x;

  int result_index = 0;

  for (int i = 0; e[i] != '\0'; i++) {
    if (isdigit(e[i]) || e[i] == '.') {
      result[result_index++] = e[i];
      while (isdigit(e[i + 1]) || e[i + 1] == '.') {
        result[result_index++] = e[++i];
      }
      result[result_index++] = ' ';
    } else if (e[i] == 'c' || e[i] == 's' || e[i] == 't' || e[i] == 'a' ||
               e[i] == 'l') {
      int trig = find_trig(str, i);
      char tmpstr[255];
      double num;

      int trig_value = find_trig_value(trig);
      i = s21FunctionExpression(e, i, tmpstr, trig_value) - 1;
      char tmp_postfix[255] = "\0";
      s21Parcer(tmpstr, tmp_postfix);

      switch (trig) {
      case 1:
        num = cos(s21Calculate(tmp_postfix));
        break;
      case 2:
        num = sin(s21Calculate(tmp_postfix));
        break;
      case 3:
        num = tan(s21Calculate(tmp_postfix));
        break;
      case 4:
        num = acos(s21Calculate(tmp_postfix));
        break;
      case 5:
        num = asin(s21Calculate(tmp_postfix));
        break;
      case 6:
        num = atan(s21Calculate(tmp_postfix));
        break;
      case 7:
        num = sqrt(s21Calculate(tmp_postfix));
        break;
      case 8:
        num = log(s21Calculate(tmp_postfix));
        break;
      case 9:
        num = log10(s21Calculate(tmp_postfix));
        break;
      }
      char numstr[255];
      if (num < 0) {
        int numlen = sprintf(numstr, "%f ", fabs(num));
        memcpy(&result[result_index], numstr, numlen);
        result_index += numlen;
        result[result_index++] = '~';
        result[result_index++] = ' ';
      } else {
        int numlen = sprintf(numstr, "%f ", num);
        memcpy(&result[result_index], numstr, numlen);
        result_index += numlen;
      }

    } else if (e[i] == '(') {
      push(stk, e[i]);
    } else if (e[i] == ')') {
      while ((x = pop(stk)) != '(') {
        result[result_index++] = x;
        result[result_index++] = ' ';
      }
    } else {
      char op = e[i];
      if (op == '-' && (i == 0 || (i > 1 && s21Prior(e[i - 1])))) {
        op = '~';
      }

      if (op == '+' && (i == 0 || (i > 1 && s21Prior(e[i - 1])))) {
        op = '#';
      }

      while (s21Prior(stkTop(stk)) >= s21Prior(op)) {
        result[result_index++] = pop(stk);
        result[result_index++] = ' ';
      }
      push(stk, op);
    }
  }
  while (stk->top != 0) {
    result[result_index++] = pop(stk);
    result[result_index++] = ' ';
  }
  free(stk);

  result[result_index - 1] = '\0';
}

int find_trig_value(int trig) {
  int result = 0;
  if (trig == 1 || trig == 2 || trig == 3 || trig == 9) {
    result = 4;
  } else if (trig == 4 || trig == 5 || trig == 6 || trig == 7) {
    result = 5;
  } else if (trig == 8) {
    result = 3;
  }
  return result;
}

int find_trig(char *e, int i) {
  int trig = 0;

  if (e[i] == 'c' && e[i + 1] == 'o' && e[i + 2] == 's' && e[i + 3] == '(') {
    trig = 1;
  }

  if (e[i] == 's' && e[i + 1] == 'i' && e[i + 2] == 'n' && e[i + 3] == '(') {
    trig = 2;
  }

  if (e[i] == 't' && e[i + 1] == 'a' && e[i + 2] == 'n' && e[i + 3] == '(') {
    trig = 3;
  }

  if (e[i] == 'a' && e[i + 1] == 'c' && e[i + 2] == 'o' && e[i + 3] == 's' &&
      e[i + 4] == '(') {
    trig = 4;
  }

  if (e[i] == 'a' && e[i + 1] == 's' && e[i + 2] == 'i' && e[i + 3] == 'n' &&
      e[i + 4] == '(') {
    trig = 5;
  }

  if (e[i] == 'a' && e[i + 1] == 't' && e[i + 2] == 'a' && e[i + 3] == 'n' &&
      e[i + 4] == '(') {
    trig = 6;
  }

  if (e[i] == 's' && e[i + 1] == 'q' && e[i + 2] == 'r' && e[i + 3] == 't' &&
      e[i + 4] == '(') {
    trig = 7;
  }

  if (e[i] == 'l' && e[i + 1] == 'n' && e[i + 2] == '(') {
    trig = 8;
  }

  if (e[i] == 'l' && e[i + 1] == 'o' && e[i + 2] == 'g' && e[i + 3] == '(') {
    trig = 9;
  }

  return trig;
}

int s21Prior(char a) {
  int priority = 0;
  switch (a) {
  case '~':
  case '#':
    priority = 5;
    break;
  case '^':
    priority = 4;
    break;
  case '*':
  case '/':
  case '%':
    priority = 3;
    break;
  case '-':
  case '+':
    priority = 2;
    break;
  case '(':
    priority = 1;
    break;
  }
  return priority;
}

int s21FunctionExpression(char str[], int i, char tmpstr[], int value) {
  memset(tmpstr, 0, 255);
  int open_bkt = 1;
  int close_bkt = 0;
  for (i += value; open_bkt != close_bkt; i++) {
    if (str[i] == '(') {
      open_bkt++;
    } else if (str[i] == ')') {
      close_bkt++;
    }
    if (open_bkt != close_bkt) {
      strncat(tmpstr, str + i, 1);
    }
  }
  return i;
}
