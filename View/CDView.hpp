#ifndef CDVIEW_HPP
#define CDVIEW_HPP

#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include "View.hpp"
#include "CDController.hpp"

class CDView : public View
{
  Q_OBJECT

private:
  QFormLayout *fl;
  QLineEdit *id;
  QLineEdit *nome;
  QLineEdit *spi;
  QLineEdit *costo;
  QLineEdit *anno;
  QLineEdit *artista;
  QCheckBox *compilation;
  QLabel *prezzo;
  QLabel *sconto;
  QPushButton *modifica;
  QPushButton *elimina;

  virtual CDController * makeController(Model *m) override;

public:
  explicit CDView(QWidget *parent);

  virtual CDController * getController() override;

signals:
  void applicaModifica(QString, QString, QString, QString, QString, QString, bool);
  void eliminaArticolo();

private slots:
  void _clickModifica();

public slots:
  void updateFields(QString);
};

#endif // CDVIEW_HPP
