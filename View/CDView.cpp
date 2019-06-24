#include "CDView.hpp"

CDController * CDView::makeController(Model *m)
{
  return new CDController(m, this);
}

CDView::CDView(QWidget *parent) : View(parent), fl(new QFormLayout(this))
{
  setAttribute(Qt::WA_DeleteOnClose);
  setFixedSize(250, 350);

  id = new QLineEdit();
  fl->addRow(QStringLiteral("ID"), id);

  nome = new QLineEdit();
  fl->addRow(QStringLiteral("Nome"), nome);

  spi = new QLineEdit();
  fl->addRow(QStringLiteral("SPI"), spi);
  spi->setText(QString::number(0));

  costo = new QLineEdit();
  fl->addRow(QStringLiteral("Costo"), costo);

  anno = new QLineEdit();
  fl->addRow(QStringLiteral("Anno"), anno);

  artista = new QLineEdit();
  fl->addRow(QStringLiteral("Artista"), artista);

  compilation = new QCheckBox();
  fl->addRow(QStringLiteral("Compilation"), compilation);

  prezzo = new QLabel();
  fl->addRow(QStringLiteral("Prezzo"), prezzo);

  sconto = new QLabel();
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
