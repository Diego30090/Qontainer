#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include "Controller.hpp"

class MainController : public Controller
{
  Q_OBJECT

public:
  explicit MainController(Model *m, View *view, QObject *parent = nullptr);
  virtual ~MainController() override;

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
