#ifndef UTIL_HPP
#define UTIL_HPP

#include "libs.hpp"
#include "defs.hpp"

// decode read string from named pipe
void decode_dict(char *msg, std::map<std::string, int> &words);

#endif
