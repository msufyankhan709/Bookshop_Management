#include <iostream>
#include <string>
#include <algorithm> // For sorting

using namespace std;

const int MAX_BOOKS = 100; // Maximum number of books

class Book
{
public:
    string title;
    string author;
    int year;

    // Constructor
    Book() : year(0) {}

    // Parameterized constructor
    Book(const string &title, const string &author, int year)
        : title(title), author(author), year(year) {}

    // Friend function to display book information
    friend void displayBookInfo(const Book &book);

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
};

class BookInventory
{
public:
    // Destructor to clean up resources
    ~BookInventory()
    {
        cout << "Cleaning up the book inventory." << endl;
    }

    // Function to add a book to the inventory
    void addBook()
    {
        if (bookCount >= MAX_BOOKS)
        {
            cout << "Maximum number of books reached. Cannot add more books." << endl;
            return;
        }

        Book book;
        cout << "Enter the title of the book: ";
        getline(cin, book.title);
        cout << "Enter the author of the book: ";
        getline(cin, book.author);
        cout << "Enter the year of publication: ";
        cin >> book.year;
        cin.ignore(); // Clear the input buffer

        books[bookCount] = book;
        bookCount++;

        cout << "Book added successfully!" << endl;
    }

    // Function to display all books in the inventory
    void displayBooks()
    {
        if (bookCount == 0)
        {
            cout << "No books in the inventory." << endl;
            return;
        }

        cout << "----- Book Inventory -----" << endl;
        for (int i = 0; i < bookCount; i++)
        {
            displayBookInfo(books[i]);
        }
    }

    // Function to search for a book by title or author
    void searchBook()
    {
        string searchTerm;
        cout << "Enter the title or author to search: ";
        getline(cin, searchTerm);

        bool found = false;

        cout << "----- Search Results -----" << endl;
        for (int i = 0; i < bookCount; i++)
        {
            const Book &book = books[i];
            if (book.getTitle().find(searchTerm) != string::npos || book.getAuthor().find(searchTerm) != string::npos)
            {
                displayBookInfo(book);
                found = true;
            }
        }

        if (!found)
        {
            cout << "No books found matching the search term." << endl;
        }
    }

    // Function to delete a book from the inventory
    void deleteBook()
    {
        if (bookCount == 0)
        {
            cout << "No books in the inventory to delete." << endl;
            return;
        }

        string titleToDelete;
        cout << "Enter the title of the book to delete: ";
        getline(cin, titleToDelete);

        bool found = false;
        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].getTitle() == titleToDelete)
            {
                // Shift the remaining books to fill the gap
                for (int j = i; j < bookCount - 1; j++)
                {
                    books[j] = books[j + 1];
                }

                bookCount--;
                found = true;
                cout << "Book deleted successfully!" << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "Book not found in the inventory." << endl;
        }
    }

    // Function to update information of an existing book
    void updateBook()
    {
        if (bookCount == 0)
        {
            cout << "No books in the inventory to update." << endl;
            return;
        }

        string titleToUpdate;
        cout << "Enter the title of the book to update: ";
        getline(cin, titleToUpdate);

        bool found = false;
        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].getTitle() == titleToUpdate)
            {
                cout << "Enter the new title of the book: ";
                getline(cin, books[i].title);
                cout << "Enter the new author of the book: ";
                getline(cin, books[i].author);
                cout << "Enter the new year of publication: ";
                cin >> books[i].year;
                cin.ignore(); // Clear the input buffer

                found = true;
                cout << "Book information updated successfully!" << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "Book not found in the inventory." << endl;
        }
    }

    // Function to sort books by title, author, or year
    void sortBooks()
    {
        int sortChoice;
        cout << "Select sorting criteria:" << endl;
        cout << "1. Sort by Title" << endl;
        cout << "2. Sort by Author" << endl;
        cout << "3. Sort by Year" << endl;
        cout << "Enter your choice: ";
        cin >> sortChoice;
        cin.ignore(); // Clear the input buffer

        switch (sortChoice)
        {
        case 1:
            sort(books, books + bookCount, [](const Book &a, const Book &b) {
                return a.getTitle() < b.getTitle();
            });
            cout << "Books sorted by Title." << endl;
            break;
        case 2:
            sort(books, books + bookCount, [](const Book &a, const Book &b) {
                return a.getAuthor() < b.getAuthor();
            });
            cout << "Books sorted by Author." << endl;
            break;
        case 3:
            sort(books, books + bookCount, [](const Book &a, const Book &b) {
                return a.getYear() < b.getYear();
            });
            cout << "Books sorted by Year." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
    }

    // Function to display statistics about the books
    void displayStatistics()
    {
        if (bookCount == 0)
        {
            cout << "No books in the inventory." << endl;
            return;
        }

        int totalYears = 0;
        for (int i = 0; i < bookCount; i++)
        {
            totalYears += books[i].getYear();
        }

        double averageYear = static_cast<double>(totalYears) / bookCount;

        cout << "----- Book Statistics -----" << endl;
        cout << "Total number of books: " << bookCount << endl;
        cout << "Average year of publication: " << averageYear << endl;
    }

private:
    static Book books[MAX_BOOKS];
    static int bookCount;

    // Friend function declaration
    friend void displayBookInfo(const Book &book);
};

// Static member initialization
Book BookInventory::books[MAX_BOOKS];
int BookInventory::bookCount = 0;

// Friend function definition
void displayBookInfo(const Book &book)
{
    cout << "Title: " << book.getTitle() << endl;
    cout << "Author: " << book.getAuthor() << endl;
    cout << "Year: " << book.getYear() << endl;
    cout << "--------------------------" << endl;
}

// Function to display a menu and get user choice
int getMenuChoice()
{
    int choice;
    cout << "------ Bookshop Management ------" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Display Books" << endl;
    cout << "3. Search Book" << endl;
    cout << "4. Delete Book" << endl;
    cout << "5. Update Book Information" << endl;
    cout << "6. Sort Books" << endl;
    cout << "7. Display Statistics" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // Clear the input buffer
    return choice;
}

int main()
{
    BookInventory bookInventory; // Creating an instance of BookInventory

    int choice;
    while (true)
    {
        choice = getMenuChoice();

        switch (choice)
        {
        case 1:
            bookInventory.addBook();
            break;
        case 2:
            bookInventory.displayBooks();
            break;
        case 3:
            bookInventory.searchBook();
            break;
        case 4:
            bookInventory.deleteBook();
            break;
        case 5:
            bookInventory.updateBook();
            break;
        case 6:
            bookInventory.sortBooks();
            break;
        case 7:
            bookInventory.displayStatistics();
            break;
        case 8:
            cout << "Exiting the program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}

