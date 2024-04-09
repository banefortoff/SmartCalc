#include "calculator.h"

void init(struct stack *stk) { stk->top = 0; }

void push(struct stack *stk, char c) {
  if (stk->top < 255) {
    stk->top++;
    stk->elem[stk->top] = c;
  } else
    printf("Стек полон, количество элементов: %d !\n", stk->top);
}

char pop(struct stack *stk) {
  char result;
  if ((stk->top) != -1) {
    result = stk->elem[stk->top--];
  } else {
    printf("Стек пуст!\n");
    result = 0;
  }
  return result;
}

char stkTop(struct stack *stk) {
  char result;
  if ((stk->top) != -1) {
    result = stk->elem[stk->top];
  } else {
    printf("Стек пуст!\n");
    result = 0;
  }
  return result;
}
