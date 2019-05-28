#ifndef VIEW_HPP
#define VIEW_HPP

#include <QWidget>

//class Model;
class Controller;

class View : public QWidget
{
  Q_OBJECT

private:
  Controller *linkedController;

  virtual Controller * makeController() = 0;

public:
  explicit View(QWidget *parent = nullptr);
  virtual ~View();

  Controller * getController();
  void setController(Controller *);

  virtual void initialize() = 0;
};

#endif // VIEW_HPP
