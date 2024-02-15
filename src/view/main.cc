#include <QApplication>

#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Facade facade;
  s21::Controller controller(&facade);
  s21::View view(&controller);
  view.show();

  return a.exec();
}
