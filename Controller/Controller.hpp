#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include "Model.hpp"
#include "View.hpp"

class Controller : public QObject
{
  Q_OBJECT

protected:
  Model *linkedModel;
  View *linkedView;

public:
  explicit Controller(Model *m, View *view, QObject *parent = nullptr);
  virtual ~Controller() = default;

signals:

public slots:
  virtual void modelUpdate() = 0;
};

#endif // CONTROLLER_HPP
