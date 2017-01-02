#include "Reading.hpp"
#include "Writing.hpp"
#include "Delete.hpp"

int main()
{
    std::ofstream fp;
    fp.open("Harddisk", std::ios::binary);
    std::ifstream rp;
    rp.open("Harddisk", std::ios::binary);
    if (check_if_empty(rp))
            reserve_table_space(fp);
    int option;
    do{
        std::cout <<"1. Create file entry \n2. Read file entry\n3. Delete Entry\n4. Quit "  << "\n";
        scanf("%d",&option);
        switch(option){
        case 1:{
            std::cout << "Enter the name of the file:"  << "\n";
            char *name = new char[20];
            scanf("%s", name);
            size_t size = write_file_to_buffer();
            unsigned int pos = write_to_disk(size, fp, rp);
            make_file_table(name, size, pos, fp, rp);
        }break;
        case 2:{
            std::cout << "Enter the name of the file" << std::endl;
            char *name = new char[20];
            scanf("%s", name);
            unsigned int pos = read_table(rp, name);
            if (pos)
                read_file(rp, pos);
            else
                std::cout << "No such file";
            delete[] name; 
        }break;
		case 3: {
			std::cout << "Enter the name of the file to be deleted" << std::endl;
			char *name = new char[20];
			scanf("%s", name);
			delete_spec result = search_for_file(name, rp);
			if (result.table_pos) {
				delete_file_entry(result.table_pos, fp);
				add_size_to_bitmap(result.size, result.pos, fp, rp);
			}
			else
				std::cout << "No such file"<< std::endl;
			delete[] name;
		}
        }
    }while(option != 4);
    fp.close();
    return 0;
}
