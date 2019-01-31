#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <QWidget>
#include <QToolBar>
#include <QTableWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QAction>

class MainView : public QWidget
{
  Q_OBJECT

public:
  explicit MainView(QWidget *parent = nullptr);

signals:
  void controllerSalva();
  void controllerSalvaConNome();
  void controllerApriBox();
  void controllerChiudiBox();
  void controllerNuovoBox();
  void controllerRicercaArticolo();
  void controllerNuovoArticolo();
  void controllerEliminaArticolo();


private slots:
  void toolbarAction(QAction *);

public slots:
  //void update();
};

#endif // MAINVIEW_HPP
