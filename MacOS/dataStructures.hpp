#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

#include <string>
#include <vector>

namespace BookManager {

    typedef int BookID;
    
    const int MAX_BOOKS = 1000;
    
    struct Book {
        BookID id;
        std::string title;
        std::string author;
        int yearOfPublication;
    };
    
}

#endif
