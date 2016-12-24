#include <iostream>
#include <vector>
#include <fstream>

/*
Table entry:      FreespaceEntry:
name;             pos;
pos;              size;
size;

 */


std::vector<char> buffer;

int mount(char *,char *);

void reserve_table_space(std::ofstream &);

bool check_if_empty (std::ifstream &);

void populate_file_struct(struct FileEntry *);

size_t write_file_to_buffer();

unsigned int write_to_disk(size_t, std::ofstream&, std::ifstream&);

void make_file_table(char *, size_t, unsigned int, std::ofstream&, std::ifstream&);

void update_bitmap(unsigned int, size_t, size_t, std::ofstream&); 
