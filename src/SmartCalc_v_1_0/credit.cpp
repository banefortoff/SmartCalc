#include "credit.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);

  ui->lineEdit_amount_credit->setValidator(
      new QIntValidator(0, 1000000000, this));
  ui->lineEdit_interest_rate->setValidator(new QDoubleValidator(0, 100, 2));
  ui->lineEdit_credit_term->setValidator(new QIntValidator(0, 1000, this));
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_result_clicked() {
  if ((ui->radioButton_a->isChecked() || ui->radioButton_d->isChecked())

      && (ui->radioButton_months->isChecked() ||
          ui->radioButton_years->isChecked())

      && (!ui->lineEdit_amount_credit->text().isEmpty() &&
          !ui->lineEdit_credit_term->text().isEmpty() &&
          !ui->lineEdit_interest_rate->text().isEmpty())) {

    double amount_credit = ui->lineEdit_amount_credit->text().toDouble();

    QString label_text = ui->lineEdit_interest_rate->text();
    double rate;

    if (label_text.contains(",")) {
      QString result = label_text;
      result.replace(',', '.');
      rate = result.toDouble();
    } else {
      rate = ui->lineEdit_interest_rate->text().toDouble();
    }

    double term = ui->lineEdit_credit_term->text().toDouble();

    if (ui->radioButton_years->isChecked()) {
      term *= 12;
    }

    ui->tableWidget->setRowCount(term);
    ui->tableWidget->setColumnCount(1);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Выплата");

    double sum = 0;
    double overpayment = 0;
    QTableWidgetItem *tbl;

    if (ui->radioButton_a->isChecked()) {
      double coef_anuitet = 0;
      double month_payment = 0;
      rate = rate / 12 / 100;
      coef_anuitet = ((rate * pow(1 + rate, term)) / (pow(1 + rate, term) - 1));
      month_payment = coef_anuitet * amount_credit;
      sum = month_payment * term;

      for (int i = 0; i < term; i++) {
        tbl = new QTableWidgetItem(QString::number(month_payment, 'f', 2));
        ui->tableWidget->setItem(i, 0, tbl);
      }
    } else if (ui->radioButton_d->isChecked()) {
      QDate data = QDate::currentDate();

      double standart_payment = amount_credit / term;
      double month_pay = 0;
      double Q = amount_credit;
      for (int i = 0; i < term; i++, data = data.addMonths(1)) {
        month_pay = standart_payment +
                    (Q * (rate / 100) * data.daysInMonth() / data.daysInYear());
        sum += month_pay;
        Q -= standart_payment;
        tbl = new QTableWidgetItem(QString::number(month_pay, 'f', 2));
        ui->tableWidget->setItem(i, 1, tbl);
      }
    }

    overpayment = sum - amount_credit;
    ui->label_total_payment->setText(QString::number(sum, 'f', 2));
    ui->label_overpayment->setText(QString::number(overpayment, 'f', 2));
  }
}
