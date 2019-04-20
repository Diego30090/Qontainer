#include "View.hpp"

View::View(QWidget *parent) : QWidget(parent), linkedController(nullptr) {}

View::~View()
{
  delete linkedController;
}

Controller * View::getController()
{
  return linkedController;
}

void View::setController(Controller *c)
{
  linkedController = c;
}
