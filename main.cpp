#include "functions.hpp"
#include "dataStructures.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace BookManager;


// Funkcja do czyszczenia bufora wejściowego
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Funkcja do wyświetlania menu
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


// Funkcja wstrzymująca program do naciśnięcia Enter
void pauseProgram() {
    std::cout << "\nNaciśnij Enter, aby kontynuować...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void processMenuChoice(int choice, std::vector<Book>& books, std::string& filename) {
    BookID id;
    std::string title;
    
    switch (choice) {
        case 1: 
            displayAllBooks(books);
            pauseProgram();
            break;
            
        case 2: 
            addBook(books);
            pauseProgram();
            break;
            
        case 3: 
            std::cout << "Podaj ID książki do edycji: ";
            std::cin >> id;
            editBook(books, id);
            pauseProgram();
            break;
            
        case 4: 
            std::cout << "Podaj ID książki do usunięcia: ";
            std::cin >> id;
            removeBook(books, id);
            pauseProgram();
            break;
            
        case 5: 
            std::cout << "Podaj ID książki do wyszukania: ";
            std::cin >> id;
            {
                Book* result = findBookById(books, id);
                if (result) {
                    std::cout << "\nZnaleziona książka:\n" << std::endl;
                    
                    // Print header with simple fixed-width columns
                    std::cout << std::left;
                    std::cout << std::setw(4) << "ID" << " | ";
                    std::cout << std::setw(35) << "Tytuł" << " | ";
                    std::cout << std::setw(30) << "Autor" << " | ";
                    std::cout << "Rok" << std::endl;
                    
                    // Print separator line
                    std::cout << std::string(80, '-') << std::endl;
                    displayBook(*result);
                    std::cout << std::string(80, '-') << std::endl;
                } else {
                    std::cout << "Nie znaleziono książki o ID " << id << std::endl;
                }
            }
            std::cout << "\nNaciśnij Enter, aby kontynuować...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
            
        case 6: 
            std::cout << "Podaj tytuł lub fragment tytułu do wyszukania: ";
            // Check if there's already a newline character in the buffer
            if (std::cin.peek() == '\n') {
                std::cin.get(); // Remove just the newline
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::getline(std::cin, title);
            {
                std::vector<Book> results = searchBooksByTitle(books, title);
                
                if (results.empty()) {
                    std::cout << "Nie znaleziono książek zawierających \"" << title << "\" w tytule." << std::endl;
                } else {
                    std::cout << "\nZnalezione książki (" << results.size() << "):\n" << std::endl;
                    
                    // Print header with simple fixed-width columns
                    std::cout << std::left;
                    std::cout << std::setw(4) << "ID" << " | ";
                    std::cout << std::setw(35) << "Tytuł" << " | ";
                    std::cout << std::setw(30) << "Autor" << " | ";
                    std::cout << "Rok" << std::endl;
                    
                    // Print separator line
                    std::cout << std::string(80, '-') << std::endl;
                    
                    for (const auto& book : results) {
                        displayBook(book);
                    }
                    std::cout << std::string(80, '-') << std::endl;
                }
            }
            pauseProgram();
            break;
            
        case 7: 
            sortBooksByTitle(books);
            pauseProgram();
            break;
            
        case 8: 
            {
                std::string saveFilename;
                std::cout << "Podaj nazwę pliku do zapisu (Enter aby użyć domyślnej nazwy \"" << filename << "\") [.txt lub .csv]:";
                // Check if there's already a newline character in the buffer
                if (std::cin.peek() == '\n') {
                    std::cin.get(); // Remove just the newline
                } else {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::getline(std::cin, saveFilename);
                
                if (saveFilename.empty()) {
                    saveFilename = filename;
                }
                
                saveBooksToFile(books, saveFilename);
                pauseProgram();
            }
            break;
            
        case 9: 
            {
                std::string loadFilename;
                std::cout << "Podaj nazwę pliku do wczytania (Enter aby użyć domyślnej nazwy \"" << filename << "\") [.txt lub .csv]:";
                // Check if there's already a newline character in the buffer
                if (std::cin.peek() == '\n') {
                    std::cin.get(); // Remove just the newline
                } else {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::getline(std::cin, loadFilename);
                
                if (loadFilename.empty()) {
                    loadFilename = filename;
                }
                
                loadBooksFromFile(books, loadFilename);
                pauseProgram();
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
            pauseProgram();
    }
}

int main(int argc, char* argv[]) {
    std::vector<Book> books;
    std::string filename = "books.txt"; // Domyślnie używamy formatu TXT
    
    
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
        // Always display the menu first
        displayMenu();
        
        // Get user choice
        if (!(std::cin >> choice)) {
            // Handle invalid input (non-numeric)
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Nieprawidłowy wybór. Spróbuj ponownie." << std::endl;
            pauseProgram();
            choice = -1; // Set to invalid choice to continue loop
            continue;
        }
        
        // Process the menu choice
        processMenuChoice(choice, books, filename);
        
        // We'll handle pauses in the processMenuChoice function instead
        
    } while (choice != 0);
    
    return 0;
}
