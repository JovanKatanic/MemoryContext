#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "types.h"

#define ALLOC_MINBITS 3

#define MAXIMUM_ALIGNOF 8
#define MAXALIGN(LEN) \
    (((uintptr_t)(LEN) + (MAXIMUM_ALIGNOF - 1)) & ~((uintptr_t)(MAXIMUM_ALIGNOF - 1)))

/* Utility functions */
void panic(const char *msg);
uint8 AllocSetFreeIndex(uint32 size);
uint32 RoundPow2Up(uint32 size);
uint32 RoundPow2Down(uint32 size);

#endif /* UTILS_H */