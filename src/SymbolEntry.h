#include <cstdint>
#include <iostream>

struct SymbolEntry{
     uint32_t      st_name;
     unsigned char st_info;
     unsigned char st_other;
     uint16_t      st_shndx;
     uint64_t     st_value;
     uint64_t      st_size;
     
     void printSymbolEntry(int index, const char* str_table);
};
