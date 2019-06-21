#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include "Controller.hpp"
#include "CDView.hpp"
#include "CDController.hpp"

class MainController : public Controller
{
  Q_OBJECT

public:
  explicit MainController(Model *m, View *view);

  const DeepPtr<Articolo> getArticolo(QString);

signals:
  void viewTableUpdate(QList<QString>);

public slots:
  virtual void modelUpdate() override;

  void modelError(QString);

  void viewToolBarTriggered(QAction *);
  void viewTableTriggered(QString);
};

#endif // MAINCONTROLLER_HPP
