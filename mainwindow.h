#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets/QMainWindow>
#include <QApplication>
#include "ProductController.h"
#include <QtGui>
#include <QLayoutItem>
#include <qlayout.h>
#include <qlabel.h>
#include <qstackedwidget.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qmessagebox.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <QMainWindow>
#include <QLabel>
#include "ui_mainwindow.h"
#include <qstackedwidget.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
