#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product
{

private:
   std::string size_;
   std::string brand_;

public:
   Clothing(std::string category_, std::string name_, double price_, int qty_, std::string size_, std::string brand_);

   std::set<std::string> keywords() const;
   std::string displayString() const;
   void dump(std::ostream &os) const;
};

#endif