#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, s21::CalcController *controller)
    : QMainWindow(parent), ui(new Ui::MainWindow), calcController(controller) {
  ui->setupUi(this);
  connect(ui->one, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->eight, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->zero, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->x, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->left_b, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->right_b, SIGNAL(clicked()), this, SLOT(s21_number()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(s21_dot()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->minus, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->mul, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->div, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->pow, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(s21_operations()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(s21_function()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(s21_function()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(s21_function()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(s21_function()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(s21_function()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(s21_function()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(s21_function()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(s21_function()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(s21_function()));
  connect(ui->AC, SIGNAL(clicked()), this, SLOT(s21_delete()));
  connect(ui->delete_one, SIGNAL(clicked()), this, SLOT(s21_delete_one()));
  connect(ui->result, SIGNAL(clicked()), this, SLOT(s21_result()));
  connect(ui->clear, SIGNAL(clicked()), this, SLOT(s21_clear()));
  //  credit = new Credit( this ,calcController);
  h = 0.001;
  xBegin = -10;
  xEnd = 10;
  ui->widget->xAxis->setRange(-10, 10);
  ui->widget->yAxis->setRange(-10, 10);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::s21_number() {
  numberflag = 1;
  if (flag == 0) ui->result_text->setText("");
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result_text->text() + button->text();
  ui->result_text->setText(new_label);
  flag = 1;
}

void MainWindow::s21_delete_one() {
  if (ui->result_text->text().size() == 1) {
    ui->result_text->setText("");
  } else {
    ui->result_text->setText(
        ui->result_text->text().left(ui->result_text->text().size() - 1));
  }
}

void MainWindow::s21_dot() {
  if (flag == 0) ui->result_text->setText("");
  if (operation == 1) dot = 0;
  if (!(ui->result_text->text().endsWith('.')) && dot == 0) {
    if (numberflag == 0)
      ui->result_text->setText(ui->result_text->text() + "0.");
    else
      ui->result_text->setText(ui->result_text->text() + ".");
    numberflag = 0;
    dot = 1;
  }
  flag = 1;
}

void MainWindow::s21_function() {
  if (flag == 0) {
    ui->result_text->setText("");
    operation = 1;
  }
  QPushButton *button = (QPushButton *)sender();

  if (button->text() == "sin") {
    ui->result_text->setText(ui->result_text->text() + "sin(");
  } else if (button->text() == "asin") {
    ui->result_text->setText(ui->result_text->text() + "asin(");
  } else if (button->text() == "cos") {
    ui->result_text->setText(ui->result_text->text() + "cos(");
  } else if (button->text() == "acos") {
    ui->result_text->setText(ui->result_text->text() + "acos(");
  } else if (button->text() == "tan") {
    ui->result_text->setText(ui->result_text->text() + "tan(");
  } else if (button->text() == "atan") {
    ui->result_text->setText(ui->result_text->text() + "atan(");
  } else if (button->text() == "ln") {
    ui->result_text->setText(ui->result_text->text() + "ln(");
  } else if (button->text() == "log") {
    ui->result_text->setText(ui->result_text->text() + "log(");
  } else if (button->text() == "sqrt") {
    ui->result_text->setText(ui->result_text->text() + "sqrt(");
  }
  flag = 1;
}

void MainWindow::s21_operations() {
  numberflag = 0;
  operation = 1;
  if (flag == 0) {
    ui->result_text->setText("");
    operation = 1;
  }
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->result_text->text();
  if (button->text() == "/" && !(ui->result_text->text().endsWith("/") ||
                                 ui->result_text->text().endsWith("*") ||
                                 ui->result_text->text().endsWith("-") ||
                                 ui->result_text->text().endsWith("^") ||
                                 ui->result_text->text().endsWith("mod") ||
                                 ui->result_text->text().endsWith("+"))) {
    new_label += "/";
  } else if (button->text() == "*" &&
             !(ui->result_text->text().endsWith("/") ||
               ui->result_text->text().endsWith("*") ||
               ui->result_text->text().endsWith("-") ||
               ui->result_text->text().endsWith("^") ||
               ui->result_text->text().endsWith("mod") ||
               ui->result_text->text().endsWith("+"))) {
    new_label += "*";
  } else if (button->text() == "+" &&
             !(ui->result_text->text().endsWith("/") ||
               ui->result_text->text().endsWith("*") ||
               ui->result_text->text().endsWith("-") ||
               ui->result_text->text().endsWith("^") ||
               ui->result_text->text().endsWith("mod") ||
               ui->result_text->text().endsWith("+"))) {
    new_label += "+";
  } else if (button->text() == "-" &&
             !(ui->result_text->text().endsWith("/") ||
               ui->result_text->text().endsWith("*") ||
               ui->result_text->text().endsWith("-") ||
               ui->result_text->text().endsWith("^") ||
               ui->result_text->text().endsWith("mod") ||
               ui->result_text->text().endsWith("+"))) {
    new_label += "-";
  } else if (button->text() == "^" &&
             !(ui->result_text->text().endsWith("/") ||
               ui->result_text->text().endsWith("*") ||
               ui->result_text->text().endsWith("-") ||
               ui->result_text->text().endsWith("^") ||
               ui->result_text->text().endsWith("mod") ||
               ui->result_text->text().endsWith("+"))) {
    new_label += "^";
  } else if (button->text() == "mod" &&
             !(ui->result_text->text().endsWith("/") ||
               ui->result_text->text().endsWith("*") ||
               ui->result_text->text().endsWith("-") ||
               ui->result_text->text().endsWith("^") ||
               ui->result_text->text().endsWith("mod") ||
               ui->result_text->text().endsWith("+"))) {
    new_label += "mod";
  } else if (button->text() == "(") {
    new_label += "(";
  } else if (button->text() == ")") {
    new_label += ")";
  }

  ui->result_text->setText(new_label);
  flag = 1;
}

void MainWindow::s21_delete() {
  flag = 1;
  operation = 0;
  dot = 0;
  numberflag = 0;
  ui->result_text->setText("");
}

void MainWindow::s21_clear() {
  ui->widget->clearGraphs();
  ui->x_eq->setValue(0);
  ui->Xmax->setValue(0);
  ui->Xmin->setValue(0);
  ui->Ymax->setValue(0);
  ui->Ymin->setValue(0);
  x.clear();
  y.clear();
  ui->widget->replot();
}

void MainWindow::s21_result() {
  ui->result_text->setText(ui->result_text->text() + "=");
  QString string = ui->result_text->text();
  ui->result_text->clear();
  char str[255] = {0};
  strcpy(str, string.toLocal8Bit().constData());
  int status = calcController->run_calc(str, ui->x_eq->value());
  x.clear();
  y.clear();
  ui->widget->clearGraphs();
  if (status == 1) {
    ui->result_text->setText("Error:  Incorrect input.");
  } else {
    QString result = QString::number(calcController->getResult(), 'f', 8);
    ui->result_text->setText(result);
  }
}

void MainWindow::on_draw_clicked() {
  ui->widget->clearGraphs();
  ui->result_text->setText(ui->result_text->text() + "=");
  QString string = ui->result_text->text();
  char str[255] = {0};
  strcpy(str, string.toLocal8Bit().constData());
  int status = calcController->run_calc(str, ui->x_eq->value());

  if (status == 0) {
    if (strchr(str, 'x') != NULL) {
      xBegin = ui->Xmin->value();
      xEnd = ui->Xmax->value();
      double y1 = ui->Ymin->value();
      double y2 = ui->Ymax->value();
      double x1 = ui->Xmin->value();
      double x2 = ui->Xmax->value();
      int status = 0;
      if (xBegin > xEnd || xBegin == xEnd || y1 == y2) {
        ui->result_text->setText("Error:  Incorrect Xmax Xmin Ymin Ymax");
      } else {
        ui->widget->xAxis->setRange(x1, x2);
        ui->widget->yAxis->setRange(y1, y2);
        h = 0.0005 * (xEnd - xBegin);
        for (X = xBegin; X <= xEnd && status != 1; X += h) {
          status = calcController->run_calc(str, X);
          double num = calcController->getResult();
          x.push_back(X);
          y.push_back(num);
        }
        if (status == 0) {
          ui->widget->addGraph();
          ui->widget->graph(0)->setPen(QColor(0, 255, 0, 125));
          ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
          ui->widget->graph(0)->setScatterStyle(
              QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
          ui->widget->graph(0)->addData(x, y);
          ui->widget->replot();
        }
      }
    } else {
      ui->result_text->setText("Error:  Incorrect input without X.");
    }

  } else {
    ui->result_text->setText("Error:  Incorrect input.");
  }
}
