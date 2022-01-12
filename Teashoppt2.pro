QT += core gui
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Accesory.cpp \
    Product.cpp \
    ProductController.cpp \
    Repository.cpp \
    Tea.cpp \
    UI.cpp \
    gui.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Accesory.h \
    Product.h \
    ProductController.h \
    Repository.h \
    Tea.h \
    Tests.h \
    UI.h \
    Utils.h \
    gui.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Downloads/Screenshot from 2021-06-02 23-29-11.jpg \
    ../Downloads/jenny-lelong-coffee-shop.webp \
    Input.csv
