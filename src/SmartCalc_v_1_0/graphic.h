#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "functions.h"
#include <QWidget>

namespace Ui {
class Graphic;
}

class Graphic : public QWidget {
  Q_OBJECT

public:
  explicit Graphic(QWidget *parent = nullptr);
  ~Graphic();

private:
  Ui::Graphic *ui;

public slots:
  void slot(QString a);

private slots:
  void on_pushButton_clicked();
};

#endif // GRAPHIC_H
