#include "mydatastore.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include <iostream>
using namespace std;

int main() {
    MyDataStore ds;

    Product* b = new Book("book", "Hidden Data", 10.0, 2, "12345", "John Doe");
    Product* c = new Clothing("clothing", "Men's Shirt", 20.0, 3, "M", "Nike");
    Product* m = new Movie("movie", "Hidden Figures DVD", 15.0, 1, "Drama", "PG");

    ds.addProduct(b);
    ds.addProduct(c);
    ds.addProduct(m);

    vector<string> terms;
    terms.push_back("hidden");
    vector<Product*> hits = ds.search(terms, 1);

    cout << "--- Search Results ---" << endl;
    for(size_t i = 0; i < hits.size(); i++) {
        cout << hits[i]->displayString() << endl;
    }

    return 0;
}
