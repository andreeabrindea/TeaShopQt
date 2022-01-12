
#include "Product.h"

class Accesory : public Product{
private:
    std::string m_typeAccesory;
public:
    // Constructor:
    Accesory(int id, const string &name, ProductType typeProduct, string typeAccesory);

    // Getter and setter:
    const string &getTypeAccesory() const;
    void setTypeAccesory(const string &typeAccesory);
    void display(ostream& os) const;
};



