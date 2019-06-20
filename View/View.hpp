#ifndef VIEW_HPP
#define VIEW_HPP

#include <QWidget>

class Model;
class Controller;

class View : public QWidget
{
  Q_OBJECT

private:
  Controller *linkedController;

  virtual Controller * makeController(Model *m) = 0;

public:
  explicit View(QWidget *parent = nullptr);
  virtual ~View();

  virtual Controller * getController();

  static void initialize(View *v, Model *m);
};

#endif // VIEW_HPP
