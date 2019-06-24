#ifndef SMARTPHONECONTROLLER_HPP
#define SMARTPHONECONTROLLER_HPP

#include <QMessageBox>
#include "Controller.hpp"

class SmartphoneController : public Controller
{
  Q_OBJECT

private:
  QString id;

public:
  SmartphoneController(Model *m, View *view);

  const DeepPtr<Smartphone> getArticolo(QString);

  void setID(QString);

signals:
  void viewUpdateFields(QString);

public slots:
  void modelUpdate() override;

  void viewApplicaModifica(QString, QString, QString, QString, bool, bool);
  void viewEliminaArticolo();
};

#endif // SMARTPHONECONTROLLER_HPP
