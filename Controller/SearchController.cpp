#include "SearchController.hpp"

QList<QString> SearchController::join(const QList<QString> &a, const QList<QString> &b)
{
  QList<QString> res;

  for (auto ia = a.begin(); ia != a.end(); ++ia)
    {
      bool found = false;

      for (auto ib = b.begin(); !(ib == b.end() || found); ++ib)
        found = *ia == *ib;

      if (found)
        res.push_back(*ia);
    }

  return res;
}

SearchController::SearchController(Model *m, View *v) : Controller(m, v)
{
  connect(linkedModel, SIGNAL(notify()), this, SLOT(modelUpdate()));

  connect(linkedView, SIGNAL(searchStart(bool, QString, QString, QString,
                                         bool, QString, QString, bool,
                                         bool, bool, bool,
                                         bool, bool, bool)),
          this, SLOT(viewSearchStart(bool, QString, QString, QString,
                                     bool, QString, QString, bool,
                                     bool, bool, bool,
                                     bool, bool, bool)));
}

void SearchController::modelUpdate()
{

}

void SearchController::viewSearchStart(bool checkA, QString nome, QString costoMax, QString prezzoMax,
                                       bool checkCD, QString annoCD, QString artista, bool compilation,
                                       bool checkC, bool usatoC, bool portatile,
                                       bool checkS, bool usatoS, bool iphone)
{
  QList<QString> res;

  try
  {
  if (checkA)
    {
      res = linkedModel->getAllArticolo();

      if (!nome.isEmpty())
        {
          auto tmp = linkedModel->getArticoloByNome(nome);

          res = join(res, tmp);
        }

      if (!costoMax.isEmpty())
        {
          auto tmp = linkedModel->getArticoloByCostoMax(costoMax.toFloat());

          res = join(res, tmp);
        }

      if (!prezzoMax.isEmpty())
        {
          auto tmp = linkedModel->getArticoloByPrezzoMax(prezzoMax.toFloat());

          res = join(res, tmp);
        }
    }
  else if (checkCD)
    {
      res = linkedModel->getAllCD();

      if(!annoCD.isEmpty())
        {
          auto tmp = linkedModel->getMediaByAnno(annoCD.toUInt());

          res = join(res, tmp);
        }

      if(!artista.isEmpty())
        {
          auto tmp = linkedModel->getCDByArtista(artista);

          res = join(res, tmp);
        }

        {
          auto tmp = linkedModel->getCDIfCompilation(compilation);

          res = join(res, tmp);
        }
    }
  else if (checkC)
    {
      res = linkedModel->getAllComputer();

      {
        auto tmp = linkedModel->getElettronicaIfUsato(usatoC);

        res = join(res, tmp);
      }

      {
        auto tmp = linkedModel->getComputerIfPortatile(portatile);

        res = join(res, tmp);
      }
    }
  else if (checkS)
    {
      res = linkedModel->getAllSmartphone();

      {
        auto tmp = linkedModel->getElettronicaIfUsato(usatoS);

        res = join(res, tmp);
      }

      {
        auto tmp = linkedModel->getSmartphoneIfiPhone(iphone);

        res = join(res, tmp);
      }
    }
  }
  catch (ContainerEmptyTableException)
  {
    return;
  }

  emit searchResult(res);
}

