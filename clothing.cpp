#include "clothing.h"
#include "util.h"
#include <string>

using namespace std;

Clothing::Clothing(const std::string& category,
                   const std::string& name,
                   double price,
                   int qty,
                   const std::string& size,
                   const std::string& brand)
    : Product(category, name, price, qty),
      size_(size),
      brand_(brand)
{
}

Clothing::~Clothing() { }

set<string> Clothing::keywords() const
{
    set<string> keys = parseStringToWords(name_);
    set<string> brandWords = parseStringToWords(brand_);
    keys.insert(brandWords.begin(), brandWords.end());
    return keys;
}

string Clothing::displayString() const
{
    string result;
    result += name_ + "\n";
    result += "Size: " + size_ + " Brand: " + brand_ + "\n";
    result += to_string(price_) + " " + to_string(qty_) + " left.";
    return result;
}

void Clothing::dump(ostream& os) const
{
    os << "clothing" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << size_ << endl;
    os << brand_ << endl;
}
