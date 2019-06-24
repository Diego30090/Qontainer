#include "ComputerController.hpp"

ComputerController::ComputerController(Model *m, View *view)
  : Controller(m, view), id(QString())
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
      catch (ModelEmptyBoxException &)
      {
        linkedView->close();
        return;
      }
      catch (ModelArticleNotFoundException &)
      {
        linkedView->close();
        return;
      }

      emit viewUpdateFields(id);
    }
}

void ComputerController::viewApplicaModifica(QString ID, QString NOME, QString _SPI, QString _COSTO,
                                             bool USATO, bool PORTATILE)
{
  if (ID.isEmpty())
    {
      QMessageBox::critical(linkedView, QStringLiteral("Errore Inserimento Dati"), QStringLiteral("ID non inserito!"));
      return;
    }

  bool ok_costo;
  bool ok_spi;

  float COSTO = _COSTO.toFloat(&ok_costo);
  unsigned int SPI = _SPI.toUInt(&ok_spi);

  if (!(ok_costo && ok_spi))
    {
      QMessageBox::critical(linkedView, QStringLiteral("Errore Inserimento Dati"), QStringLiteral("I dati inseriti non sono corretti:\ncontrollare i valori numerici"));
      return;
    }

  id = ID;

  try
  {
    linkedModel->getArticolo(ID);
  }
  catch (ModelEmptyBoxException &)
  {
    linkedModel->insert(ID, Computer(PORTATILE, USATO, NOME.toStdString(), COSTO, SPI));
    return;
  }
  catch (ModelArticleNotFoundException &)
  {
    linkedModel->insert(ID, Computer(PORTATILE, USATO, NOME.toStdString(), COSTO, SPI));
    return;
  }

  linkedModel->setArticolo(ID, NOME, COSTO, SPI);
  linkedModel->setElettronica(ID, USATO);
  linkedModel->setComputer(ID, PORTATILE);
}

void ComputerController::viewEliminaArticolo()
{
  linkedModel->remove(id);
}
