#include <QApplication>
#include "MainView.hpp"
#include "Model.hpp"
#include <QDebug>

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
  //m->saveBox();

  auto l = m->filterByPrice(m->getAllArticolo(), Model::minoreUguale, 1000);

  for (int i = 0; i < l.size(); ++i)
    qDebug() << l[i] << endl;

  qDebug() << dynamic_cast<Smartphone &>(*m->getArticolo("abc")).isUsato() << endl;

  m->setElettBrunoUsato("abc", true);

  qDebug() << dynamic_cast<Smartphone &>(*m->getArticolo("abc")).isUsato() << endl;

  return a.exec();
}
