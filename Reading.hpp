#ifndef READING_HPP_
#define READING_HPP_

#include "main.hpp"
#include <cstring>

int
read_table(std::ifstream&, char *);

void
read_file(std::ifstream&, unsigned int);
#endif
