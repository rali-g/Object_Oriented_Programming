#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning(disable : 4996)

namespace Constants{
	const int MAX_CELL_SIZE = 50;
	const int MAX_COLUMNS_SIZE = 30;
	const int MAX_ROWS_SIZE = 30;
	const int MAX_LINE_SIZE = 1024;
	const char TABLE_SEPARATOR[] = "table";
	const char HEADER_SEPARATOR[] = "th";
	const char ROW_SEPARATOR[] = "tr";
	const char CELL_SEPARATOR[] = "td";
	const int COMMAND_LENGTH = 10;
	const int VALUE_LENGTH = 100;		
}

namespace Commands {
	const char* COMMAND_ADD = "add";
	const char* COMMAND_REMOVE = "remove";
	const char* COMMAND_EDIT = "edit";
	const char* COMMAND_PRINT = "print";
	const char* COMMAND_EXIT = "exit";
}

typedef char Field[Constants::MAX_CELL_SIZE];
typedef Field Row[Constants::MAX_COLUMNS_SIZE];

struct Table
{
	Row rows[Constants::MAX_ROWS_SIZE];
	size_t rowsCount = 0;
	size_t columnsCount = 0;

	int headerIndexesX[Constants::MAX_COLUMNS_SIZE * Constants::MAX_ROWS_SIZE];
	int headerIndexesY[Constants::MAX_COLUMNS_SIZE * Constants::MAX_ROWS_SIZE];
	size_t headersCount = 0;
};

Table readFromFile(const char* filename)
{
	Table table;
	size_t currentColumnsCount = 0;

	std::ifstream ifs(filename);

	if (!ifs.is_open())
	{
		throw std::exception();
	}

	char buff[Constants::MAX_LINE_SIZE];

	while (true)
	{
		if (ifs.eof())
		{
			break;
		}

		ifs.getline(buff, Constants::MAX_LINE_SIZE, '<');
		ifs.getline(buff, Constants::MAX_LINE_SIZE, '>');

		if (strcmp(buff, Constants::TABLE_SEPARATOR) == 0)
		{
			//in table
			//use with multiple tables
		}
		else if (strcmp(buff, Constants::ROW_SEPARATOR) == 0)
		{
			for (size_t i = currentColumnsCount; i < table.columnsCount; i++)
			{
				strcpy(table.rows[table.rowsCount - 1][i], "");
			}

			table.rowsCount++;
			currentColumnsCount = 0;
		}
		else if (strcmp(buff, Constants::HEADER_SEPARATOR) == 0 ||
			strcmp(buff, Constants::CELL_SEPARATOR) == 0)
		{
			currentColumnsCount++;
			if (currentColumnsCount > table.columnsCount)
			{
				table.columnsCount = currentColumnsCount;

				for (size_t i = 0; i < table.rowsCount - 1; i++)
				{
					strcpy(table.rows[i][currentColumnsCount - 1], "");
				}
			}

			if (strcmp(buff, Constants::HEADER_SEPARATOR) == 0)
			{
				table.headerIndexesX[table.headersCount] = table.rowsCount - 1;
				table.headerIndexesY[table.headersCount] = currentColumnsCount - 1;
				table.headersCount++;
			}

			ifs.getline(buff, Constants::MAX_LINE_SIZE, '<');

			strcpy(table.rows[table.rowsCount - 1][currentColumnsCount - 1], buff);
		}


	}
	ifs.close();

	return table;
}

bool isHeader(int x, int y, const Table& table)
{
	for (int i = 0; i < table.headersCount; i++)
	{
		if (table.headerIndexesX[i] == x && table.headerIndexesY[i] == y)
		{
			return true;
		}
	}
	return false;
}

void saveTable(const char* filename, const Table& table)
{
	std::ofstream ofs(filename);

	if (!ofs.is_open())
	{
		std::cout << "File not found";
		return;
	}

	ofs << "<" << Constants::TABLE_SEPARATOR << ">" << std::endl;

	for (int i = 0; i < table.rowsCount; i++)
	{
		ofs << " <" << Constants::ROW_SEPARATOR << ">" << std::endl;

		for (int j = 0; j < table.columnsCount; j++)
		{
			if (isHeader(i, j, table))
			{
				ofs << "  <" << Constants::HEADER_SEPARATOR << ">";
				ofs << table.rows[i][j];
				ofs << "</" << Constants::HEADER_SEPARATOR << ">" << std::endl;
			}
			else
			{
				ofs << "  <" << Constants::CELL_SEPARATOR << ">";
				ofs << table.rows[i][j];
				ofs << "</" << Constants::CELL_SEPARATOR << ">" << std::endl;
			}
		}

		ofs << " </" << Constants::ROW_SEPARATOR << ">" << std::endl;
	}
	ofs << "</" << Constants::TABLE_SEPARATOR << ">" << std::endl;
	
	ofs.close();

	std::cout << "Succesfully saved!";
}

void characterReference(Table& table)
{
	for (size_t i = 0; i < table.rowsCount; i++)
	{
		for (size_t j = 0; j < table.columnsCount; j++)
		{
			char* pointer = table.rows[i][j];

			while (*pointer)
			{
				char* oldIdx = pointer;
				if (*pointer++ == '&' && *pointer == '#')
				{
					pointer++;
					int currentNumber = *pointer - '0';
					while (*(++pointer) && *pointer != ';')
					{
						currentNumber *= 10;
						currentNumber += *pointer - '0';
					}
					*oldIdx++ = currentNumber;

					while (*pointer++)
					{
						*oldIdx++ = *pointer;
					}
					*oldIdx = '\0';
				}
			}
		}
	}
}

int wordLength(const char* word)
{
	int result = 0;
	while (*word)
	{
		result++;
		word++;
	}

	return result;
}

int longestWordInColumn(const Table& table, int columnIdx)
{
	int maxValue = INT_MIN;
	for (int i = 0; i < table.rowsCount; i++)
	{
			int tempLength = wordLength(table.rows[i][columnIdx]);
			if (tempLength > maxValue)
			{
				maxValue = tempLength;
			}
	}
	return maxValue;	
}

void printSpaces(int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << " ";
	}
}

void printTable(const Table& table)
{
	int maxValue[Constants::MAX_COLUMNS_SIZE];

	for (int i = 0; i < table.columnsCount; i++)
	{
		maxValue[i] = longestWordInColumn(table, i);
	}

	for (size_t i = 0; i < table.rowsCount; i++)
	{
		for (size_t j = 0; j < table.columnsCount; j++)
		{
			if (isHeader(i, j, table))
			{
				std::cout << "|*" << table.rows[i][j];

				int currentValue = wordLength(table.rows[i][j]);
				printSpaces(maxValue[j] - currentValue);
				std::cout << "*";
			}

			else
			{
				std::cout << "| " << table.rows[i][j] << " ";
				int currentValue = wordLength(table.rows[i][j]);
				printSpaces(maxValue[j] - currentValue);
			}
		}
		std::cout << "|" << std::endl;
	}
}

void edit(Table& table, size_t rowNumber, size_t colNumber, const char* value)
{
	if (rowNumber >= table.rowsCount || colNumber >= table.columnsCount)
	{
		std::cout << "Out of table size!" << std::endl;
		return;
	}

	strcpy(table.rows[rowNumber][colNumber], value);
	std::cout << "Data saved!" << std::endl;
}

void copyRow(Table& table, int from, int to)
{
	for (size_t i = 0; i < table.columnsCount; i++)
	{
		strcpy(table.rows[to][i], table.rows[from][i]);
	}
}

void removeRow(Table& table, size_t rowNumber)
{
	if (rowNumber >= table.rowsCount)
	{
		std::cout << "Out of table size!" << std::endl;
		return;
	}

	for (size_t i = rowNumber; i < table.rowsCount - 1; i++)
	{
		copyRow(table, i + 1, i);
	}
	table.rowsCount--;
	std::cout << "Removed succesfully!" << std::endl;
}

void addRow(Table& table, int rowNumber, const char words[][Constants::MAX_CELL_SIZE])
{

	table.rowsCount++;

	for (int i = table.rowsCount - 2; i >= rowNumber; i--)
	{
		copyRow(table, i, i + 1);
	}

	for (size_t i = 0; i < table.columnsCount; i++)
	{
		strcpy(table.rows[rowNumber][i], words[i]);
	}

	std::cout << "Added succesfully!" << std::endl;
}

void insertCommands(Table& result)
{
	char command[Constants::COMMAND_LENGTH];

	while (true)
	{
		std::cout << "Enter command: ";
		std::cin.getline(command, Constants::COMMAND_LENGTH);

		if (!strcmp(command, Commands::COMMAND_ADD))
		{
			int rowNumber;
			std::cout << "Enter row number: ";
			std::cin >> rowNumber;

			std::cin.ignore();

			if (rowNumber > result.rowsCount)
			{
				std::cout << "Out of table size!" << std::endl;
				continue;
			}

			char words[Constants::MAX_COLUMNS_SIZE][Constants::MAX_CELL_SIZE];

			for (size_t i = 0; i < result.columnsCount; i++)
			{
				std::cout << "Enter column number " << (i + 1) << " value: ";
				std::cin.getline(words[i], Constants::MAX_CELL_SIZE);
			}

			addRow(result, rowNumber, words);
		}
		else if (!strcmp(command, Commands::COMMAND_REMOVE))
		{
			int rowNumber;
			std::cout << "Enter row number: ";

			std::cin >> rowNumber;
			std::cin.ignore();

			removeRow(result, rowNumber);
		}
		else if (!strcmp(command, Commands::COMMAND_EDIT))
		{
			int rowNumber, colNumber;
			char value[Constants::VALUE_LENGTH];

			std::cout << "Enter row number: ";
			std::cin >> rowNumber;

			std::cout << "Enter column number: ";
			std::cin >> colNumber;
			std::cin.ignore();

			std::cout << "Enter value: ";
			std::cin.getline(value, Constants::VALUE_LENGTH);

			edit(result, rowNumber, colNumber, value);
		}
		else if (!strcmp(command, Commands::COMMAND_PRINT))
		{
			printTable(result);
		}
		else if(!strcmp(command, Commands::COMMAND_EXIT))
		{
			break;
		}
		else std::cout << "Wrong command!" << std::endl;
	}
}

void printCommands()
{
	std::cout << "Available commands: " << std::endl;
	std::cout << "1. " << Commands::COMMAND_ADD << std::endl;
	std::cout << "2. " << Commands::COMMAND_EDIT << std::endl;
	std::cout << "3. " << Commands::COMMAND_REMOVE << std::endl;
	std::cout << "4. " << Commands::COMMAND_PRINT << std::endl;
	std::cout << "5. " << Commands::COMMAND_EXIT << std::endl;
}

int main()
{
	Table table;

	table = readFromFile("table.txt");
	characterReference(table);

	printCommands();
	insertCommands(table);

	saveTable("table1.txt", table);
}