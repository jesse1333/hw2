#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"

class Movies : public Product
{

private:
   std::string genre_;
   std::string rating_;

public:
   Movies(std::string category_, std::string name_, double price_, int qty_, std::string genre_, std::string rating_);

   std::set<std::string> keywords() const;
   std::string displayString() const;
   void dump(std::ostream &os) const;
};

#endif