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

bool write_to_pipe(map<string, int> &mapped_words)
{

    if (mkfifo(FIFO_REDUCE, 0777) == -1 && errno != EEXIST)
    {
        cerr << "Failed to open fifo file for mapper"  << endl;
        return 0;
    }

    int fifo_id = open(FIFO_REDUCE, O_WRONLY);
    for (auto const& word:mapped_words)
    {
        string str = word.first + KEY_VAL_SEPERATOR + to_string(word.second);
        cout << "Mapper writing " << str << " to reducer" << endl;
        write(fifo_id, str.c_str(), str.size()+1);
    }
    close(fifo_id);

    return 1;
}

int main(int argc, char *argv[])
{
    string file = string(argv[1]);
    cout << file << " assigned to a mapper."  << endl << endl;
    
    vector<string> words = read_file(file);

    map<string, int> mapped_words = map_words(words);

    if (write_to_pipe(mapped_words) == 0)
    {
        cerr << "Error sending words to reducer!" << endl;
        return 1;
    }

    //send the map to reducer (open named pipe and send it)

    return 0;
}