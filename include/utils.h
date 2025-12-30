#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "types.h"

#define ALLOC_MINBITS 3

/* Utility functions */
void panic(const char *msg);
uint8 AllocSetFreeIndex(uint32 size);
uint32 RoundPow2Up(uint32 size);
uint32 RoundPow2Down(uint32 size);

#endif /* UTILS_H */