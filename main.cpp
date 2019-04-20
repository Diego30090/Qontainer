#include <QApplication>
#include "MainView.hpp"
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainView w;
  w.show();

  QObject::connect(&w, SIGNAL(controllerSalva()))

  return a.exec();
}
