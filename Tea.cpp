
#include "Tea.h"

#include <utility>

const string &Tea::getFlavor() const {
    return m_flavor;
}

void Tea::setFlavor(const string &flavor) {
    this->m_flavor = flavor;
}

Tea::Tea(int id, const string &name, ProductType typeProduct, string flavor) : Product(id,
                                                                                                                 name,
                                                                                                                 typeProduct),
                                                                                                         m_flavor(std::move(
                                                                                                                 flavor)) {}

void Tea::display(ostream &os) const {
    os<<"Tea: ";
    Product::display(os);
    os<<"with the flavor: "<<m_flavor;
}
