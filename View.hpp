#ifndef VIEW_HPP
#define VIEW_HPP

#include <QWidget>

class Model;
class Controller;

class View : public QWidget
{
  Q_OBJECT

private:
  Model *linkedModel;
  Controller *linkedController;

public:
  explicit View(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // VIEW_HPP
