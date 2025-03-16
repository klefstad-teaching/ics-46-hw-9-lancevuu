#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " - " << word1 << ", " << word2 << endl; // prints out error message
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int str1_len = str1.length();
    int str2_len = str2.length();
    if (abs(str1_len - str2_len) > d) return false;
    vector<int> prev(str2_len + 1), curr(str2_len + 1);
    for (int j = 0; j <= str2_len; ++j) prev[j] = j;

    for (int i = 1; i <= sr1_len; ++i) {
        curr[0] = i;
        int minimum = curr[0];
        for (int j = 1; j <= str2_len; ++j) {
            if (str1[i - 1] == str2[j - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = min({prev[j - 1] + 1, prev[j] + 1, curr[j - 1] + 1});
            minimum = min(minimum, curr[j]);
        }
        if (minimum > d) return false;
        swap(prev, curr);
    }
    return prev[len2] <= d;
} // checks whether or not the edit dstance between str1 and str2 is within d (going to be 1 for this homework)