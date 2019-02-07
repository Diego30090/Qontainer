#ifndef MODEL_HPP
#define MODEL_HPP

#include <QObject>
#include <QVector>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QFile>
#include <QString>
#include "Gerarchia.hpp"
#include "DeepPtr.hpp"
#include "Container.hpp"

class Controller;

class ModelException : public std::exception
{
  virtual const char * what() const noexcept; // overriding
};

class ModelBoxNotOpenException : public ModelException
{
  virtual const char * what() const noexcept; // overriding
};

class ModelBoxNotClosedException : public ModelException
{
  virtual const char * what() const noexcept; // overriding
};

class ModelBoxPathNotSetException : public ModelException
{
  virtual const char * what() const noexcept; // overriding
};

class ModelFileNotAvailableException : public ModelException
{
  virtual const char * what() const noexcept; // overriding
};

class ModelBadTypeException : public ModelException
{
  virtual const char * what() const noexcept; // overriding
};


class Model : public QObject
{
  Q_OBJECT

private:
  static const unsigned int OPEN_FILE_ATTEMPTS = 50;

  QString containerPath;
  Container<DeepPtr<Articolo>, std::string> *box;

public:
  explicit Model(QObject *parent = nullptr);

  // Metodi per la gestione dei dati
  const DeepPtr<Articolo> getArticolo(QString) const;

  QList<QString> getAllArticolo() const;
  QList<QString> getArticoloByNome(QString) const;
  QList<QString> getArticoloByPrezzoListino(float) const;
  QList<QString> getArticoloBySPI(unsigned int) const;

  QList<QString> getAllAlbum() const;
  QList<QString> getAlbumByArtista(QString) const;
  QList<QString> getAlbumIfCompilation(bool) const;

  QList<QString> getAllElettBruno() const;
  QList<QString> getElettBrunoIfUsato(bool) const;

  QList<QString> getAllComputer() const;
  QList<QString> getComputerIfPortatile(bool) const;

  QList<QString> getAllSmartphone() const;
  QList<QString> getSmartphoneIfExtWarr(bool) const;

  enum priceFilter { uguale, diverso, maggiore, minore, maggioreUguale, minoreUguale };
  QList<QString> filterByPrice(QList<QString>, priceFilter, float);

  // Metodi per la gestione dei box
  bool isOpen() const;

  void newBox();
  void openBox();
  void closeBox();
  void saveBox() const;

  void changeBoxPath(QString);

signals:
  void notify() const;

public slots:
  // Metodi per la gestione dei dati
  void insert(const DeepPtr<Articolo> &);
  void remove(QString);
  void remove(QList<QString>);

  void setArticoloNome(QString, QString) const;
  void setArticoloPrezzoListino(QString, float) const;
  void setArticoloSPI(QString, unsigned int) const;
//  void setArticoloImgPath(QString, QString) const;

  void setAlbumArtista(QString, QString) const;
  void setAlbumCompilation(QString, bool) const;

  void setElettBrunoUsato(QString, bool) const;

  void setComputerPortatile(QString, bool) const;

  void setSmartphoneExtWarr(QString, bool) const;
};

#endif // MODEL_HPP
