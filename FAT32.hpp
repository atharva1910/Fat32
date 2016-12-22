#include <iostream>
#include <fstream>

struct FileEntry{
    char name[20]; // 20
    unsigned int size; //4
    std::streampos pos;
};

struct FreeSpace{
    uint64_t pos;
    int size;
};

int mount(char *,char *);

void reserve_table_space(std::ofstream &);

bool check_if_empty (std::ifstream &);

void populate_file_struct(struct FileEntry *);
