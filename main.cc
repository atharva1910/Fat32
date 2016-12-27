#include "Reading.hpp"
#include "Writing.hpp"

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
        std::cout <<"1. Create file entry \n2. Read file entry "  << "\n";
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
