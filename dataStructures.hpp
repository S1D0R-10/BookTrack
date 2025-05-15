#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

#include <string>
#include <vector>

namespace BookManager {

    // Typedef for book ID
    typedef int BookID;
    
    // Maximum number of books in the database
    const int MAX_BOOKS = 1000;
    
    // Book structure definition
    struct Book {
        BookID id;             // Unique identifier for the book
        std::string title;     // Book title
        std::string author;    // Book author
        int yearOfPublication; // Year of publication
    };
    
} // namespace BookManager

#endif // DATA_STRUCTURES_HPP
