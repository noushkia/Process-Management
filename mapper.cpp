#include "mapper.hpp"

using namespace std;

std::vector<std::string> read_file(const std::string &file)
{
    vector<string> words;
    ifstream input_file(file);

    if(!input_file.is_open()) 
        throw std::runtime_error("Could not open file!");

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

    for (auto const& word:mapped_words)
        cout << word.first << ": " << word.second << endl;

    return mapped_words;
}

int main(int argc, char *argv[])
{
    string file = string(argv[1]);
    cout << file << " assigned to a mapper."  << endl << endl;
    
    vector<string> words = read_file(file);

    cout << "Mapper mapped the words for file: " << file << endl;

    map<string, int> mapped_words = map_words(words);

    //send the map to reducer (open named pipe and send it)

    return 0;
}