#include "View.hpp"

View::View(QWidget *parent) : QWidget(parent), linkedController(nullptr)
{
  setWindowFlags(Qt::Window);
}

Controller * View::getController()
{
  return linkedController;
}

void View::initialize(View *v, Model *m)
{
  v->linkedController = v->makeController(m);
}
