#include "context.h"
#include <stdio.h>
#include <stdlib.h>

_Thread_local MemoryContext *CURRENT_CONTEXT = NULL;

void SwitchTo(MemoryContext *context)
{
    CURRENT_CONTEXT = context;
}

Block Alloc(uint32 size)
{
    return CURRENT_CONTEXT->methods->alloc(CURRENT_CONTEXT, size);
}

void Free(Block block)
{
    return CURRENT_CONTEXT->methods->jfree(CURRENT_CONTEXT, block);
}

void Delete()
{
    CURRENT_CONTEXT->methods->delete(CURRENT_CONTEXT);
    SwitchTo(NULL);
}
