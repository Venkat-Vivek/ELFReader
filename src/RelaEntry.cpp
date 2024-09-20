#include "RelaEntry.h"
#include <unordered_map>

using namespace std;

uint32_t RelaEntry::getRelocationType(){
    return r_info & 0xFFFFFFFF;  
}

uint32_t RelaEntry::getSymbolIndex()
{
    return r_info >> 32;  
}

void RelaEntry::printRelaEntry(const char* dynsymstrs) {
    int symind = getSymbolIndex(); 
    const char* section_name = dynsymstrs + symind;
    unordered_map<int, string> relocation_map = {
        {0, "R_386_NONE"},
        {1, "R_386_32"},
        {2, "R_386_PC32"},
        {3, "R_386_GOT32"},
        {4, "R_386_PLT32"},
        {5, "R_386_COPY"},
        {6, "R_386_GLOB_DAT"},
        {7, "R_386_JMP_SLOT"},
        {8, "R_386_RELATIVE"},
        {9, "R_386_GOTOFF"},
        {10, "R_386_GOTPC"}
    };

    cout << "  R_offset: " << hex << r_offset << '\n';
    cout << "  Relocation type: " << relocation_map[getRelocationType()] << '\n';
    cout << "  Sym Name + Addend: " << section_name << " + " << hex << r_addend << '\n';
}
