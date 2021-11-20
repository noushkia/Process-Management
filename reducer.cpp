#include "reducer.hpp"

using namespace std;

std::map<std::string, int> recieve_words()
{
    map<string, int> words;
    int fifo_id = open(FIFO_REDUCE, O_RDONLY);
    char msg[MAX_LEN];
    while (read(fifo_id, msg, MAX_LEN))
    {
        string word_count = msg;
        int seperator_idx = word_count.find(KEY_VAL_SEPERATOR);
        if (seperator_idx == string::npos)
        {
            cerr << "invalid input!\n" << endl;
            continue;
        }

        string word = word_count.substr(0, seperator_idx);
        int count = stoi(word_count.substr(seperator_idx+1, word_count.size()-seperator_idx));

        if (words.find(word) != words.end())
            words[word] += count;
        else
            words.insert({word, count});

        cout << word << KEY_VAL_SEPERATOR << count << endl;
    }

    close(fifo_id); 
    return words;
}

int main()
{
    int fifo_fd = open(FIFO_REDUCE, O_RDONLY);

    if (fifo_fd < 0)
        cerr << "Filed to open fifo file!" << endl;

    map<string, int> words = recieve_words();
    
    //send the words back to main

    return 0;
}