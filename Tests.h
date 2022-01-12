
#pragma once
//#include "Product.h"
#include "Repository.h"
#include "ProductController.h"
#include <assert.h>

void testGetters(Product product)
{
    assert(product.getId() == 17);
    assert(product.getName() == "Basilur");
}

void testSetters(Product product)
{
    product.setId(21);
    product.setName("Lipton");

    assert(product.getId() == 21);
    assert(product.getName() == "Lipton");

    bool exceptionThrown = false;
    try
    {
        product.setName("Nestea");
    }
    catch (...)
    {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    bool exceptionThrown1 = false;
    try
    {
        product.setId(-2323.565);
    }
    catch (...)
    {
        exceptionThrown1 = true;
    }
    assert(exceptionThrown1);
}

void testOperatorEqual(Product product)
{
    Product product2{22, "Teapot", ProductType::ACCESORY};
    Product product1{21, "Lipton", ProductType::TEA};

//    assert(product1 == product);
//    assert(!(static_cast<Product>(product) == product2));
}

void TestProduct()
{
    Product product{ 21, "Lipton", ProductType::TEA}, product2{ 22, "Teapot", ProductType::ACCESORY};

    testGetters(product);
    testSetters(product2);
    testOperatorEqual(product);
};
////////////////////////////////////////////////////////////////////

void testAdd(Repository &database)
{
    assert(database.addProduct(new Product(21, "Lipton", ProductType::TEA)) == true);
    assert(database.addProduct(new Product(1, "Teaspoon", ProductType::ACCESORY)) == true);
    assert(database.addProduct(new Product(2, "Nestea", ProductType::TEA)) == true);
    assert(database.addProduct(new Product(21, "Lipton", ProductType::TEA)) == false);
}

void testDelete(Repository database)
{
    Product product1={21, "Lipton", ProductType:: TEA};
//    assert(database.deleteProduct(21, "Lipton") == product1);
    bool exceptionThrown1 = false;
    try
    {
        database.deleteProduct(21);
    }
    catch (...)
    {
        exceptionThrown1 = true;
    }
    assert(exceptionThrown1);
}


void testReturnDatabase(Repository database)
{
    Product product1{ 21, "Lipton", ProductType::TEA}, product2{ 22, "Teapot", ProductType::ACCESORY};
//    assert(static_cast<Product>(database.returnDatabase()[0]) == product1);
//    assert(database.returnDatabase()[1] == product2);
//    assert(!(database.returnDatabase()[2] == product2));
}

void TestProductDatabase()
{
    Repository database;

    testAdd(database);
    testDelete(database);
    testReturnDatabase(database);
};
////////////////////////////////////////////////////////////////////

void runAllTests()
{
    TestProduct();

}

