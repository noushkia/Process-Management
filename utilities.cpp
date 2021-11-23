#include "utilities.hpp"

using namespace std;

void decode_dict(char *msg, std::map<std::string, int> &words)
{
    string word_count;
    stringstream word_counts(msg);
    while (getline(word_counts, word_count))
    {
        int seperator_idx = word_count.find(KEY_VAL_SEPERATOR);
        string word = word_count.substr(0, seperator_idx);
        int count = stoi(word_count.substr(seperator_idx+1, word_count.size()-seperator_idx));

        if (words.find(word) == words.end())
            words[word] += count;
        else
            words[word] = count;
    }
}
