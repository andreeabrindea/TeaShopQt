#pragma once
#include <string>
#include <cstring>
#include <utility>
#include <vector>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Product.h"
#include <stack>


class Repository {
private:
    std::vector<Product*> m_database;
    std::stack<std::pair<Product*, int>> undo;
    std::stack<std::pair<Product*, int>> redo;

    //Searches for a product in the database
    int searchProduct(int id);

public:

    //Adds a new product to the database
    bool addProduct(Product* p);

    //Deletes a product from the database
    Product deleteProduct(int id);

    //Returns the database
    vector<Product *> returnDatabase() { return this->m_database; }

    //Set the database
    void setMDatabase(const vector<Product *> &mDatabase);

    bool operator==(const Repository &rhs) const;
    bool operator!=(const Repository &rhs) const;
    Repository& operator=(const Repository&);

    ostream& display(ostream &os, bool(*filterFunction)(Product*));

    string ProductToCSV(Product *p);

    //Load the data from a CSV file
    void loadFromFile();

    //Saves the database in a CSV file
    void saveToFile();

};

