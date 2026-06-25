#include <fstream>
#include <iostream>
#include <vector>
class Book {
public:
  std::string title;
  std::string author;
  int ISBN;
  bool isAvailable;
  Book(std::string title, std::string author, int ISBN, bool isAvailable)
      : title(title), author(author), ISBN(ISBN), isAvailable(isAvailable) {}
};
class Library {
  std::vector<Book> library;
  std::fstream myFile;

  // adding book
public:
  void addBooks() {
    int size;
    std::cout << "How many books do you want to store?\n";
    std::cin >> size;
    std::cout << "Enter the title, author, and ISBN:\n";
    std::string title;
    std::string author;
    int ISBN;
    for (int i = 0; i < size; i++) {
      std::cout << "Enter the title:" << std::endl;
      std::getline(std::cin >> std::ws, title);
      std::cout << "Enter the author:" << std::endl;
      std::getline(std::cin >> std::ws, author);
      std::cout << "Enter ISBN:" << std::endl;
      std::cin >> ISBN;
      Book a(title, author, ISBN, true);
      library.push_back(a);
    }
  }

  // Displaying Books
  void displayBooks() {
    for (int i = 0; i < library.size(); i++) {
      std::cout << "Title: " << library[i].title << std::endl;
      std::cout << "Author: " << library[i].author << std::endl;
      std::cout << "ISBN: " << library[i].ISBN << std::endl;
      std::cout << "Available: " << library[i].isAvailable << std::endl;
    }
  }
  // Searching for a book
  void searchBook() {
    bool found = false;
    std::cout << "Enter a title to search for:" << std::endl;
    std::string book_to_search;
    std::getline(std::cin >> std::ws, book_to_search);
    for (int i = 0; i < library.size(); i++) {
      if (library[i].title == book_to_search) {
        found = 1;
        std::cout << "Title: " << library[i].title << std::endl;
        std::cout << "Author: " << library[i].author << std::endl;
        std::cout << "ISBN: " << library[i].ISBN << std::endl;
        std::cout << "Available: " << library[i].isAvailable << std::endl;
      }
    }
    if (found) {
      std::cout << "Found!" << std::endl;

    } else {
      std::cout << "Book not found." << std::endl;
    }
  }

  // Borrowing
  void borrowBook() {
    bool found = false;
    std::cout << "Enter a book to borrow:" << std::endl;
    std::string book_to_search;
    std::getline(std::cin >> std::ws, book_to_search);
    for (int i = 0; i < library.size(); i++) {
      if (library[i].title == book_to_search) {
        found = true;
        if (library[i].isAvailable == true) {
          std::cout << "Book borrowed successfully." << std::endl;
          library[i].isAvailable = false;

        } else {
          std::cout << "This book is already borrowed." << std::endl;
        }
      }
    }
    if (!found) {
      std::cout << "Book not found." << std::endl;
    }
  }
  // Returning a book
  void returnBook() {
    bool found = false;
    std::cout << "Enter a book to return:" << std::endl;
    std::string book_to_return;
    std::getline(std::cin >> std::ws, book_to_return);
    for (int i = 0; i < library.size(); i++) {
      if (library[i].title == book_to_return) {
        found = true;
        if (library[i].isAvailable == false) {
          std::cout << "Book returned successfully." << std::endl;
          library[i].isAvailable = true;

        } else {
          std::cout << "Nothing to return." << std::endl;
        }
      }
    }
    if (!found) {
      std::cout << "Book not found." << std::endl;
    }
  }
  void removeBook() {
    bool found = false;
    std::cout << "Enter a book to delete:" << std::endl;
    std::string deleted_book;
    std::getline(std::cin >> std::ws, deleted_book);
    for (int i = 0; i < library.size(); i++) {
      if (library[i].title == deleted_book) {
        auto it = library.begin() + i;
        library.erase(it);
        std::cout << "Book removed successfully." << std::endl;
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "Book not found." << std::endl;
    }
  }
  void saveToFile() {
    myFile.open("Library.txt", std::ios::out);
    for (int i = 0; i < library.size(); i++) {
      myFile << library[i].title << "\n";
      myFile << library[i].author << "\n";
      myFile << library[i].ISBN << "\n";
      myFile << library[i].isAvailable << "\n";
    }
    myFile.close();
  }

  void loadFromFile() {
    myFile.open("Library.txt", std::ios::in);
    std::string title;
    std::string author;
    int ISBN;
    bool isAvailable;
    while (std::getline(myFile, title)) {
      std::getline(myFile, author);
      myFile >> ISBN;
      myFile >> isAvailable;
      myFile.ignore();

      Book a(title, author, ISBN, isAvailable);
      library.push_back(a);
    }
    myFile.close();
  }

  void updateBook() {
    std::cout << "Enter the title of the book to update:" << std::endl;
    bool found = false;
    std::string newTitle;
    std::string newAuthor;
    std::string book_to_update;
    int newISBN;
    int choice;

    std::getline(std::cin >> std::ws, book_to_update);
    for (int i = 0; i < library.size(); i++) {
      if (library[i].title == book_to_update) {
        found = true;
        std::cout << "What would you like to update?\n";
        std::cout << "1. Title\n";
        std::cout << "2. Author\n";
        std::cout << "3. ISBN\n";
        std::cin >> choice;

        switch (choice) {
          case 1:
            std::cout << "Enter the new title: ";
            std::getline(std::cin >> std::ws, newTitle);
            library[i].title = newTitle;
            break;
          case 2:
            std::cout << "Enter the new author: ";
            std::getline(std::cin >> std::ws, newAuthor);
            library[i].author = newAuthor;
            break;
          case 3:
            std::cout << "Enter the new ISBN: ";
            std::cin >> newISBN;

            library[i].ISBN = newISBN;
            break;
        }
        std::cout << "Updated successfully " << std::endl;
        break;
      }
    }
    if (!found) {
      std::cout << "Not found!";
    }
  }
};

int main() {
  Library a;
  a.loadFromFile();

  int choice = 0;

  while (choice != 8) {
    std::cout << R"(
        Enter a choice:
        1. Add Books
        2. Display Books
        3. Search Book
        4. Borrow Book
        5. Return Book
        6. Remove Book
        7. Update Book
        8. Save & Exit)"
              << std::endl;

    std::cin >> choice;

    switch (choice) {
      case 1:
        a.addBooks();
        break;
      case 2:
        a.displayBooks();
        break;
      case 3:
        a.searchBook();
        break;
      case 4:
        a.borrowBook();
        break;
      case 5:
        a.returnBook();
        break;
      case 6:
        a.removeBook();
        break;
      case 7:
        a.updateBook();
        break;
      case 8:
        a.saveToFile();
        break;
      default:
        std::cout << "Invalid choice." << std::endl;
    }
  }
  std::cout << "Thanks for using the program!" << std::endl;

  return 0;
}