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

//get the maps from named pipes
std::map<std::string, int> recieve_words(int mapper_count);

// count all instances of given words
