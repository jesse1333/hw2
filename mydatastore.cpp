#include "mydatastore.h"
#include "util.h"
#include <iostream>
using namespace std;

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product *p)
{
   // create a map of keywords that map to a set of Product pointers that point to products associated with keywords
   productsSet.insert(p);
   set<string> s1;
   s1 = p->keywords();

   for (set<string>::iterator iter = s1.begin(); iter != s1.end(); ++iter)
   {
      // if not found
      if (dataMap.find(*iter) == dataMap.end())
      {
         set<Product *> productSet;
         productSet.insert(p);
         dataMap[*iter] = productSet;
      }

      // if found already
      else
      {
         dataMap[*iter].insert(p);
      }
   }
}

/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User *u)
{
   queue<Product *> cart;
   userMap[u] = cart;
   usersSet.insert(u);
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product *> MyDataStore::search(std::vector<std::string> &terms, int type)
{
   set<Product *> result;
   bool firstPass = false;

   for (vector<string>::iterator iter = terms.begin(); iter != terms.end(); ++iter)
   {
      // edge case of 1 keyword
      if (firstPass == false)
      {
         if (dataMap.find(convToLower(*iter)) != dataMap.end())
         {
            result = dataMap[*iter];
         }
         firstPass = true;
         continue;
      }

      // if keyword is found
      if (dataMap.find(convToLower(*iter)) != dataMap.end())
      {
         if (type == 0)
         {
            set<Product *> temp = setIntersection(result, dataMap[*iter]);
            result = temp;
         }

         else if (type == 1)
         {
            set<Product *> temp = setUnion(result, dataMap[*iter]);
            result = temp;
         }
      }
   }

   vector<Product *> resultVect(result.begin(), result.end());
   return resultVect;
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream &ofile)
{
   ofile << "<products>\n";
   for (set<Product *>::iterator iter = productsSet.begin(); iter != productsSet.end(); ++iter)
   {
      (*iter)->dump(ofile);
   }
   ofile << "</products>\n";
   ofile << "<users>\n";

   for (set<User *>::iterator iter = usersSet.begin(); iter != usersSet.end(); ++iter)
   {
      (*iter)->dump(ofile);
   }
   ofile << "</users>\n";
}

void MyDataStore::addCart(string username, int search_hit_number, vector<Product *> &hits)
{
   bool validInput = false;
   for (unordered_map<User *, std::queue<Product *>>::iterator iter = userMap.begin(); iter != userMap.end(); ++iter)
   {
      if (iter->first->getName() == username)
      {
         validInput = true;
         iter->second.push(hits[search_hit_number - 1]);
      }
   }

   if (!validInput) {
      cout << "Invalid request" << endl;
   }
}

void MyDataStore::viewCart(string username) {
   int itemNum = 1;
   bool validUsername = false;

   for (unordered_map<User *, std::queue<Product *>>::iterator iter = userMap.begin(); iter != userMap.end(); ++iter)
   {
      if (iter->first->getName() == username)
      {
         validUsername = true;
         queue<Product *> tempQueue = iter->second;

         while (!tempQueue.empty())
         {
            cout << "Item " << itemNum << endl;
            cout << tempQueue.front()->displayString();
            tempQueue.pop();
            itemNum++;
         }
      }
   }

   if (!validUsername) {
      cout << "Invalid username" << endl;
   }
}

void MyDataStore::purchaseCart(string username) {
   bool nameChecked = false;
   queue<Product*> temp;

   for (unordered_map<User *, std::queue<Product *>>::iterator iter = userMap.begin(); iter != userMap.end(); ++iter)
   {
      if (convToLower(iter->first->getName()) == convToLower(username))
      {
         nameChecked = true;

         // if you can purchase
         while (!iter -> second.empty())
         {
            if (iter->first->getBalance() >= iter->second.front()->getPrice() && iter->second.front()->getQty() > 0) {
               iter->first->deductAmount(iter->second.front()->getPrice());
               iter->second.front()->subtractQty(1);
               iter->second.pop();
            }

            else {
               temp.push(iter->second.front());
               iter -> second.pop();
            }
         }

         while (!iter->second.empty()) {
            temp.push(iter->second.front());
            iter->second.pop();
         }
         iter -> second = temp;

         while (!temp.empty()) {
            temp.pop();
         }
      }
   }

   if (!nameChecked) {
      cout << "Invalid username" << endl; 
   }
}