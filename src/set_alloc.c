#include "context.h"
#include <stdio.h>
#include <stdlib.h>

static void *alloc(MemoryContext *context, uint32 size);
// void reset(MemoryContext *context);
static void delete(MemoryContext *context);

static const MemoryContextMethods AllocSetMethods = {
    .alloc = alloc,
    .delete = delete,
};

MemoryContext *CreateSetAllocContext(char *name)
{
    uint32 block_header = sizeof(MemBlock); // TODO padded(ALIGNUP)
    uint32 context_header = sizeof(MemoryContext);
    uint32 tot_capacity = block_header + context_header + INITIAL_CAPACITY;

    uint8 *buffer = malloc(tot_capacity);
    if (buffer == NULL)
        panic("Failed to allocate block");

    // Calculate offsets of block and context metadata

    MemBlock *block = (MemBlock *)buffer;

    uint8 *context_start = buffer + block_header;

    MemoryContext *context = (MemoryContext *)context_start;

    uint8 *data_start = context_start + context_header;

    // Initialize values for block and context metadata

    block->capacity = INITIAL_CAPACITY;
    block->len = 0;
    block->start = buffer;
    block->curr = data_start;
    block->end = buffer + tot_capacity;
    block->next = NULL;

    context->name = name;
    context->blocks = block;
    context->last = block;
    context->parent = CURRENT_CONTEXT;
    context->methods = &AllocSetMethods;
    context->children = NULL;
    context->next = NULL;

    // Change parent state so it contains this node as child
    // for later removal when free is called

    if (CURRENT_CONTEXT != NULL)
    {
        if (CURRENT_CONTEXT->children == NULL)
        {
            CURRENT_CONTEXT->children = context;
        }
        else
        {
            MemoryContext *curr = CURRENT_CONTEXT->children;
            while (curr->next != NULL)
            {
                curr = curr->next;
            }
            curr->next = context;
        }
    }

    SwitchTo(context);

    return context;
}

static MemBlock *initBlock(uint32 capacity)
{
    uint32 header = sizeof(MemBlock); // TODO padded(ALIGNUP)

    uint8 *buffer = malloc(header + capacity);
    if (buffer == NULL)
        panic("Failed to allocate block");

    MemBlock *block = (MemBlock *)buffer;

    uint8 *data_start = buffer + header;

    block->capacity = capacity;
    block->len = 0;
    block->start = buffer;
    block->curr = data_start;
    block->end = data_start + capacity;
    block->next = NULL;

    return block;
}

static void *alloc(MemoryContext *context, uint32 size)
{
    if (context->last->curr + size > context->last->end)
    {
        // TODO add when reset is called to use existing block chain
        uint32 lastCap = context->last->capacity << 1;
        MemBlock *block = initBlock(lastCap);
        context->last->next = block;
        context->last = block;
    }
    uint8 *result = context->last->curr;
    context->last->curr += size;
    context->last->len += size;
    return result;
}

static void delete(MemoryContext *context)
{
    if (context == NULL)
        return;

    delete(context->next);
    delete(context->children);

    MemBlock *curr = context->blocks;
    while (curr != NULL)
    {
        MemBlock *next = curr->next;
        free(curr->start);
        curr = next;
    }
}
