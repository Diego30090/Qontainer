#include <QApplication>
#include "Controller.hpp"
#include "MainView.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainView w;
  w.show();

  return a.exec();
}
