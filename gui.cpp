#include "gui.h"
#include <QLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <vector>
#include <QMessageBox>
#include <QCoreApplication>
#include <QKeySequence>
#include <QDebug>

using namespace std;

GUI::GUI(ProductController &s) : controller{s}
{
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void GUI::initGUI()
{
    this->productsListWidget = new QListWidget{};
    this->idLineEdit = new QLineEdit{};
    this->nameLineEdit = new QLineEdit{};
    this->typeLineEdit = new QLineEdit{};
    this->addButton = new QPushButton{"Add"};
    this->deleteButton = new QPushButton{"Delete"};
    this->undoButton = new QPushButton{"Undo"};
    this->redoButton = new QPushButton{"Redo"};

    QVBoxLayout* mainLayout = new QVBoxLayout{this};
    mainLayout->addWidget(this->productsListWidget);

    QFormLayout* productDetailsLayout = new QFormLayout{};
    productDetailsLayout->addRow("ID", this->idLineEdit);
    productDetailsLayout->addRow("Name", this->nameLineEdit);
    productDetailsLayout->addRow("Type", this->typeLineEdit);

    mainLayout->addLayout(productDetailsLayout);

    QGridLayout* buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->deleteButton, 0,1);
    buttonsLayout->addWidget(this->undoButton, 1, 0);
    buttonsLayout->addWidget(this->redoButton, 1,1);

    mainLayout->addLayout(buttonsLayout);
}

void GUI::populateList()
{
    this->productsListWidget->clear();

    vector<Product*> allProducts = this->controller.getAllProducts();
    for(auto s: allProducts)
        this->productsListWidget->addItem(QString::fromStdString(s->getId()+ "." + s->getName()+ " " + (s->getTypeProduct() == ProductType::TEA ? "TEA" : "ACCESSORY")));

}

void GUI::connectSignalsAndSlots()
{
    QObject::connect(this->productsListWidget, &QListWidget::itemSelectionChanged, [this](){
            int selectedIndex = this->getSelectedIndex();
            if(selectedIndex < 0)
                return;
            Product* p = this->controller.getAllProducts()[selectedIndex];
            this->idLineEdit->setText(QString::fromStdString(to_string(p->getId())));
            this->nameLineEdit->setText(QString::fromStdString(p->getName()));
            this->typeLineEdit->setText(QString::fromStdString(p->getTypeProduct()== ProductType::TEA ? "TEA" : "ACCESSORY"));

    });

   QObject::connect(this->addButton, &QPushButton::clicked,this, &GUI::addProduct);
   QObject::connect(this->deleteButton, &QPushButton::clicked, this, &GUI::deleteProduct);
   QObject::connect(this->undoButton, &QPushButton::clicked, this, &GUI::undoAction);
   QObject::connect(this->redoButton, &QPushButton::clicked, this, &GUI::redoAction);

}

int GUI::getSelectedIndex() const
{
    QModelIndexList selectedIndexes = this->productsListWidget->selectionModel()->selectedIndexes();
    if(selectedIndexes.size()==0)
    {
        this->idLineEdit->clear();
        this->nameLineEdit->clear();
        this->typeLineEdit->clear();
        return -1;
    }
     int selectedIndex = selectedIndexes.at(0).row();
     return selectedIndex;
}

void GUI::addProduct()
{


    int id = stoi(this->idLineEdit->text().toStdString());
    string name = this->nameLineEdit->text().toStdString();
    string type = this->typeLineEdit->text().toStdString();

    this->controller.addaNewProduct(new Product(id, name, type == "TEA" ? ProductType::TEA : ProductType::ACCESORY));
    this->populateList();

    int lastElement = this->controller.getAllProducts().size()-1;
    this->productsListWidget->setCurrentRow(lastElement);
}

void GUI::deleteProduct()
{
    int selectedIndex = this->getSelectedIndex();
    if(selectedIndex < 0)
    {
        QMessageBox::critical(this, "Error", "No product was selected!");
        return;
    }
    Product* p = this->controller.getAllProducts()[selectedIndex];
    this->controller.deleteProductById(p->getId());

    this->populateList();
}

void GUI::undoAction()
{
   this->controller.undo();
    this->populateList();

}

void GUI::redoAction()
{
    this->controller.redo();
    this->populateList();

}

void GUI::keyPressEvent(QKeyEvent *event)
{if(event->type()==QKeyEvent::KeyPress){
        if(event->matches(QKeySequence::Undo))
        {
            //QCoreApplication::undo();
            qDebug()<<"Ctrl + Z pressed!";
        }
    else
            if(event->matches(QKeySequence::Redo))
                qDebug()<<"Ctrl + Shift + Z pressed!";
    }
}
