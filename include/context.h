#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdint.h>

typedef uint32_t uint32;
typedef uint8_t uint8;

static const uint32 INITIAL_CAPACITY = 4096; // should be power of 2

typedef struct MemoryContext MemoryContext;
typedef struct MemBlock MemBlock;

typedef struct MemBlock
{
    uint32 capacity;
    uint32 len;
    uint8 *start;
    uint8 *curr;
    uint8 *end;
    struct MemBlock *next;
} MemBlock;

typedef struct MemoryContextMethods
{
    void *(*alloc)(MemoryContext *, uint32);
    // void (*reset)(MemoryContext *);
    void (*delete)(MemoryContext *);
} MemoryContextMethods;

typedef struct MemoryContext
{
    char *name;
    MemBlock *blocks;
    MemBlock *last;
    struct MemoryContext *parent;
    struct MemoryContext *children;
    struct MemoryContext *next;
    const MemoryContextMethods *methods;
} MemoryContext;

extern _Thread_local MemoryContext *CURRENT_CONTEXT;

/* Public API */
MemoryContext *CreateSetAllocContext(char *name);
void *Alloc(uint32 size);
void Delete();
void SwitchTo(MemoryContext *context);

/* Utility functions */
void panic(const char *msg);

#endif /* MEMORY_H */