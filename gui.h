#pragma once
#include <qwidget.h>
#include "ProductController.h"
#include "qlistwidget.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include <QKeyEvent>

class GUI : public QWidget
{
private:
    ProductController& controller;

    // graphical elements:
    QListWidget* productsListWidget;
    QLineEdit* idLineEdit, *nameLineEdit, *typeLineEdit;
    QPushButton* addButton, *deleteButton, *undoButton, *redoButton;

public:
    GUI(ProductController& s);

private:
    void initGUI();
    void populateList();
    void connectSignalsAndSlots();
    int getSelectedIndex() const;
    void addProduct();
    void deleteProduct();
    void undoAction();
    void redoAction();
    void keyPressEvent(QKeyEvent *event);

};
