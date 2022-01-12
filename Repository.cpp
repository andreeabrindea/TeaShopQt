#pragma once
#include <algorithm>
#include "Repository.h"
#include <utility>
#include <vector>
#include <fstream>
#include <QDebug>
#include <QFile>
#include <QDir>

int Repository::searchProduct(int id) {
    for(int it = 0; it < this->m_database.size(); ++it){
        if(this->m_database.at(it)->getId() == id){
            return it;
        }
    }
    return 0;
}

bool Repository::addProduct(Product* a) {
    if(searchProduct(a->getId()) != 0 && !this->m_database.empty())
        return false;
    m_database.push_back(a);
    return true;
}

Product Repository::deleteProduct(int id) {

    int it = searchProduct(id);
    if (it == this->m_database.size())
        throw std::string("Nonexistent product!");

    Product product= reinterpret_cast<Product &&>(this->m_database[it]);
    this->m_database.erase(this->m_database.begin()+it);
    return product;
}


bool Repository::operator==(const Repository &rhs) const {
    return m_database == rhs.m_database;
}

bool Repository::operator!=(const Repository &rhs) const {
    return !(rhs == *this);
}

void Repository::setMDatabase(const vector<Product *> &mDatabase) {
    m_database = mDatabase;
}

Repository &Repository::operator=(const Repository &other) {
    // Guard self assignment
    if (this == &other)
        return *this;

    std::copy(other.m_database.begin(), other.m_database.end(), this->m_database.begin());
    return *this;
}

void Repository::loadFromFile() {
//    fstream inputFile;
    QFile inputFile("Input.csv");
    if(!inputFile.open(QIODevice::ReadWrite)){
        qDebug() << "error";
    }

    QTextStream in(&inputFile);
//    QString line = in.readLine();
    while (!in.atEnd()) {
       QString line = in.readLine();
       QStringList tokens = line.split(",");

       int id = tokens[0].toInt();;
       string name = tokens[1].toUtf8().constData();
       ProductType typeProduct = tokens[2] == "TEA" ? ProductType::TEA : ProductType::ACCESORY;

       addProduct(new Product(id, name, typeProduct));
    }

//    while (getline(inputFile, line))
//    {
//        vector<string> tokens;
//        stringstream ss(line);
//        string token;
//        while (getline(ss, token, ','))
//            tokens.push_back(token);


//        int id = (stoi(tokens[0]));
//        string name = (tokens[1]);
//        ProductType typeProduct = tokens[2] == "TEA" ? ProductType::TEA : ProductType::ACCESORY;

//        addProduct(new Product(id, name, typeProduct));
//    }
    inputFile.close();
}

void Repository::saveToFile() {

    fstream fout;
    try
    {
        fout.open("Output.csv", ios::out);
    }
    catch (const exception&)
    {
        cout << "\n FIle can't be open!";
    }

    for (auto i = 0; i < m_database.size(); i++)
        fout <<ProductToCSV(m_database[i]) << endl;
    fout.close();
}

string Repository::ProductToCSV(Product *p) {
    string result;
    result = to_string(p->getId()) + ',' + p->getName() + ',' + (p->getTypeProduct() == ProductType::TEA ? "TEA" : "ACCESORY");
    return result;
}

ostream& Repository::display(ostream &os, bool (*filterFunction)(Product *)) {
for(int i=0; i<m_database.size(); i++)
    if(filterFunction(m_database[i])==true)
        os<<*m_database[i]<<endl;
    return os;
}



