#include "ComputerController.hpp"

ComputerController::ComputerController(Model *m, View *view)
  : Controller(m, view), id(QStringLiteral(""))
{
  connect(this, SIGNAL(viewUpdateFields(QString)), linkedView, SLOT(updateFields(QString)));

  connect(linkedModel, SIGNAL(notify()), this, SLOT(modelUpdate()));

  connect(linkedView, SIGNAL(applicaModifica(QString, QString, QString, QString, bool, bool)),
          this, SLOT(viewApplicaModifica(QString, QString, QString, QString, bool, bool)));

  connect(linkedView, SIGNAL(eliminaArticolo()), this, SLOT(viewEliminaArticolo()));
}

const DeepPtr<Computer> ComputerController::getArticolo(QString ID)
{
  return dynamic_cast<const Computer *>(&linkedModel->getArticolo(ID));
}

void ComputerController::setID(QString ID)
{
  id = ID;
  emit viewUpdateFields(id);
}

void ComputerController::modelUpdate()
{
  if (!id.isEmpty())
    {
      try
      {
        linkedModel->getArticolo(id);
      }
      catch (ModelEmptyBoxException)
      {
        linkedView->close();
        return;
      }
      catch (ModelArticleNotFoundException)
      {
        linkedView->close();
        return;
      }

      emit viewUpdateFields(id);
    }
}

void ComputerController::viewApplicaModifica(QString ID, QString NOME, QString SPI, QString COSTO,
                                             bool USATO, bool PORTATILE)
{
  id = ID;

  try
  {
    linkedModel->getArticolo(ID);
  }
  catch (ModelEmptyBoxException)
  {
    linkedModel->insert(ID, Computer(PORTATILE, USATO, NOME.toStdString(), COSTO.toFloat(), SPI.toUInt()));
    return;
  }
  catch (ModelArticleNotFoundException)
  {
    linkedModel->insert(ID, Computer(PORTATILE, USATO, NOME.toStdString(), COSTO.toFloat(), SPI.toUInt()));
    return;
  }

  linkedModel->setArticolo(ID, NOME, COSTO.toFloat(), SPI.toUInt());
  linkedModel->setElettronica(ID, USATO);
  linkedModel->setComputer(ID, PORTATILE);
}

void ComputerController::viewEliminaArticolo()
{
  linkedModel->remove(id);
}