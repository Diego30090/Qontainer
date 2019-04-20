#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <QToolBar>
#include <QTableWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QAction>
#include "View.hpp"
#include "MainController.hpp"

class MainView : public View
{
  Q_OBJECT

  friend MainController;

private:
  QHBoxLayout *hl;
  QWidget *sideWindow;

  virtual MainController * makeController() override;

public:
  explicit MainView(QWidget *parent = nullptr);

  virtual void initialize() override;

signals:
//  void salva();
//  void salvaConNome();
//  void apriBox();
//  void chiudiBox();
//  void nuovoBox();
//  void ricercaArticolo();
//  void nuovoArticolo();
//  void eliminaArticolo();
  void toolBarActionTriggered(QAction *);

private slots:
  void addSideWindow(QWidget *);

public slots:
  void update(QList<QString>);
};

#endif // MAINVIEW_HPP
