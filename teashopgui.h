#pragma once
#include <qwidget.h>
#include "ProductController.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class Teashopgui : public QWidget
{
private:
    ProductController& controller; //reference to service

    //graphical elements:
    QListWidget* productsListWidget;
    QLineEdit* IdLineEdit, * NameLineEdit, * ProductTypeLineEdit;
    QPushButton* addbutton, * deleteButton, *listButton, *BarChartButton;


public:
    Teashopgui(ProductController& controller);
private:
    void initGui();
    void populateList();
    void connectSignalAndSlots();   //function that populates the name, etc, layouts
    //void barChart();
    int getSelectedIndex() const;

    //CRUD
    void addProduct();
    void deleteProduct();
    void listProductFiles();
};
