#include "MainView.hpp"

MainView::MainView(QWidget *parent) : QWidget(parent)
{
  this->resize(800, 500);

  // Layout orizzontale
  auto h = new QHBoxLayout(this);

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
  connect(upperToolBar, SIGNAL(actionTriggered(QAction *)), this, SLOT(toolbarAction(QAction *))); // Collego le azioni della toolbar ad uno slot che emetterà il giusto segnale
  h->setMenuBar(upperToolBar); // La metto come barra dei menù

  // Tabella
  QTableWidget *tab = new QTableWidget(this);
  h->addWidget(tab);

  //h->addWidget();

}

void MainView::toolbarAction(QAction *a)
{
  auto opt = a->text();

  if (opt == "Salva")
    emit controllerSalva();
  else if (opt == "Salva con Nome")
    emit controllerSalvaConNome();
  else if (opt == "Apri Box")
    emit controllerApriBox();
  else if (opt == "Chiudi Box")
    emit controllerChiudiBox();
  else if (opt == "Nuovo Box")
    emit controllerNuovoBox();
  else if (opt == "Ricerca")
    emit controllerRicercaArticolo();
  else if (opt == "Nuovo Articolo")
    emit controllerNuovoArticolo();
  else if (opt == "Elimina Articolo")
    emit controllerEliminaArticolo();
}
