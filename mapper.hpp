#ifndef MAPP_HPP
#define MAPP_HPP

#include "libs.hpp"
#include "defs.hpp"
#include "utilities.hpp"

// read data from given file path and return the words
std::vector<std::string> read_file(const std::string &file);

// given words of a file, map each word and count it's instances in that file
// KEY: word string
// VALUE: word occurance count
std::map<std::string, int> map_words(const std::vector<std::string> &words);

// write the mapped words to named pipe for reducer to recieve it
bool write_to_pipe(std::map<std::string, int> &mapped_words, std::string mapper_id);

#endif
