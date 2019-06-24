#include "ComputerView.hpp"

ComputerController * ComputerView::makeController(Model *m)
{
  return new ComputerController(m, this);
}

ComputerView::ComputerView(QWidget *parent) : View(parent), fl(new QFormLayout(this))
{
  setAttribute(Qt::WA_DeleteOnClose);
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

  portatile = new QCheckBox(this);
  fl->addRow(QStringLiteral("Portatile"), portatile);

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

ComputerController * ComputerView::getController()
{
  return dynamic_cast<ComputerController *>(View::getController());
}

void ComputerView::_clickModifica()
{
  emit applicaModifica(id->text(), nome->text(), spi->text(), costo->text(),
                       usato->isChecked(), portatile->isChecked());
}

void ComputerView::updateFields(QString ID)
{
  const DeepPtr<Computer> c = getController()->getArticolo(ID);

  id->setText(ID);
  nome->setText(QString::fromStdString(c->getNome()));
  spi->setText(QString::number(c->getSPI()));
  costo->setText(QString::number(static_cast<double>(c->getCosto())));
  usato->setChecked(c->isUsato());
  portatile->setChecked(c->isPortatile());
  prezzo->setText(QString::number(static_cast<double>(c->getPrezzo())));
  sconto->setText(QString::number(c->getSconto()) + QStringLiteral("%"));
  garanzia->setText(QString::number(c->getWarranty()));

  modifica->setText(QStringLiteral("Applica Mod."));
  elimina->setVisible(true);
}
