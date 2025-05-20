#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

#include <string>
#include <vector>


#define MAX_BOOKS 1000
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 50

typedef unsigned int BookID;
typedef std::vector<std::string> StringList;
typedef int YearType;


namespace BookManager {
    
    struct Book {
        BookID id;
        std::string title;
        std::string author;
        YearType yearOfPublication;

        
        Book(BookID _id = 0, const std::string& _title = "", 
             const std::string& _author = "", YearType _year = 0)
            : id(_id), title(_title), author(_author), yearOfPublication(_year) {}
    };
}

#endif 
