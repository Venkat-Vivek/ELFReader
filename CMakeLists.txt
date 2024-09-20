cmake_minimum_required(VERSION 3.10)
project(ElfViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

set(SOURCES
    src/main.cpp
    src/ELFHeader.cpp
    src/PHeader.cpp
    src/SHeader.cpp
    src/RelaEntry.cpp
    src/NoteEntry.cpp
    src/SymbolEntry.cpp
    src/DynamicEntry.cpp
)

add_executable(elf_parser ${SOURCES})
