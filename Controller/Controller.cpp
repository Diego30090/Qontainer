#include "Controller.hpp"

Controller::Controller(Model *m, View *view, QObject *parent)
  : QObject(parent), linkedModel(m), linkedView(view)
{
  connect(m, SIGNAL(notify()), this, SLOT(modelUpdate()));
}
