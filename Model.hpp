#ifndef MODEL_HPP
#define MODEL_HPP

#include <QObject>
#include <QVector>
#include "Gerarchia.hpp"
#include "DeepPtr.hpp"
#include "Container.hpp"

class Controller;

class Model : public QObject
{
  Q_OBJECT

private:
  QString containerPath;
  Container<DeepPtr<Articolo>, std::string> *box;

//  QVector<Controller const * const> subscription;
//  void notify();

public:
  explicit Model(QObject *parent = nullptr);

  // Metodi per la gestione dei dati
  QList<DeepPtr<Articolo>> getData() const;

signals:
  void notify();

public slots:
  // Metodi per la gestione dei box
  void newBox();
  void deleteBox();
  void saveBox() const;
  void saveBoxAs() const;

//  // Metodi per la gestione della subscription
//  void attach(Controller const * const);
//  void detach(Controller const * const);

};

#endif // MODEL_HPP
