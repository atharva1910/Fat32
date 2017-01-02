#include "Writing.hpp"

std::vector<char> buffer;

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
    unsigned int pos = 512+257;
    unsigned int size = 20000;
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
    unsigned int pos, sizes = 0;
    unsigned int bitmap_update_pos;
    while(sizes == 0 && size > sizes){
        bitmap_update_pos = rp.tellg();
        rp.read((char *)&pos, sizeof(pos));
        rp.read((char *)&sizes, sizeof(sizes));
    }
    fp.seekp(pos, std::ios::beg);
    fp.write((char *)&buffer, sizeof(buffer));
    fp.flush();
    update_bitmap(bitmap_update_pos, size, sizes, fp);    
    return pos;
}

void update_bitmap(unsigned int pos, size_t size, size_t sizes, std::ofstream &fp)
/*
 * Update the current bitmap 
 * reduce the value of the size
 * and remap the pos 
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
    }while(!name_check);
    fp.seekp(fp_pos);
    fp.write(name, 20);
    fp.write((char *)&pos, sizeof(pos));
    fp.write((char *)&size, sizeof(size));
    fp.flush();
}
