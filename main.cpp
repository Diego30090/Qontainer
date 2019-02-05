#include <QApplication>
#include "MainView.hpp"
#include "Model.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  //MainView w;
  //w.show();

  auto m = new Model(&a);

  m->newBox();
  m->changeBoxPath("//Users//alechimetto//Desktop//a.xml");

  m->insert(new Computer(false, false, "amp", "Apple MacBook Pro", 1000));
  m->insert(new Computer(false, false, "hp6", "HP Pavillion dv6", 500));
  m->insert(new Album("Skid Row", false, "skr", "Skid Row", 10.5f));
  m->insert(new Smartphone(false, false, "abc", "Apple iPhone X", 1200));
  m->saveBox();

//  m->changeBoxPath("//Users//alechimetto//Desktop//a.xml");

//  m->openBox();

//  m->changeBoxPath("//Users//alechimetto//Desktop//b.xml");
//  m->saveBox();

  return a.exec();
}
