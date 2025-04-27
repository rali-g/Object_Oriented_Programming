#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable : 4996)

class Game
{
private:
	char title[20];
	int price;
	bool isAvailable;
public:
	Game() : price(0), isAvailable(0)
	{
		strcpy(title, "");
	}

	Game(const char* title, int price, bool isAvailable)
	{
		strcpy(this->title, title);
		this->price = price;
		this->isAvailable = isAvailable;
	}

	Game(const char* title)
	{
		strcpy(this->title, title);
		this->price = 0;
		this->isAvailable = true;
	}

	const char* getTitle() const
	{
		return this->title;
	}

	int getPrice() const
	{
		return this->price;
	}

	bool getIsAvailable() const
	{
		return isAvailable;
	}

	void setTitle(const char* title)
	{
		strcpy(this->title, title);
	}

	void setPrice(int price)
	{
		this->price = price;
	}

	void setIsAvailable(bool isAvailable)
	{
		this->isAvailable = isAvailable;
	}

	bool isFree()
	{
		return (price == 0);
	}

	void print()
	{
		std::cout << "Title: " << title << "\nPrice: " 
		<< price << "\nIsAvailable: " << std::boolalpha << isAvailable;
	}
};

int stringToInt(const char* ch)
{
	int result = 0;
	while (*ch)
	{
		result += *ch - '0';
		result *= 10;
		ch++;
	}
	result /= 10;
	return result;
}

class GamePlatform
{
private:
	Game games[100];
	int size = 0;
public:
	GamePlatform() : size(0) {}

	GamePlatform(const Game* games, int size)
	{
		this->size = size;
		for (int i = 0; i < size; i++)
		{
			this->games[i] = games[i];
		}
	}

	int getSize() const
	{
		return size;
	}

	const Game* getGames() const
	{
		return games;
	}

	void addGame(const Game& game)
	{
		if (size >= 100)
		{
			std::cout << "Out of size!";
			return;
		}

		this->games[size++] = game;
	}

	Game findByTitle(const char* title)
	{
		for (int i = 0; i < size; i++)
		{
			if (strcmp(this->games[i].getTitle(), title) == 0)
			{
				return games[i];
			}
		}
		return Game();
	}

	Game findMostExpensiveGame()
	{
		if (size < 1)
		{
			return Game();
		}

		Game result = games[0];
		for (int i = 1; i < size; i++)
		{
			if (result.getPrice() < games[i].getPrice())
			{
				result = games[i];
			}
		}
		return result;
	}

	void removeGameByTitle(const char* title)
	{
		int index = size;
		bool isFound = 0;
		for (int i = 0; i < size; i++)
		{
			if (strcmp(this->games[i].getTitle(), title) == 0)
			{
				index = i;
				isFound = 1;
				break;
			}
		}

		for (int i = index; i < size - 1; i++)
		{
			std::swap(games[i], games[i + 1]);
		}

		if (isFound)
		{
			size--;
		}

	}
	
	void printGames()
	{
		for (int i = 0; i < size; i++)
		{
			games[i].print();
			std::cout << std::endl;
		}
	}

	void printAvailableGames()
	{
		for (int i = 0; i < size; i++)
		{
			if (games[i].getIsAvailable())
			{
				games[i].print();
				std::cout << std::endl;
			}
		}
	}

	void saveFile(const char* filePath)
	{
		std::ofstream ofs(filePath);

		if (!ofs.is_open())
		{
			return;
		}

		ofs << "Size: " << size << std::endl;
		
		for (int i = 0; i < size; i++)
		{
			ofs << "Title: " << games[i].getTitle() << "\nPrice: " << games[i].getPrice()
				<< "\nIs Available: " << games[i].getIsAvailable() << std::endl;
		}

		ofs.close();
	}

	void readFromFile(const char* filePath)
	{
		std::ifstream ifs(filePath);

		if (!ifs.is_open())
		{
			return;
		}

		char buffer[1024];
		ifs.getline(buffer, 1024, ' ');
		ifs.getline(buffer, 1024);

		size = stringToInt(buffer);
		for (size_t i = 0; i < size; i++)
		{
			ifs.getline(buffer, 1024, ' ');
			ifs.getline(buffer, 1024);
			games[i].setTitle(buffer);

			ifs.getline(buffer, 1024, ' ');
			ifs.getline(buffer, 1024);
			games[i].setPrice(stringToInt(buffer));

			ifs.getline(buffer, 1024, ' ');
			ifs.getline(buffer, 1024, ' ');
			ifs.getline(buffer, 1024);
			games[i].setIsAvailable((bool)stringToInt(buffer));
		}
	}

	void sortByName()
	{
		for (size_t i = 0; i < size - 1; i++)
		{
			for (size_t j = 0; j < size - i - 1; j++)
			{
				if (strcmp(games[j].getTitle(), games[j + 1].getTitle()) > 0)
				{
					std::swap(games[j], games[j + 1]);
				}
			}
		}
	}
};

int main()
{
	Game game1{ "Minecraft", 50, 1 };
	Game game2{ "Uno", 2, 1 };
	Game game3{ "Dixie", 25, 0 };

	GamePlatform steam;
	steam.addGame(game1);
	steam.addGame(game2);
	steam.addGame(game3);

	steam.printGames();

	std::cout << steam.findMostExpensiveGame().getTitle() << std::endl;

	steam.saveFile("Games.txt");
	std::cout << steam.findByTitle("Uno").getTitle() << std::endl;
	steam.removeGameByTitle("Uno");
	steam.printAvailableGames();

	std::cout << std::endl;
	GamePlatform steam2;
	steam2.readFromFile("Games.txt");
	steam2.printGames();

	std::cout << std::endl;
	steam2.sortByName();
	steam2.printGames();
}