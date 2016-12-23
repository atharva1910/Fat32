
#include "FAT32.hpp"

void reserve_table_space(std::ofstream &fp)
/*
 * Clear the first 512bytes of the file
 * and next 256 for freespace bitmap
 * for the file tables 
 */
{
    fp.seekp(0, std::ios::beg);
    const char c = 'a';
    for (int i = 0; i < 512+256; i++) {
        fp.write(&c, sizeof(c));
    }
    // wirte the first freespace struct
    fp.seekp(512);
    struct FreeSpace *temp = new struct FreeSpace;
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

size_t write_file_to_buffer()
/*
 * Create a buffer to write the file
 * call function reserve_space to
 * reserve the space on the memory block 
 */
{
    std::cout <<"Enter the contents of the file" << "\n";
    char a;
    while(std::cin >> a){
        buffer.push_back(a);
    }
    return buffer.size();
}

void write_to_disk(size_t size, std::ofstream &fp)
{
    std::ifstream rp;
    rp.open("Harddisk");
    std::streampos pos;
    rp.seekg(512, std::ios::beg);
    char *reads = new char [sizeof(struct FreeSpace)];
    rp.read(reads, sizeof(struct FreeSpace));
    std::cout << "Reading  " << reads << "\n";
    while(true);
    /*
    struct FreeSpace *file = (struct FreeSpace *)read;
    std::cout << file->size  << "\n";
    std::cout << file->pos << "\n";
    fp.write((char *)&buffer, sizeof(buffer));
    */
}

int main()
{
    std::ofstream fp;
    fp.open("Harddisk", std::ios::binary);
    //    readFile.open("Harddisk", std::ios::binary);
    //    if (check_if_empty(readFile))
            reserve_table_space(fp);

    int option;
    do{
        std::cout <<"1. Create file entry \n2. Delete file entry "  << "\n";
        std::cin >> option;
        switch(option){
        case 1:{
            std::cout << "Enter the name of the file:"  << "\n";
            struct FileEntry *temp = new struct FileEntry;
            std::cin >> temp->name;
            size_t size = write_file_to_buffer();
            write_to_disk(size, fp);
        }break;

        case 2:{
            
        }break;
        }
    }while(option != 3);
    fp.close();
    return 0;
}
