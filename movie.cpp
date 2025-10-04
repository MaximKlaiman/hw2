#include "movie.h"
#include "util.h"
#include <string>

using namespace std;

Movie::Movie(const std::string& category,
             const std::string& name,
             double price,
             int qty,
             const std::string& genre,
             const std::string& rating)
    : Product(category, name, price, qty),
      genre_(genre),
      rating_(rating)
{
}

Movie::~Movie() { }

set<string> Movie::keywords() const
{
    set<string> keys = parseStringToWords(name_);
    // genre is a verbatim keyword
    keys.insert(genre_);
    return keys;
}

string Movie::displayString() const
{
    string result;
    result += name_ + "\n";
    result += "Genre: " + genre_ + " Rating: " + rating_ + "\n";
    result += to_string(price_) + " " + to_string(qty_) + " left.";
    return result;
}

void Movie::dump(ostream& os) const
{
    os << "movie" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << genre_ << endl;
    os << rating_ << endl;
}
