#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "functions.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QValidator>
#include <QVector>
#include <credit.h>
#include <graphic.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  Graphic *graphic;
  Credit *credit;

signals:
  void signal(QString);

private slots:
  void digits_numbers();
  void digits_point();
  void operators();
  void full_clear();
  void clear();
  void functions();
  void other_operators();
  void brackets();
  void digits_x();
  void equals();

  int check_length();
  int is_operator(QString str);
  int is_arithmetic_operator(QString str);
  int error_check(QString label_text);

  void on_action_triggered();
  void on_action_2_triggered();
};

#endif // MAINWINDOW_H
