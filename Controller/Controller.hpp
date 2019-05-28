#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>

class Controller : public QObject
{
  Q_OBJECT

private:
  QWidget *linkedView;

public:
  explicit Controller(QWidget *view, QObject *parent = nullptr);
  virtual ~Controller();

signals:

public slots:
  virtual void modelUpdate() = 0;

};

#endif // CONTROLLER_HPP
