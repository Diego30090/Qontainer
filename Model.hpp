#ifndef MODEL_HPP
#define MODEL_HPP

#include <QObject>
#include <QVector>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QFile>
#include <QString>
#include "ModelException.hpp"
#include "Gerarchia.hpp"
#include "DeepPtr.hpp"
#include "Container.hpp"

class Controller;

class Model : public QObject
{
  Q_OBJECT

private:
  static const unsigned int OPEN_FILE_ATTEMPTS = 50;

  QString containerPath;
  Container<DeepPtr<Articolo>, std::string> *box;

public:
  explicit Model(QObject *parent = nullptr);
  ~Model();

  // Metodi per la gestione dei dati
  const DeepPtr<Articolo> getArticolo(QString) const;

  QList<QString> getAllArticolo() const;
  QList<QString> getArticoloByNome(QString) const;
  QList<QString> getArticoloByCostoMax(float) const;
  QList<QString> getArticoloByPrezzoMax(float, bool) const;
  QList<QString> getArticoloBySPIMin(unsigned int) const;

  QList<QString> getAllMedia() const;
  QList<QString> getMediaByAnno(unsigned int) const;

  QList<QString> getAllCD() const;
  QList<QString> getCDByArtista(QString) const;
  QList<QString> getCDIfCompilation(bool) const;

  QList<QString> getAllElettronica() const;
  QList<QString> getElettronicaIfUsato(bool) const;
  QList<QString> getElettronicaByWarranty(bool) const;

  QList<QString> getAllComputer() const;
  QList<QString> getComputerIfPortatile(bool) const;

  QList<QString> getAllSmartphone() const;
  QList<QString> getSmartphoneIfiPhone(bool) const;

//  enum priceFilter { uguale, diverso, maggiore, minore, maggioreUguale, minoreUguale };
//  QList<QString> filterByPrice(QList<QString>, priceFilter, float);

  // Metodi per la gestione dei box
  bool isOpen() const;

  void newBox();
  void openBox();
  void closeBox();
  void saveBox() const;

  void changeBoxPath(QString);

signals:
  void notify() const;
  void err(QString) const;

public slots:
  // Metodi per la gestione dei dati
  void insert(QString, const DeepPtr<Articolo> &);
  void remove(QString);
  void remove(QList<QString>);

  void setArticolo(QString, QString, float, unsigned int) const;

  void setMedia(QString, unsigned int) const;

  void setCD(QString, QString, bool) const;

//  void setElettronica(QString, bool) const;

//  void setComputer(QString, bool) const;

//  void setSmartphone(QString, bool) const;
};

#endif // MODEL_HPP
