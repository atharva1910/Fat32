#include <iostream>
#include <vector>
#include <fstream>

std::vector<char> buffer;

struct FileEntry{
    char name[20]; // 20
    uint64_t size;
    std::streampos pos;
};

struct FreeSpace{
    int pos;
    uint64_t size;
};

int mount(char *,char *);

void reserve_table_space(std::ofstream &);

bool check_if_empty (std::ifstream &);

void populate_file_struct(struct FileEntry *);

size_t write_file_to_buffer();

void write_to_disk(size_t, std::ofstream&);
