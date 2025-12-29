#include "context.h"
#include <stdio.h>

MemoryContext *createSetContext(char *name)
{
    printf("new context \n");
    MemoryContext *context = CreateSetAllocContext(name);
    uint8 *ptr1 = Alloc(100);
    uint8 *ptr2 = Alloc(2000);

    uint8 *start = context->last->curr;
    printf("ptr1: %ld\n", ptr1 - start);
    printf("ptr2: %ld\n", ptr2 - start);

    uint8 *ptr3 = Alloc(2000);
    uint8 *ptr4 = Alloc(2000);
    uint8 *start2 = context->last->curr;
    printf("ptr3: %ld\n", ptr3 - start2);
    printf("ptr4: %ld\n", ptr4 - start2);

    return context;
}

MemoryContext *createSlabContext(char *name)
{
    printf("new context \n");
    MemoryContext *context = CreateSetAllocContext(name);
    uint8 *ptr1 = Alloc(100);
    uint8 *ptr2 = Alloc(2000);

    uint8 *start = context->last->curr;
    printf("ptr1: %ld\n", ptr1 - start);
    printf("ptr2: %ld\n", ptr2 - start);

    uint8 *ptr3 = Alloc(2000);
    uint8 *ptr4 = Alloc(2000);
    uint8 *start2 = context->last->curr;
    printf("ptr3: %ld\n", ptr3 - start2);
    printf("ptr4: %ld\n", ptr4 - start2);

    return context;
}

int main(void)
{
    MemoryContext *context = createSetContext("context");
    MemoryContext *context_child_1 = createSlabContext("child1");
    MemoryContext *context_child_2 = createSetContext("child2");
    printf("%p %p %p\n", (void *)context, (void *)context_child_1, (void *)context_child_2);

    SwitchTo(context_child_1);
    Delete();
    SwitchTo(context);
    Delete();

    return 0;
}