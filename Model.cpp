#include "Model.hpp"

// IMPLEMENTAZIONE ECCEZIONI
const char * ModelException::what() const noexcept
{
  return "Errore sconosciuto Modello";
}

const char * ModelBoxNotOpenException::what() const noexcept
{
  return "Si è cercato di effettuare un'operazione a box chiuso";
}

const char * ModelBoxNotClosedException::what() const noexcept
{
  return "Si è cercato di effettuare un'operazione a box aperto";
}

const char * ModelBoxPathNotSetException::what() const noexcept
{
  return "Non è stato impostato un percorso per il box";
}

const char * ModelFileNotAvailableException::what() const noexcept
{
  return "Errore nell'apertura del file";
}

const char * ModelBadTypeException::what() const noexcept
{
  return "Operazione non consentita su questo tipo di dato";
}


// IMPLEMENTAZIONE MODEL
Model::Model(QObject *parent) : QObject(parent), containerPath(QStringLiteral("")), box(nullptr) {}

const DeepPtr<Articolo> Model::getArticolo(QString id) const
{
  return box->get(id.toStdString())->clone();
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

QList<QString> Model::getArticoloByPrezzoListino(float pl) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if ((*it)->getPrezzoListino() == pl)
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getArticoloBySPI(unsigned int spi) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if ((*it)->getSPI() == spi)
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getAllAlbum() const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if (dynamic_cast<Album *>(&*it))
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getAlbumByArtista(QString artista) const
{
  if (!box) throw ModelBoxNotOpenException();

  std::string a = artista.toStdString();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<Album *>(&*it);
      if (ptr && ptr->getArtista() == a)
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

QList<QString> Model::getAlbumIfCompilation(bool c) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<Album *>(&*it);
      if (ptr && ptr->isCompilation() == c)
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

QList<QString> Model::getAllElettBruno() const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if (dynamic_cast<ElettBruno *>(&*it))
      res.push_back(QString::fromStdString(it.getKey()));

  return res;
}

QList<QString> Model::getElettBrunoIfUsato(bool u) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<ElettBruno *>(&*it);
      if (ptr && ptr->isUsato() == u)
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

QList<QString> Model::getSmartphoneIfExtWarr(bool ew) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto ptr = dynamic_cast<Smartphone *>(&*it);
      if (ptr && ptr->hasExtendedWarranty() == ew)
        res.push_back(QString::fromStdString(it.getKey()));
    }

  return res;
}

QList<QString> Model::filterByPrice(QList<QString> l, priceFilter pf, float prezzo)
{
  switch (pf)
    {
    case uguale:
      for (auto it = l.begin(); it != l.end(); ++it)
        if (box->get(it->toStdString())->getPrezzo() != prezzo)
          it-- = l.erase(it);
      break;

    case diverso:
      for (auto it = l.begin(); it != l.end(); ++it)
        if (box->get(it->toStdString())->getPrezzo() == prezzo)
          it-- = l.erase(it);
      break;

    case maggiore:
      for (auto it = l.begin(); it != l.end(); ++it)
        if (box->get(it->toStdString())->getPrezzo() <= prezzo)
          it-- = l.erase(it);
      break;

    case minore:
      for (auto it = l.begin(); it != l.end(); ++it)
        if (box->get(it->toStdString())->getPrezzo() >= prezzo)
          it-- = l.erase(it);
      break;

    case maggioreUguale:
      for (auto it = l.begin(); it != l.end(); ++it)
        if (box->get(it->toStdString())->getPrezzo() < prezzo)
          it-- = l.erase(it);
      break;

    case minoreUguale:
      for (auto it = l.begin(); it != l.end(); ++it)
        if (box->get(it->toStdString())->getPrezzo() > prezzo)
          it-- = l.erase(it);
      break;
    }
  return l;
}

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

void Model::openBox()
{
  if (box) throw ModelBoxNotClosedException();

  newBox();

  auto f = new QFile(containerPath);

  QDomDocument saveFile;

  unsigned int i;
  for (i = 0; !f->open(QIODevice::ReadOnly) && i < OPEN_FILE_ATTEMPTS; ++i);
  if (i >= OPEN_FILE_ATTEMPTS) throw ModelFileNotAvailableException();

  if (!saveFile.setContent(f)) throw ModelFileNotAvailableException();

  QDomElement root = saveFile.firstChildElement(QStringLiteral("box"));

  for (QDomElement elt = root.firstChildElement(QStringLiteral("entry")); !elt.isNull(); elt = elt.nextSiblingElement("entry"))
    {
      QDomElement articolo = elt.firstChildElement(QStringLiteral("articolo"));

      if (!articolo.firstChildElement(QStringLiteral("album")).isNull())
        {
          QDomElement album = articolo.firstChildElement(QStringLiteral("album"));

          box->put(articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
                   new Album(album.firstChildElement(QStringLiteral("artista")).text().toStdString(),
                             album.firstChildElement(QStringLiteral("compilation")).text().toUInt(),
                             articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
                             articolo.firstChildElement(QStringLiteral("nome")).text().toStdString(),
                             articolo.firstChildElement(QStringLiteral("prezzoListino")).text().toFloat(),
                             articolo.firstChildElement(QStringLiteral("spi")).text().toUInt(),
                             articolo.firstChildElement(QStringLiteral("imgPath")).text().toStdString()));
        }
      else if (!articolo.firstChildElement(QStringLiteral("elettBruno")).isNull())
        {
          QDomElement elettBruno = articolo.firstChildElement(QStringLiteral("elettBruno"));

          if (!elettBruno.firstChildElement(QStringLiteral("computer")).isNull())
            {
              QDomElement computer = elettBruno.firstChildElement(QStringLiteral("computer"));

              box->put(articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
                       new Computer(computer.firstChildElement(QStringLiteral("portatile")).text().toUInt(),
                                    elettBruno.firstChildElement(QStringLiteral("usato")).text().toUInt(),
                                    articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
                                    articolo.firstChildElement(QStringLiteral("nome")).text().toStdString(),
                                    articolo.firstChildElement(QStringLiteral("prezzoListino")).text().toFloat(),
                                    articolo.firstChildElement(QStringLiteral("spi")).text().toUInt(),
                                    articolo.firstChildElement(QStringLiteral("imgPath")).text().toStdString()));
            }
          else if (!elettBruno.firstChildElement(QStringLiteral("smartphone")).isNull())
            {
              QDomElement smartphone = elettBruno.firstChildElement(QStringLiteral("smartphone"));

              box->put(articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
                       new Smartphone(smartphone.firstChildElement(QStringLiteral("extendedWarranty")).text().toUInt(),
                                      elettBruno.firstChildElement(QStringLiteral("usato")).text().toUInt(),
                                      articolo.firstChildElement(QStringLiteral("id")).text().toStdString(),
                                      articolo.firstChildElement(QStringLiteral("nome")).text().toStdString(),
                                      articolo.firstChildElement(QStringLiteral("prezzoListino")).text().toFloat(),
                                      articolo.firstChildElement(QStringLiteral("spi")).text().toUInt(),
                                      articolo.firstChildElement(QStringLiteral("imgPath")).text().toStdString()));
            }
        }
    }

  f->close();
}

void Model::closeBox()
{
  if (!box) throw ModelBoxNotOpenException();

  delete box;
  box = nullptr;

  emit notify();
}

void Model::saveBox() const
{
  if (!box) throw ModelBoxNotOpenException();

  if (containerPath == "") throw ModelBoxPathNotSetException();

  auto f = new QFile(containerPath);

  auto writeStream = new QXmlStreamWriter(f);
  writeStream->setAutoFormatting(true);

  unsigned int i;
  for (i = 0; !f->open(QIODevice::WriteOnly) && i < OPEN_FILE_ATTEMPTS; ++i);
  if (i >= OPEN_FILE_ATTEMPTS) throw ModelFileNotAvailableException();

  writeStream->writeStartDocument();
  writeStream->writeStartElement(QStringLiteral("box"));

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      QString elementType;
      if (dynamic_cast<Album *>(&**it))
        {
          elementType = QStringLiteral("Album");
        }
      else if (dynamic_cast<ElettBruno *>(&**it))
        {
          if (dynamic_cast<Computer *>(&**it))
            {
              elementType = QStringLiteral("Computer");
            }
          else if (dynamic_cast<Smartphone *>(&**it))
            {
              elementType = QStringLiteral("Smartphone");
            }
        }

      writeStream->writeStartElement(QStringLiteral("entry"));
      writeStream->writeAttribute(QStringLiteral("tipo"), elementType);

      writeStream->writeStartElement(QStringLiteral("articolo"));

      writeStream->writeTextElement(QStringLiteral("id"), QString::fromStdString((*it)->getId()));
      writeStream->writeTextElement(QStringLiteral("nome"), QString::fromStdString((*it)->getNome()));
      writeStream->writeTextElement(QStringLiteral("prezzoListino"), QString().setNum((*it)->getPrezzoListino()));
      writeStream->writeTextElement(QStringLiteral("spi"), QString().setNum((*it)->getSPI()));
      writeStream->writeTextElement(QStringLiteral("imgPath"), QString::fromStdString((*it)->getImgPath()));

      if (dynamic_cast<Album *>(&*it))
        {
          writeStream->writeStartElement(QStringLiteral("album"));

          auto tmp = dynamic_cast<Album *>(&*it);

          writeStream->writeTextElement(QStringLiteral("artista"), QString::fromStdString(tmp->getArtista()));
          writeStream->writeTextElement(QStringLiteral("compilation"), QString().setNum(tmp->isCompilation()));

          writeStream->writeEndElement(); // album
        }
      else if (dynamic_cast<ElettBruno *>(&*it))
        {
          writeStream->writeStartElement(QStringLiteral("elettBruno"));

          auto tmp = dynamic_cast<ElettBruno *>(&*it);

          writeStream->writeTextElement(QStringLiteral("usato"), QString().setNum(tmp->isUsato()));

          if (dynamic_cast<Computer *>(&*it))
            {
              writeStream->writeStartElement(QStringLiteral("computer"));

              auto tmp = dynamic_cast<Computer *>(&*it);

              writeStream->writeTextElement(QStringLiteral("portatile"), QString().setNum(tmp->isPortatile()));

              writeStream->writeEndElement(); // computer
            }
          else if (dynamic_cast<Smartphone *>(&*it))
            {
              writeStream->writeStartElement(QStringLiteral("smartphone"));

              auto tmp = dynamic_cast<Smartphone *>(&*it);

              writeStream->writeTextElement(QStringLiteral("extendedWarranty"), QString().setNum(tmp->hasExtendedWarranty()));

              writeStream->writeEndElement(); // smartphone
            }

          writeStream->writeEndElement(); // elettBruno

        }

      writeStream->writeEndElement(); // articolo
      writeStream->writeEndElement(); // id

    }

  writeStream->writeEndElement();
  writeStream->writeEndDocument();
  f->close();
}

void Model::changeBoxPath(QString path)
{
  containerPath = path;
}

void Model::insert(const DeepPtr<Articolo> &i)
{
  box->put(i->getId(), i);

  emit notify();
}

void Model::remove(QString id)
{
  box->remove(id.toStdString());

  emit notify();
}

void Model::remove(QList<QString> l)
{
  for (int i = 0; i < l.size(); ++i)
    box->remove(l[i].toStdString());

  emit notify();
}

void Model::setArticoloNome(QString id, QString nome) const
{
  box->get(id.toStdString())->setNome(nome.toStdString());

  emit notify();
}

void Model::setArticoloPrezzoListino(QString id, float pl) const
{
  box->get(id.toStdString())->setPrezzoListino(pl);

  emit notify();
}

void Model::setArticoloSPI(QString id, unsigned int spi) const
{
  box->get(id.toStdString())->setSPI(spi);

  emit notify();
}

void Model::setAlbumArtista(QString id, QString art) const
{
  auto ptr = dynamic_cast<Album *>(&box->get(id.toStdString()));

  if (ptr)
    ptr->setArtista(art.toStdString());
  else
    throw ModelBadTypeException();

  emit notify();
}

void Model::setAlbumCompilation(QString id, bool c) const
{
  auto ptr = dynamic_cast<Album *>(&box->get(id.toStdString()));

  if (ptr)
    ptr->setCompilation(c);
  else
    throw ModelBadTypeException();

  emit notify();
}

void Model::setElettBrunoUsato(QString id, bool u) const
{
  auto ptr = dynamic_cast<ElettBruno *>(&box->get(id.toStdString()));

  if (ptr)
    ptr->setUsato(u);
  else
    throw ModelBadTypeException();

  emit notify();
}

void Model::setComputerPortatile(QString id, bool p) const
{
  auto ptr = dynamic_cast<Computer *>(&box->get(id.toStdString()));

  if (ptr)
    ptr->setPortatile(p);
  else
    throw ModelBadTypeException();

  emit notify();
}

void Model::setSmartphoneExtWarr(QString id, bool ew) const
{
  auto ptr = dynamic_cast<Smartphone *>(&box->get(id.toStdString()));

  if (ptr)
    ptr->setExtendedWarranty(ew);
  else
    throw ModelBadTypeException();

  emit notify();
}
