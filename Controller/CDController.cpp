#include "CDController.hpp"

CDController::CDController(Model *m, View *view)
  : Controller(m, view), id(QStringLiteral(""))
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
      catch (ModelArticleNotFoundException)
      {
        linkedView->close();
        return;
      }

      emit viewUpdateFields(id);
    }
}

void CDController::viewApplicaModifica(QString ID, QString NOME, QString SPI, QString COSTO,
                                       QString ANNO, QString ARTISTA, bool COMPILATION)
{
  try
  {
    linkedModel->getArticolo(ID);
  }
  catch (ModelArticleNotFoundException)
  {
    linkedModel->insert(ID, CD(ARTISTA.toStdString(), COMPILATION, ANNO.toUInt(), NOME.toStdString(), COSTO.toFloat(), SPI.toUInt()));
    return;
  }

  id = ID;
  linkedModel->setArticolo(ID, NOME, COSTO.toFloat(), SPI.toUInt());
  linkedModel->setMedia(ID, ANNO.toUInt());
  linkedModel->setCD(ID, ARTISTA, COMPILATION);
}

void CDController::viewEliminaArticolo()
{
  linkedModel->remove(id);
}
