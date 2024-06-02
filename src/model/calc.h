#ifndef CALC_H
#define CALC_H
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stack>
#define OK 0
#define ERROR 1
#define MAX 255
namespace s21 {

class Calc {
 private:
  typedef struct stack {
    char elem[MAX];
    double num[MAX];
    int top;
  } stack_p;

  std::stack<char> elem[MAX];

  // stack function from s21_stack_work.c
 public:
  Calc() {}
  ~Calc() {}
  void initialization(stack_p *stack);
  void push(stack_p *stack, char c, double n);
  void take_top(stack_p *stack, char *c, double *n);
  int pop(stack_p *stack, char *c, double *n);
  int check_stack_empty(stack_p *stack);
  // 0 is not empty
  // 1 is empty

  // from s21_postfix_parcer.c
  char is_unary(char *str, int i);
  int is_oper(char c) { return (strchr("m+-*/^", c) != NULL); }
  int is_func(char c) { return (strchr("sctal", c) != NULL && c != '\0'); }
  int is_digit(char c) { return (c >= '0' && c <= '9'); }
  int is_brace(char c) { return (c == '(' || c == ')'); }
  int check_func_brace(int i, char *str) { return (str[i] != '('); }
  int check_number(char *str, int i, int *len_num);
  char generate_single_char_token(int *len, char *str, int i);
  int priority(char c);
  //
  int check_and_parcer(char *str, char *polish);
  int oper_tr_in_stack(char *polish, stack_p *stack);
  // add in stack
  void add(char *polish_str, char c);
  void add_num(char *str, char *polish_str, int i);
  void add_sign(char str, char *polish_str, stack_p *stack);
  int add_brace(char str, char *polish_str, stack_p *stack);
  void clean_polish(char *polish);
  int calc(char *polish, double *result, double x);
  int m_calc(char *str, double *result, double x);
  // from credit
  int credit_calc(double total_sum, int time, double procent_rate, int type,
                  double *month_pay, double *overpay, double *total_pay);
};

}  // namespace s21

#endif  // CALC_H