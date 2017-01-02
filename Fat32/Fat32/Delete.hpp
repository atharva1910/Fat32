#pragma once
#include "main.hpp"

struct delete_spec {
	unsigned int table_pos;
	unsigned int size;
	unsigned int pos;
};

delete_spec
search_for_file(char *, std::ifstream &);

void
delete_file_entry(unsigned int, std::ofstream &);

bool
add_size_to_bitmap(unsigned int, unsigned int, std::ofstream &, std::ifstream &);