#include "FAT32.hpp"

void reserve_table_space(std::ofstream &fp)
/*
 * Clear the first 512bytes of the file
 * and next 256 for freespace bitmap
 * for the file tables 
 */
{
    const char c = 0;
    for (int i = 0; i < 512+256; i++) {
        fp.write(&c, sizeof(c));
    }
    
    // wirte the first freespace struct
    fp.seekp(512);
    struct FreeSpace *temp = (struct FreeSpace *)malloc(sizeof(struct FreeSpace));
    temp->pos = 512+257;
    temp->size = 20000;
    fp.write((char *)&temp->pos, sizeof(temp->pos));
    fp.write((char *)&temp->size, sizeof(temp->size));
}

bool check_if_empty(std::ifstream &fp)
/*
 * Checks if the file is empty
 * peek -> peeks into file if empty return eof 
 */
{
    fp.seekg(0, std::ios::end);
    std::streampos end = fp.tellg();
    return (end == 0)? true : false;
}

void populate_file_struct(struct FileEntry *fe)
/*
 * Populate the file structure
 * so it can be stored in the
 * file table
 */
{
    std::cout << "Enter name of the file" << "\n";
    std::cin >> fe->name;
}

int main()
{
    std::ofstream fp;
    std::ifstream readFile;
    fp.open("Harddisk", std::ios::binary);
    readFile.open("Harddisk");

    if (check_if_empty(readFile)){
            std::cout <<" Harddisk empty"  << "\n";
            reserve_table_space(fp);
    }
    int option;
    do{
        std::cout <<"1. Create file entry \n2. Delete file entry "  << "\n";
        std::cin >> option;
        switch(option){
        case 1:{

        }break;

        case 2:{
            
        }break;
        }
    }while(option != 3);
    fp.close();
    return 0;
}
