#include "util.h"
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<string> words = parseStringToWords("Men's Fitted Shirt!! I'll go.");
    for(set<string>::iterator it = words.begin(); it != words.end(); ++it) {
        cout << *it << endl;
    }
    return 0;
}