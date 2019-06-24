#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <QToolBar>
#include <QTableWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QHeaderView>
#include "View.hpp"
#include "MainController.hpp"

class MainView : public View
{
  Q_OBJECT

private:
  QHBoxLayout *hl;
  QTableWidget *tab;

  MainController * makeController(Model *m) override;

public:
  explicit MainView(QWidget *parent = nullptr);

  MainController * getController() override;

signals:
  void toolBarTriggered(QAction *);
  void tableTriggered(QString);

private slots:
  void _tableTriggered(int);

public slots:
  void updateTable(QList<QString>);
};



#endif // MAINVIEW_HPP
