#ifndef PHEADER_H
#define PHEADER_H

#include <iostream>
#include <iomanip>
#include <cstdint>
using namespace std;

struct PHeader {
    uint32_t p_type;
    uint32_t p_flags;
    uint64_t p_offset;
    uint64_t p_vaddr;
    uint64_t p_paddr;
    uint64_t p_filesz;
    uint64_t p_memsz;
    uint64_t p_align;

    void printPHeader(int index);
};

#endif
