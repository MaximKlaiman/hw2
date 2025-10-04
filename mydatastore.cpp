#include "mydatastore.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    for(Product* p : products_) {
        delete p;
    }
    for(User* u : users_) {
        delete u;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);

    set<string> keys = p->keywords();
    for(const string& key : keys) {
        string lowerKey = key;
        transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);
        keywordMap_[lowerKey].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    users_.push_back(u);

    string uname = u->getName();
    transform(uname.begin(), uname.end(), uname.begin(), ::tolower);
    carts_[uname] = vector<Product*>();
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    vector<Product*> hits;

    if(terms.empty()) return hits;

    vector<string> termsLower;
    for(string t : terms) {
        transform(t.begin(), t.end(), t.begin(), ::tolower);
        termsLower.push_back(t);
    }

    if(type == 1) {
        set<Product*> result;
        for(string t : termsLower) {
            if(keywordMap_.count(t)) {
                result = setUnion(result, keywordMap_[t]);
            }
        }
        hits.insert(hits.end(), result.begin(), result.end());
    }
    else {
        set<Product*> result;
        bool first = true;
        for(string t : termsLower) {
            if(keywordMap_.count(t)) {
                if(first) {
                    result = keywordMap_[t];
                    first = false;
                } else {
                    result = setIntersection(result, keywordMap_[t]);
                }
            }
        }
        hits.insert(hits.end(), result.begin(), result.end());
    }
    return hits;
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << std::endl;
    for(size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    for(size_t j = 0; j < users_.size(); j++) {
        users_[j]->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

bool MyDataStore::addToCart(const std::string& uname, Product* p)
{
    string lower = uname;
    for(size_t i = 0; i < lower.size(); i++) {
        lower[i] = tolower(lower[i]);
    }

    if(carts_.find(lower) == carts_.end()) {
        return false;
    }
    carts_[lower].push_back(p);
    return true;
}

bool MyDataStore::viewCart(const std::string& uname)
{
    string lower = uname;
    for(size_t i = 0; i < lower.size(); i++) {
        lower[i] = tolower(lower[i]);
    }

    if(carts_.find(lower) == carts_.end()) {
        return false; 
    }

    vector<Product*>& cart = carts_[lower];
    for(size_t i = 0; i < cart.size(); i++) {
        cout << "Item " << (i+1) << endl;
        cout << cart[i]->displayString() << endl;
        cout << endl;
    }
    return true;
}

bool MyDataStore::buyCart(const std::string& uname)
{
    string lower = uname;
    for(size_t i = 0; i < lower.size(); i++) {
        lower[i] = tolower(lower[i]);
    }

    if(carts_.find(lower) == carts_.end()) {
        return false; 
    }

    User* buyer = NULL;
    for(size_t i = 0; i < users_.size(); i++) {
        string u = users_[i]->getName();
        for(size_t j = 0; j < u.size(); j++) {
            u[j] = tolower(u[j]);
        }
        if(u == lower) {
            buyer = users_[i];
            break;
        }
    }
    if(buyer == NULL) return false;

    vector<Product*>& cart = carts_[lower];
    vector<Product*> remaining; 

    for(size_t i = 0; i < cart.size(); i++) {
        Product* p = cart[i];
        if(p->getQty() > 0 && buyer->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            buyer->deductAmount(p->getPrice());
        }
        else {
            remaining.push_back(p);
        }
    }

    cart = remaining; 
    return true;
}
