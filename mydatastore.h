#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include <map>
#include <queue>

/**
 * MyDataStore implements the DataStore interface
 */
class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    // Inherited virtuals
    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;
    bool addToCart(const std::string& uname, Product* p);
    bool viewCart(const std::string& uname);
    bool buyCart(const std::string& uname);


private:
    std::vector<Product*> products_;
    std::vector<User*> users_;

    // keyword → set of matching products
    std::map<std::string, std::set<Product*>> keywordMap_;

    // username (lowercased) → cart
    std::map<std::string, std::vector<Product*>> carts_;
};

#endif
