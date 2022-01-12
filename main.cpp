#include <QDir>
#include <QApplication>
#include <QStandardPaths>
#include <QString>
#include <QDebug>   // this is cout
#include "UI.h"
#include "mainwindow.h"
#include "gui.h"
#include <QPalette>


    int main(int argc, char *argv[])
    {
        QApplication a(argc, argv);
       //MainWindow m;
        //m.show;
        ProductController serv;
        serv.loadFromFile();

//        qDebug() << "aa";
        for(auto p : serv.getAllProducts()){
            qDebug() << p->getId() << " ";
        }

        GUI gui{serv};
        gui.show();
        gui.setWindowTitle("Welcome to my Teashop!");

        return a.exec();
    }



