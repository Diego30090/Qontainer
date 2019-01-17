#include "widget.h"
#include "Container.hpp"
#include <QApplication>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  auto *dat = new Container<string>;

  dat->put("a", "prima entry");
  dat->put("b", "seconda entry");
  dat->put("c", "terza entry");

  std::cout << dat->get("a") << endl << dat->get("b") << endl << dat->get("c") << endl;

//  QApplication a(argc, argv);
//  Widget w;
//  w.show();

//  return a.exec();
}
