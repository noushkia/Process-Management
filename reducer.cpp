#include "reducer.hpp"

using namespace std;

std::map<std::string, int> recieve_words()
{
    map<string, int> words;
    int fifo_id = open(FIFO_REDUCE, O_RDONLY);
    char msg[MAX_LEN];
    while (read(fifo_id, msg, MAX_LEN))
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
    close(fifo_id); 
    return words;
}

int main(int argc, char *argv[])
{
    int fdwrite = atoi(argv[1]);
    int fifo_fd = open(FIFO_REDUCE, O_RDONLY);

    if (fifo_fd < 0)
        cerr << "Failed to open fifo file!" << endl;

    map<string, int> words = recieve_words();
    
    string words_str = "";
    for (auto word : words)
    {
        string str = word.first + KEY_VAL_SEPERATOR + to_string(word.second) + "\n";
        words_str += str;
    }
    write(fdwrite, words_str.c_str(), MAX_LEN);
    close(fdwrite);
    
    return 0;
}