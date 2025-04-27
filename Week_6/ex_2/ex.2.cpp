#include "Item.h"
#include "ShoppingCart.h"

int main()
{
	Item item1{ "candy", 1, 10 };
	Item item2{ "fruit", 1, 3 };
	Item item3{ "ball", 1, 5 };
	Item item4{ "doll", 0, 7 };
	Item item5 = item1;
	//item3.printItem();
	//item2.printItem();

	Item items[3];
	items[0] = item1;
	items[1] = item2;
	items[2] = item3;

	ShoppingCart cart2(items, 3);
	ShoppingCart cart1(cart2);

	cart1.printCart();
	std::cout << std::endl << std::endl;
	cart1.addItem(item4);
	cart1.addItem(item5);
	cart1.removeItem("candy");
	cart1.printCart();
	std::cout << std::endl << std::endl;

	std::cout << cart1.totalPrice();
	cart1.sortByName();
	cart1.printCart();

	cart1.save("cart.txt");
	
}