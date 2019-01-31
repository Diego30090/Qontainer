#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <QObject>
#include <QVector>
//#include "controller.hpp"
#include "Gerarchia.hpp"
#include "DeepPtr.hpp"
#include "Container.hpp"

class Controller;

class Model : public QObject
{
  Q_OBJECT

private:
  Container<DeepPtr<Articolo>, std::string> box;

  QVector<Controller * const> subscription;

public:
  explicit Model(QObject *parent = nullptr);

  // Metodi per accedere alla subscription
  //void attach(Controller * const);
  //void detach(Controller * const);

  // Metodi per la richiesta dei dati

signals:
  void notify();

public slots:


};

#endif // MODEL_HPP
