#include "ladder.h"
#include <algorithm>
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

    for (int i = 1; i <= str1_len; ++i) {
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
    return prev[str2_len] <= d;
} // checks whether or not the edit dstance between str1 and str2 is within d (going to be 1 for this homework)

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1); // edit distance of 1 allowed for adjacency
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> word_ladder;
    set<string> seen;
    word_ladder.push({begin_word});
    seen.insert(begin_word);
    while (!word_ladder.empty()) {
        vector<string> curr = word_ladder.front();
        word_ladder.pop();
        string last = curr.back();
        for (const string& word : word_list) {
            if (is_adjacent(last, word) && !seen.count(word)) {
                vector<string> new_ladder = curr;
                new_ladder.push_back(word);
                if (word == end_word) return new_ladder;
                seen.insert(word);
                word_ladder.push(new_ladder);
            }
        }
    }
    return {}; // generates the word ladder, checking each word in the word list for adjacency and adding the new ladder to the queue or returns an empty vector with no ladder
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error opening file: " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    } // loads word from text file into the word list for processing
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << ladder[i];
    }
    cout << endl; // prints out the word ladder into the proper format
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
} // verifies whether the word ladder actually generates properly and wworks properly
