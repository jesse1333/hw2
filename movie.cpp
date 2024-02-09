#include "movie.h"
#include "util.h"
#include <iostream>
#include <set>

Movies::Movies(std::string category_, std::string name_, double price_, int qty_, std::string genre_, std::string rating_) : Product(category_, name_, price_, qty_)
{
   this->genre_ = genre_;
   this->rating_ = rating_;
}

std::set<std::string> Movies::keywords() const
{
   std::set<std::string> result;

   result = parseStringToWords(this->name_);

   result.insert(convToLower(this->genre_));

   return result;
}

std::string Movies::displayString() const
{
   std::string displayString = this->name_ + "\n" + "Genre: " + this->genre_ + " Rating: " + this->rating_ + "\n" + std::to_string(this->price_) + " " + std::to_string(this->qty_) + " left.\n";
   return displayString;
}

void Movies::dump(std::ostream &os) const
{
   os << "movie" << std::endl;
   os << this->name_ << std::endl;
   os << this->price_ << std::endl;
   os << this->qty_ << std::endl;
   os << this->genre_ << std::endl;
   os << this->rating_ << std::endl;
}