#include "Book.h"
#include "Library.h"
int main()
{
	Book book1{ "a", Genre::romance, "abc" };
	Book book2{ "b", Genre::fantasy, "bca" };
	Book book3{ "c", Genre::drama, "cba" };
	Book book4(book1);
	Book book5 = book2;
	//book1.print();
	//book2.print();
	//book3.print();
	//book4.print();
	//book5.print();

	Library library;
	library.returnBook(book1);
	library.returnBook(book2);
	library.returnBook(book3);
	library.lendBook("a");
	library.printLibrary();
	library.writeIn("books");
	Library resLibrary;
	resLibrary.readFrom("books");
	resLibrary.printLibrary();
}