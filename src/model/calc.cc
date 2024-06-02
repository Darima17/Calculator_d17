#include "calc.h"
namespace s21 {

//=========================== work with stack ===========================//
void Calc::initialization(stack_p *stack) { stack->top = 0; }

// add elements
void Calc::push(stack_p *stack, char c, double n) {
  if (stack->top < MAX) {
    if (c != -1) {
      stack->elem[stack->top] = c;
    } else {
      stack->num[stack->top] = n;
    }
    stack->top++;
  }
}

// take top element
void Calc::take_top(stack_p *stack, char *c, double *n) {
  if (n != NULL) {
    *n = stack->num[stack->top - 1];
  } else {
    *c = stack->elem[stack->top - 1];
  }
}

// delete element
int Calc::pop(stack_p *stack, char *c, double *n) {
  int status = OK;
  if (stack->top > 0) {
    stack->top--;
    if (n == NULL) {
      *c = stack->elem[stack->top];
    } else {
      *n = stack->num[stack->top];
    }
  } else {
    status = ERROR;
  }
  return status;
}

// check stack is empty?
int Calc::check_stack_empty(stack_p *stack) {
  int result = 0;
  if (stack->top == 0) {
    result = 1;
  }
  return result;
}
//=========================== calc ===========================//
char Calc::is_unary(char *str, int i) {
  char check_unar = '0';
  if (((str[i] == '-' || str[i] == '+') && (str[i - 1] == '(' || i == 0))) {
    check_unar = (str[i] == '-') ? '~' : 'p';
  }
  return check_unar;
}

int Calc::check_number(char *str, int i, int *len_num) {
  int status = OK;
  *len_num = 0;
  if (str[0] == '0' && str[1] == '0') {
    status = ERROR;
  } else {
    while (is_digit(str[i])) {
      (*len_num)++;
      i++;
    }
    if (str[i] == '.') {
      (*len_num)++;
      i++;
      if (!is_digit(str[i])) {
        status = ERROR;
      } else {
        while (is_digit(str[i])) {
          (*len_num)++;
          i++;
        }
      }
    }
  }
  return status;
}

char Calc::generate_single_char_token(int *len, char *str, int i) {
  char token = 0;
  if (str[i] >= 'a' && str[i] <= 'z') {
    if (strncmp("cos", str + i, 3) == 0)
      token = 'c';
    else if (strncmp("sin", str + i, 3) == 0)
      token = 's';
    else if (strncmp("tan", str + i, 3) == 0)
      token = 't';
    else if (strncmp("acos", str + i, 4) == 0)
      token = 'C';
    else if (strncmp("asin", str + i, 4) == 0)
      token = 'S';
    else if (strncmp("atan", str + i, 4) == 0)
      token = 'T';
    else if (strncmp("sqrt", str + i, 4) == 0)
      token = 'q';
    else if (strncmp("ln", str + i, 2) == 0)
      token = 'L';
    else if (strncmp("log", str + i, 3) == 0)
      token = 'l';
  }
  if (token == 'c' || token == 's' || token == 't' || token == 'l')
    *len += 2;
  else if (token == 'C' || token == 'S' || token == 'T' || token == 'q')
    *len += 3;
  else if (token == 'L')
    *len += 1;
  return token;
}

int Calc::priority(char c) {
  int priority = 0;
  switch (c) {
    case '+':
    case '-':
      priority = 1;
      break;
    case '*':
    case '/':
    case '%':
      priority = 2;
      break;
    case '~':
    case 'p':
      priority = 3;
      break;
    case '^':
      priority = 4;
      break;
    default:
      break;
  }
  return priority;
}

int Calc::check_and_parcer(char *str, char *polish) {
  if (str == NULL) return ERROR;
  stack_p stack;
  initialization(&stack);
  int status = OK;
  int i = 0;

  while (str[i] != '=' && status == OK) {
    char sign;
    int len = 1;
    if (is_oper(str[i])) {
      if ((sign = is_unary(str, i)) != '0') {
        add_sign(sign, polish, &stack);
      } else {
        add_sign(str[i], polish, &stack);
        len = (str[i] == 'm') ? 3 : 1;
      }
    } else if (is_digit(str[i])) {
      status = check_number(str, i, &len);
      if (status == OK) add_num(str, polish, i);
    } else if (is_brace(str[i])) {
      status = add_brace(str[i], polish, &stack);
      if (str[i] == '(' && str[i + 1] == ')') status = ERROR;
    } else if (is_func(str[i])) {
      char func = generate_single_char_token(&len, str, i);
      int b = i + len;
      if (check_func_brace(b, str)) {
        status = ERROR;
      } else {
        push(&stack, func, 0);
      }
    } else if (str[i] == 'x') {
      add(polish, str[i]);
      add(polish, ' ');
    } else {
      status = ERROR;
    }
    i += len;
  }
  if (status == OK) {
    status = oper_tr_in_stack(polish, &stack);
  } else {
    clean_polish(polish);
  }
  return status;
}

int Calc::oper_tr_in_stack(char *polish, stack_p *stack) {
  char c = 0;
  int status = OK;
  take_top(stack, &c, NULL);
  while (strchr("%~^p+-/*", c) != NULL && c != '\0') {
    pop(stack, &c, NULL);
    add(polish, c);
    if (!check_stack_empty(stack)) {
      add(polish, ' ');
      take_top(stack, &c, NULL);
    } else {
      break;
    }
  }
  if (is_brace(c)) {
    status = ERROR;
  }
  return status;
}

void Calc::add(char *polish_str, char c) {
  char temp[2] = {'\0'};
  temp[0] = c;
  strcat(polish_str, temp);
}

void Calc::add_num(char *str, char *polish_str, int i) {
  while (is_digit(str[i]) || str[i] == '.') {
    add(polish_str, str[i]);
    i++;
  }
  add(polish_str, ' ');
}

void Calc::add_sign(char str, char *polish_str, stack_p *stack) {
  char sign_1 = 0;
  if (str == 'm') {
    sign_1 = '%';
  } else {
    sign_1 = str;
  }
  char sign_2 = 0;
  take_top(stack, &sign_2, NULL);
  while ((priority(sign_1) <= priority(sign_2)) &&
         !(sign_1 == '^' && sign_2 == '^')) {
    pop(stack, &sign_2, NULL);
    add(polish_str, sign_2);
    add(polish_str, ' ');
    take_top(stack, &sign_2, NULL);
  }
  push(stack, sign_1, 0);
}

int Calc::add_brace(char str, char *polish_str, stack_p *stack) {
  int status = OK;
  if (str == '(') {
    push(stack, str, -1);
  } else {
    char c = 0;
    take_top(stack, &c, NULL);
    while (c != '(') {
      if (check_stack_empty(stack)) {
        status = ERROR;
        break;
      }
      pop(stack, &c, NULL);
      add(polish_str, c);
      add(polish_str, ' ');
      take_top(stack, &c, NULL);
    }
    pop(stack, &c, NULL);
    take_top(stack, &c, NULL);
    if (strchr("cstCSTqLl", c) != NULL && c != '\0') {
      pop(stack, &c, NULL);
      add(polish_str, c);
      add(polish_str, ' ');
    }
  }
  return status;
}

void Calc::clean_polish(char *polish) {
  for (int i = 0; i < MAX; i++) {
    polish[i] = '\0';
  }
}

int Calc::m_calc(char *str, double *result, double x) {
  char polish[MAX] = {0};
  int status = check_and_parcer(str, polish);
  // out(polish);
  if (strchr(polish, 'x') != NULL) {
    char *current = polish;
    status = calc(current, result, x);
  } else {
    if (status == OK) {
      char *current = polish;
      status = calc(current, result, 0);
    }
  }
  return status;
}

int Calc::calc(char *polish, double *result, double x) {
  int status = OK;
  char polish_copy[255] = {0};
  strcpy(polish_copy, polish);
  char *lexem = 0;
  stack_p stack;
  initialization(&stack);
  lexem = strtok(polish_copy, " ");

  while (lexem != NULL && status != ERROR) {
    if (is_digit(*lexem)) {
      double num = atof(lexem);
      push(&stack, -1, num);
    } else if (*lexem == 'x') {
      push(&stack, -1, x);
    } else {
      if (*lexem == '~' || *lexem == 'p' ||
          strchr("cstCSTqLl", *lexem) != NULL) {
        if (check_stack_empty(&stack)) {
          status = ERROR;
        } else {
          double first = 0;
          pop(&stack, NULL, &first);
          switch (*lexem) {
            case '~':
              first = -first;
              break;
            case 'p':
              first = +first;
              break;
            case 's':
              first = sin(first);
              break;
            case 'c':
              first = cos(first);
              break;
            case 't':
              first = tan(first);
              break;
            case 'S':
              first = asin(first);
              break;
            case 'C':
              first = acos(first);
              break;
            case 'T':
              first = atan(first);
              break;
            case 'L':
              first = log(first);
              break;
            case 'l':
              first = log10(first);
              break;
            case 'q':
              first = sqrt(first);
              break;
          }
          push(&stack, -1, first);
        }
      } else {
        if (stack.top <= 1) {
          status = ERROR;
        } else {
          double first = 0;
          double second = 0;
          pop(&stack, NULL, &first);
          pop(&stack, NULL, &second);
          switch (*lexem) {
            case '+':
              second += first;
              break;
            case '-':
              second -= first;
              break;
            case '*':
              second *= first;
              break;
            case '/':
              second /= first;
              break;
            case '%':
              second = fmod(second, first);
              break;
            case '^':
              second = pow(second, first);
              break;
          }
          push(&stack, -1, second);
        }
      }
    }
    lexem = strtok(NULL, " ");
  }
  if (stack.top != 1) status = ERROR;
  if (status == OK) pop(&stack, NULL, result);
  return status;
}
//=========================== credit ===========================//
int Calc::credit_calc(double total_sum, int time, double procent_rate, int type,
                      double *month_pay, double *overpay, double *total_pay) {
  int status = OK;
  if (total_sum < 0 || time < 1 || procent_rate < 0 || procent_rate >= 100 ||
      type < 1 || type > 2 || procent_rate < 0.01) {
    status = ERROR;
  } else {
    if (type == 1) {
      double i = procent_rate / 100 / 12;
      month_pay[0] = total_sum * (i + (i / (pow(1 + i, time) - 1)));
      *total_pay = time * month_pay[0];
      *overpay = *total_pay - total_sum;
    }
    if (type == 2) {
      *total_pay = 0;
      for (int i = 1; i <= time; i++) {
        month_pay[i - 1] =
            (total_sum) / time + (total_sum - (total_sum / time) * (i - 1)) *
                                     ((procent_rate / 100) / 12);
        *total_pay += month_pay[i - 1];
      }
      *overpay = *total_pay - total_sum;
    }
  }
  return status;
}

}  // namespace s21