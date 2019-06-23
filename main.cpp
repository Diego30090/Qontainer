#include <QApplication>
#include "MainView.hpp"
#include "Model.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Model m(&a);
  m.newBox();

  MainView w;
  View::initialize(&w, &m);
  w.show();

  return a.exec();
}
