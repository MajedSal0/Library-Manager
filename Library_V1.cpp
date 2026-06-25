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
    std::cout << "How many book you wanna store?:\n";
    std::cin >> size;
    std::cout << "Enter title , author , ISBN:\n";
    std::string title;
    std::string author;
    int ISBN;
    for (int i = 0; i < size; i++) {
      std::cout << "Enter title:" << std::endl;
      std::getline(std::cin >> std::ws, title);
      std::cout << "Enter an author: " << std::endl;
      std::getline(std::cin >> std::ws, author);
      std::cout << "Enter ISBN" << std::endl;
      std::cin >> ISBN;
      Book a(title, author, ISBN, true);
      library.push_back(a);
    }
  }

  // Displaying Books
  void displayBooks() {
    for (int i = 0; i < library.size(); i++) {
      std::cout << "Title " << library[i].title << std::endl;
      std::cout << "Author " << library[i].author << std::endl;
      std::cout << "ISBN " << library[i].ISBN << std::endl;
      std::cout << "Is Available? " << library[i].isAvailable << std::endl;
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
        std::cout << "Title " << library[i].title << std::endl;
        std::cout << "Author " << library[i].author << std::endl;
        std::cout << "ISBN " << library[i].ISBN << std::endl;
        std::cout << "Is Available? " << library[i].isAvailable << std::endl;
      }
    }
    if (found) {
      std::cout << "Found!" << std::endl;

    } else {
      std::cout << "Not found:" << std::endl;
    }
  }

  // Borrwing
  void borrowBook() {
    bool found = false;
    std::cout << "Enter a book to to borrow :" << std::endl;
    std::string book_to_search;
    std::getline(std::cin >> std::ws, book_to_search);
    for (int i = 0; i < library.size(); i++) {
      if (library[i].title == book_to_search) {
        found = true;
        if (library[i].isAvailable == true) {
          std::cout << "Borrow it" << std::endl;
          library[i].isAvailable = false;

        } else {
          std::cout << "Already borrowed!" << std::endl;
        }
      }
    }
    if (!found) {
      std::cout << "Not found!" << std::endl;
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
          std::cout << "Book returned:" << std::endl;
          library[i].isAvailable = true;

        } else {
          std::cout << "Noting to be returnd:" << std::endl;
        }
      }
    }
    if (!found) {
      std::cout << "Not found!" << std::endl;
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
        std::cout << "Book removed!:";
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "Not found:" << std::endl;
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
};

int main() {
  Library a;
  a.loadFromFile();

  int choise = 0;

  while (choise != 7) {
    std::cout << R"(
        Enter a choise:
        1. Add books
        2. Display books
        3. Search book
        4. Borrow book
        5. Return book
        6. Remove book
        7. Save &Exit)"
              << std::endl;

    std::cin >> choise;

    switch (choise) {
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
      case 7:a.saveToFile();
        break;
      default:
        std::cout << "Invalid value" << std::endl;
    }
  }
  std::cout << "Thanks for using the program!" << std::endl;

  return 0;
}