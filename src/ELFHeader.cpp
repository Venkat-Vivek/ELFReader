#include "ELFHeader.h"
#include <unordered_map>

void ELFHeader:: printELFHeader(){

     unordered_map<int, string> machine_map = {
          {0, "No machine"},
          {1, "AT&T WE 32100"},
          {2, "SUN SPARC"},
          {3, "Intel 80386"},
          {4, "Motorola m68k family"},
          {5, "Motorola m88k family"},
          {6, "Intel MCU"},
          {7, "Intel 80860"},
          {8, "MIPS R3000 big-endian"},
          {9, "IBM System/370"},
          {10, "MIPS R3000 little-endian"},
          {15, "HPPA"},
          {17, "Fujitsu VPP500"},
          {18, "Sun's v8plus"},
          {19, "Intel 80960"},
          {20, "PowerPC"},
          {21, "PowerPC 64-bit"},
          {22, "IBM S390"},
          {23, "IBM SPU/SPC"},
          {36, "NEC V800 series"},
          {37, "Fujitsu FR20"},
          {38, "TRW RH-32"},
          {39, "Motorola RCE"},
          {40, "ARM"},
          {41, "Digital Alpha"},
          {42, "Hitachi SH"},
          {43, "SPARC v9 64-bit"},
          {44, "Siemens Tricore"},
          {45, "Argonaut RISC Core"},
          {46, "Hitachi H8/300"},
          {47, "Hitachi H8/300H"},
          {48, "Hitachi H8S"},
          {49, "Hitachi H8/500"},
          {50, "Intel Merced"},
          {51, "Stanford MIPS-X"},
          {52, "Motorola Coldfire"},
          {53, "Motorola M68HC12"},
          {54, "Fujitsu MMA Multimedia Accelerator"},
          {55, "Siemens PCP"},
          {56, "Sony nCPU embedded RISC"},
          {57, "Denso NDR1 microprocessor"},
          {58, "Motorola Start*Core processor"},
          {59, "Toyota ME16 processor"},
          {60, "STMicroelectronic ST100 processor"},
          {61, "Advanced Logic Corp. Tinyj emb.fam"},
          {62, "AMD x86-64 architecture"},
          {63, "Sony DSP Processor"},
          {64, "Digital PDP-10"}
          };

          std::unordered_map<int, std::string> file_type_map = {
          {0, "No file type"},
          {1, "Relocatable file"},
          {2, "Executable file"},
          {3, "Shared object file"},
          {4, "Core file"},
          {5, "Number of defined types"},
          {0xfe00, "OS-specific range start"},
          {0xfeff, "OS-specific range end"},
          {0xff00, "Processor-specific range start"},
          {0xffff, "Processor-specific range end"}
     };


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
          << (((int)e_ident[6] == 1) ? "1 (current)" : "Invalid Version"  ) << '\n';
     cout << "  OS/ABI:                            " 
          << (int)e_ident[7] << '\n';
     cout << "  ABI Version:                       " 
          << (int)e_ident[8] << '\n';
     cout << "  Type:                              " 
          << file_type_map[e_type] << '\n';
     cout << "  Machine:                           " 
          << machine_map[e_machine] << '\n';
     cout << "  Version:                           0x" 
          << hex << e_version << '\n';
     cout << "  Entry point address:               0x" 
          << hex << e_entry << '\n';
     cout << "  Start of program headers:          " 
          << dec << e_phoff << " (bytes into file)\n";
     cout << "  Start of section headers:          " 
          << e_shoff << " (bytes into file)\n";
     cout << "  Flags:                             0x" 
          << hex << e_flags << '\n';
     cout << "  Size of this header:               " 
          << dec << e_ehsize << " (bytes)\n";
     cout << "  Size of program headers:           " 
          << e_phentsize << " (bytes)\n";
     cout << "  Number of program headers:         " 
          << e_phnum << '\n';
     cout << "  Size of section headers:           " 
          << e_shentsize << " (bytes)\n";
     cout << "  Number of section headers:         " 
          << e_shnum << '\n';
     cout << "  Section header string table index: " 
          << e_shstrndx << '\n';
}
