#include "NoteEntry.h"
using namespace std;

void NoteEntry :: printNoteEntry(){
    cout << "  Name size: " << dec << n_namesz << '\n';
    cout << "  Desc size: " << dec << n_descsz << '\n';
    cout << "  Type: " << hex << n_type << '\n';
}