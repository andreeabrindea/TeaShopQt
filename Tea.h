
#include "Product.h"

class Tea : public Product {
private:
    string m_flavor;

public:
    // Constructor:
    Tea(int id, const string &name, ProductType typeProduct, string flavor);

    // Getter and setter:
    const string &getFlavor() const;
    void setFlavor(const string &flavor);

    void display(ostream& os) const override;
};



