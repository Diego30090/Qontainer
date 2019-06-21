#include "MainController.hpp"

MainController::MainController(Model *m, View *view)
  : Controller(m, view)
{
  connect(m, SIGNAL(err(QString)), this, SLOT(modelError(QString)));

  connect(this, SIGNAL(viewTableUpdate(QList<QString>)), linkedView, SLOT(updateTable(QList<QString>)));

  connect(linkedView, SIGNAL(toolBarTriggered(QAction *)), this, SLOT(viewToolBarTriggered(QAction *)));
  connect(linkedView, SIGNAL(tableTriggered(QString)), this, SLOT(viewTableTriggered(QString)));
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
  QString fileName = QStringLiteral("");

  switch (a->data().toInt())
    {
    case 0:
      if (!linkedModel->getBoxPath().isEmpty())
        {
          linkedModel->saveBox();
          break;
        }
      [[clang::fallthrough]];

    case 1:
      fileName = QFileDialog::getSaveFileName(linkedView, QStringLiteral("Salva"), linkedModel->getBoxPath(), QStringLiteral("YAML Files (*.yaml *.yml)"));

      if (!fileName.isEmpty())
        {
          linkedModel->changeBoxPath(fileName);
          linkedModel->saveBox();
        }
      break;

    case 2:
      fileName = QFileDialog::getOpenFileName(linkedView, QStringLiteral("Apri"), QStringLiteral(""), QStringLiteral("YAML Files (*.yaml *.yml)"));

      if (!fileName.isEmpty())
        {
          linkedModel->closeBox();
          linkedModel->changeBoxPath(fileName);
          linkedModel->openBox();
        }
      break;

    case 3:
      break;

    case 4:
      break;
    }
}

void MainController::viewTableTriggered(QString id)
{
  auto a = linkedModel->getArticolo(id);

  if (auto m = dynamic_cast<const Media *>(&a))
    {
      if (auto cd = dynamic_cast<const CD *>(&a))
        {
          auto v = new CDView(linkedView);
          View::initialize(v, linkedModel);
          v->getController()->setID(id);
          v->show();
        }
    }
  else if (auto e = dynamic_cast<const Elettronica *>(&a))
    {

    }
}
