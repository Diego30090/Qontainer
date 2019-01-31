#include "Model.hpp"

Model::Model(QObject *parent) : QObject(parent), containerPath(QStringLiteral("")), box(nullptr) {}

void Model::newBox()
{
  box = new Container<DeepPtr<Articolo>, std::string>;
  emit notify();
}

void Model::deleteBox()
{
  delete box;
  emit notify();
}

void Model::saveBox() const
{

}

void Model::saveBoxAs() const
{

}

//void Model::attach(Controller const * const c)
//{
//  subscription.push_back(c);
//}

//void Model::detach(Controller const * const c)
//{
//  bool found = false;

//  for(auto seek = subscription.begin(); !found && seek != subscription.end(); ++seek)
//    {
//      if (c == *seek)
//        {
//          subscription.erase(seek);
//          found = true;
//        }
//    }
//}
