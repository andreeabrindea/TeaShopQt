#pragma once
#include <string>
#include <cstring>
#include <vector>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;


enum class ProductType
{
    TEA,
    ACCESORY
};

// Class defining q product. Product information: id, name and type.
class Product {

private:
    int m_id;

protected:
    std::string m_name;
    ProductType m_typeProduct;

public:
    Product(int id, const string &name, ProductType typeProduct); // Constructor
    Product() = default;

    // Setters:
    void setId(int id);
    void setName(const string &name);
    void setTypeProduct(ProductType typeProduct);
    std::string productToString();


    // Getters:
    int getId() const;
    const string &getName() const;
    ProductType getTypeProduct() const;


    // overloading operators
    friend std::ostream& operator<<(std::ostream& stream, const Product& product);
    //friend std::istream& operator>>(std::istream& stream, Product& product);
    friend bool operator==(const Product&, const Product&);

    virtual void display(ostream& os) const;


};


