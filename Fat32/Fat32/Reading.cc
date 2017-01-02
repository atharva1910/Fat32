#include "Reading.hpp"

int
read_table(std::ifstream &rp, char *name)
/*
 * Check if the given name exists in the
 * file table entry
 */
{
    unsigned int return_pos;
    unsigned int pos = 0;
    rp.seekg(pos, std::ios::beg);
    char match[20];

    // Check the entrie file table for similar name
    while(pos < 512){
        rp.read((char *)&match ,sizeof(match));
        return_pos = rp.tellg();        
        if(strcmp(match, name) == 0)
            return return_pos;
        pos = pos + 2 *sizeof(unsigned int);
        rp.seekg(pos, std::ios::beg);
    }
    return 0;
}


void
read_file(std::ifstream &rp, unsigned int pos)
/*
 * get the positon at the file table where postion
 * and size is stored.
 * Read the actual file from the harddisk 
 */
{
    // Read the postion and size of the file
    rp.seekg(pos, std::ios::beg);
    unsigned int size,position;
    rp.read((char*)&position, sizeof(unsigned int));
    rp.read((char*)&size, sizeof(unsigned int));
    
    // Jump to position of file
    rp.seekg(position, std::ios::beg);
    char *buff = new char[size];
    rp.read((char *)&buff, size);
    std::cout << buff << "\n";
    delete[] buff;
}
