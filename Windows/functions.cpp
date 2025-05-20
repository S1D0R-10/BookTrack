#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <sstream>
#include <iomanip>

namespace BookManager {

    void addBook(std::vector<Book>& books) {
        if (books.size() >= MAX_BOOKS) {
            std::cout << "Maksymalna liczba książek została osiągnięta." << std::endl;
            return;
        }

        Book newBook;
        
        newBook.id = generateUniqueId(books);
        
        std::cout << "Dodawanie nowej książki (ID: " << newBook.id << ")" << std::endl;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Podaj tytuł: ";
        std::getline(std::cin, newBook.title);
        
        std::cout << "Podaj autora: ";
        std::getline(std::cin, newBook.author);
        
        std::cout << "Podaj rok wydania: ";
        std::cin >> newBook.yearOfPublication;
        
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidłowy format roku. Podaj rok wydania ponownie: ";
            std::cin >> newBook.yearOfPublication;
        }
        
        books.push_back(newBook);
        std::cout << "Książka została dodana pomyślnie!" << std::endl;
    }
    
    
    void removeBook(std::vector<Book>& books, BookID id) {
        int index = findBookIndexById(books, id);
        
        if (index == -1) {
            std::cout << "Książka o ID " << id << " nie została znaleziona." << std::endl;
            return;
        }
        
        books.erase(books.begin() + index);
        std::cout << "Książka o ID " << id << " została usunięta." << std::endl;
    }
    
    
    void editBook(std::vector<Book>& books, BookID id) {
        int index = findBookIndexById(books, id);
        
        if (index == -1) {
            std::cout << "Książka o ID " << id << " nie została znaleziona." << std::endl;
            return;
        }
        
        Book& book = books[index];
        
        int choice;
        std::cout << "Edycja książki o ID " << id << ":" << std::endl;
        std::cout << "Co chcesz edytować?" << std::endl;
        std::cout << "1. Tytuł" << std::endl;
        std::cout << "2. Autor" << std::endl;
        std::cout << "3. Rok wydania" << std::endl;
        std::cout << "4. Wszystkie informacje" << std::endl;
        std::cout << "0. Anuluj" << std::endl;
        std::cout << "Wybór: ";
        std::cin >> choice;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                std::cout << "Nowy tytuł: ";
                std::getline(std::cin, book.title);
                break;
            case 2:
                std::cout << "Nowy autor: ";
                std::getline(std::cin, book.author);
                break;
            case 3:
                std::cout << "Nowy rok wydania: ";
                std::cin >> book.yearOfPublication;
                while (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Nieprawidłowy format roku. Podaj rok wydania ponownie: ";
                    std::cin >> book.yearOfPublication;
                }
                break;
            case 4:
                std::cout << "Nowy tytuł: ";
                std::getline(std::cin, book.title);
                
                std::cout << "Nowy autor: ";
                std::getline(std::cin, book.author);
                
                std::cout << "Nowy rok wydania: ";
                std::cin >> book.yearOfPublication;
                while (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Nieprawidłowy format roku. Podaj rok wydania ponownie: ";
                    std::cin >> book.yearOfPublication;
                }
                break;
            case 0:
                std::cout << "Edycja anulowana." << std::endl;
                return;
            default:
                std::cout << "Nieprawidłowy wybór." << std::endl;
                return;
        }
        
        std::cout << "Książka została zaktualizowana." << std::endl;
    }
    
    
    void displayAllBooks(const std::vector<Book>& books) {
    if (books.empty()) {
        std::cout << "Brak książek w bazie danych." << std::endl;
        return;
    }
    
    std::cout << "\n==== Lista wszystkich książek (" << books.size() << ") ====\n" << std::endl;
    
    std::cout << std::left;
    std::cout << std::setw(4) << "ID" << " | ";
    std::cout << std::setw(35) << "Tytuł" << " | ";
    std::cout << std::setw(30) << "Autor" << " | ";
    std::cout << "Rok" << std::endl;
    
    std::cout << std::string(80, '-') << std::endl;
    
    for (const auto& book : books) {
        displayBook(book);
    }
    
    std::cout << std::string(80, '-') << std::endl;
}
    
    
    void displayBook(const Book& book) {
    std::cout << std::left;
    std::cout << std::setw(4) << book.id;
    std::cout << " | ";
    
    if (book.title.length() > 30) {
        std::cout << book.title.substr(0, 27) << "...";
    } else {
        std::cout << book.title;
    }
    std::cout << std::string(35 - std::min(30, (int)book.title.length()), ' ');
    std::cout << " | ";
    
    if (book.author.length() > 25) {
        std::cout << book.author.substr(0, 22) << "...";
    } else {
        std::cout << book.author;
    }
    std::cout << std::string(30 - std::min(25, (int)book.author.length()), ' ');
    std::cout << " | ";
    
    std::cout << book.yearOfPublication;
    
    std::cout << std::endl;
}
    
    
    Book* findBookById(std::vector<Book>& books, BookID id) {
        for (auto& book : books) {
            if (book.id == id) {
                return &book;
            }
        }
        
        return nullptr;
    }
    
    
    int findBookIndexById(const std::vector<Book>& books, BookID id) {
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].id == id) {
                return static_cast<int>(i);
            }
        }
        
        return -1;
    }
    
    
    std::vector<Book> searchBooksByTitle(const std::vector<Book>& books, const std::string& title) {
        std::vector<Book> results;
        
        for (const auto& book : books) {
            
            std::string bookTitleLower = book.title;
            std::string searchTitleLower = title;
            
            std::transform(bookTitleLower.begin(), bookTitleLower.end(), bookTitleLower.begin(), ::tolower);
            std::transform(searchTitleLower.begin(), searchTitleLower.end(), searchTitleLower.begin(), ::tolower);
            
            if (bookTitleLower.find(searchTitleLower) != std::string::npos) {
                results.push_back(book);
            }
        }
        
        return results;
    }
    
    
    void sortBooksByTitle(std::vector<Book>& books) {
        if (books.empty() || books.size() == 1) {
            return;
        }
        
        bool swapped;
        for (size_t i = 0; i < books.size() - 1; ++i) {
            swapped = false;
            
            for (size_t j = 0; j < books.size() - i - 1; ++j) {
                
                std::string title1 = books[j].title;
                std::string title2 = books[j + 1].title;
                
                std::transform(title1.begin(), title1.end(), title1.begin(), ::tolower);
                std::transform(title2.begin(), title2.end(), title2.begin(), ::tolower);
                
                if (title1 > title2) {
                    std::swap(books[j], books[j + 1]);
                    swapped = true;
                }
            }
            
            if (!swapped) {
                break;
            }
        }
        
        std::cout << "Książki zostały posortowane według tytułu." << std::endl;
    }
    
    
    bool loadBooksFromFile(std::vector<Book>& books, const std::string& filename) {
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            std::cerr << "Nie można otworzyć pliku " << filename << std::endl;
            return false;
        }
        
        books.clear();
        

        bool isCsv = false;
        size_t dotPos = filename.find_last_of('.');
        if (dotPos != std::string::npos) {
            std::string extension = filename.substr(dotPos + 1);
            std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
            isCsv = (extension == "csv");
        }
        
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::istringstream iss(line);
            Book book;
            
            if (isCsv) {

                std::string idStr, yearStr;
                

                if (!std::getline(iss, idStr, ',')) continue;
                if (!std::getline(iss, book.title, ',')) continue;
                if (!std::getline(iss, book.author, ',')) continue;
                if (!std::getline(iss, yearStr)) continue;
                

                idStr.erase(0, idStr.find_first_not_of(" \t"));
                idStr.erase(idStr.find_last_not_of(" \t") + 1);
                
                book.title.erase(0, book.title.find_first_not_of(" \t"));
                book.title.erase(book.title.find_last_not_of(" \t") + 1);
                
                book.author.erase(0, book.author.find_first_not_of(" \t"));
                book.author.erase(book.author.find_last_not_of(" \t") + 1);
                
                yearStr.erase(0, yearStr.find_first_not_of(" \t"));
                yearStr.erase(yearStr.find_last_not_of(" \t") + 1);
                
                try {
                    book.id = std::stoi(idStr);
                    book.yearOfPublication = std::stoi(yearStr);
                } catch (const std::exception& e) {
                    std::cerr << "Błąd podczas parsowania linii: " << line << std::endl;
                    continue;
                }
            } else {
                if (!(iss >> book.id)) continue;
                
                char delimiter;
                iss >> delimiter; 
                
                std::getline(iss, book.title, '|');
                std::getline(iss, book.author, '|');
                iss >> book.yearOfPublication;
                
                book.title.erase(0, book.title.find_first_not_of(" \t"));
                book.title.erase(book.title.find_last_not_of(" \t") + 1);
                
                book.author.erase(0, book.author.find_first_not_of(" \t"));
                book.author.erase(book.author.find_last_not_of(" \t") + 1);
            }
            
            books.push_back(book);
        }
        
        file.close();
        
        std::cout << "Wczytano " << books.size() << " książek z pliku " << filename << std::endl;
        return true;
    }
    
    
    bool saveBooksToFile(const std::vector<Book>& books, const std::string& filename) {
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            std::cerr << "Nie można otworzyć pliku " << filename << " do zapisu." << std::endl;
            return false;
        }
        
        bool isCsv = false;
        size_t dotPos = filename.find_last_of('.');
        if (dotPos != std::string::npos) {
            std::string extension = filename.substr(dotPos + 1);
            std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
            isCsv = (extension == "csv");
        }
        
        for (const auto& book : books) {
            if (isCsv) {
                file << book.id << "," << book.title << "," << book.author << "," << book.yearOfPublication << std::endl;
            } else {
                file << book.id << " | " << book.title << " | " << book.author << " | " << book.yearOfPublication << std::endl;
            }
        }
        
        file.close();
        
        std::cout << "Zapisano " << books.size() << " książek do pliku " << filename << std::endl;
        return true;
    }
    
    
    BookID generateUniqueId(const std::vector<Book>& books) {
        if (books.empty()) {
            return 1;
        }
        
        
        BookID maxId = 0;
        for (const auto& book : books) {
            if (book.id > maxId) {
                maxId = book.id;
            }
        }
        
        
        return maxId + 1;
    }
}
