#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "dataStructures.hpp"
#include <vector>
#include <string>

namespace BookManager {
    
    void addBook(std::vector<Book>& books);
    
    void removeBook(std::vector<Book>& books, BookID id);
    
    void editBook(std::vector<Book>& books, BookID id);
    
    void displayAllBooks(const std::vector<Book>& books);
    
    Book* findBookById(std::vector<Book>& books, BookID id);
    
    int findBookIndexById(const std::vector<Book>& books, BookID id);
    
    std::vector<Book> searchBooksByTitle(const std::vector<Book>& books, const std::string& title);
    
    void sortBooksByTitle(std::vector<Book>& books);
    
    bool loadBooksFromFile(std::vector<Book>& books, const std::string& filename);
    
    bool saveBooksToFile(const std::vector<Book>& books, const std::string& filename);
    
    BookID generateUniqueId(const std::vector<Book>& books);
    
    void displayBook(const Book& book);
}

#endif 
