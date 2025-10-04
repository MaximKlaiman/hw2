#include "book.h"
#include "util.h"
#include <string>

using namespace std;

Book::Book(const std::string& category,
           const std::string& name,
           double price,
           int qty,
           const std::string& isbn,
           const std::string& author)
    : Product(category, name, price, qty),
      isbn_(isbn),
      author_(author)
{
}

Book::~Book() { }

set<string> Book::keywords() const
{
    set<string> keys = parseStringToWords(name_);
    set<string> authWords = parseStringToWords(author_);
    keys.insert(authWords.begin(), authWords.end());
    keys.insert(isbn_);
    return keys;
}

string Book::displayString() const
{
    string result;
    result += name_ + "\n";
    result += "Author: " + author_ + " ISBN: " + isbn_ + "\n";
    result += to_string(price_) + " " + to_string(qty_) + " left.";
    return result;
}

void Book::dump(ostream& os) const
{
    os << "book" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << isbn_ << endl;
    os << author_ << endl;
}
