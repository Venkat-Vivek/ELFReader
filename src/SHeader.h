#include <iostream>
#include <iomanip>
#include <cstdint>
using namespace std;

struct SHeader {
    uint32_t sh_name;
    uint32_t sh_type;
    uint64_t sh_flags;
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;

    void printSHeader(int index, const char* str_table);
};
