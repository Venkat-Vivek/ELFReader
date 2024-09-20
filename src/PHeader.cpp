#include "PHeader.h"
#include <iostream>
#include <unordered_map>

void PHeader::printPHeader(int index) {
   
    unordered_map<int, string> programHeaderTypes = {
        {0, "NULL"},
        {1, "LOAD"},
        {2, "DYNAMIC"},
        {3, "INTERP"},
        {4, "NOTE"},
        {5, "SHLIB"},
        {6, "PHDR"},
        {7, "TLS"},
        {8, "NUM"},
        {0x60000000, "LOOS"},
        {0x6474e550, "GNU_EH_FRAME"},
        {0x6474e551, "GNU_STACK"},
        {0x6474e552, "GNU_RELRO"},
        {0x6ffffffa, "LOSUNW"},
        {0x6ffffffa, "SUNWBSS"},
        {0x6ffffffb, "SUNWSTACK"},
        {0x6fffffff, "HISUNW"},
        {0x6fffffff, "HIOS"},
        {0x70000000, "LOPROC"},
        {0x7fffffff, "HIPROC"}
    };

    cout << "Program Header[" << index << "]:\n";
    cout << "  Type: "  << programHeaderTypes[p_type] << '\n';
    cout << "  Flags: 0x" << hex << p_flags << '\n';
    cout << "  Offset: " << dec << p_offset << " (bytes)\n";
    cout << "  Virtual Addr: 0x" << hex << p_vaddr << '\n';
    cout << "  Physical Addr: 0x" << hex << p_paddr << '\n';
    cout << "  File Size: " << dec << p_filesz << " (bytes)\n";
    cout << "  Memory Size: " << dec << p_memsz << " (bytes)\n";
    cout << "  Align: " << dec << p_align << '\n';
}
