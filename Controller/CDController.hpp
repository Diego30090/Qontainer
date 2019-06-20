#ifndef CDCONTROLLER_HPP
#define CDCONTROLLER_HPP

#include <QMessageBox>
#include "Controller.hpp"

class CDController : public Controller
{
  Q_OBJECT

private:
  QString id;

public:
  CDController(Model *m, View *view, QObject *parent = nullptr);
  virtual ~CDController() override = default;

  const DeepPtr<CD> getArticolo(QString);

  void setID(QString);

signals:
  void viewUpdateFields(QString);

public slots:
  virtual void modelUpdate() override;

  void viewApplicaModifica(QString, QString, QString, QString, QString, QString, bool);


};

#endif // CDCONTROLLER_HPP
