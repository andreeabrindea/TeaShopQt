#include "teashopgui.h"
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <qlayout.h>
#include <qgridlayout.h>
#include <vector>
#include "ProductController.h"
#include <qmessagebox.h>
#include <vector>
#include <qwindow.h>
#include "QtPrintSupport/qprinter.h"
#include "QCborParserError"


using namespace std;

Teashopgui::Teashopgui(ProductController& controller): controller {controller}
{
    this->initGui(); //initialize gui
    this->populateList();
    this->connectSignalAndSlots();
}

void Teashopgui::initGui()
{

    //alocate memory
    this->productsListWidget = new QListWidget{};
    this->NameLineEdit = new QLineEdit{};
    this->IdLineEdit = new QLineEdit{};
    this->addbutton = new QPushButton{ "Add" };
    this->deleteButton = new QPushButton{ "Delete" };
    this->listButton = new QPushButton{ "List" };
    this->BarChartButton = new QPushButton{ "Chart" };

    //build layout
    QVBoxLayout* mainLayout = new QVBoxLayout{ this }; //current widget

    mainLayout->addWidget(this->productsListWidget); ///created the list of victims

    QFormLayout* ProductsDetailsLayout = new QFormLayout{};
    ProductsDetailsLayout->addRow("Id", this->IdLineEdit);
    ProductsDetailsLayout->addRow("Name", this->NameLineEdit);
    ProductsDetailsLayout->addRow("Product type: ", this->ProductTypeLineEdit);;

    mainLayout->addLayout(ProductsDetailsLayout); //add layout to the main layout

    //buttons
    QGridLayout* buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(this->addbutton, 0, 0);
    buttonsLayout->addWidget(this->deleteButton, 0, 1);
    buttonsLayout->addWidget(this->listButton, 1, 1);
    buttonsLayout->addWidget(this->BarChartButton, 2, 0);

    mainLayout->addLayout(buttonsLayout);

    //QFileDialog::getOpenFileNames(this, "Select a file to open...", QDir::homePath());



}

//after each operation we are going to refresh the list
//so this function is called in other methods too
void Teashopgui::populateList()
{
    this->productsListWidget->clear();

    vector<Product> allProducts = this->controller.getAllProducts();
    for (Product& product : allProducts) {
        this->productsListWidget->addItem(QString::fromStdString(to_string(product.getId()) + " - " + product.getName() + " - " + product.getTypeProduct() ));
    }
}


void Teashopgui::connectSignalAndSlots()
{
    ///............... widget, adress of signal, slot
    QObject::connect(this->productsListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0) {
            return;
        }
        Product product = this->controller.getAllProducts()[selectedIndex]; // we need to check if the selectedIndex is > size
        this->IdLineEdit->setText(QString::fromStdString(to_string(product.getId())));
        this->NameLineEdit->setText(QString::fromStdString(product.Name()));
        this->ProductTypeLineEdit->setText(QString::fromStdString(product.getProductType()));
        });

    QObject::connect(this->addbutton, &QPushButton::clicked, this, &Teashopgui::addProduct);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &Teashopgui::deleteProduct);
    QObject::connect(this->BarChartButton, &QPushButton::clicked, this, &Teashopgui::barChart);
}

//using single selection
int Teashopgui::getSelectedIndex() const
{
    QModelIndexList selectedIndexes = this->productsListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.size() == 0) {
        this->IdLineEdit->clear();
        this->NameLineEdit->clear();
        this->ProductTypeLineEdit->clear();
        return -1; //nothing is selected
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void Teashopgui::addProduct()
{
    string name = this->NameLineEdit->text().toStdString();
    string productType = this->ProductTypeLineEdit->text().toStdString();
    int id = stoi(this->IdLineEdit->text().toStdString());
    this->controller.addaNewProduct(id, name, productType);
    this->populateList();

    int lastElement = this->controller.getAllProducts().size() - 1;
    this->productsListWidget->setCurrentRow(lastElement);

}

void Teashopgui::deleteProduct()
{
    int selectedIndex = this->getSelectedIndex();
    if (selectedIndex < 0) {
        QMessageBox::critical(this, "Error", "No product selected");
        return;
    }
    Product product = this->controller.getAllProducts()[selectedIndex];
    this->controller.deleteProduct(product.getName());

    this->populateList();
}


//void Teashopgui::barChart()
//{
//    QCustomPlot *customPlot = new QCustomPlot();

//    // set dark background gradient:
//    QLinearGradient gradient(0, 0, 0, 400);
//    gradient.setColorAt(0, QColor(90, 90, 90));
//    gradient.setColorAt(0.38, QColor(10, 100, 50, 70));
//    gradient.setColorAt(1, QColor(70, 70, 70));
//    customPlot->setBackground(QBrush(gradient));

//    // create empty bar chart objects:
//    QCPBars* fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

//    fossil->setAntialiased(false);

//    fossil->setStackingGap(1);
//    // set names and colors:
//    fossil->setName("Name Of The Victim");
//    fossil->setPen(QPen(QColor(0, 0, 255, 127).lighter(170)));
//    fossil->setBrush(QColor(0, 0, 255, 127));


//    // prepare x axis with country labels:
//    QVector<double> ticks;
//    QVector<QString> labels;
//    vector<Product> allProducts = this->controller.getAllProducts();
//    int count = 0;
//    for (Product& product : allProducts) {
//        count += 1;
//        ticks << count;
//        labels << QString::fromStdString(product.getName());
//    }
//    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
//    textTicker->addTicks(ticks, labels);
//    customPlot->xAxis->setTicker(textTicker);
//    customPlot->xAxis->setTickLabelRotation(60);
//    customPlot->xAxis->setSubTicks(false);
//    customPlot->xAxis->setTickLength(0, 4);
//    customPlot->xAxis->setRange(0, 8);
//    customPlot->xAxis->setBasePen(QPen(Qt::white));
//    customPlot->xAxis->setTickPen(QPen(Qt::white));
//    customPlot->xAxis->grid()->setVisible(true);
//    customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
//    customPlot->xAxis->setTickLabelColor(Qt::white);
//    customPlot->xAxis->setLabelColor(Qt::white);

//    // prepare y axis:
//    customPlot->yAxis->setRange(0, 100);
//    customPlot->yAxis->setPadding(5); // a bit more space to the left border
//    customPlot->yAxis->setLabel("Age of death");
//    customPlot->yAxis->setBasePen(QPen(Qt::white));
//    customPlot->yAxis->setTickPen(QPen(Qt::white));
//    customPlot->yAxis->setSubTickPen(QPen(Qt::white));
//    customPlot->yAxis->grid()->setSubGridVisible(true);
//    customPlot->yAxis->setTickLabelColor(Qt::white);
//    customPlot->yAxis->setLabelColor(Qt::white);
//    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
//    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

//    // Add data:
//    QVector<double> nameData;
//    vector<Product> AllProducts = this->controller.getAllProducts();
//    int count20 = 0;
//    for (Product& product : AllProducts) {
//        if (product.getId() >= 0 && product.getId() < 20)
//            nameData << 1.8 * 10.5;
//    }
//    fossil->setData(ticks, nameData);


//    // setup legend:
//    customPlot->legend->setVisible(true);
//    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignHCenter);
//    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
//    customPlot->legend->setBorderPen(Qt::NoPen);
//    QFont legendFont = font();
//    legendFont.setPointSize(10);
//    customPlot->legend->setFont(legendFont);
//    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

//    customPlot->show();
//}
