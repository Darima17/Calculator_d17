#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>

#include "../model/calc.h"

namespace s21 {
class CalcController {
 public:
  CalcController(s21::Calc *model) : model_(model) {}
  int run_calc(char *str, double x) { return model_->m_calc(str, &result, x); }
  double getResult() { return result; }

 private:
  Calc *model_;
  double result;
};
}  // namespace s21
#endif
