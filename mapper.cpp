#include "mapper.hpp"

using namespace std;

std::vector<std::string> read_file(const std::string &file)
{
    vector<string> words;
    ifstream input_file(file);

    if(!input_file.is_open()) 
        throw std::runtime_error("Could not open file " + file);

    string line;
    //read the file line by line
    while(getline(input_file, line, DELIM))
    {
        stringstream ss(line);
        
        string word;
        while(ss >> word)
            words.push_back(word);
        
    }
    
    input_file.close();

    return words;
}

std::map<std::string, int> map_words(const std::vector<std::string> &words)
{
    map<string, int> mapped_words;

    for (auto word:words)
    {
        if (mapped_words.find(word) != mapped_words.end())
            mapped_words[word]++;
        else
            mapped_words.insert({word, 1});
    }    
    
    return mapped_words;
}

bool write_to_pipe(map<string, int> &mapped_words, string mapper_id)
{
    string fifo_file = FIFO_REDUCE;

    if (mkfifo(FIFO_REDUCE, 0777) == -1 && errno != EEXIST)
    {
        cerr << "Failed to open fifo file for mapper"  << endl;
        return 0;
    }

    int fifo_id = open(fifo_file.c_str(), O_WRONLY);

    cout << "Mapper " << mapper_id << ": Sending mapped words to reducer using file " << fifo_id << endl;
    string words = "";
    for (auto word:mapped_words)
    {
        string str = word.first + KEY_VAL_SEPERATOR + to_string(word.second) + "\n";
        words+=str;
    }
    write(fifo_id, words.c_str(), MAX_LEN);
    close(fifo_id);

    return 1;
}

int main(int argc, char *argv[])
{
    string file = string(argv[1]);
    regex rgx(".*(\\w+)\\.csv.*");
    smatch match;
    if (!regex_search(file, match, rgx))
        cerr << "Invalid arguments for mapper!" << endl;

    cout << file << " assigned to mapper " << match[1] << endl << endl;

    vector<string> words = read_file(file);
    cout << "Mapper " << match[1] << ": read from file\n";

    map<string, int> mapped_words = map_words(words);
    cout << "Mapper " << match[1] << ": mapped words\n";

    if (write_to_pipe(mapped_words, match[1]) == 0)
    {
        cerr << "Error sending words to reducer!" << endl;
        return 1;
    }

    return 0;
}