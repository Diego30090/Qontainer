#include "View.hpp"

View::View(QWidget *parent) : QWidget(parent), linkedController(nullptr) {}

View::~View()
{
  if (linkedController)
    delete linkedController;
}

Controller * View::getController()
{
  return linkedController;
}

void View::initialize(View *v, Model *m)
{
  v->linkedController = v->makeController(m);
}
