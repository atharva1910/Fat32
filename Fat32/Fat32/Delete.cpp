#include "Delete.hpp"

delete_spec
search_for_file(char *name, std::ifstream &rp)
/*
* Search through the file tables to file if file exists
* return the position of the table entry
*/
{
	rp.seekg(0, std::ios::beg);
	char *check_name = new char[20];
	unsigned int size,pos;
	do{
		rp.read((char *)&check_name, 20);
		rp.read((char *)&pos, sizeof(pos));
		rp.read((char *)&size, sizeof(int));
	} while (strcmp(check_name, name) != 0 && rp.tellg() < 512);
	if (rp.tellg() >= 512)
		return 0;
	delete_spec result;
	result.size = size;
	result.pos = pos;
	result.table_pos = rp.tellg() - (sizeof(char[20]) + 2 * sizeof(int));
	return result;
}

void
delete_file_entry(unsigned int pos, std::ofstream &fp)
/*
* Go to the table entry and clear the table to 0's 
* Find the size of the file in the table and return 
*/
{
	fp.seekp(pos, std::ios::beg);
	unsigned int table_size = sizeof(char[20]) + 2 * sizeof(int);
	const char c = 0;
	for (size_t i = 0; i < table_size; i++) {
		fp.write(&c, sizeof(c));
	}
}

bool
add_size_to_bitmap(unsigned int size, unsigned int pos, std::ofstream &fp, std::ifstream &rp)
/*
* Find the free bitmap and add the size to it
*/
{
	rp.seekg(512, std::ios::beg);
	unsigned int bitmap_position;
	do
	{
		rp.read((char *)&bitmap_position, sizeof(bitmap_position));
		rp.seekg(rp.tellg() + sizeof(int), std::ios::beg);
	} while (bitmap_position || rp.tellg < 728);

	fp.seekp(rp.tellg() - 2 * sizeof(int), std::ios::beg);
	fp.write((char *)pos, sizeof(pos));
	fp.write((char *)size, sizeof(size));
}