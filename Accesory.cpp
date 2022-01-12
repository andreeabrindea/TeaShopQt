
#include "Accesory.h"

#include <utility>

const string &Accesory::getTypeAccesory() const {
    return m_typeAccesory;
}

void Accesory::setTypeAccesory(const string &typeAccesory) {
    m_typeAccesory = typeAccesory;
}

Accesory::Accesory(int id, const string &name, ProductType typeProduct, string typeAccesory)
        : Product(id, name, typeProduct), m_typeAccesory(std::move(typeAccesory)) {}

void Accesory::display(ostream &os) const {
    os<<"Accesory: ";
    Product::display(os);
    os<<m_typeAccesory;
}
