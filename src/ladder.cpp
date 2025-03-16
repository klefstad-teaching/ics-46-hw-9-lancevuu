#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " - " << word1 << ", " << word2 << endl; // prints out error message
}