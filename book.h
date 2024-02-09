#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book : public Product
{

private:
   std::string ISBN_number_;
   std::string author_;

public:
   Book(std::string category_, std::string name_, double price_, int qty_, std::string ISBN_number_, std::string author_);

   std::set<std::string> keywords() const;
   std::string displayString() const;
   void dump(std::ostream &os) const;
};

#endif