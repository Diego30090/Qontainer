#include "SmartphoneController.hpp"

SmartphoneController::SmartphoneController(Model *m, View *view)
  : Controller(m, view), id("")
{
  connect(this, SIGNAL(viewUpdateFields(QString)), linkedView, SLOT(updateFields(QString)));

  connect(linkedModel, SIGNAL(notify()), this, SLOT(modelUpdate()));

  connect(linkedView, SIGNAL(applicaModifica(QString, QString, QString, QString, bool, bool)),
          this, SLOT(viewApplicaModifica(QString, QString, QString, QString, bool, bool)));

  connect(linkedView, SIGNAL(eliminaArticolo()), this, SLOT(viewEliminaArticolo()));
}

const DeepPtr<Smartphone> SmartphoneController::getArticolo(QString ID)
{
  return dynamic_cast<const Smartphone *>(&linkedModel->getArticolo(ID));
}

void SmartphoneController::setID(QString ID)
{
  id = ID;
  emit viewUpdateFields(id);
}

void SmartphoneController::modelUpdate()
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

void SmartphoneController::viewApplicaModifica(QString ID, QString NOME, QString _SPI, QString _COSTO,
                                             bool USATO, bool IPHONE)
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
    linkedModel->insert(ID, Smartphone(IPHONE, USATO, NOME.toStdString(), COSTO, SPI));
    return;
  }
  catch (ModelArticleNotFoundException &)
  {
    linkedModel->insert(ID, Smartphone(IPHONE, USATO, NOME.toStdString(), COSTO, SPI));
    return;
  }

  linkedModel->setArticolo(ID, NOME, COSTO, SPI);
  linkedModel->setElettronica(ID, USATO);
  linkedModel->setSmartphone(ID, IPHONE);
}

void SmartphoneController::viewEliminaArticolo()
{
  linkedModel->remove(id);
}
