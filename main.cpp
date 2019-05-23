#include <QApplication>
//#include "MainView.hpp"
#include <QDebug>
#include "Model.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
//  MainView w;
//  w.show();

  auto m = new Model(&a);
  m->newBox();

//  m->insert("skd", CD("Skid Row", false, 1987, "Skid Row", 10));

//  auto l1 = m->getAllArticolo();
//  qDebug() << l1;

  m->insert("ipx", Smartphone(true, false, "iPhone X", 1000));

  auto l2 = m->getAllArticolo();
  qDebug() << l2;

//  m->remove("ipx");

//  auto l3 = m->getAllArticolo();
//  qDebug() << l3;

  //auto prova = m->getArticolo("skd"); //Funziona

  delete m;

//const Articolo * p = dynamic_cast<const CD *>(&m->getArticolo("skd")); //NON FUNZIONA

//  qDebug() << QString().fromStdString(prova->getNome()) << prova->getCosto() << prova->getPrezzo() << prova->getSconto();

//  m->setArticolo("ipxax", "Ciao Bello", 500, 0);
//  m->setArticolo("ipx", "Ciao Bello", 500, 0);

//  auto p = m->getArticolo("ipx");

//  qDebug() << "Prova del getPrezzo: " << p->getPrezzo();

//  m->setMedia("skd", 1989);
//  m->setCD("skd", "Skid Row", true);

//  const DeepPtr<CD> cd = dynamic_cast<const CD *>(&m->getArticolo("skd"));

//  qDebug() << QString().fromStdString(cd->getNome()) << cd->getCosto() << cd->getPrezzo() << cd->getSconto()
//           << cd->isCompilation() << cd->getAnno();

//  return a.exec();
}
