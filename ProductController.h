#pragma once
#include "Repository.h"
#include <iostream>
#include <stack>
enum class ActionType{
    ADD,
    REMOVE
};
class ProductController {
private:
    Repository m_repo;
    std::stack<pair<ActionType, Product*>> m_undoStack;
    std::stack<pair<ActionType, Product*>> m_redoStack;
public:
    ProductController();
    explicit ProductController(const Repository &mRepo);
    void addaNewProduct(Product* a);
    void deleteProductById(int id);
    std::vector<Product*> getAllProducts();
    void display();
    void displayByType();
    void loadFromFile();
    void saveToFile();
    void undo();
    void redo();


};

