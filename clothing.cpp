#include "clothing.h"
#include "util.h"
#include <iostream>
#include <set>

Clothing::Clothing(std::string category_, std::string name_, double price_, int qty_, std::string size_, std::string brand_) : Product(category_, name_, price_, qty_)
{
   this->size_ = size_;
   this->brand_ = brand_;
}

std::set<std::string> Clothing::keywords() const {
  
   std::set<std::string> result;
   std::set<std::string> nameSet = parseStringToWords(this->name_);
   std::set<std::string> brandSet = parseStringToWords(this->brand_);

   result = setUnion(nameSet, brandSet);
   
   return result;
}

std::string Clothing::displayString() const {
   std::string displayString = this->name_ + "\n" + "Size: " + this->size_ + " Brand: " + this->brand_ + "\n" + std::to_string(this->price_) + " " + std::to_string(this->qty_) + " left.\n";
   return displayString;
}

void Clothing::dump(std::ostream& os) const {
   os << "clothing" << std::endl;
   os << this -> name_ << std::endl;
   os << this -> price_ << std::endl;
   os << this -> qty_ << std::endl;
   os << this -> size_ << std::endl;
   os << this -> brand_ << std::endl;
}