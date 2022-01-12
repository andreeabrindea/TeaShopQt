
#include "ProductController.h"

ProductController::ProductController()
{

}

ProductController::ProductController(const Repository &mRepo) : m_repo(mRepo) {}

void ProductController::addaNewProduct(Product *a) {
    m_repo.addProduct(a);
    m_undoStack.push(std::make_pair(ActionType::ADD, a));

//    new Product product;
//    this->undoStack.push({product,1 });  //mark that the operation called was add

}

void ProductController::deleteProductById(int id) {
    Product p = m_repo.deleteProduct(id);
    m_undoStack.push(std::make_pair(ActionType::REMOVE, &p));
}

void ProductController::display() {
    m_repo.display(std::cout, [](Product *p)->bool {return true;});

}

void ProductController::loadFromFile() {
    m_repo.loadFromFile();

}

void ProductController::saveToFile() {
    m_repo.saveToFile();

}



void ProductController::displayByType() {
    m_repo.display(std::cout, [](Product* p)->bool {
        if (p->getTypeProduct() == ProductType::TEA ? "TEA": "ACCESORY")
            return true;
        return false;
    });
}

std::vector<Product*> ProductController::getAllProducts()
{
    return this->m_repo.returnDatabase();
}

void ProductController::undo() {
    if (!m_undoStack.empty())
    {
        pair<ActionType, Product*> lastOperation = m_undoStack.top();
        m_redoStack.push(lastOperation);

        if (lastOperation.first == ActionType::ADD)
        { m_repo.deleteProduct(lastOperation.second->getId()); }
        else
            m_repo.addProduct(lastOperation.second);
        m_undoStack.pop();
    }
}

void ProductController::redo() {

    if (!m_undoStack.empty()) {
        pair < ActionType, Product * > lastOperation = m_redoStack.top();
        m_undoStack.push(lastOperation);

        if (lastOperation.first == ActionType::ADD) { m_repo.deleteProduct(lastOperation.second->getId()); }
        else
            m_repo.addProduct(lastOperation.second);

        m_redoStack.pop();
    }
}
