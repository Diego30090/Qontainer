#include "MainView.hpp"

MainController * MainView::makeController(Model *m)
{
  return new MainController(m, this);
}

MainView::MainView(QWidget *parent) : View(parent), hl(new QHBoxLayout(this))
{
  resize(500, 500);

  // Layout orizzontale
  hl->setContentsMargins(0, 0, 0, 0);

  // Barra degli strumenti
  QToolBar *upperToolBar = new QToolBar(QStringLiteral("BarraDegliStrumenti"), this);
  QAction *tmp;

  upperToolBar->setMovable(false);

  tmp = upperToolBar->addAction(QStringLiteral("Salva"));
  tmp->setData(0);

  tmp = upperToolBar->addAction(QStringLiteral("Salva con Nome"));
  tmp->setData(1);

  tmp = upperToolBar->addAction(QStringLiteral("Apri"));
  tmp->setData(2);

  upperToolBar->addSeparator();

  tmp = upperToolBar->addAction(QStringLiteral("Ricerca"));
  tmp->setData(3);

  tmp = upperToolBar->addAction(QStringLiteral("Nuovo Articolo"));
  tmp->setData(4);

  connect(upperToolBar, SIGNAL(actionTriggered(QAction *)), this, SIGNAL(toolBarTriggered(QAction *)));

  hl->setMenuBar(upperToolBar);

  // Tabella
  tab = new QTableWidget(0, 4, this);

  QStringList labels;
  labels << QStringLiteral("ID") << QStringLiteral("Nome") << QStringLiteral("SPI") << QStringLiteral("Prezzo");
  tab->setHorizontalHeaderLabels(labels);
  tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  tab->verticalHeader()->setVisible(false);
  tab->setEditTriggers(QAbstractItemView::NoEditTriggers);
  tab->setSelectionBehavior(QAbstractItemView::SelectItems);
  tab->setSelectionMode(QAbstractItemView::SingleSelection);

  connect(tab, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(_tableTriggered(int)));

  hl->addWidget(tab);
}

MainController * MainView::getController()
{
  return dynamic_cast<MainController *>(View::getController());
}

void MainView::_tableTriggered(int row/*, int col*/)
{
  emit tableTriggered(tab->item(row, 0)->text());
}

void MainView::updateTable(QList<QString> l)
{
  tab->clearContents();
  tab->setRowCount(0);

  for (auto it = l.begin(); it != l.end(); ++it)
    {
      const DeepPtr<Articolo> a = getController()->getArticolo(*it);

      tab->setRowCount(tab->rowCount() + 1);

      tab->setItem(tab->rowCount() - 1, 0, new QTableWidgetItem(*it, 0));
      tab->setItem(tab->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(a->getNome()), 0));
      tab->setItem(tab->rowCount() - 1, 2, new QTableWidgetItem(QString::number(a->getSPI()), 0));
      tab->setItem(tab->rowCount() - 1, 3, new QTableWidgetItem(QString::number(static_cast<double>(a->getPrezzo()), 'f', 2), 0));
    }
}
