#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <cstring>
#include <bits/stdc++.h>

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

    void printPHeader(int index) {
        cout << "Program Header[" << index << "]:\n";
        cout << "  Type:          0x" << hex << p_type << '\n';
        cout << "  Flags:         0x" << hex << p_flags << '\n';
        cout << "  Offset:        " << dec << p_offset << " (bytes)\n";
        cout << "  Virtual Addr:  0x" << hex << p_vaddr << '\n';
        cout << "  Physical Addr: 0x" << hex << p_paddr << '\n';
        cout << "  File Size:     " << dec << p_filesz << " (bytes)\n";
        cout << "  Memory Size:   " << dec << p_memsz << " (bytes)\n";
        cout << "  Align:         " << dec << p_align << '\n';
    }
};

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

    void printSHeader(int index, const char* str_table) {
        const char* section_name = str_table + sh_name;

        cout << "Section Header[" << index << "]:\n";
        cout << "  Name:          " << section_name << '\n';
        cout << "  Type:          0x" << hex << sh_type << '\n';
        cout << "  Flags:         0x" << hex << sh_flags << '\n';
        cout << "  Address:       " << dec << sh_addr << " (bytes)\n";
        cout << "  Offset Addr:   0x" << hex << sh_offset << '\n';
        cout << "  Size:          0x" << hex << sh_size << '\n';
        cout << "  Link:          " << dec << sh_link << " (bytes)\n";
        cout << "  Info:          " << dec << sh_info << " (bytes)\n";
        cout << "  Align:         " << dec << sh_addralign << '\n';
    }
};

struct RelaEntry {
    uint64_t r_offset;
    uint64_t r_info;
    uint64_t r_addend;

    uint32_t getSymbolIndex() {
        return r_info >> 32;
    }

    uint32_t getRelocationType() {
        return r_info & 0xFFFFFFFF;
    }

    void printRelaEntry() {
        int symind = getSymbolIndex();
        cout << "  R_offset: " << hex << r_offset << '\n';
        cout << "  Relocation type: " << dec << getRelocationType() << '\n';
        cout << "  Sym Name + Addend: " << hex << r_addend << '\n';
    }
};

struct RelEntry {
    uint64_t r_offset;
    uint64_t r_info;

    uint32_t getSymbolIndex() {
        return r_info >> 32;
    }

    uint32_t getRelocationType() {
        return r_info & 0xFFFFFFFF;
    }

    void printRelEntry() {
        cout << "  R_offset: " << hex << r_offset << '\n';
        cout << "  Symbol index: " << dec << getSymbolIndex() << '\n';
        cout << "  Relocation type: " << dec << getRelocationType() << '\n';
    }
};

struct SymbolEntry {
    uint32_t st_name;
    unsigned char st_info;
    unsigned char st_other;
    uint16_t st_shndx;
    uint64_t st_value;
    uint64_t st_size;

    void printSymbolEntry(int index, const char* str_table) {
        const char* section_name = str_table + st_name;

        cout << "Symbol Entry[" << dec << index << "]:\n";
        cout << "  name:          " << section_name << '\n';
        cout << "  Addr:          " << hex << st_value << '\n';
        cout << "  Size:          0x" << hex << st_size << '\n';
        cout << "  other:          " << st_other << "\n";
        cout << "  Shndx:          " << hex << st_shndx << "\n";
        cout << "  Info:         " << hex << st_info << '\n';
    }
};

struct DynamicEntry {
    uint64_t d_tag;
    union {
        uint64_t d_val;
        uint64_t d_ptr;
    } d_un;

    void printDynamicEntry() {
        cout << "Tag: " << hex << d_tag << endl;

        if (d_tag % 2 == 0) {
            cout << "Address (d_ptr): " << d_un.d_ptr << endl;
        } else {
            cout << "Value (d_val): " << d_un.d_val << endl;
        }
    }
};

struct ELFHeader {
    unsigned char e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;

    void printELFHeader() {
        cout << "ELF Header:\n";
        cout << "  Magic:   ";
        for (int i = 0; i < 16; i++) {
            cout << hex << setw(2) << setfill('0') << (int)e_ident[i] << " ";
        }
        cout << "\n  Class:                             "
             << ((e_ident[4] == 1) ? "ELF32" : "ELF64") << '\n';
        cout << "  Data:                              "
             << ((e_ident[5] == 1) ? "2's complement, little endian" : "Big Endian") << '\n';
        cout << "  Version:                           "
             << (((int)e_ident[6] == 1) ? "1 (current)" : "Invalid Version") << '\n';
        cout << "  OS/ABI:                            " << (int)e_ident[7] << '\n';
        cout << "  ABI Version:                       " << (int)e_ident[8] << '\n';
        cout << "  Type:                              0x" << hex << e_type << '\n';
        cout << "  Machine:                           0x" << hex << e_machine << '\n';
        cout << "  Version:                           0x" << hex << e_version << '\n';
        cout << "  Entry point address:               0x" << hex << e_entry << '\n';
        cout << "  Start of program headers:          " << dec << e_phoff << " (bytes into file)\n";
        cout << "  Start of section headers:          " << e_shoff << " (bytes into file)\n";
        cout << "  Flags:                             0x" << hex << e_flags << '\n';
        cout << "  Size of this header:               " << dec << e_ehsize << " (bytes)\n";
        cout << "  Size of program headers:           " << e_phentsize << " (bytes)\n";
        cout << "  Number of program headers:         " << e_phnum << '\n';
        cout << "  Size of section headers:           " << e_shentsize << " (bytes)\n";
        cout << "  Number of section headers:         " << e_shnum << '\n';
        cout << "  Section header string table index: " << e_shstrndx << '\n';
    }
};

struct NoteEntry {
    uint32_t n_namesz;
    uint32_t n_descsz;
    uint32_t n_type;

    void printNoteEntry() {
        cout << "  Name size: " << dec << n_namesz << '\n';
        cout << "  Desc size: " << dec << n_descsz << '\n';
        cout << "  Type: " << hex << n_type << '\n';
    }
};

int main() {

    string filePath;
    cout << "Enter the file path: ";
    getline(cin, filePath);  

    ifstream elfFile(filePath, ios::in | ios::binary);

    if (!elfFile) {
        cerr << "Error: Could not open file\n";
        return 1;
    }

    ELFHeader elfHeader;
    elfFile.read((char*)(&elfHeader), sizeof(ELFHeader));

    if (memcmp(elfHeader.e_ident, "\x7f" "ELF", 4) != 0) {
        cerr << "Error: Not a valid ELF file\n";
        return 1;
    }

    elfFile.seekg(elfHeader.e_phoff);
    PHeader pHeaders[elfHeader.e_phnum];
    elfFile.read((char*)(pHeaders), elfHeader.e_phnum * sizeof(PHeader));

    elfFile.seekg(elfHeader.e_shoff);
    SHeader sHeaders[elfHeader.e_shnum];
    elfFile.read((char*)(sHeaders), elfHeader.e_shnum * sizeof(SHeader));

    elfFile.seekg(sHeaders[elfHeader.e_shstrndx].sh_offset);
    vector<char> shstrtab(sHeaders[elfHeader.e_shstrndx].sh_size);
    elfFile.read(shstrtab.data(), sHeaders[elfHeader.e_shstrndx].sh_size);

    int off = 0, symoff = 0;
    for (int i = 0; i < elfHeader.e_shnum; i++) {
        string section_name(shstrtab.data() + sHeaders[i].sh_name);
        if (section_name.compare(".strtab") == 0) {
            off = i;
            break;
        }
    }
    for (int i = 0; i < elfHeader.e_shnum; i++) {
        string section_name(shstrtab.data() + sHeaders[i].sh_name);
        if (section_name.compare(".symtab") == 0) {
            symoff = i;
            break;
        }
    }

    elfFile.seekg(sHeaders[off].sh_offset);
    vector<char> symstrs(sHeaders[off].sh_size);
    elfFile.read(symstrs.data(), sHeaders[off].sh_size);

    elfFile.seekg(sHeaders[symoff].sh_offset);
    cout << sHeaders[symoff].sh_entsize << " symoff" << endl;
    SymbolEntry symbolTable[sHeaders[symoff].sh_size / sHeaders[symoff].sh_entsize];
    elfFile.read((char*)(symbolTable), sHeaders[symoff].sh_size);

    int dynoff = 0, dynsymoff = 0;
    for (int i = 0; i < elfHeader.e_shnum; i++) {
        string section_name(shstrtab.data() + sHeaders[i].sh_name);
        if (section_name.compare(".dynstr") == 0) {
            dynoff = i;
            break;
        }
    }
    for (int i = 0; i < elfHeader.e_shnum; i++) {
        string section_name(shstrtab.data() + sHeaders[i].sh_name);
        if (section_name.compare(".dynsym") == 0) {
            dynsymoff = i;
            break;
        }
    }

    elfFile.seekg(sHeaders[dynoff].sh_offset);
    vector<char> dynsymstrs(sHeaders[dynoff].sh_size);
    elfFile.read(dynsymstrs.data(), sHeaders[dynoff].sh_size);

    elfFile.seekg(sHeaders[dynsymoff].sh_offset);
    cout << sHeaders[dynsymoff].sh_entsize << " dymoff" << endl;
    SymbolEntry dynamicSymbolTable[sHeaders[dynsymoff].sh_size / sHeaders[dynsymoff].sh_entsize];
    elfFile.read((char*)(dynamicSymbolTable), sHeaders[dynsymoff].sh_size);

    int noteoff = 0;
    for (int i = 0; i < elfHeader.e_shnum; i++) {
        if (sHeaders[i].sh_type == 7) {
            noteoff = i;
            break;
        }
    }

    int dynamicoff = 0;
    for (int i = 0; i < elfHeader.e_shnum; i++) {
        if (sHeaders[i].sh_type == 6) {
            dynamicoff = i;
            break;
        }
    }

    elfFile.seekg(sHeaders[dynamicoff].sh_offset);
    cout << sHeaders[dynamicoff].sh_entsize << " dynamic" << endl;
    DynamicEntry dynamicTable[sHeaders[dynamicoff].sh_size / sHeaders[dynamicoff].sh_entsize];
    elfFile.read((char*)(dynamicTable), sHeaders[dynamicoff].sh_size);

    int choice;
    cout << "Enter your choice: \n1 To print ELF header \n2 To print program headers \n3 To print section headers \n4 To print symbol table\n5 To print Note section\n6 To print relocation table\n7 To Dynamic table\n";
    cin >> choice;
    switch (choice) {
        case 1:
            elfHeader.printELFHeader();
            break;

        case 2:
            for (int i = 0; i < elfHeader.e_phnum; i++) {
                pHeaders[i].printPHeader(i);
            }
            break;

        case 3:
            for (int i = 0; i < elfHeader.e_shnum; i++) {
                sHeaders[i].printSHeader(i, shstrtab.data());
            }
            break;

        case 4:
            for (int i = 0; i < sHeaders[symoff].sh_size / sHeaders[symoff].sh_entsize; i++) {
                symbolTable[i].printSymbolEntry(i, symstrs.data());
            }
            cout << endl;
            for (int i = 0; i < sHeaders[dynsymoff].sh_size / sHeaders[dynsymoff].sh_entsize; i++) {
                dynamicSymbolTable[i].printSymbolEntry(i, dynsymstrs.data());
            }
            break;

        case 5: {
            for (int i = 0; i < elfHeader.e_shnum; i++) {
                if (sHeaders[i].sh_type == 7) {
                    cout << "Note Table at index [" << dec << i << "]" << endl;
                    elfFile.seekg(sHeaders[i].sh_offset);
                    vector<unsigned char> note_data(sHeaders[i].sh_size);
                    elfFile.read((char*)(note_data.data()), sHeaders[i].sh_size);

                    int offset = 0;
                    NoteEntry* note_entry = (NoteEntry*)(note_data.data() + offset);

                    if (note_entry->n_namesz + sizeof(NoteEntry) <= sHeaders[i].sh_size) {
                        note_entry->printNoteEntry();

                        if (note_entry->n_namesz != 0) {
                            int name_offset = offset + sizeof(NoteEntry);
                            string name((char*)(note_data.data() + name_offset), note_entry->n_namesz);
                            cout << "  Name: " << name << endl;
                        }

                        if (note_entry->n_descsz != 0) {
                            int desc_offset = offset + sizeof(NoteEntry) + note_entry->n_namesz;

                            cout << "  Description: ";
                            for (int i = 0; i < note_entry->n_descsz; ++i) {
                                cout << (unsigned int)(note_data[desc_offset + i]) << " ";
                            }
                            cout << endl;
                        }
                    }
                }
            }
            break;
        }

        case 6: {
            for (int i = 0; i < elfHeader.e_shnum; i++) {
                if (sHeaders[i].sh_type == 4) {
                    cout << "Relocation Table at index [" << dec << i << "]" << endl;
                    elfFile.seekg(sHeaders[i].sh_offset);
                    RelaEntry relaTable[sHeaders[i].sh_size / sHeaders[i].sh_entsize];
                    elfFile.read((char*)(relaTable), sHeaders[i].sh_size);
                    for (int j = 0; j < sHeaders[i].sh_size / sHeaders[i].sh_entsize; j++) {
                        relaTable[j].printRelaEntry();
                        cout << endl;
                    }
                }
                if (sHeaders[i].sh_type == 9) {
                    cout << "Relocation Table at index [" << dec << i << "]" << endl;
                    elfFile.seekg(sHeaders[i].sh_offset);
                    RelEntry relTable[sHeaders[i].sh_size / sHeaders[i].sh_entsize];
                    elfFile.read((char*)(relTable), sHeaders[i].sh_size);
                    for (int j = 0; j < sHeaders[i].sh_size / sHeaders[i].sh_entsize; j++) {
                        relTable[j].printRelEntry();
                        cout << endl;
                    }
                }
            }
            break;
        }

        case 7: {
            for (int i = 0; i < sHeaders[dynamicoff].sh_size / sHeaders[dynamicoff].sh_entsize; i++) {
                dynamicTable[i].printDynamicEntry();
                cout << endl;
                if (dynamicTable[i].d_tag == 0) break;
            }
            break;
        }

        default:
            cout << "Invalid choice\n";
    }

    elfFile.close();
    return 0;
}
