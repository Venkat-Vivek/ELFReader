#include "SymbolEntry.h"
#include <unordered_map>

using namespace std;

void SymbolEntry :: printSymbolEntry(int index, const char* str_table){

    unordered_map<int, string> symbolBindings = {
        {0, "LOCAL"},
        {1, "GLOBAL"},
        {2, "WEAK"},
        {3, "NUM"},
        {10, "LOOS"},
        {10, "GNU_UNIQUE"},
        {12, "HIOS"},
        {13, "LOPROC"},
        {15, "HIPROC"}
    };

    unordered_map<int, string> symbolTypes = {
        {0, "NOTYPE"},
        {1, "OBJECT"},
        {2, "FUNC"},
        {3, "SECTION"},
        {4, "FILE"},
        {13, "LOPROC"},
        {15, "HIPROC"}
    };

    const char* section_name = str_table + st_name;
    
    cout << "Symbol Entry[" << dec << index << "]:\n";
    cout << "  name:          " << section_name<< '\n';  
    cout << "  Addr:          " << hex << st_value << '\n';  
    cout << "  Size:          0x" << hex << st_size << '\n';
    cout << "  Type:          " << symbolTypes[(st_info)&0xf] << "\n";
    cout << "  Shndx:          " << hex << st_shndx << "\n";
    cout << "  Bind:          " << symbolBindings[st_info>>4] << '\n';
} 