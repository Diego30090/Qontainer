#include "SmartphoneView.hpp"

SmartphoneController * SmartphoneView::makeController(Model *m)
{
  return new SmartphoneController(m, this);
}

SmartphoneView::SmartphoneView(QWidget *parent) : View(parent), fl(new QFormLayout(this))
{
  setFixedSize(250, 350);

  id = new QLineEdit(this);
  fl->addRow(QStringLiteral("ID"), id);

  nome = new QLineEdit(this);
  fl->addRow(QStringLiteral("Nome"), nome);

  spi = new QLineEdit(this);
  fl->addRow(QStringLiteral("SPI"), spi);
  spi->setText(QString::number(0));

  costo = new QLineEdit(this);
  fl->addRow(QStringLiteral("Costo"), costo);

  usato = new QCheckBox(this);
  fl->addRow(QStringLiteral("Usato"), usato);

  iphone = new QCheckBox(this);
  fl->addRow(QStringLiteral("iPhone"), iphone);

  prezzo = new QLabel(this);
  fl->addRow(QStringLiteral("Prezzo"), prezzo);

  sconto = new QLabel(this);
  fl->addRow(QStringLiteral("Sconto"), sconto);

  garanzia = new QLabel(this);
  fl->addRow(QStringLiteral("Anni Garanzia"), garanzia);

  modifica = new QPushButton(QStringLiteral("Inserisci"));
  fl->addWidget(modifica);
  connect(modifica, SIGNAL(clicked()), this, SLOT(_clickModifica()));

  elimina = new QPushButton(QStringLiteral("Elimina"));
  fl->addWidget(elimina);
  connect(elimina, SIGNAL(clicked()), this, SIGNAL(eliminaArticolo()));
  elimina->setVisible(false);
}

SmartphoneController * SmartphoneView::getController()
{
  return dynamic_cast<SmartphoneController *>(View::getController());
}

void SmartphoneView::_clickModifica()
{
  emit applicaModifica(id->text(), nome->text(), spi->text(), costo->text(),
                       usato->isChecked(), iphone->isChecked());
}

void SmartphoneView::updateFields(QString ID)
{
  const DeepPtr<Smartphone> s = getController()->getArticolo(ID);

  id->setText(ID);
  nome->setText(QString::fromStdString(s->getNome()));
  spi->setText(QString::number(s->getSPI()));
  costo->setText(QString::number(static_cast<double>(s->getCosto())));
  usato->setChecked(s->isUsato());
  iphone->setChecked(s->isiPhone());
  prezzo->setText(QString::number(static_cast<double>(s->getPrezzo())));
  sconto->setText(QString::number(s->getSconto()) + QStringLiteral("%"));
  garanzia->setText(QString::number(s->getWarranty()));

  modifica->setText(QStringLiteral("Applica Mod."));
  elimina->setVisible(true);
}
