#include "CDView.hpp"

CDController * CDView::makeController(Model *m)
{
  return new CDController(m, this);
}

CDView::CDView(QWidget *parent) : View(parent), fl(new QFormLayout(this))
{
  setFixedSize(250, 350);

  id = new QLineEdit(this);
  fl->addRow(QStringLiteral("ID"), id);

  nome = new QLineEdit(this);
  fl->addRow(QStringLiteral("Nome"), nome);

  spi = new QLineEdit(this);
  fl->addRow(QStringLiteral("SPI"), spi);

  costo = new QLineEdit(this);
  fl->addRow(QStringLiteral("Costo"), costo);

  anno = new QLineEdit(this);
  fl->addRow(QStringLiteral("Anno"), anno);

  artista = new QLineEdit(this);
  fl->addRow(QStringLiteral("Artista"), artista);

  compilation = new QCheckBox(this);
  fl->addRow(QStringLiteral("Compilation"), compilation);

  prezzo = new QLabel(this);
  fl->addRow(QStringLiteral("Prezzo"), prezzo);

  sconto = new QLabel(this);
  fl->addRow(QStringLiteral("Sconto"), sconto);

  modifica = new QPushButton(QStringLiteral("Inserisci"));
  fl->addWidget(modifica);
  connect(modifica, SIGNAL(clicked()), this, SLOT(_clickModifica()));

  elimina = new QPushButton(QStringLiteral("Elimina"));
  fl->addWidget(elimina);
  connect(elimina, SIGNAL(clicked()), this, SIGNAL(eliminaArticolo()));
  elimina->setVisible(false);
}

CDController * CDView::getController()
{
  return dynamic_cast<CDController *>(View::getController());
}

void CDView::_clickModifica()
{
  emit applicaModifica(id->text(), nome->text(), spi->text(), costo->text(),
                       anno->text(), artista->text(), compilation->isChecked());
}

void CDView::updateFields(QString ID)
{
  const DeepPtr<CD> cd = getController()->getArticolo(ID);

  id->setText(ID);
  nome->setText(QString::fromStdString(cd->getNome()));
  spi->setText(QString::number(cd->getSPI()));
  costo->setText(QString::number(static_cast<double>(cd->getCosto())));
  anno->setText(QString::number(cd->getAnno()));
  artista->setText(QString::fromStdString(cd->getArtista()));
  compilation->setChecked(cd->isCompilation());
  prezzo->setText(QString::number(static_cast<double>(cd->getPrezzo())));
  sconto->setText(QString::number(cd->getSconto()) + QStringLiteral("%"));

  modifica->setText(QStringLiteral("Applica Mod."));
  elimina->setVisible(true);
}
