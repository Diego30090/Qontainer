#include "Model.hpp"

Model::Model(QObject *parent) : QObject(parent), containerPath(QStringLiteral("")), box(nullptr) {}

Model::~Model()
{
  closeBox();
}

const DeepPtr<Articolo> Model::getArticolo(QString id) const
{
  return box->get(id.toStdString());
}

QList<QString> Model::getAllArticolo() const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getArticoloByNome(QString nome) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  std::string n = nome.toStdString();

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if ((*it)->getNome() == n)
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getArticoloByCostoMax(float cm) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if ((*it)->getSPI() <= cm)
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getArticoloByPrezzoMax(float pm, bool sconto) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      float prezzoArticolo = (*it)->getPrezzo();

      if (sconto)
        prezzoArticolo = prezzoArticolo - prezzoArticolo * (*it)->getSconto() / 100;

      if (prezzoArticolo <= pm)
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

QList<QString> Model::getArticoloBySPIMin(unsigned int spi) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if ((*it)->getSPI() >= spi)
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getAllMedia() const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if (dynamic_cast<Media *>(&*it))
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getMediaByAnno(unsigned int a) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<Media *>(&*it);
      if (ptr && ptr->getAnno() == a)
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

QList<QString> Model::getAllCD() const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if (dynamic_cast<CD *>(&*it))
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getCDByArtista(QString artista) const
{
  if (!box) throw ModelBoxNotOpenException();

  std::string a = artista.toStdString();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<CD *>(&*it);
      if (ptr && ptr->getArtista() == a)
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

QList<QString> Model::getCDIfCompilation(bool c) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<CD *>(&*it);
      if (ptr && ptr->isCompilation() == c)
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

QList<QString> Model::getAllElettronica() const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if (dynamic_cast<Elettronica *>(&*it))
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getElettronicaIfUsato(bool u) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<Elettronica *>(&*it);
      if (ptr && ptr->isUsato() == u)
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

QList<QString> Model::getElettronicaByWarranty(bool w) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<Elettronica *>(&*it);
      if (ptr && ((w && ptr->getWarranty()) || (!w && !ptr->getWarranty())))
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

QList<QString> Model::getAllComputer() const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if (dynamic_cast<Computer *>(&*it))
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getComputerIfPortatile(bool p) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<Computer *>(&*it);
      if (ptr && ptr->isPortatile() == p)
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

QList<QString> Model::getAllSmartphone() const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if (dynamic_cast<Smartphone *>(&*it))
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getSmartphoneIfiPhone(bool ew) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<Smartphone *>(&*it);
      if (ptr && ptr->isiPhone() == ew)
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

//QList<QString> Model::filterByPrice(QList<QString> l, priceFilter pf, float costo)
//{
//  switch (pf)
//    {
//    case uguale:
//      for (auto it = l.begin(); it != l.end(); ++it)
//        if (box->get(it->toStdString())->getSconto() != costo)
//          it-- = l.erase(it);
//      break;

//    case diverso:
//      for (auto it = l.begin(); it != l.end(); ++it)
//        if (box->get(it->toStdString())->getSconto() == costo)
//          it-- = l.erase(it);
//      break;

//    case maggiore:
//      for (auto it = l.begin(); it != l.end(); ++it)
//        if (box->get(it->toStdString())->getSconto() <= costo)
//          it-- = l.erase(it);
//      break;

//    case minore:
//      for (auto it = l.begin(); it != l.end(); ++it)
//        if (box->get(it->toStdString())->getSconto() >= costo)
//          it-- = l.erase(it);
//      break;

//    case maggioreUguale:
//      for (auto it = l.begin(); it != l.end(); ++it)
//        if (box->get(it->toStdString())->getSconto() < costo)
//          it-- = l.erase(it);
//      break;

//    case minoreUguale:
//      for (auto it = l.begin(); it != l.end(); ++it)
//        if (box->get(it->toStdString())->getSconto() > costo)
//          it-- = l.erase(it);
//      break;
//    }
//  return l;
//}

bool Model::isOpen() const
{
  return box;
}

void Model::newBox()
{
  if (box) throw ModelBoxNotClosedException();

  box = new Container<DeepPtr<Articolo>, std::string>;
  emit notify();
}

//void Model::openBox()
//// THROWS: ModelFileNotAvailableException
//{
//  if (box) throw ModelBoxNotClosedException();

//  newBox();

//  auto f = new QFile(containerPath);

//  QDomDocument saveFile;

//  unsigned int i;
//  for (i = 0; !f->open(QIODevice::ReadOnly) && i < OPEN_FILE_ATTEMPTS; ++i);
//  if (i >= OPEN_FILE_ATTEMPTS) throw ModelFileNotAvailableException();

//  if (!saveFile.setContent(f)) throw ModelFileNotAvailableException();

//  QDomElement root = saveFile.firstChildElement(QStringLiteral("box"));

//  for (QDomElement elt = root.firstChildElement(QStringLiteral("entry")); !elt.isNull(); elt = elt.nextSiblingElement("entry"))
//    {
//      QDomElement articolo = elt.firstChildElement(QStringLiteral("articolo"));

//      if (!articolo.firstChildElement(QStringLiteral("CD")).isNull())
//        {
//          QDomElement CD = articolo.firstChildElement(QStringLiteral("CD"));

//          box->put(articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
//                   new CD(CD.firstChildElement(QStringLiteral("artista")).text().toStdString(),
//                             CD.firstChildElement(QStringLiteral("compilation")).text().toUInt(),
//                             articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
//                             articolo.firstChildElement(QStringLiteral("nome")).text().toStdString(),
//                             articolo.firstChildElement(QStringLiteral("costo")).text().toFloat(),
//                             articolo.firstChildElement(QStringLiteral("spi")).text().toUInt(),
//                             articolo.firstChildElement(QStringLiteral("imgPath")).text().toStdString()));
//        }
//      else if (!articolo.firstChildElement(QStringLiteral("Elettronica")).isNull())
//        {
//          QDomElement Elettronica = articolo.firstChildElement(QStringLiteral("Elettronica"));

//          if (!Elettronica.firstChildElement(QStringLiteral("computer")).isNull())
//            {
//              QDomElement computer = Elettronica.firstChildElement(QStringLiteral("computer"));

//              box->put(articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
//                       new Computer(computer.firstChildElement(QStringLiteral("portatile")).text().toUInt(),
//                                    Elettronica.firstChildElement(QStringLiteral("usato")).text().toUInt(),
//                                    articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
//                                    articolo.firstChildElement(QStringLiteral("nome")).text().toStdString(),
//                                    articolo.firstChildElement(QStringLiteral("costo")).text().toFloat(),
//                                    articolo.firstChildElement(QStringLiteral("spi")).text().toUInt(),
//                                    articolo.firstChildElement(QStringLiteral("imgPath")).text().toStdString()));
//            }
//          else if (!Elettronica.firstChildElement(QStringLiteral("smartphone")).isNull())
//            {
//              QDomElement smartphone = Elettronica.firstChildElement(QStringLiteral("smartphone"));

//              box->put(articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
//                       new Smartphone(smartphone.firstChildElement(QStringLiteral("extendedWarranty")).text().toUInt(),
//                                      Elettronica.firstChildElement(QStringLiteral("usato")).text().toUInt(),
//                                      articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
//                                      articolo.firstChildElement(QStringLiteral("nome")).text().toStdString(),
//                                      articolo.firstChildElement(QStringLiteral("costo")).text().toFloat(),
//                                      articolo.firstChildElement(QStringLiteral("spi")).text().toUInt(),
//                                      articolo.firstChildElement(QStringLiteral("imgPath")).text().toStdString()));
//            }
//        }
//    }

//  f->close();
//}

void Model::closeBox()
// THROWS: ModelBoxNotOpenException
{
  if (!box) throw ModelBoxNotOpenException();

  delete box;
  box = nullptr;

  emit notify();
}

//void Model::saveBox() const
//// THROWS: ModelBoxNotOpenException, ModelBoxPathNotSetException, ModelFileNotAvailableException
//{
//  if (!box) throw ModelBoxNotOpenException();

//  if (containerPath == "") throw ModelBoxPathNotSetException();

//  auto f = new QFile(containerPath);

//  auto writeStream = new QXmlStreamWriter(f);
//  writeStream->setAutoFormatting(true);

//  unsigned int i;
//  for (i = 0; !f->open(QIODevice::WriteOnly) && i < OPEN_FILE_ATTEMPTS; ++i);
//  if (i >= OPEN_FILE_ATTEMPTS) throw ModelFileNotAvailableException();

//  writeStream->writeStartDocument();
//  writeStream->writeStartElement(QStringLiteral("box"));

//  for (auto it = box->begin(); !it.isEnd(); ++it)
//    {
//      QString elementType;
//      if (dynamic_cast<CD *>(&**it))
//        {
//          elementType = QStringLiteral("CD");
//        }
//      else if (dynamic_cast<Elettronica *>(&**it))
//        {
//          if (dynamic_cast<Computer *>(&**it))
//            {
//              elementType = QStringLiteral("Computer");
//            }
//          else if (dynamic_cast<Smartphone *>(&**it))
//            {
//              elementType = QStringLiteral("Smartphone");
//            }
//        }

//      writeStream->writeStartElement(QStringLiteral("entry"));
//      writeStream->writeAttribute(QStringLiteral("tipo"), elementType);

//      writeStream->writeStartElement(QStringLiteral("articolo"));

//      writeStream->writeTextElement(QStringLiteral("id"), QString::fromStdString((*it)->getId()));
//      writeStream->writeTextElement(QStringLiteral("nome"), QString::fromStdString((*it)->getNome()));
//      writeStream->writeTextElement(QStringLiteral("costo"), QString().setNum((*it)->getcosto()));
//      writeStream->writeTextElement(QStringLiteral("spi"), QString().setNum((*it)->getSPI()));
//      writeStream->writeTextElement(QStringLiteral("imgPath"), QString::fromStdString((*it)->getImgPath()));

//      if (dynamic_cast<CD *>(&*it))
//        {
//          writeStream->writeStartElement(QStringLiteral("CD"));

//          auto tmp = dynamic_cast<CD *>(&*it);

//          writeStream->writeTextElement(QStringLiteral("artista"), QString::fromStdString(tmp->getArtista()));
//          writeStream->writeTextElement(QStringLiteral("compilation"), QString().setNum(tmp->isCompilation()));

//          writeStream->writeEndElement(); // CD
//        }
//      else if (dynamic_cast<Elettronica *>(&*it))
//        {
//          writeStream->writeStartElement(QStringLiteral("Elettronica"));

//          auto tmp = dynamic_cast<Elettronica *>(&*it);

//          writeStream->writeTextElement(QStringLiteral("usato"), QString().setNum(tmp->isUsato()));

//          if (dynamic_cast<Computer *>(&*it))
//            {
//              writeStream->writeStartElement(QStringLiteral("computer"));

//              auto tmp = dynamic_cast<Computer *>(&*it);

//              writeStream->writeTextElement(QStringLiteral("portatile"), QString().setNum(tmp->isPortatile()));

//              writeStream->writeEndElement(); // computer
//            }
//          else if (dynamic_cast<Smartphone *>(&*it))
//            {
//              writeStream->writeStartElement(QStringLiteral("smartphone"));

//              auto tmp = dynamic_cast<Smartphone *>(&*it);

//              writeStream->writeTextElement(QStringLiteral("extendedWarranty"), QString().setNum(tmp->hasExtendedWarranty()));

//              writeStream->writeEndElement(); // smartphone
//            }

//          writeStream->writeEndElement(); // Elettronica

//        }

//      writeStream->writeEndElement(); // articolo
//      writeStream->writeEndElement(); // id

//    }

//  writeStream->writeEndElement();
//  writeStream->writeEndDocument();
//  f->close();
//}

void Model::changeBoxPath(QString path)
{
  containerPath = path;
}

void Model::insert(QString k, const DeepPtr<Articolo> &i)
{
  try
  {
    box->put(k.toStdString(), i);
  }
  catch (std::exception &e)
  {
    emit err(e.what());
    return;
  }

  emit notify();
}

void Model::remove(QString id)
{
  try
  {
    box->remove(id.toStdString());
  }
  catch (std::exception &e)
  {
    emit err(e.what());
    return;
  }

  emit notify();
}

void Model::remove(QList<QString> l)
{
  try
  {
    for (int i = 0; i < l.size(); ++i)
      box->remove(l[i].toStdString());
  }
  catch (std::exception &e)
  {
    emit err(e.what());
    return;
  }

  emit notify();
}

void Model::setArticolo(QString k, QString nome, float costo, unsigned int spi) const
{
  Articolo *a;

  try
  {
    a = &box->get(k.toStdString());
  }
  catch (std::exception &e)
  {
    emit err(e.what());
    return;
  }

  a->setNome(nome.toStdString());
  a->setCosto(costo);
  a->setSPI(spi);
}

void Model::setMedia(QString k, unsigned int anno) const
{
  Media *m;

  try
  {
    m = dynamic_cast<Media *>(&box->get(k.toStdString()));

    if (!m) throw ModelBadTypeException();
  }
  catch (std::exception &e)
  {
    emit err(e.what());
    return;
  }

  m->setAnno(anno);
}

void Model::setCD(QString k, QString artista, bool comp) const
{
  CD *cd;

  try
  {
    cd = dynamic_cast<CD *>(&box->get(k.toStdString()));

    if (!cd) throw ModelBadTypeException();
  }
  catch (std::exception &e)
  {
    emit err(e.what());
    return;
  }

  cd->setArtista(artista.toStdString());
  cd->setCompilation(comp);
}


