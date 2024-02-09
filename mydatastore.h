#ifndef MY_DATASTORE_H
#define MY_DATASTORE_H
#include <unordered_map>
#include <set>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include "product.h"
#include "datastore.h"
#include "user.h"
#include "util.h"

class MyDataStore : public DataStore
{

private:
   std::unordered_map<std::string, std::set<Product *>> dataMap;
   std::set<Product *> productsSet;
   std::set<User *> usersSet;
   std::unordered_map<User *, std::queue<Product *>> userMap;

public:
   MyDataStore()
   {
   }

   ~MyDataStore()
   {
      for (std::set<Product *>::iterator iter = productsSet.begin(); iter != productsSet.end(); ++iter)
      {
         delete *iter;
      }

      for (std::set<User *>::iterator iter = usersSet.begin(); iter != usersSet.end(); ++iter)
      {
         delete *iter;
      }
   }

   /**
    * Adds a product to the data store
    */
   void addProduct(Product *p);

   /**
    * Adds a user to the data store
    */
   void addUser(User *u);

   /**
    * Performs a search of products whose keywords match the given "terms"
    *  type 0 = AND search (intersection of results for each term) while
    *  type 1 = OR search (union of results for each term)
    */
   std::vector<Product *> search(std::vector<std::string> &terms, int type);

   /**
    * Reproduce the database file from the current Products and User values
    */
   void dump(std::ostream &ofile);

   void addCart(std::string username, int search_hit_number, std::vector<Product *> &hits);
   void viewCart(std::string username);
   void purchaseCart(std::string username);
};

#endif
