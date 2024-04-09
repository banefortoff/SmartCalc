#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  graphic = new Graphic;
  credit = new Credit;

  connect(this, &MainWindow::signal, graphic, &Graphic::slot);

  connect(ui->zero_pushButton, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->one_pushButton, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->two_pushButton, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->three_pushButton, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->four_pushButton, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->five_pushButton, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->six_pushButton, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->seven_pushButton, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->eight_pushButton, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->nine_pushButton, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->x_pushButton, SIGNAL(clicked()), this, SLOT(digits_x()));

  connect(ui->point_pushButton, SIGNAL(clicked()), this, SLOT(digits_point()));

  connect(ui->open_bracket_pushButton, SIGNAL(clicked()), this,
          SLOT(brackets()));
  connect(ui->close_bracket_pushButton, SIGNAL(clicked()), this,
          SLOT(brackets()));

  connect(ui->AC_pushButton, SIGNAL(clicked()), this, SLOT(full_clear()));
  connect(ui->pushButton_c, SIGNAL(clicked()), this, SLOT(clear()));

  connect(ui->add_pushButton, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->sub_pushButton, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->multi_pushButton, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->division_pushButton, SIGNAL(clicked()), this, SLOT(operators()));

  connect(ui->mod_pushButton, SIGNAL(clicked()), this, SLOT(other_operators()));
  connect(ui->degree_pushButton, SIGNAL(clicked()), this,
          SLOT(other_operators()));

  connect(ui->sin_pushButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->cos_pushButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->tan_pushButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->asin_pushButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->acos_pushButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->atan_pushButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->log_pushButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->ln_pushButton, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->sqrt_pushButton, SIGNAL(clicked()), this, SLOT(functions()));

  connect(ui->equals_pushButton, SIGNAL(clicked()), this, SLOT(equals()));
}

MainWindow::~MainWindow() { delete ui; }

///////////ОБРАБОТКА ЧИСЕЛ////////////////////////////////////////////////////////////////////////////////////
void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  int num;
  QString new_label;
  num = (button->text()).toInt();

  if (ui->radioButton_x->isChecked() && ui->label_x->text().length() < 9) {
    new_label = ui->label_x->text() + QString::number(num);
    ui->label_x->setText(new_label);
  } else if (!ui->radioButton_x->isChecked() && check_length()) {
    new_label = ui->label_main->text() + QString::number(num);
    ui->label_main->setText(new_label);
  }
}

//////////ОБРАБОТКА ТОЧКИ////////////////////////////////////////////////////////////////////////////////////
void MainWindow::digits_point() {
  QPushButton *button = (QPushButton *)sender();
  QString label_text;

  if (ui->radioButton_x->isChecked()) {
    label_text = ui->label_x->text();
  } else {
    label_text = ui->label_main->text();
  }

  int index_point = label_text.lastIndexOf(".");
  int str_length = label_text.length();

  if (check_length()) {
    if (str_length != 0 && label_text[str_length - 1].isDigit()) {
      if (index_point != -1) {
        QString str_after_point = label_text.mid(index_point + 1);
        QString char_before_point = label_text[index_point - 1];

        if (is_operator(str_after_point) && char_before_point[0].isDigit() &&
            !str_after_point.contains(".") && is_operator(str_after_point)) {
          ui->label_main->setText(label_text + button->text());
        }
      } else if (str_length - index_point != 1) {
        if (ui->radioButton_x->isChecked()) {
          ui->label_x->setText(label_text + button->text());
        } else {
          ui->label_main->setText(label_text + button->text());
        }
      }
    }
  }
}

///////////ОБРАБОТКА СКОБОК////////////////////////////////////////////////////////////////////////////////////
void MainWindow::brackets() {
  if (check_length() && !ui->radioButton_x->isChecked()) {
    QPushButton *button = (QPushButton *)sender();
    QString label_text = ui->label_main->text();
    int label_length = label_text.length(), open_brk_count = 0,
        close_brk_count = 0;

    open_brk_count = label_text.count('(');
    close_brk_count = label_text.count(')');

    if ((open_brk_count == 0 && button->text() == ")") ||
        (label_length > 0 && label_text[label_length - 1] == '.')) {
      ui->label_main->setText(label_text);
    } else {
      if (button->text() == '(') {
        if (label_length == 0 || (!label_text[label_length - 1].isDigit() &&
                                  label_text[label_length - 1] != 'x' &&
                                  label_text[label_length - 1] != ')')) {
          ui->label_main->setText(label_text + button->text());
        }
      } else if (open_brk_count > close_brk_count) {
        ui->label_main->setText(label_text + button->text());
        close_brk_count++;
      }
    }
  }
}

//////ОБРАБОТКА АРИФМЕТИЧЕСКИХ ОПЕРАТОРОВ///////////////////////////////////////////////////////////////
void MainWindow::operators() {
  QPushButton *button = (QPushButton *)sender();

  if (check_length()) {
    if (!ui->radioButton_x->isChecked()) {
      QString label_text = ui->label_main->text();
      int label_length = label_text.length();

      if (label_length > 0 && !is_operator(label_text[label_length - 1]) &&
          label_text[label_length - 1] != '.') {
        ui->label_main->setText(label_text + button->text());
      } else if (button->text() == '-' &&
                 (label_length == 0 ||
                  (label_length > 0 &&
                   is_arithmetic_operator(label_text[label_length - 1]) &&
                   (label_length > 1 &&
                    !is_arithmetic_operator(label_text[label_length - 2]))))) {
        ui->label_main->setText(label_text + button->text());
      }
    } else if (button->text() == '-' && ui->label_x->text().isEmpty()) {
      ui->label_x->setText(button->text());
    }
  }
}

/////////ОБРАБОТКА ОСТАЛЬНЫХ ОПЕРАТОРОВ///////////////////////////////////////////////////////////////
void MainWindow::other_operators() {
  QPushButton *button = (QPushButton *)sender();
  QString label_text = ui->label_main->text();
  int label_length = label_text.length();

  if (check_length()) {
    if (!ui->radioButton_x->isChecked()) {
      if (label_length > 0 && (label_text[label_length - 1].isDigit() ||
                               label_text[label_length - 1] == 'x' ||
                               label_text[label_length - 1] == ')')) {
        ui->label_main->setText(label_text + button->text() + "(");
      }
    }
  }
}

/////////ОБРАБОТКА ФУНКЦИЙ///////////////////////////////////////////////////////////////
void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();

  if (check_length()) {
    if (!ui->radioButton_x->isChecked()) {

      QString label_text = ui->label_main->text();
      int label_length = label_text.length();

      if (label_length == 0 ||
          (label_length > 0 && (label_text[label_length - 1] != '.' &&
                                !label_text[label_length - 1].isDigit() &&
                                label_text[label_length - 1] != ')'))) {
        ui->label_main->setText(label_text + button->text() + "(");
      }
    }
  }
}

/////////ПОЛНАЯ ОЧИСТКА///////////////////////////////////////////////////////////////
void MainWindow::full_clear() {

  if (ui->radioButton_x->isChecked()) {
    ui->label_x->setText("");
  } else {
    ui->label_main->setText("");
  }
}

////////ОЧИСТКА///////////////////////////////////////////////////////////////
void MainWindow::clear() {

  if (ui->radioButton_x->isChecked()) {
    QString label_text = ui->label_x->text();
    label_text.chop(1);
    ui->label_x->setText(label_text);
  } else {
    QString text = ui->label_main->text();

    if (text.endsWith("asin(") || text.endsWith("atan(") ||
        text.endsWith("acos(") || text.endsWith("sqrt(")) {
      text.chop(5);
    } else if (text.endsWith("sin(") || text.endsWith("cos(") ||
               text.endsWith("tan(") || text.endsWith("log(")) {
      text.chop(4);
    } else if (text.endsWith("ln(")) {
      text.chop(3);
    } else if (text.endsWith("^(") || text.endsWith("%(")) {
      text.chop(2);
    } else {
      text.chop(1);
    }

    ui->label_main->setText(text);
  }
}

////////ОБРАБОТКА X///////////////////////////////////////////////////////////////////
void MainWindow::digits_x() {

  if (!ui->radioButton_x->isChecked() && check_length()) {
    QPushButton *button = (QPushButton *)sender();
    QString label_text = ui->label_main->text();
    int label_length = label_text.length();

    if (label_length == 0) {
      ui->label_main->setText(label_text + button->text());
    } else {
      QChar prev_char = label_text[label_length - 1];
      if (!prev_char.isDigit() && prev_char != '.' && prev_char != ')' &&
          prev_char != 'x') {
        ui->label_main->setText(label_text + button->text());
      }
    }
  }
}

/////////РАВНО/////////////////////////////////////////////////////////////////////////
void MainWindow::equals() {

  QString label_text = ui->label_main->text();
  QString label_text_x = ui->label_x->text();

  if (label_text.contains("inf") || label_text.contains("nan")) {
    ui->label_main->setText("");
  } else if (error_check(label_text) == 1) {
    if (label_text.contains('x')) {
      label_text = convert_x(label_text, label_text_x);
    }

    label_text = calculate(label_text);
    ui->label_main->setText(label_text);
  }
}

////////////ГРАФИКИ/////////////////////////////////////////////////////////////////////
void MainWindow::on_action_triggered() {
  if (error_check(ui->label_main->text())) {
    graphic->show();
    emit signal(ui->label_main->text());
  }
}

//////////КРЕДИТ////////////////////////////////////////////////////////////////////////
void MainWindow::on_action_2_triggered() { credit->show(); }

//////ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ//////////////////////////////////////////////////////////
int MainWindow::error_check(QString str) {

  int open_brk = 0, close_brk = 0, error_flag = 1;
  int end_str = str.length() - 1;

  for (int i = 0; i < end_str; i++) {
    if ((str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '%' ||
         str[i] == '+' || str[i] == '-' || str[i] == '.' || str[i] == '(') &&
        (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '^' ||
         str[i + 1] == '%' || str[i + 1] == '.')) {
      error_flag = 0;
    }

    if ((str[i] == '(' && str[i + 1] == ')') ||
        (str[i] == ')' && str[i + 1] == '(')) {
      error_flag = 0;
    }
  }

  open_brk = str.count('(');
  close_brk = str.count(')');

  if (end_str >= 0) {
    if (str[end_str] == '*' || str[end_str] == '/' || str[end_str] == '^' ||
        str[end_str] == '%' || str[end_str] == '(' || str[end_str] == '+' ||
        str[end_str] == '-' || str[end_str] == '.') {
      error_flag = 0;
    }
  }

  if (open_brk != close_brk || str.length() == 0) {
    error_flag = 0;
  }

  if (str.contains('x') && ui->label_x->text().isEmpty()) {
    error_flag = 2;
  }

  return error_flag;
}

int MainWindow::check_length() {
  int result = 1;
  QString str = ui->label_main->text();

  if (str.length() >= 255) {
    result = 0;
  }

  return result;
}

int MainWindow::is_operator(QString str) {
  int result = 0;
  if (str.contains("+") || str.contains("-") || str.contains("*") ||
      str.contains("/") || str.contains("%") || str.contains("^")) {
    result = 1;
  }
  return result;
}

int MainWindow::is_arithmetic_operator(QString str) {
  int result = 0;
  if (str.contains("+") || str.contains("-") || str.contains("*") ||
      str.contains("/")) {
    result = 1;
  }
  return result;
}
