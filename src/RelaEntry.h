#include <cstdint>
#include <iostream>

struct RelaEntry{
    uint64_t r_offset;
    uint64_t r_info;
    uint64_t r_addend;

    uint32_t getSymbolIndex();

    uint32_t getRelocationType();

    void printRelaEntry(const char* dynsymstrs);
};