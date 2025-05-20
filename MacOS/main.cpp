#include "functions.hpp"
#include "dataStructures.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <cstdlib>

using namespace BookManager;

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void displayMenu() {
    std::cout << "\n===== BookBase - Menedżer książek =====\n" << std::endl;
    std::cout << "1. Wyświetl wszystkie książki" << std::endl;
    std::cout << "2. Dodaj nową książkę" << std::endl;
    std::cout << "3. Edytuj książkę" << std::endl;
    std::cout << "4. Usuń książkę" << std::endl;
    std::cout << "5. Wyszukaj książkę po ID" << std::endl;
    std::cout << "6. Wyszukaj książkę po tytule" << std::endl;
    std::cout << "7. Sortuj książki alfabetycznie" << std::endl;
    std::cout << "8. Zapisz do pliku (TXT/CSV)" << std::endl;
    std::cout << "9. Wczytaj z pliku (TXT/CSV)" << std::endl;
    std::cout << "0. Wyjście" << std::endl;
    std::cout << "\nWybierz opcję: ";
}

void showErrorMessageBox(const std::string& message) {
    std::string appleScriptCommand = "osascript -e 'display dialog \"" + message + "\" buttons {\"OK\"} with icon stop with title \"Błąd BookBase\"'";
    system(appleScriptCommand.c_str());
}

void waitForEnter() {
    std::cout << "\nNaciśnij Enter, aby powrócić do menu..." << std::flush;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void processMenuChoice(int choice, std::vector<Book>& books, std::string& filename) {
    BookID id;
    std::string title;
    
    switch (choice) {
        case 1:
            clearScreen();
            displayAllBooks(books);
            waitForEnter();
            clearScreen();
            break;
            
        case 2:
            clearScreen();
            addBook(books);
            waitForEnter();
            clearScreen();
            break;
            
        case 3:
            clearScreen();
            std::cout << "Podaj ID książki do edycji: ";
            std::cin >> id;
            editBook(books, id);
            waitForEnter();
            clearScreen();
            break;
            
        case 4:
            clearScreen();
            std::cout << "Podaj ID książki do usunięcia: ";
            std::cin >> id;
            removeBook(books, id);
            waitForEnter();
            clearScreen();
            break;
            
        case 5:
            clearScreen();
            std::cout << "Podaj ID książki do wyszukania: ";
            std::cin >> id;
            {
                Book* result = findBookById(books, id);
                if (result) {
                    std::cout << "\nZnaleziona książka:\n" << std::endl;
                    
                    std::cout << std::left;
                    std::cout << std::setw(4) << "ID" << " | ";
                    std::cout << std::setw(35) << "Tytuł" << " | ";
                    std::cout << std::setw(30) << "Autor" << " | ";
                    std::cout << "Rok" << std::endl;
                    
                    std::cout << std::string(80, '-') << std::endl;
                    displayBook(*result);
                    std::cout << std::string(80, '-') << std::endl;
                } else {
                    std::cout << "Nie znaleziono książki o ID " << id << std::endl;
                }
            }
            waitForEnter();
            clearScreen();
            break;
            
        case 6:
            clearScreen();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Podaj tytuł (lub fragment tytułu) książki do wyszukania: ";
            std::getline(std::cin, title);
            {
                std::vector<Book> results = searchBooksByTitle(books, title);
                
                if (!results.empty()) {
                    std::cout << "\nZnalezione książki (" << results.size() << "):\n" << std::endl;
                    
                    std::cout << std::left;
                    std::cout << std::setw(4) << "ID" << " | ";
                    std::cout << std::setw(35) << "Tytuł" << " | ";
                    std::cout << std::setw(30) << "Autor" << " | ";
                    std::cout << "Rok" << std::endl;
                    
                    std::cout << std::string(80, '-') << std::endl;
                    
                    for (const auto& book : results) {
                        displayBook(book);
                    }
                    
                    std::cout << std::string(80, '-') << std::endl;
                } else {
                    std::cout << "Nie znaleziono książek pasujących do tytułu \"" << title << "\"" << std::endl;
                }
            }
            waitForEnter();
            clearScreen();
            break;
            
        case 7:
            clearScreen();
            sortBooksByTitle(books);
            waitForEnter();
            clearScreen();
            break;
            
        case 8:
            clearScreen();
            {
                std::string saveFilename;
                std::cout << "Podaj nazwę pliku do zapisu (Enter aby użyć domyślnej nazwy \"" << filename << "\") [.txt lub .csv]:";
                if (std::cin.peek() == '\n') {
                    std::cin.get();
                } else {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::getline(std::cin, saveFilename);
                
                if (saveFilename.empty()) {
                    saveFilename = filename;
                }
                
                saveBooksToFile(books, saveFilename.empty() ? filename : saveFilename);
            }
            waitForEnter();
            clearScreen();
            break;
            
        case 9:
            clearScreen();
            {
                std::string loadFilename;
                std::cout << "Podaj nazwę pliku do wczytania (Enter aby użyć domyślnej nazwy \"" << filename << "\") [.txt lub .csv]:";
                if (std::cin.peek() == '\n') {
                    std::cin.get();
                } else {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::getline(std::cin, loadFilename);
                
                if (loadFilename.empty()) {
                    loadFilename = filename;
                }
                
                if (loadBooksFromFile(books, loadFilename)) {
                    if (!loadFilename.empty()) {
                        filename = loadFilename;
                    }
                }
            }
            waitForEnter();
            clearScreen();
            break;
            
        case 0:
            clearScreen();
            std::cout << "Czy chcesz zapisać zmiany przed wyjściem? (t/n): ";
            char saveChoice;
            std::cin >> saveChoice;
            
            if (saveChoice == 't' || saveChoice == 'T') {
                saveBooksToFile(books, filename);
            }
            
            std::cout << "Do widzenia!" << std::endl;
            
            std::cout << "\nNaciśnij Enter, aby zakończyć..." << std::flush;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
            
        default:
            clearScreen();
            std::cout << "Nieprawidłowy wybór. Spróbuj ponownie." << std::endl;
            showErrorMessageBox("Nieprawidłowy wybór z menu");
            waitForEnter();
            clearScreen();
    }
}

int main(int argc, char* argv[]) {
    clearScreen();
    
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
            
            showErrorMessageBox("Nieprawidłowy format danych - wprowadź liczbę");
            
            waitForEnter();
            choice = -1;
            continue;
        }
        
        processMenuChoice(choice, books, filename);
        
    } while (choice != 0);
    
    return 0;
}
