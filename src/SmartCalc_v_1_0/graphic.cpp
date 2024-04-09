#include "graphic.h"
#include "ui_graphic.h"

Graphic::Graphic(QWidget *parent) : QWidget(parent), ui(new Ui::Graphic) {
  ui->setupUi(this);
  ui->lineEdit->setValidator(new QIntValidator(-1000000, 1000000, this));
  ui->lineEdit_2->setValidator(new QIntValidator(-1000000, 1000000, this));

  ui->widget->xAxis->setRange(-10, 10);
  ui->widget->yAxis->setRange(-10, 10);
}

Graphic::~Graphic() { delete ui; }

void Graphic::slot(QString a) { ui->label->setText(a); }

void Graphic::on_pushButton_clicked() {
  ui->widget->clearGraphs();
  QString xbegin = ui->lineEdit->text();
  QString xend = ui->lineEdit_2->text();

  double xBegin = (xbegin).toDouble();
  double xEnd = (xend).toDouble();
  double result = 0;

  QVector<double> x, y;

  if (!xbegin.isEmpty() && !xend.isEmpty() && xBegin <= xEnd) {
    QString str = ui->label->text();
    QString str_x = "\0", str_copy = str;

    for (double i = xBegin; i <= xEnd; i += 0.01) {
      x.push_back(i);
      str_x = QString::number(i, 'f', 3);
      str = convert_x(str_copy, str_x);

      if (str.contains("nan")) {
        break;
      }
      str = calculate(str);

      result = str.toDouble();
      y.push_back(result);
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(-10, 10);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeDrag, true);
    ui->widget->setInteraction(QCP::iRangeZoom, true);
  }
}
