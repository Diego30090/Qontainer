#include "Model.hpp"
#include <QDebug>

// Implementazione eccezioni
const char * ModelException::what() const noexcept
{
  return "Errore sconosciuto Modello";
}

const char * ModelBoxNotOpenException::what() const noexcept
{
  return "Box non aperto";
}

const char * ModelFileNotAvailableException::what() const noexcept
{
  return "Errore nell'apertura del file";
}

// Implementazione Model
Model::Model(QObject *parent) : QObject(parent), containerPath(QStringLiteral("")), box(nullptr) {}

QList<DeepPtr<Articolo>> Model::getData() const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<DeepPtr<Articolo>> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    res.push_back(*it);

  return res;
}

bool Model::isOpen() const
{
  return box;
}

void Model::newBox()
{
  if (box) throw 3; //////////////////////////////////////////////////////////////////////////////////////

  box = new Container<DeepPtr<Articolo>, std::string>;
  emit notify();
}

void Model::openBox()
{
  if (box) throw 2; //////////////////////////////////////////////////////////////////////////////////////

  newBox();

  auto f = new QFile(containerPath);

  auto readStream = new QXmlStreamReader(f);

  unsigned int i;
  for (i = 0; !f->open(QIODevice::ReadOnly) && i < OPEN_FILE_ATTEMPTS; ++i);
  if (i >= OPEN_FILE_ATTEMPTS) throw ModelFileNotAvailableException();

  while (!readStream->atEnd())
    {
      readStream->readNext();

      qDebug() << readStream->name().toString();

      if (readStream->name().toString() == "Album")
        {
          auto att = readStream->attributes();

          box->put(att.at(0).value().toString().toStdString(),
                   new Album(att.at(5).value().toString().toStdString(),
                             att.at(6).value().toString().toUInt(),
                             att.at(0).value().toString().toStdString(),
                             att.at(1).value().toString().toStdString(),
                             att.at(2).value().toString().toFloat(),
                             att.at(3).value().toString().toUInt(),
                             att.at(4).value().toString().toStdString()));
        }
      else if (readStream->name().toString() == "Computer")
        {
          auto att = readStream->attributes();

          box->put(att.at(0).value().toString().toStdString(),
                   new Computer(att.at(5).value().toString().toUInt(),
                                att.at(6).value().toString().toUInt(),
                                att.at(0).value().toString().toStdString(),
                                att.at(1).value().toString().toStdString(),
                                att.at(2).value().toString().toFloat(),
                                att.at(3).value().toString().toUInt(),
                                att.at(4).value().toString().toStdString()));
        }
      else if (readStream->name().toString() == "Smartphone")
        {
          auto att = readStream->attributes();

          box->put(att.at(0).value().toString().toStdString(),
                   new Smartphone(att.at(5).value().toString().toUInt(),
                                  att.at(6).value().toString().toUInt(),
                                  att.at(0).value().toString().toStdString(),
                                  att.at(1).value().toString().toStdString(),
                                  att.at(2).value().toString().toFloat(),
                                  att.at(3).value().toString().toUInt(),
                                  att.at(4).value().toString().toStdString()));
        }
    }
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

  if (containerPath == "") throw 1; /////////////////////////////////////////////////////////////////////////////

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
//      QString elementName;
//      if (dynamic_cast<Album *>(&**it))
//        {
//          elementName = QStringLiteral("Album");
//        }
//      else if (dynamic_cast<ElettBruno *>(&**it))
//        {
//          if (dynamic_cast<Computer *>(&**it))
//            {
//              elementName = QStringLiteral("Computer");
//            }
//          else if (dynamic_cast<Smartphone *>(&**it))
//            {
//              elementName = QStringLiteral("Smartphone");
//            }
//        }

      writeStream->writeStartElement(QStringLiteral("entry"));

      writeStream->writeStartElement(QStringLiteral("articolo"));

      writeStream->writeTextElement(QStringLiteral("id"), QString::fromStdString((*it)->getId()));
      writeStream->writeTextElement(QStringLiteral("nome"), QString::fromStdString((*it)->getNome()));
      writeStream->writeTextElement(QStringLiteral("prezzoListino"), QString().setNum((*it)->getPrezzoListino()));
      writeStream->writeTextElement(QStringLiteral("spi"), QString().setNum((*it)->getSPI()));
      writeStream->writeTextElement(QStringLiteral("imgPath"), QString::fromStdString((*it)->getImgPath()));

      if (dynamic_cast<Album *>(&*it))
        {
          writeStream->writeStartElement(QStringLiteral("album"));

          auto tmp = dynamic_cast<Album *>(&(*it));

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

              auto tmp = dynamic_cast<Computer *>(&(*it));

              writeStream->writeTextElement(QStringLiteral("portatile"), QString().setNum(tmp->isPortatile()));

              writeStream->writeEndElement(); // computer
            }
          else if (dynamic_cast<Smartphone *>(&(*it)))
            {
              writeStream->writeStartElement(QStringLiteral("smartphone"));

              auto tmp = dynamic_cast<Smartphone *>(&(*it));

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
}

//void Model::attach(Controller const * const c)
//{
//  subscription.push_back(c);
//}

//void Model::detach(Controller const * const c)
//{
//  bool found = false;

//  for(auto seek = subscription.begin(); !found && seek != subscription.end(); ++seek)
//    {
//      if (c == *seek)
//        {
//          subscription.erase(seek);
//          found = true;
//        }
//    }
//}
