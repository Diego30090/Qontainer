#-------------------------------------------------
#
# Project created by QtCreator 2019-01-17T10:04:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qontainer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11


HEADERS += \
        \ # Model
        $$PWD/Model/Container.hpp \
        $$PWD/Model/ContainerException.hpp \
        $$PWD/Model/DeepPtr.hpp \
        $$PWD/Model/Gerarchia.hpp \
        $$PWD/Model/Model.hpp \
        $$PWD/Model/ModelException.hpp \
        \ # Controller
        $$PWD/Controller/Controller.hpp \
        $$PWD/Controller/MainController.hpp \
        $$PWD/Controller/CDController.hpp \
        \ # View
        $$PWD/View/View.hpp \
        $$PWD/View/MainView.hpp \
        $$PWD/View/CDView.hpp \
        \ # YAML
        $$PWD/yaml-cpp/*.h

SOURCES += \        
        main.cpp \
        \ # Model
        $$PWD/Model/Gerarchia.cpp \
        $$PWD/Model/Model.cpp \
        $$PWD/Model/ModelException.cpp \
        $$PWD/Model/ContainerException.cpp \
        \ # Controller
        $$PWD/Controller/Controller.cpp \
        $$PWD/Controller/MainController.cpp \
        $$PWD/Controller/CDController.cpp \
        \ # View
        $$PWD/View/View.cpp \
        $$PWD/View/MainView.cpp \
        $$PWD/View/CDView.cpp \
        \ # YAML
        $$PWD/yaml-cpp/*.cpp

INCLUDEPATH += \
        $$PWD/Model \
        $$PWD/Controller \
        $$PWD/View

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
