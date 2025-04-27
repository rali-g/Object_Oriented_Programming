#include <iostream>
#include "FoodPanda.h"

int main()
{
    Product product1;
    Product product2{"Pavel"};
    Product product3{"Rali"};

    Restaurant rest1;
    rest1.setName("Peistaurant");
    Restaurant rest2(rest1);

    rest2.setName("Ik");

    rest1.addProduct(product2);

    rest2.addProduct(product3);
    rest2.addProduct(product1);

    rest1.print();
    std::cout << std::endl;
    rest2.print();
    std::cout << std::endl;

    rest1[0].print();
    std::cout << std::endl;

    Purchase purchase1("Ik");
    Purchase purchase2("Peistaurant");
    Purchase purchase3("Bla");

    purchase1.addProduct(product1);
    purchase1.addProduct(product3);
    purchase2.addProduct(product2);
    purchase2.addProduct(product1);
    purchase2.addProduct(product2);

    Purchase purchases[3];
    purchases[0] = purchase1;
    purchases[1] = purchase2;
    purchases[2] = purchase3;

    FoodPanda food;
    food.addRestaurant(rest1);
    food.addRestaurant(rest2);
    food.addProductInRestaurant(product1, "Peistaurant");
    food.acceptPurchases(purchases, 3);

 /*   try 
    {
        std::cout << rest1.acceptPurchase(purchase);
    }
    catch (std::invalid_argument& arg)
    {
        std::cout << arg.what();
    }*/
}