#include "MainController.hpp"

MainController::MainController(Model *m, View *view, QObject *parent)
  : Controller(m, view, parent)
{
  connect(this, SIGNAL(viewTableUpdate(QList<QString>)), linkedView, SLOT(updateTable(QList<QString>)));

  connect(m, SIGNAL(err(QString)), this, SLOT(modelError(QString)));

  connect(linkedView, SIGNAL(toolBarTriggered(QAction *)), this, SLOT(viewToolBarTriggered(QAction *)));
  connect(linkedView, SIGNAL(tableTriggered(QString)), this, SLOT(viewTableTriggered(QString)));
}

MainController::~MainController()
{
  delete linkedModel;
}

const DeepPtr<Articolo> MainController::getArticolo(QString id)
{
  return linkedModel->getArticolo(id);
}

void MainController::modelUpdate()
{
  if (linkedModel->isOpen())
    {
      if (linkedModel->isEmpty())
        emit viewTableUpdate(QStringList());
      else
        emit viewTableUpdate(linkedModel->getAllArticolo());
    }
}

void MainController::modelError(QString msg)
{
  QMessageBox::critical(linkedView, QStringLiteral("Errore Modello"), msg);
}

void MainController::viewToolBarTriggered(QAction *a)
{
  switch (a->data().toInt())
    {
    case 2:
      QString fileName = QStringLiteral("");
      fileName = QFileDialog::getOpenFileName(linkedView, QStringLiteral("Apri")/*, QStringLiteral("YAML Files (*.yaml, *.yml)")*/);

      if (!fileName.isEmpty())
        {
          linkedModel->closeBox();
          linkedModel->changeBoxPath(fileName);
          linkedModel->openBox();
        }
      break;
    }
}

void MainController::viewTableTriggered(QString id)
{

}
