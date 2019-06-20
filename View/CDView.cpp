#include "CDView.hpp"

CDController * CDView::getController()
{
  return dynamic_cast<CDController *>(View::getController());
}

CDView::CDView(QWidget *parent) : View(parent), fl(new QFormLayout(this))
{
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

  auto b = new QPushButton(QStringLiteral("Applica Mod."));
  fl->addWidget(b);
  connect(b, SIGNAL(clicked()), this, SLOT(_clickModifica()));
}

CDView::~CDView()
{
  delete id;
  delete nome;
  delete spi;
  delete prezzo;
  delete anno;
  delete artista;
  delete compilation;
  delete prezzo;
  delete sconto;
  delete fl;
}

CDController * CDView::makeController(Model *m)
{
  return new CDController(m, this, parent());
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
}
