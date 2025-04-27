#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable : 4996)

class User
{
private:
	static size_t userCount;
	size_t id;
	char name[32];
	double balance;
public:
	User() : balance(0)
	{
		strcpy(name, "");
		userCount++;
		id = userCount;
	}

	User(const char* name, double balance) : balance(balance)
	{
		strcpy(this->name, name);
		userCount++;
		id = userCount;
	}

	void setName(const char* name)
	{
		strcpy(this->name, name);
	}

	size_t getId() const
	{
		return id;
	}
	
	double getBalance() const
	{
		return balance;
	}

	void updateMoney(double amount)
	{
		this->balance += amount;
	}

	bool hasMoney(double amount) const
	{
		return balance >= amount;
	}
	void printUser() const
	{
		std::cout << "Name: " << name << "\nBalance: " << balance << "\nId: " << id << std::endl;
	}
};
size_t User::userCount = 0;

class Product
{
private:
	static size_t productCount;
	size_t productId;

	char name[32];
	size_t ownerId;
	size_t quantity;
public:
	Product() : quantity(0), ownerId(0)
	{
		strcpy(name, "");

		productCount++;
		productId = productCount;
	}

	Product(const char* name, size_t ownerId, size_t quantity)
	{
		strcpy(this->name, name);
		this->ownerId = ownerId;
		this->quantity = quantity;

		productCount++;
		productId = productCount;
	}

	void setName(const char* name)
	{
		strcpy(this->name, name);
	}

	void setOwnerId(size_t ownerId)
	{
		this->ownerId = ownerId;
	}

	size_t getQuantity() const
	{
		return quantity;
	}

	size_t getProductId() const
	{
		return productId;
	}

	size_t getOwnerId() const
	{
		return ownerId;
	}

	void updateQuantity(int amount)
	{
		if (amount < 0)
		{
			return;
		}
		quantity = amount;
	}
	void printProduct() const
	{
		std::cout << "Name: " << name << "\nQuantity: " << quantity
			<< "\nOwner id: " << ownerId << "\nProduct id: " << productId << std::endl;
	}
};
size_t Product::productCount = 0;

class Price
{
private:
	size_t productId;
	double price;
public:
	Price() : productId(0), price(0) {}

	Price(size_t productId, double price)
	{
		this->productId = productId;
		this->price = price;
	}

	void setId(size_t productId)
	{
		this->productId = productId;
	}

	void setPrice(double price)
	{
		if (price < 0)
		{
			return;
		}
		this->price = price;
	}

	double getPrice() const
	{
		return price;
	}

	size_t getId() const
	{
		return productId;
	}

	void updatePrice(double amount)
	{
		if (amount < 0)
		{
			return;
		}
		price += amount;
	}
	void printPrice() const
	{
		std::cout << "Price: " << price << "\nProduct id: " << productId << std::endl;
	}
};

const int DATABASECOUNT = 3;
class UsersDatabase
{
private:
	User users[50];
	size_t size;
public:
	UsersDatabase() : size(0) {}

	UsersDatabase(const User* users, size_t size)
	{
		this->size = size;
		for (size_t i = 0; i < size; i++)
		{
			this->users[i] = users[i];
		}
	}

	size_t getSize() const
	{
		return size;
	}

	User& getUserByIdx(size_t idx)
	{
		return users[idx];
	}

	void addUser(const User& user)
	{
		if (size >= DATABASECOUNT)
		{
			for (size_t i = 0; i < size - 1; i++)
			{
				users[i] = users[i + 1];
			}
			users[size - 1] = user;
			return;
		}
		this->users[size++] = user;
	}

	bool hasEnoughMoney(size_t id, double money) const
	{
		for (size_t i = 0; i < size; i++)
		{
			if (users[i].getId() == id)	
			{
				return users[i].hasMoney(money);
			}
		}
		return false;
	}

	bool existUser(size_t id) const
	{
		for (size_t i = 0; i < size; i++)
		{
			if (users[i].getId() == id)
			{
				return true;
			}
		}
		return false;
	}

	int existUserById(size_t id) const
	{
		for (size_t i = 0; i < size; i++)
		{
			if (users[i].getId() == id)
			{
				return i;
			}
		}
		return -1;
	}

	void printUsers() const
	{
		for (size_t i = 0; i < size; i++)
		{
			users[i].printUser();
		}
	}
};

class ProductsDatabase
{
private:
	Product products[DATABASECOUNT];
	size_t size;
public:
	ProductsDatabase() : size(0) {}

	ProductsDatabase(const Product* products, size_t size)
	{
		this->size = size;
		for (size_t i = 0; i < size; i++)
		{
			this->products[i] = products[i];
		}
	}
	
	size_t getSize() const
	{
		return size;
	}

	void addProduct(const Product& product)
	{
		if (size >= DATABASECOUNT)
		{
			for (size_t i = 0; i < size - 1; i++)
			{
				products[i] = products[i + 1];
			}
			products[size - 1] = product;
			return;
		}
		products[size++] = product;
	}

	void addProduct(const char* name, size_t ownerId, size_t quantity)
	{
		Product product{ name, ownerId, quantity };
		addProduct(product);
	}

	size_t itemsOwned(size_t id, size_t productId)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (products[i].getOwnerId() == id && 
				products[i].getProductId() == productId)
			{
				return products[i].getQuantity();
			}
		}

		return 0;
	}

	void update(size_t id, size_t productID, size_t update)
	{
		int idx = existProductIdx(id, productID);
		if (idx == -1)
		{
			return;
		}
		products[idx].updateQuantity(update);
	}

	int existProductIdx(size_t id, size_t productId)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (products[i].getOwnerId() == id &&
				products[i].getProductId() == productId)
			{
				return i;
			}
		}
		return -1;
	}

	Product& getProductByIdx(size_t idx)
	{
		return products[idx];
	}
	void printProducts() const
	{
		for (size_t i = 0; i < size; i++)
		{
			products[i].printProduct();
		}
	}
};

class PricesDatabase
{
private:
	Price prices[DATABASECOUNT];
	size_t size;
public:
	PricesDatabase() : size(0) {}

	PricesDatabase(const Price* prices, size_t size)
	{
		this->size = size;
		for (size_t i = 0; i < size; i++)
		{
			this->prices[i] = prices[i];
		}
	}

	size_t getSize() const
	{
		return size;
	}

	void addPrice(const Price& price)
	{
		if (size >= DATABASECOUNT)
		{
			for (size_t i = 0; i < size - 1; i++)
			{
				prices[i] = prices[i + 1];
			}
			prices[size - 1] = price;
			return;
		}
		prices[size++] = price;
	}

	double getPrice(size_t id) const
	{
		for (size_t i = 0; i < size; i++)
		{
			if (prices[i].getId() == id)
			{
				return prices[i].getPrice();
			}
		}
	}
	void printPrices() const
	{
		for (size_t i = 0; i < size; i++)
		{
			prices[i].printPrice();
		}
	}

	int existPriceIdx(size_t productId)
	{
		for (size_t i = 0; i < size; i++)
		{
			if(prices[i].getId() == productId)
			{
				return i;
			}
		}
		return -1;
	}
};

class SalesSystem
{
private:
	UsersDatabase users;
	ProductsDatabase products;
	PricesDatabase prices;
public:
	SalesSystem() {}
	SalesSystem(const UsersDatabase& users, const ProductsDatabase& products, const PricesDatabase& prices) 
	{
		this->users = users;
		this->products = products;
		this->prices = prices;
	}

	void addUser(const User& user)
	{
		users.addUser(user);
	}

	void addProduct(const Product& product)
	{
		size_t usersSize = users.getSize();
		for (size_t i = 0; i < usersSize; i++)
		{
			if (users.getUserByIdx(i).getId() == product.getOwnerId())
			{
				products.addProduct(product);
				return;
			}
		}
	}

	void addPrice(const Price& price)
	{
		if (price.getPrice() < 0)
		{
			return;
		}

		size_t productsSize = products.getSize();
		for (size_t i = 0; i < productsSize; i++)
		{
			if (products.getProductByIdx(i).getProductId() == price.getId())
			{
				prices.addPrice(price);
				return;
			}
		}
	}

	void sell(size_t idFrom, size_t idTo, size_t productID)
	{
		int productIdx = products.existProductIdx(idFrom, productID);
		if (productIdx == -1)
		{
			return;
		}

		int priceIdx = prices.existPriceIdx(productID);
		double cost = 0;
		if (priceIdx != -1)
		{
			cost = products.getProductByIdx(productIdx).getQuantity() *
				   prices.getPrice(productID);
		}

		//std::cout << cost << std::endl;
		int idxFrom = users.existUserById(idFrom);
		int idxTo = users.existUserById(idTo);
		if (!users.getUserByIdx(idxTo).hasMoney(cost))
		{
			return;
		}

		users.getUserByIdx(idxTo).updateMoney(-cost);
		users.getUserByIdx(idxFrom).updateMoney(cost);
		products.getProductByIdx(productIdx).setOwnerId(users.getUserByIdx(idxTo).getId());

		users.printUsers();
		std::cout << std::endl;
		products.printProducts();
		std::cout << std::endl;
	}
};


int main()
{
	User user1;
	User user2("Ivan", 50);
	User user3("Lubo", 100);
 
	Product product1{ "guitar", 1, 5 };
	Product product2{ "shirt", 2, 10 };
	Product product3{ "shoes", 3, 1 };

	Price price1{ 1, 5 };
	Price price2{ 2, 2 };
	Price price3{ 3, 1 };

	UsersDatabase userDatabase;
	userDatabase.addUser(user1);
	userDatabase.addUser(user2);
	userDatabase.addUser(user3);

	userDatabase.printUsers();
	std::cout << std::endl;

	//userDatabase.addUser(user2);

	userDatabase.printUsers();
	std::cout << std::endl;

	ProductsDatabase productsDatabase;
	productsDatabase.addProduct(product1);
	productsDatabase.addProduct(product2);
	productsDatabase.addProduct(product3);
	productsDatabase.printProducts();
	std::cout << std::endl;

	PricesDatabase pricesDatabase;
	pricesDatabase.addPrice(price1);
	pricesDatabase.addPrice(price2);
	pricesDatabase.addPrice(price3);
	pricesDatabase.printPrices();
	std::cout << std::endl;

	SalesSystem system{userDatabase, productsDatabase, pricesDatabase};
	system.sell(2, 3, 2);

}