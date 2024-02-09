#include "book.h"
#include "util.h"
#include <iostream>
#include <set>

Book::Book(std::string category_, std::string name_, double price_, int qty_, std::string ISBN_number_, std::string author_) : Product(category_, name_, price_, qty_)
{
   this->author_ = author_;
   this->ISBN_number_ = ISBN_number_;
}

std::set<std::string> Book::keywords() const
{
   std::set<std::string> result;
   std::set<std::string> authorSet = parseStringToWords(this->author_);
   std::set<std::string> nameSet = parseStringToWords(this->name_);

   result = setUnion(authorSet, nameSet);

   result.insert(this->ISBN_number_);

   return result;
}

std::string Book::displayString() const
{
   std::string displayString = this->name_ + "\n" + "Author: " + this->author_ + " ISBN: " + this->ISBN_number_ + "\n" + std::to_string(this->price_) + " " + std::to_string(this->qty_) + " left.\n";
   return displayString;
}

void Book::dump(std::ostream &os) const
{
   os << "book" << std::endl;
   os << this->name_ << std::endl;
   os << this->price_ << std::endl;
   os << this->qty_ << std::endl;
   os << this->ISBN_number_ << std::endl;
   os << this->author_ << std::endl;
}