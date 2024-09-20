#include "SHeader.h"
#include <iostream>
#include <unordered_map>

void SHeader::printSHeader(int index, const char* str_table) {

    unordered_map<int, string> sectionHeaderTypes = {
        {0, "NULL"},
        {1, "PROGBITS"},
        {2, "SYMTAB"},
        {3, "STRTAB"},
        {4, "RELA"},
        {5, "HASH"},
        {6, "DYNAMIC"},
        {7, "NOTE"},
        {8, "NOBITS"},
        {9, "REL"},
        {10, "SHLIB"},
        {11, "DYNSYM"},
        {14, "INIT_ARRAY"},
        {15, "FINI_ARRAY"},
        {16, "PREINIT_ARRAY"},
        {17, "GROUP"},
        {18, "SYMTAB_SHNDX"},
        {19, "NUM"},
        {0x60000000, "LOOS"},
        {0x6ffffff5, "GNU_ATTRIBUTES"},
        {0x6ffffff6, "GNU_HASH"},
        {0x6ffffff7, "GNU_LIBLIST"},
        {0x6ffffff8, "CHECKSUM"},
        {0x6ffffffa, "LOSUNW"},
        {0x6ffffffa, "SUNW_move"},
        {0x6ffffffb, "SUNW_COMDAT"},
        {0x6ffffffc, "SUNW_syminfo"},
        {0x6ffffffd, "GNU_verdef"},
        {0x6ffffffe, "GNU_verneed"},
        {0x6fffffff, "GNU_versym"},
        {0x6fffffff, "HISUNW"},
        {0x6fffffff, "HIOS"},
        {0x70000000, "LOPROC"},
        {0x7fffffff, "HIPROC"},
        {0x80000000, "LOUSER"}
    };

    const char* section_name = str_table + sh_name;
    cout << "Section Header[" << index << "]:\n";
    cout << "  Name: " << section_name << '\n';
    cout << "  Type: " << sectionHeaderTypes[sh_type] << '\n';
    cout << "  Flags: 0x" << hex << sh_flags << '\n';
    cout << "  Address: " << dec << sh_addr << " (bytes)\n";
    cout << "  Offset: 0x" << hex << sh_offset << '\n';
    cout << "  Size: 0x" << hex << sh_size << '\n';
    cout << "  Link: " << dec << sh_link << " (bytes)\n";
    cout << "  Info: " << dec << sh_info << " (bytes)\n";
    cout << "  Align: " << dec << sh_addralign << '\n';
}
