#ifndef SMARTPHONEVIEW_HPP
#define SMARTPHONEVIEW_HPP

#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include "View.hpp"
#include "SmartphoneController.hpp"

class SmartphoneView : public View
{
  Q_OBJECT

private:
  QFormLayout *fl;
  QLineEdit *id;
  QLineEdit *nome;
  QLineEdit *spi;
  QLineEdit *costo;
  QCheckBox *usato;
  QCheckBox *iphone;
  QLabel *prezzo;
  QLabel *sconto;
  QLabel *garanzia;
  QPushButton *modifica;
  QPushButton *elimina;

  virtual SmartphoneController * makeController(Model *m) override;

public:
  explicit SmartphoneView(QWidget *parent);

  virtual SmartphoneController * getController() override;

signals:
  void applicaModifica(QString, QString, QString, QString, bool, bool);
  void eliminaArticolo();

private slots:
  void _clickModifica();

public slots:
  void updateFields(QString);
};

#endif // SMARTPHONEVIEW_HPP
