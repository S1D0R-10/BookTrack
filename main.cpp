#include "functions.hpp"
#include "dataStructures.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace BookManager;


void displayMenu() {
    std::cout << "\n===== BookBase - Menedżer książek =====\n" << std::endl;
    std::cout << "1. Wyświetl wszystkie książki" << std::endl;
    std::cout << "2. Dodaj nową książkę" << std::endl;
    std::cout << "3. Edytuj książkę" << std::endl;
    std::cout << "4. Usuń książkę" << std::endl;
    std::cout << "5. Wyszukaj książkę po ID" << std::endl;
    std::cout << "6. Wyszukaj książkę po tytule" << std::endl;
    std::cout << "7. Sortuj książki alfabetycznie" << std::endl;
    std::cout << "8. Zapisz do pliku" << std::endl;
    std::cout << "9. Wczytaj z pliku" << std::endl;
    std::cout << "0. Wyjście" << std::endl;
    std::cout << "\nWybierz opcję: ";
}


void processMenuChoice(int choice, std::vector<Book>& books, std::string& filename) {
    BookID id;
    std::string title;
    
    switch (choice) {
        case 1: 
            displayAllBooks(books);
            break;
            
        case 2: 
            addBook(books);
            break;
            
        case 3: 
            std::cout << "Podaj ID książki do edycji: ";
            std::cin >> id;
            editBook(books, id);
            break;
            
        case 4: 
            std::cout << "Podaj ID książki do usunięcia: ";
            std::cin >> id;
            removeBook(books, id);
            break;
            
        case 5: 
            std::cout << "Podaj ID książki do wyszukania: ";
            std::cin >> id;
            {
                Book* result = findBookById(books, id);
                if (result) {
                    std::cout << "\nZnaleziona książka:\n" << std::endl;
                    std::cout << "ID    | Tytuł" << std::string(30, ' ') << "| Autor" << std::string(25, ' ') << "| Rok" << std::endl;
                    std::cout << std::string(80, '-') << std::endl;
                    displayBook(*result);
                } else {
                    std::cout << "Nie znaleziono książki o ID " << id << std::endl;
                }
            }
            break;
            
        case 6: 
            std::cout << "Podaj tytuł lub fragment tytułu do wyszukania: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, title);
            {
                std::vector<Book> results = searchBooksByTitle(books, title);
                
                if (results.empty()) {
                    std::cout << "Nie znaleziono książek zawierających \"" << title << "\" w tytule." << std::endl;
                } else {
                    std::cout << "\nZnalezione książki (" << results.size() << "):\n" << std::endl;
                    std::cout << "ID    | Tytuł" << std::string(30, ' ') << "| Autor" << std::string(25, ' ') << "| Rok" << std::endl;
                    std::cout << std::string(80, '-') << std::endl;
                    
                    for (const auto& book : results) {
                        displayBook(book);
                    }
                }
            }
            break;
            
        case 7: 
            sortBooksByTitle(books);
            break;
            
        case 8: 
            {
                std::string saveFilename;
                std::cout << "Podaj nazwę pliku do zapisu (Enter aby użyć domyślnej nazwy \"" << filename << "\"): ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, saveFilename);
                
                if (saveFilename.empty()) {
                    saveFilename = filename;
                }
                
                saveBooksToFile(books, saveFilename);
            }
            break;
            
        case 9: 
            {
                std::string loadFilename;
                std::cout << "Podaj nazwę pliku do wczytania (Enter aby użyć domyślnej nazwy \"" << filename << "\"): ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, loadFilename);
                
                if (loadFilename.empty()) {
                    loadFilename = filename;
                }
                
                loadBooksFromFile(books, loadFilename);
            }
            break;
            
        case 0: 
            std::cout << "Czy chcesz zapisać zmiany przed wyjściem? (t/n): ";
            {
                char saveChoice;
                std::cin >> saveChoice;
                
                if (saveChoice == 't' || saveChoice == 'T') {
                    saveBooksToFile(books, filename);
                }
                
                std::cout << "Do widzenia!" << std::endl;
            }
            break;
            
        default:
            std::cout << "Nieprawidłowy wybór. Spróbuj ponownie." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::vector<Book> books;
    std::string filename = "books.txt"; 
    
    
    if (argc > 1) {
        filename = argv[1];
        std::cout << "Używam pliku: " << filename << std::endl;
        
        
        loadBooksFromFile(books, filename);
    } else {
        std::cout << "Nie podano nazwy pliku. Używam domyślnej nazwy: " << filename << std::endl;
        
        
        if (!loadBooksFromFile(books, filename)) {
            std::cout << "Utworzono nową bazę danych." << std::endl;
        }
    }
    
    int choice;
    
    do {
        displayMenu();
        
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidłowy wybór. Spróbuj ponownie." << std::endl;
            continue;
        }
        
        processMenuChoice(choice, books, filename);
        
    } while (choice != 0);
    
    return 0;
}
