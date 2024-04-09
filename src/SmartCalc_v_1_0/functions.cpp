#include "functions.h"

/////////ОБРАБОТКА РЕЗУЛЬТАТА//////////////////////////////////////////
QString calculate(QString str) {

  std::string std_infix = str.toStdString();
  char char_infix[255] = "\0";
  char char_postfix[255] = "\0";
  double result = 0;

  strlcpy(char_infix, std_infix.c_str(), str.length() + 1);
  s21Parcer(char_infix, char_postfix);

  QString check_nan = QString::fromUtf8(char_postfix);

  if (check_nan.contains("nan")) {
    str = "nan";
  } else {
    result = s21Calculate(char_postfix);
    str = QString::number(result, 'f', 7);
  }
  return str;
}

///////ВСТАВКА X//////////////////////////////////////////////////////
QString convert_x(QString str, QString x) {
  QString result = str;
  result.replace('x', x);

  return result;
}
