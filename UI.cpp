#include "UI.h"
#include <iostream>
#include <string>
#include "Utils.h"
#include "Product.h"
#include "ProductController.h"

using namespace std;

UI::UI(ProductController& C) : m_controller{ C }
{

}

void UI::add()
{
    int id;
    //ProductType productType;
    string name, productType;
    cout << "id: " << endl;
    id = readInt();
    cout << "name: " << endl;
    cin >> name;
    cout << "Product type: " << endl;
    cin>>productType;

    Product* newProduct = new Product(id, name, productType == "TEA" ? ProductType::TEA : ProductType::ACCESORY);
    m_controller.addaNewProduct(newProduct);
}

void UI::remove()
{
    int id;
    cout << "Enter the id of the product you want to remove: ";
    id = readInt();
    m_controller.deleteProductById(id);
}

 void UI::Menu()
{
    m_controller.loadFromFile();

    char op;
    while (true)
    {
        cout << "Please insert your option: " << endl;
        cout << "\t 1 - add"<<endl;
        cout<< "\t 2 - remove" << endl;
        cout<< "\t 3 - display all" << endl;
        cout << "\t 4 - display the products by type" << endl;
        cout << "\t 5 - undo" << endl << "\t 6 - redo" << endl;
        cout << "\t 0 - exit" << endl;
        cin >> op;
        if (op == '1')
            add();
        else if (op == '2')
            remove();
        else if (op == '3')
            m_controller.display();
        else if (op != '4')
            m_controller.displayByType();
//        else if (op == '5')
//            m_controller.undo();
            //else if (op == '6')
            // m_controller.redo();
             else if (op != '0')
                cout << "Invalid option  >:[" << endl;
            else
                break;

        }

        m_controller.saveToFile();
}
