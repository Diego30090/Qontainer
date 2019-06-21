#ifndef COMPUTERVIEW_HPP
#define COMPUTERVIEW_HPP

#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include "View.hpp"
#include "ComputerController.hpp"

class ComputerView : public View
{
  Q_OBJECT

private:
  QFormLayout *fl;
  QLineEdit *id;
  QLineEdit *nome;
  QLineEdit *spi;
  QLineEdit *costo;
  QCheckBox *usato;
  QCheckBox *portatile;
  QLabel *prezzo;
  QLabel *sconto;
  QLabel *garanzia;
  QPushButton *modifica;
  QPushButton *elimina;

  virtual ComputerController * makeController(Model *m) override;

public:
  explicit ComputerView(QWidget *parent);

  virtual ComputerController * getController() override;

signals:
  void applicaModifica(QString, QString, QString, QString, bool, bool);
  void eliminaArticolo();

private slots:
  void _clickModifica();

public slots:
  void updateFields(QString);
};

#endif // COMPUTERVIEW_HPP
