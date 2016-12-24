#include "FAT32.hpp"

void reserve_table_space(std::ofstream &fp)
/*
 * Clear the first 512bytes of the file
 * and next 256 for freespace bitmap
 * for the file tables 
 */
{
    std::cout << "Harddisk empty" << "\n";
    fp.seekp(0, std::ios::beg);
    const char c = 0;
    for (int i = 0; i < 512+256; i++) {
        fp.write(&c, sizeof(c));
    }

    // wirte the first freespace struct
    fp.seekp(512);
    int pos = 512+257;
    int size = 20000;
    fp.write((char *)&pos, sizeof(pos));
    fp.write((char *)&size, sizeof(size));
    fp.flush();
}

bool check_if_empty(std::ifstream &fp)
/*
 * Checks if the file is empty
 */
{
    fp.seekg(0, std::ios::end);
    std::streampos end = fp.tellg();
    return (end == 0)? true : false;
}

size_t write_file_to_buffer()
/*
 * Create a buffer to write the file
 * and return size for error checking
 */
{
    std::cout <<"Enter the contents of the file" << "\n";
    char a;
    buffer.clear();
    while(std::cin >> a){
        buffer.push_back(a);
    }
    return buffer.size();
}

unsigned int write_to_disk(size_t size, std::ofstream &fp, std::ifstream &rp)
/*
 * Write files to the location on harddisk 
 * and call function to make a file table
 */
{
    if (buffer.size() != size){
        std::cout << "Error writing to disk" << "\n";
        return 0;
    }
    rp.seekg(512, std::ios::beg);
    unsigned int pos; size_t sizes;
    unsigned int bitmap_update_pos;
    do{
    bitmap_update_pos = rp.tellg();        
    rp.read((char *)&pos, sizeof(pos));
    rp.read((char *)&sizes, sizeof(sizes));
    }while(sizes != 0 && sizes > size);
    update_bitmap(bitmap_update_pos, size, sizes, fp);
    fp.seekp(pos);
    fp.write((char *)&buffer, sizeof(buffer));
    fp.flush();
    return pos;
}

void update_bitmap(unsigned int pos, size_t size, size_t sizes, std::ofstream &fp)
/*
 *
 */
{
    fp.seekp(pos, std::ios::beg);
    unsigned int value = pos + size;
    fp.write((char *)&value, sizeof(value));
    size_t updated_size = size - sizes;
    fp.write((char *)&updated_size, sizeof(updated_size));
    fp.flush();
}

void make_file_table(char *name, size_t size, unsigned int pos, std::ofstream &fp, std::ifstream &rp)
/*
 * Make a file table entry as follows:
 * Name char[20]
 * pos  uint
 * size uint
 */
{
    rp.seekg(0, std::ios::beg);
    char *name_check = new char[20];
    int pos_check, size_check, fp_pos;
    do{
        fp_pos = rp.tellg();
        rp.read(name_check, sizeof(name_check));
        rp.read((char *)&pos_check, sizeof(pos_check));
        rp.read((char *)&size_check, sizeof(size_check));
    }while(name_check != NULL);
    fp.seekp(fp_pos);
    fp.write(name, sizeof(name));
    fp.write((char *)&pos, sizeof(pos));
    fp.write((char *)&size, sizeof(size));
    fp.flush();
    while(true);
}

int main()
{
    std::ofstream fp;
    fp.open("Harddisk", std::ios::binary);
    std::ifstream rp;
    rp.open("Harddisk", std::ios::binary);
    rp.tie(&fp);
    if (check_if_empty(rp))
            reserve_table_space(fp);
    int option;
    do{
        std::cout <<"1. Create file entry \n2. Delete file entry "  << "\n";
        std::cin >> option;
        switch(option){
        case 1:{
            std::cout << "Enter the name of the file:"  << "\n";
            char *name = new char[20];
            std::cin >> name;
            size_t size = write_file_to_buffer();
            unsigned int pos = write_to_disk(size, fp, rp);
            if(pos)
                make_file_table(name, size, pos, fp, rp);
        }break;

        case 2:{
            
        }break;
        }
    }while(option != 3);
    fp.close();
    return 0;
}
