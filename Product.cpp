
#include "Product.h"

void Product::setId(int id) {
    m_id = id;
}

void Product::setName(const string &name) {
    m_name = name;
}


int Product::getId() const {
    return m_id;
}

const string &Product::getName() const {
    return m_name;
}


std::ostream &operator<<(ostream &stream, const Product &product) {
    stream<<product.m_id<<"|"<<product.m_name<<"\n";
    return stream;
}

Product::Product(int id, const string &name, ProductType typeProduct) {
    this->m_id = id;
    this->m_name = name;
    this->m_typeProduct = typeProduct;
}


bool operator==(const Product &a, const Product &b) {
    return (a.getId() == b.getId() && a.getName() == b.getName() && a.getTypeProduct() == b.getTypeProduct());
}

void Product::display(ostream &os) const {
    vector<Product> products;
    os << m_id << " ";
    for (auto i = 0; i < products.size(); i++)
        os << products[i] << i << " ";

}

void Product::setTypeProduct(ProductType typeProduct) {
    m_typeProduct = typeProduct;
}

ProductType Product::getTypeProduct() const {
    return m_typeProduct;
}
std::string Product::productToString(){
        return (this->m_typeProduct == ProductType::TEA ? "TEA" : "ACCESSORY");
    }
