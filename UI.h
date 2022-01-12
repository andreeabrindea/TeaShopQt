#pragma once
#include "ProductController.h"
class UI
{
private:
    ProductController m_controller;

public:
    UI(ProductController&);

    void add();
    void remove();

    void Menu();


};
