#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>

class Controller : public QObject
{
  Q_OBJECT

private:

public:
  explicit Controller(QObject *parent = nullptr);

signals:
  void modelSearch(std::string);

public slots: 
};

#endif // CONTROLLER_HPP
