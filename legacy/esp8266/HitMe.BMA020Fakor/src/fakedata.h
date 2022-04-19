#ifndef FAKEDATA_H 
#define FAKEDATA_H 
#include <stdint.h>
extern uint16_t sizeData;
uint16_t sizeData = 60;

extern uint8_t data[];
uint8_t data[] = {
   2,  64,   2,  64,   2,  64, //   0    576
   3,  80,   3,  80,   3,  80, //   1   -176
   3, 164,   3, 164,   3, 164, //   2    -92
   1, 152,   1, 152,   1, 152, //   3   -616
   2,  35,   2,  35,   2,  35, //   4   -477
   3, 103,   3, 103,   3, 103, //   5   -153
   3, 246,   3, 246,   3, 246, //   6    -10
   0,   1,   0,   1,   0,   1, //   7      1
   0,  82,   0,  82,   0,  82, //   8     82
   1, 104,   1, 104,   1, 104, //   9    360
};

#endif // FAKEDATA_H
