#include <cstdint>
#include <iostream>

struct NoteEntry {
     uint32_t n_namesz;
     uint32_t n_descsz;
     uint32_t n_type;

     void printNoteEntry();
};