#include "Model.hpp"

Model::Model(QObject *parent) : QObject(parent), containerPath(QStringLiteral("")), box(nullptr) {}

Model::~Model()
{
  if (box)
    closeBox();
}

const DeepPtr<Articolo> Model::getArticolo(QString id) const
{
  try
  {
    return box->get(id.toStdString());
  }
  catch (ContainerEmptyTableException)
  {
    throw ModelEmptyBoxException();
  }
  catch (ContainerCellNotFoundException)
  {
    throw ModelArticleNotFoundException();
  }
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

QList<QString> Model::getArticoloByPrezzoMax(float pm) const
{
  if (!box) throw ModelBoxNotOpenException();

  QList<QString> res;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    if ((*it)->getPrezzo() <= pm)
      res.push_back(QString::fromStdString(it.getKey()));

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

bool Model::isOpen() const
{
  return box;
}

bool Model::isEmpty() const
{
  return box->empty();
}

void Model::newBox()
{
  if (box) throw ModelBoxNotClosedException();

  box = new Container<DeepPtr<Articolo>, std::string>;
}

void Model::openBox()
// THROWS: ModelFileNotAvailableException
{
  if (box) throw ModelBoxNotClosedException();

  newBox();

  YAML::Node f = YAML::LoadFile(containerPath.toStdString())["BOX"];

  for (unsigned int i = 0; i < f.size(); ++i)
    {
      auto a = f[i];

      auto id = a["id"].as<std::string>();
      auto nome = a["nome"].as<std::string>();
      auto costo = a["costo"].as<float>();
      auto spi = a["spi"].as<unsigned int>();

      if (YAML::Node m = a["media"])
        {
          auto anno = m["anno"].as<unsigned int>();

          if (YAML::Node cd = m["cd"])
            {
              auto artista = cd["artista"].as<std::string>();
              auto compilation = cd["compilation"].as<bool>();

              box->put(id, CD(artista, compilation, anno, nome, costo, spi));
            }
        }
      else if (YAML::Node e = a["elettronica"])
        {
          auto usato = e["usato"].as<bool>();

          if (YAML::Node c = e["computer"])
            {
              auto portatile = c["portatile"].as<bool>();

              box->put(id, Computer(portatile, usato, nome, costo, spi));
            }
          else if (YAML::Node s = e["smartphone"])
            {
              auto iphone = s["iphone"].as<bool>();

              box->put(id, Smartphone(iphone, usato, nome, costo, spi));
            }
        }
    }

  emit notify();
}

void Model::closeBox()
// THROWS: ModelBoxNotOpenException
{
  if (!box) throw ModelBoxNotOpenException();

  delete box;
  box = nullptr;
}

void Model::saveBox() const
// THROWS: ModelBoxNotOpenException, ModelBoxPathNotSetException, ModelFileNotAvailableException
{
  if (!box) throw ModelBoxNotOpenException();

  if (containerPath == "") throw ModelBoxPathNotSetException();

  YAML::Emitter out;
  out << YAML::BeginDoc << YAML::BeginMap;
  out << YAML::Key << "BOX" << YAML::Value << YAML::BeginSeq;

  for (auto it = box->begin(); !it.isEnd(); ++it)
    {
      auto a = *it;

      out << YAML::BeginMap;

      out << YAML::Key << "id" << YAML::Value << it.getKey();
      out << YAML::Key << "nome" << YAML::Value << a->getNome();
      out << YAML::Key << "costo" << YAML::Value << a->getCosto();
      out << YAML::Key << "spi" << YAML::Value << a->getSPI();

      if (auto m = dynamic_cast<Media *>(&a))
        {
          out << YAML::Key << "media" << YAML::BeginMap;

          out << YAML::Key << "anno" << YAML::Value << m->getAnno();

          if (auto cd = dynamic_cast<CD *>(&a))
            {
              out << YAML::Key << "cd" << YAML::BeginMap;

              out << YAML::Key << "artista" << YAML::Value << cd->getArtista();
              out << YAML::Key << "compilation" << YAML::Value << cd->isCompilation();

              out << YAML::EndMap;
            }

          out << YAML::EndMap;
        }
      else if (auto e = dynamic_cast<Elettronica * >(&a))
        {
          out << YAML::Key << "elettronica" << YAML::BeginMap;

          out << YAML::Key << "usato" << YAML::Value << e->isUsato();

          if (auto c = dynamic_cast<Computer *>(&a))
            {
              out << YAML::Key << "computer" << YAML::BeginMap;

              out << YAML::Key << "portatile" << YAML::Value << c->isPortatile();

              out << YAML::EndMap;
            }
          else if (auto s = dynamic_cast<Smartphone *>(&a))
            {
              out << YAML::Key << "smartphone" << YAML::BeginMap;

              out << YAML::Key << "iphone" << YAML::Value << s->isiPhone();

              out << YAML::EndMap;
            }

          out << YAML::EndMap;
        }

      out << YAML::EndMap;
    }
  out << YAML::EndSeq << YAML::EndMap << YAML::EndDoc;

  auto f = new QFile(containerPath);

  unsigned int i;
  for (i = 0; !f->open(QIODevice::WriteOnly) && i < OPEN_FILE_ATTEMPTS; ++i);
  if (i >= OPEN_FILE_ATTEMPTS) throw ModelFileNotAvailableException();

  f->flush();
  f->write(out.c_str());
  f->close();
  delete f;
}

QString Model::getBoxPath()
{
  return containerPath;
}

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

  emit notify();
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

  emit notify();
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

  emit notify();
}

void Model::setElettronica(QString k, bool us) const
{
  Elettronica *el;

  try
  {
    el = dynamic_cast<Elettronica *>(&box->get(k.toStdString()));

    if (!el) throw ModelBadTypeException();
  }
  catch (std::exception &e)
  {
    emit err(e.what());
    return;
  }

  el->setUsato(us);

  emit notify();
}

void Model::setComputer(QString k, bool p) const
{
  Computer *c;

  try
  {
    c = dynamic_cast<Computer *>(&box->get(k.toStdString()));

    if (!c) throw ModelBadTypeException();
  }
  catch (std::exception &e)
  {
    emit err(e.what());
    return;
  }

  c->setPortatile(p);

  emit notify();
}

void Model::setSmartphone(QString k, bool ip) const
{
  Smartphone *s;

  try
  {
    s = dynamic_cast<Smartphone *>(&box->get(k.toStdString()));

    if (!s) throw ModelBadTypeException();
  }
  catch (std::exception &e)
  {
    emit err(e.what());
    return;
  }

  s->setiPhone(ip);

  emit notify();
}
