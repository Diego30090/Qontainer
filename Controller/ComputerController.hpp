#ifndef COMPUTERCONTROLLER_HPP
#define COMPUTERCONTROLLER_HPP

#include <QMessageBox>
#include "Controller.hpp"

class ComputerController : public Controller
{
  Q_OBJECT

private:
  QString id;

public:
  ComputerController(Model *m, View *view);

  const DeepPtr<Computer> getArticolo(QString);

  void setID(QString);

signals:
  void viewUpdateFields(QString);

public slots:
  virtual void modelUpdate() override;

  void viewApplicaModifica(QString, QString, QString, QString, bool, bool);
  void viewEliminaArticolo();
};

#endif // COMPUTERCONTROLLER_HPP
