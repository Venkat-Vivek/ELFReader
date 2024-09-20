#include <iostream>
#include <fstream>
#include "ELFHeader.h"
#include "PHeader.h"
#include "SHeader.h"
#include "RelaEntry.h"
#include "NoteEntry.h"
#include "SymbolEntry.h"
#include "DynamicEntry.h"
#include<bits/stdc++.h>
using namespace std;

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

     if (elfHeader.e_ident[0] != 0x7f || elfHeader.e_ident[1] != 'E' || elfHeader.e_ident[2] != 'L' || elfHeader.e_ident[3] != 'F') {
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
     for(int i = 0; i < elfHeader.e_shnum; i++){
          string section_name(shstrtab.data() + sHeaders[i].sh_name);
          if(section_name.compare(".strtab") == 0){
               off = i;
               break;
          }
     }
     for(int i = 0; i < elfHeader.e_shnum; i++){
          string section_name(shstrtab.data() + sHeaders[i].sh_name);
          if(section_name.compare(".symtab") == 0){
               symoff = i;
               break;
          }
     }

     elfFile.seekg(sHeaders[off].sh_offset);
     vector<char> symstrs(sHeaders[off].sh_size);
     elfFile.read(symstrs.data(), sHeaders[off].sh_size);

     elfFile.seekg(sHeaders[symoff].sh_offset);
     // cout<<sHeaders[symoff].sh_entsize<< " symoff"<<endl;
     SymbolEntry symbolTable[sHeaders[symoff].sh_size / sHeaders[symoff].sh_entsize];
     elfFile.read((char*) (symbolTable), sHeaders[symoff].sh_size);

     elfFile.seekg(sHeaders[1].sh_offset);
     char *interp_data = (char*)malloc(sHeaders[1].sh_size);
     elfFile.read(interp_data, sHeaders[1].sh_size);

     // for (int i=0;i<sHeaders[1].sh_size;i++) {
     //      cout << (char)*(interp_data+i);
     // }
     // cout << endl;
     // return 0;
     int choice;
     cout << "Enter your choice: \n1 To print ELF header \n2 To print program headers \n3 To print section headers \n4 To print symbol table\n5 To print Note section\n6 To print relocation table\n7 To Dynamic table\n8 To print global offset table";
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

          case 4:{
               int dynoff = -1, dynsymoff = -1;
               for(int i = 0; i < elfHeader.e_shnum; i++){
                    string section_name(shstrtab.data() + sHeaders[i].sh_name);
                    if(section_name.compare(".dynstr") == 0){
                         dynoff = i;
                         break;
                    }
               }
               for(int i = 0; i < elfHeader.e_shnum; i++){
                    string section_name(shstrtab.data() + sHeaders[i].sh_name);
                    if(section_name.compare(".dynsym") == 0){
                         dynsymoff = i;
                         break;
                    }
               }
               
               for (uint64_t i = 0; i < (int)sHeaders[symoff].sh_size / sHeaders[symoff].sh_entsize; i++) {
                    symbolTable[i].printSymbolEntry(i, symstrs.data());
               }
               cout << endl;

               if(dynoff != -1 && dynsymoff != -1){
                    elfFile.seekg(sHeaders[dynoff].sh_offset);
                    vector<char> dynsymstrs(sHeaders[dynoff].sh_size);
                    elfFile.read(dynsymstrs.data(), sHeaders[dynoff].sh_size);

                    elfFile.seekg(sHeaders[dynsymoff].sh_offset);
                    // cout<<sHeaders[dynsymoff].sh_entsize<<" dymoff"<<endl;
                    SymbolEntry dynamicSymbolTable[sHeaders[dynsymoff].sh_size / sHeaders[dynsymoff].sh_entsize];
                    elfFile.read((char*) (dynamicSymbolTable), sHeaders[dynsymoff].sh_size);
                    for (uint64_t i = 0; i < (int)sHeaders[dynsymoff].sh_size / sHeaders[dynsymoff].sh_entsize; i++) {
                         dynamicSymbolTable[i].printSymbolEntry(i, dynsymstrs.data());
                    }
               }
               break;
          }
          case 5:{
               for (int i = 0; i < elfHeader.e_shnum; i++) {
                    if(sHeaders[i].sh_type == 7){
                         cout << "Note Table at index [" << dec << i << "]" << endl;
                         elfFile.seekg(sHeaders[i].sh_offset);
                         vector<unsigned char> note_data(sHeaders[i].sh_size);
                         elfFile.read((char*) (note_data.data()), sHeaders[i].sh_size);

                         int offset = 0;
                         NoteEntry* note_entry = (NoteEntry*) (note_data.data() + offset);

                         if (note_entry->n_namesz + sizeof(NoteEntry) <= sHeaders[i].sh_size) {
                              note_entry->printNoteEntry();

                              if (note_entry->n_namesz != 0) {
                                   int name_offset = offset + sizeof(NoteEntry);
                                   string name((char*) (note_data.data() + name_offset), note_entry->n_namesz);
                                   cout << "  Name: " << name << endl;
                              }
     
                              if (note_entry->n_descsz != 0) {
                                   int desc_offset = offset + sizeof(NoteEntry) + note_entry->n_namesz;

                                   cout << "  Description: ";
                                   for (int i = 0; i < (int)note_entry->n_descsz; ++i) {
                                        cout << (unsigned int)(note_data[desc_offset + i]) << " ";
                                   }
                                   cout << endl;
                              }
                         }
                    }
               }
               break;
          }

          case 6:{
               int dynoff = -1;
               for(int i = 0; i < elfHeader.e_shnum; i++){
                    string section_name(shstrtab.data() + sHeaders[i].sh_name);
                    if(section_name.compare(".dynstr") == 0){
                         dynoff = i;
                         break;
                    }
               }
               elfFile.seekg(sHeaders[dynoff].sh_offset);
               vector<char> dynsymstrs(sHeaders[dynoff].sh_size);
               elfFile.read(dynsymstrs.data(), sHeaders[dynoff].sh_size);

               for (int i = 0; i < elfHeader.e_shnum; i++) {
                    if(sHeaders[i].sh_type == 4){
                         cout << "Relocation Table at index [" << dec << i << "]" << endl;
                         elfFile.seekg(sHeaders[i].sh_offset);
                         RelaEntry relaTable[sHeaders[i].sh_size / sHeaders[i].sh_entsize];
                         elfFile.read((char*) (relaTable), sHeaders[i].sh_size);
                         for(uint64_t j = 0; j < sHeaders[i].sh_size / sHeaders[i].sh_entsize; j++){
                              relaTable[j].printRelaEntry(dynsymstrs.data());
                              cout << endl;
                         }
                    }
                    // if(sHeaders[i].sh_type == 9){
                    //      cout << "Relocation Table at index [" << dec << i << "]" << endl;
                    //      elfFile.seekg(sHeaders[i].sh_offset);
                    //      RelEntry relTable[sHeaders[i].sh_size / sHeaders[i].sh_entsize];
                    //      elfFile.read((char*) (relTable), sHeaders[i].sh_size);
                    //      for(int j = 0; j < sHeaders[i].sh_size / sHeaders[i].sh_entsize; j++){
                    //           relTable[j].printRelEntry();
                    //           cout << endl;
                    //      }
                    // }
               }
               break;
          }
          
          case 7:{

               int dynamicoff = -1;
               for(int i = 0; i < elfHeader.e_shnum; i++){
                    if(sHeaders[i].sh_type == 6){
                         dynamicoff = i;
                         break;
                    }
               }
               if(dynamicoff != -1){
                    elfFile.seekg(sHeaders[dynamicoff].sh_offset);
                    // cout<<sHeaders[dynamicoff].sh_entsize<<" dynamic"<<endl;
                    DynamicEntry dynamicTable[sHeaders[dynamicoff].sh_size / sHeaders[dynamicoff].sh_entsize];
                    elfFile.read((char*) (dynamicTable), sHeaders[dynamicoff].sh_size);
                    for (uint64_t i = 0; i < sHeaders[dynamicoff].sh_size / sHeaders[dynamicoff].sh_entsize; i++) {
                         dynamicTable[i].printDynamicEntry();
                         cout << endl;
                         if(dynamicTable[i].d_tag == 0) break;
                    }
               }
               else{
                    cout << "No Dynamic section" << endl;
               }
               break;
          }

          case 8:{
               int gotoff = -1;
               for(int i = 0; i < elfHeader.e_shnum; i++){
                    uint32_t sh_name = sHeaders[i].sh_name; 
                    const char* section_name = shstrtab.data() + sh_name;
                    if(memcmp(section_name, ".got", 4) == 0){
                         gotoff = i;
                         break;
                    }
               }
               if(gotoff != -1){
                    elfFile.seekg(sHeaders[gotoff].sh_offset);
                    vector<uint64_t> got_entries(sHeaders[gotoff].sh_size / sizeof(uint64_t));
                    elfFile.read((char*)got_entries.data(), sHeaders[gotoff].sh_size);

                    for(size_t i = 0; i < got_entries.size(); i++){
                         cout << "GOT Entry[" << i << "]: " << hex << got_entries[i] << endl;
                    }
               }
               else{
                    cout << "No .got section found!" << endl;
               }
               break;
          }


          default:
               cout << "Invalid choice\n";
     }

     elfFile.close();
     return 0;
}

