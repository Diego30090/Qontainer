#ifndef SEARCHVIEW_HPP
#define SEARCHVIEW_HPP

#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QCloseEvent>
#include "View.hpp"
#include "SearchController.hpp"

class SearchView : public View
{
  Q_OBJECT

private:
  QGroupBox *checkA;
  QLineEdit *nome;
  QLineEdit *costoMax;
  QLineEdit *prezzoMax;

  QGroupBox *checkCD;
  QLineEdit *annoCD;
  QLineEdit *artista;
  QCheckBox *compilation;

  QGroupBox *checkC;
  QCheckBox *usatoC;
  QCheckBox *portatile;

  QGroupBox *checkS;
  QCheckBox *usatoS;
  QCheckBox *iphone;

  SearchController * makeController(Model *m) override;

public:
  explicit SearchView(QWidget *parent);
  
  SearchController * getController() override;

protected:
  void closeEvent(QCloseEvent *) override;

signals:
  void searchStart(bool, QString, QString, QString, // Articolo
                   bool, QString, QString, bool,    // CD
                   bool, bool, bool,                // Computer
                   bool, bool, bool,                // Smartphone
                   bool);                           // Rimozione
  void closing();
  
private slots:
  void _checkedA(bool);
  void _checkedCD(bool);
  void _checkedC(bool);
  void _checkedS(bool);

public slots:
  void searchStart();
  void deleteSearched();
};

#endif // SEARCHVIEW_HPP
