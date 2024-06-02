#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QString>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr,
             s21::CalcController *controller = nullptr);
  ~MainWindow();

 private slots:
  void s21_number();
  void s21_operations();
  void s21_result();
  void s21_delete();
  void s21_dot();
  void s21_function();
  void s21_delete_one();
  void s21_clear();
  void on_draw_clicked();

 private:
  Ui::MainWindow *ui;
  int flag = 1;
  int operation = 0;
  int dot = 0;
  int numberflag = 0;
  double xBegin, xEnd, h, X;
  QVector<double> x, y;
  s21::CalcController *calcController;
};
#endif  // MAINWINDOW_H
