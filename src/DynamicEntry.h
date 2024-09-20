#include <cstdint>
#include <iostream>

struct DynamicEntry{
     uint64_t d_tag;
     union {
          uint64_t     d_val;
          uint64_t     d_ptr;
     } d_un;

     void printDynamicEntry();
};