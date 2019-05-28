#include "MainView.hpp"

MainController * MainView::makeController()
{
  return new MainController(this, parent());
}

MainView::MainView(QWidget *parent) : View(parent), hl(new QHBoxLayout(this))
{
  this->resize(800, 500);

  // Layout orizzontale
  hl->setContentsMargins(0, 0, 0, 0);

  // Barra degli strumenti
  QToolBar *upperToolBar = new QToolBar(QStringLiteral("BarraDegliStrumenti"), this);
  upperToolBar->setMovable(false);
  upperToolBar->addAction(QStringLiteral("Salva"));
  upperToolBar->addAction(QStringLiteral("Salva con Nome"));
  upperToolBar->addSeparator();
  upperToolBar->addAction(QStringLiteral("Apri Box"));
  upperToolBar->addAction(QStringLiteral("Chiudi Box"));
  upperToolBar->addAction(QStringLiteral("Nuovo Box"));
  upperToolBar->addSeparator();
  upperToolBar->addAction(QStringLiteral("Ricerca"));
  upperToolBar->addAction(QStringLiteral("Nuovo Articolo"));
  upperToolBar->addAction(QStringLiteral("Elimina Articolo"));
  connect(upperToolBar, SIGNAL(actionTriggered(QAction *)), this, SIGNAL(toolBarActionTriggered(QAction *)));
  hl->setMenuBar(upperToolBar); // La metto come barra dei menù

  // Tabella
  QTableWidget *tab = new QTableWidget(this);
  hl->addWidget(tab);
}

void MainView::initialize()
{
  setController(makeController());

  ///////////////////////////////////////////// Vari connect
}



//void MainView::toolbarAction(QAction *a)
//{
//  auto opt = a->text();

//  if (opt == "Salva")
//    emit salva();
//  else if (opt == "Salva con Nome")
//    emit salvaConNome();
//  else if (opt == "Apri Box")
//    emit apriBox();
//  else if (opt == "Chiudi Box")
//    emit chiudiBox();
//  else if (opt == "Nuovo Box")
//    emit nuovoBox();
//  else if (opt == "Ricerca")
//    emit ricercaArticolo();
//  else if (opt == "Nuovo Articolo")
//    emit nuovoArticolo();
//  else if (opt == "Elimina Articolo")
//    emit eliminaArticolo();
//}
