#include "reducer.hpp"

using namespace std;

std::map<std::string, int> recieve_words(int mapper_count)
{
    map<string, int> words;
    for(int i = 1; i <= mapper_count; i++)
    {   
        string fifofile = FIFO_REDUCE+to_string(i);
        int fifo_id = open(fifofile.c_str(), O_RDONLY);
        char msg[MAX_LEN];
        while (read(fifo_id, msg, MAX_LEN))
            decode_dict(msg, words);

        close(fifo_id);
    }

    return words;
}

int main(int argc, char *argv[])
{
    int fdwrite = atoi(argv[1]);

    map<string, int> words = recieve_words(atoi(argv[2]));
    
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
