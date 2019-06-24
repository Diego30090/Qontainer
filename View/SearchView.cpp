#include "SearchView.hpp"

SearchController * SearchView::makeController(Model *m)
{
  return new SearchController(m, this);
}

SearchView::SearchView(QWidget *parent) : View(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setFixedSize(310, 550);

  auto vl = new QVBoxLayout(this);

  checkA = new QGroupBox(QStringLiteral("Articoli"));
  checkA->setCheckable(true);
  checkA->setChecked(true);
  vl->addWidget(checkA);
  connect(checkA, SIGNAL(toggled(bool)), this, SLOT(_checkedA(bool)));

  auto flA = new QFormLayout();
  checkA->setLayout(flA);

  nome = new QLineEdit();
  flA->addRow(QStringLiteral("Nome"), nome);

  costoMax = new QLineEdit();
  flA->addRow(QStringLiteral("Costo massimo"), costoMax);

  prezzoMax = new QLineEdit();
  flA->addRow(QStringLiteral("Prezzo massimo"), prezzoMax);


  checkCD = new QGroupBox(QStringLiteral("CD"));
  checkCD->setCheckable(true);
  checkCD->setChecked(false);
  vl->addWidget(checkCD);
  connect(checkCD, SIGNAL(toggled(bool)), this, SLOT(_checkedCD(bool)));

  auto flCD = new QFormLayout();
  checkCD->setLayout(flCD);

  annoCD = new QLineEdit();
  flCD->addRow(QStringLiteral("Anno"), annoCD);

  artista = new QLineEdit();
  flCD->addRow(QStringLiteral("Artista"), artista);

  compilation = new QCheckBox();
  flCD->addRow(QStringLiteral("Compilation"), compilation);


  checkC = new QGroupBox(QStringLiteral("Computer"));
  checkC->setCheckable(true);
  checkC->setChecked(false);
  vl->addWidget(checkC);
  connect(checkC, SIGNAL(toggled(bool)), this, SLOT(_checkedC(bool)));


  auto flC = new QFormLayout();
  checkC->setLayout(flC);

  usatoC = new QCheckBox();
  flC->addRow(QStringLiteral("Usato"), usatoC);

  portatile = new QCheckBox();
  flC->addRow(QStringLiteral("Portatile"), portatile);


  checkS = new QGroupBox(QStringLiteral("Smartphone"));
  checkS->setCheckable(true);
  checkS->setChecked(false);
  vl->addWidget(checkS);
  connect(checkS, SIGNAL(toggled(bool)), this, SLOT(_checkedS(bool)));

  auto flS = new QFormLayout();
  checkS->setLayout(flS);

  usatoS = new QCheckBox();
  flS->addRow(QStringLiteral("Usato"), usatoS);

  iphone = new QCheckBox();
  flS->addRow(QStringLiteral("iPhone"), iphone);


  auto b = new QPushButton(QStringLiteral("Cerca"));
  vl->addWidget(b);
  connect(b, SIGNAL(clicked()), this, SLOT(_searchStart()));
}

SearchController * SearchView::getController()
{
  return dynamic_cast<SearchController *>(View::getController());
}

void SearchView::closeEvent(QCloseEvent *event)
{
  emit closing();
  event->accept();
}

void SearchView::_searchStart()
{
  emit searchStart(checkA->isChecked(), nome->text(), costoMax->text(), prezzoMax->text(),
                   checkCD->isChecked(), annoCD->text(), artista->text(), compilation->isChecked(),
                   checkC->isChecked(), usatoC->isChecked(), portatile->isChecked(),
                   checkS->isChecked(), usatoS->isChecked(), iphone->isChecked());
}

void SearchView::_checkedA(bool on)
{
  nome->setEnabled(on);
  costoMax->setEnabled(on);
  prezzoMax->setEnabled(on);

  if (on)
    {
      checkCD->setChecked(false);
      checkC->setChecked(false);
      checkS->setChecked(false);
    }
}

void SearchView::_checkedCD(bool on)
{
  annoCD->setEnabled(on);
  artista->setEnabled(on);
  compilation->setEnabled(on);

  if (on)
    {
      checkA->setChecked(false);
      checkC->setChecked(false);
      checkS->setChecked(false);
    }
}

void SearchView::_checkedC(bool on)
{
  usatoC->setEnabled(on);
  portatile->setEnabled(on);

  if (on)
    {
      checkCD->setChecked(false);
      checkA->setChecked(false);
      checkS->setChecked(false);
    }
}

void SearchView::_checkedS(bool on)
{
  usatoS->setEnabled(on);
  iphone->setEnabled(on);

  if (on)
    {
      checkCD->setChecked(false);
      checkC->setChecked(false);
      checkA->setChecked(false);
    }
}
