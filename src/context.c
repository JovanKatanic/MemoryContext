#include "context.h"
#include <stdio.h>
#include <stdlib.h>

_Thread_local MemoryContext *CURRENT_CONTEXT = NULL;

void unlinkFromParent(MemoryContext *context);

void unlinkFromParent(MemoryContext *context)
{
    MemoryContext *parent = context->parent;

    if (parent == NULL)
        return;

    MemoryContext **prev = &parent->children;
    while (*prev && *prev != context)
    {
        prev = &(*prev)->next;
    }

    if (*prev == context)
    {
        *prev = context->next;
    }

    context->parent = NULL;
    context->next = NULL;
}

void SwitchTo(MemoryContext *context)
{
    CURRENT_CONTEXT = context;
}

void *Alloc(uint32 size)
{
    return CURRENT_CONTEXT->methods->alloc(CURRENT_CONTEXT, size);
}

void Delete()
{
    unlinkFromParent(CURRENT_CONTEXT);
    CURRENT_CONTEXT->methods->delete(CURRENT_CONTEXT);
    SwitchTo(NULL);
}
