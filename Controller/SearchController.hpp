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
  
public slots:
  virtual void modelUpdate() override;
  
  void viewSearchStart(bool, QString, QString, QString, // Articolo
                       bool, QString, QString, bool,    // CD
                       bool, bool, bool,                // Computer
                       bool, bool, bool);               // Smartphone
};

#endif // SEARCHCONTROLLER_HPP
