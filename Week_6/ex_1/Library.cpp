#include "Library.h"

void Library::free()
{
	//for (size_t i = 0; i < size; i++)
	//{
	//	delete books[i];
	//}
	delete[] books;
	
	books = nullptr;
	size = 0;
	capacity = CAPACITY_LENGHT;
}
void Library::copyFrom(const Library& other)
{
	size = other.size;
	books = new Book[other.capacity];
	for (size_t i = 0; i < size; i++)
	{
		books[i] = other.books[i];
	}
	capacity = other.capacity;
}
void Library::resize() 
{
	capacity *= 2;
	
	Book* oldBooks = books;
	books = new Book[capacity];
	for (size_t i = 0; i < size; i++)
	{
		books[i] = oldBooks[i];
	}
	delete[] oldBooks;
}
Library::Library() : size(0)
{
	capacity = CAPACITY_LENGHT;
	books = new Book[capacity];
}
Library::Library(const Book* books, size_t size)
{
	this->size = size;
	if (size >= CAPACITY_LENGHT)
	{
		capacity = size;
	}
	else
	{
		capacity = CAPACITY_LENGHT;
	}

	this->books = new Book[capacity];
	for (size_t i = 0; i < size; i++)
	{
		this->books[i] = books[i];
	}
}
Library::Library(const Library& other)
{
	copyFrom(other);
}
Library& Library::operator=(const Library& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Library::~Library()
{
	free();
}
const Book& Library::lendBook(const char* name)
{
	size_t i = 0;
	for (i; i < size; i++)
	{
		if (strcmp(books[i].getName(), name) == 0)
		{
			break;
		}
	}
	Book result;
	if (i < size)
	{
		result = books[i];
	}
	else
	{
		throw std::exception("Book not found");
	}
	for (i; i < size - 1; i++)
	{
		books[i] = books[i + 1];
	}
	size--;
	return result;
}
void Library::returnBook(const Book& book)
{
	if (capacity <= size)
	{
		resize();
	}
	books[size++] = book;
}
void Library::writeIn(const char* fileName) const
{
	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}

	ofs << size << std::endl << capacity << std::endl;
	ofs.write((const char*)books, sizeof(Book) * size);

	ofs.close();
}
void Library::readFrom(const char* fileName) 
{
	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	char buffer[1024];
	ifs.getline(buffer, 1024);
	this->size = stringToInt(buffer);
	ifs.getline(buffer, 1024);
	this->capacity = stringToInt(buffer);

	delete[] books;
	this->books = new Book[capacity];
	ifs.read((char*)books, sizeof(Book) * size);
	ifs.close();
}

int Library::stringToInt(const char* str)
{
	int result = 0;
	while (*str)
	{
		result += *str - '0';
		result *= 10;
		str++;
	}
	result /= 10;
	return result;
}

void Library::printLibrary()
{
	for (size_t i = 0; i < size; i++)
	{
		books[i].print();
		std::cout << std::endl;
	}
	std::cout << "Capacity: " << capacity << std::endl
		<< "Size: " << size << std::endl;
}
