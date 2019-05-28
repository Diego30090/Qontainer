#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include "Controller.hpp"

class MainController : public Controller
{
public:
  explicit MainController(QWidget *, QObject * = nullptr);

public slots:
  virtual void modelUpdate() override;
};

#endif // MAINCONTROLLER_HPP
