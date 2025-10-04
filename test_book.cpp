#include "book.h"
#include <iostream>
using namespace std;

int main() {
    Book b("book", "Great Men and Women of Troy", 19.50, 5,
           "978-000000000-1", "Tommy Trojan");

    cout << "--- displayString() ---" << endl;
    cout << b.displayString() << endl;

    cout << "--- keywords() ---" << endl;
    set<string> keys = b.keywords();
    for(set<string>::iterator it = keys.begin(); it != keys.end(); ++it) {
        cout << *it << endl;
    }
    return 0;
}
