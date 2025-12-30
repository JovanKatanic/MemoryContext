#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdint.h>

typedef uint32_t uint32;
typedef uint8_t uint8;

typedef struct MemoryContext MemoryContext;

typedef struct Block
{
    void *data;
    uint32 size;
} Block;

typedef struct MemoryContextMethods
{
    Block (*alloc)(MemoryContext *, uint32);
    void (*jfree)(MemoryContext *ctx, Block block);
    void (*delete)(MemoryContext *);
} MemoryContextMethods;

typedef struct MemoryContext
{
    char *name;
    MemoryContext *parent;
    MemoryContext *children;
    MemoryContext *next;
    MemoryContextMethods *methods;
} MemoryContext;

extern _Thread_local MemoryContext *CURRENT_CONTEXT;

/* Public API */
MemoryContext *CreateSetAllocContext(char *name);
Block Alloc(uint32 size);
void Free(Block block);
void Delete();
void SwitchTo(MemoryContext *context);

/* Utility functions */
void panic(const char *msg);

#endif /* MEMORY_H */