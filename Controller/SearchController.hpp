#ifndef SEARCHCONTROLLER_HPP
#define SEARCHCONTROLLER_HPP

#include "Controller.hpp"

class SearchController : public Controller
{
  Q_OBJECT

private:
  static QList<QString> join(const QList<QString> &, const QList<QString> &);

public:
  explicit SearchController(Model *m, View *v);

signals:
  void searchResult(QList<QString>);
  void viewClosing();
  void viewSearchStart();
  
public slots:
  void modelUpdate() override;
  
  void viewSearchStart(bool, QString, QString, QString,
                       bool, QString, QString, bool,
                       bool, bool, bool,
                       bool, bool, bool,
                       bool);
};

#endif // SEARCHCONTROLLER_HPP
