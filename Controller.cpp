#include "Controller.hpp"

Controller::Controller(QWidget *view, QObject *parent) : QObject(parent), linkedView(view) {}

Controller::~Controller() {}
