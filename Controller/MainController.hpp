#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include <QPointer>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include "Controller.hpp"
#include "CDView.hpp"
#include "ComputerView.hpp"
#include "SmartphoneView.hpp"
#include "SearchView.hpp"

class MainController : public Controller
{
  Q_OBJECT

private:
  QPointer<SearchView> rw;

public:
  explicit MainController(Model *m, View *view);

  const DeepPtr<Articolo> getArticolo(QString);

signals:
  void viewTableUpdate(QList<QString>);

public slots:
  void modelUpdate() override;

  void modelError(QString);

  void viewToolBarTriggered(QAction *);
  void viewTableTriggered(QString);

  void insertCD();
  void insertComputer();
  void insertSmartphone();
};

#endif // MAINCONTROLLER_HPP
