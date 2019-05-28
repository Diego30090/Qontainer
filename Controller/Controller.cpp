#include "Controller.hpp"

Controller::Controller(QWidget *view, QObject *parent) : QObject(parent), linkedView(view)
{
  //connect()
}

Controller::~Controller() {}
