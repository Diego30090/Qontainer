#include "CDController.hpp"

CDController::CDController(Model *m, View *view)
  : Controller(m, view), id("")
{
  connect(this, SIGNAL(viewUpdateFields(QString)), linkedView, SLOT(updateFields(QString)));

  connect(linkedModel, SIGNAL(notify()), this, SLOT(modelUpdate()));

  connect(linkedView, SIGNAL(applicaModifica(QString, QString, QString, QString, QString, QString, bool)),
          this, SLOT(viewApplicaModifica(QString, QString, QString, QString, QString, QString, bool)));

  connect(linkedView, SIGNAL(eliminaArticolo()), this, SLOT(viewEliminaArticolo()));
}

const DeepPtr<CD> CDController::getArticolo(QString ID)
{
  return dynamic_cast<const CD *>(&linkedModel->getArticolo(ID));
}

void CDController::setID(QString ID)
{
  id = ID;
  emit viewUpdateFields(id);
}

void CDController::modelUpdate()
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

void CDController::viewApplicaModifica(QString ID, QString NOME, QString _SPI, QString _COSTO,
                                       QString _ANNO, QString ARTISTA, bool COMPILATION)
{
  if (ID.isEmpty())
    {
      QMessageBox::critical(linkedView, QStringLiteral("Errore Inserimento Dati"), QStringLiteral("ID non inserito!"));
      return;
    }

  bool ok_costo;
  bool ok_spi;
  bool ok_anno;

  float COSTO = _COSTO.toFloat(&ok_costo);
  unsigned int SPI = _SPI.toUInt(&ok_spi);
  unsigned int ANNO = _ANNO.toUInt(&ok_anno);

  if (!(ok_costo && ok_spi && ok_anno))
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
    linkedModel->insert(ID, CD(ARTISTA.toStdString(), COMPILATION, ANNO, NOME.toStdString(), COSTO, SPI));
    return;
  }
  catch (ModelArticleNotFoundException &)
  {
    linkedModel->insert(ID, CD(ARTISTA.toStdString(), COMPILATION, ANNO, NOME.toStdString(), COSTO, SPI));
    return;
  }

  linkedModel->setArticolo(ID, NOME, COSTO, SPI);
  linkedModel->setMedia(ID, ANNO);
  linkedModel->setCD(ID, ARTISTA, COMPILATION);
}

void CDController::viewEliminaArticolo()
{
  linkedModel->remove(id);
}
