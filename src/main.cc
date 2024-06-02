#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
    s21::Calc model;
    s21::CalcController controller(&model);
    MainWindow w(nullptr, &controller);
  w.setWindowTitle("Smart Calc v2.0");
  w.show();
  return a.exec();
}
