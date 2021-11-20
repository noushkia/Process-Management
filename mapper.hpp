#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "defs.hpp"

// read data from given file path and return the words
std::vector<std::string> read_file(const std::string &file);

// given words of a file, map each word and count it's instances in that file
// KEY: word string
// VALUE: word occurance count
std::map<std::string, int> map_words(const std::vector<std::string> &words);

// write the mapped words to named pipe for reducer to recieve it
bool write_to_pipe(std::map<std::string, int> &mapped_words);
