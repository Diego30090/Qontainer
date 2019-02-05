#ifndef MODEL_HPP
#define MODEL_HPP

#include <QObject>
#include <QVector>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
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

class ModelFileNotAvailableException : public ModelException
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

//  QVector<Controller const * const> subscription;
//  void notify();

public:
  explicit Model(QObject *parent = nullptr);

  // Metodi per la gestione dei dati
  QList<DeepPtr<Articolo>> getData() const;

  bool isOpen() const;

signals:
  void notify();

public slots:
  // Metodi per la gestione dei box
  void newBox();
  void openBox();
  void closeBox();
  void saveBox() const;
  void changeBoxPath(QString);
  void insert(const DeepPtr<Articolo> &);

//  // Metodi per la gestione della subscription
//  void attach(Controller const * const);
//  void detach(Controller const * const);

};

#endif // MODEL_HPP
