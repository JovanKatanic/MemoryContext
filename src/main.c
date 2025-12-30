#include "context.h"
#include <stdio.h>

MemoryContext *createSetContext(char *name)
{
    printf("new context \n");
    MemoryContext *context = CreateSetAllocContext(name);
    Block ptr1 = Alloc(100);
    Block ptr2 = Alloc(2000);

    printf("ptr2: %ld\n", ptr2.data - ptr1.data);

    Block ptr3 = Alloc(3000);
    Block ptr4 = Alloc(1000);
    printf("ptr4: %ld\n", ptr4.data - ptr3.data);

    Free(ptr3);
    Block ptr5 = Alloc(3000);
    printf("ptr6: %ld\n", ptr5.data - ptr3.data);

    return context;
}

MemoryContext *createSlabContext(char *name)
{
    // printf("new context \n");
    // MemoryContext *context = CreateSetAllocContext(name);
    // Block ptr1 = Alloc(100);
    // Block ptr2 = Alloc(2000);

    // Block start = context->last->curr;
    // printf("ptr1: %ld\n", ptr1 - start);
    // printf("ptr2: %ld\n", ptr2 - start);

    // Block ptr3 = Alloc(2000);
    // Block ptr4 = Alloc(2000);
    // Block start2 = context->last->curr;
    // printf("ptr3: %ld\n", ptr3 - start2);
    // printf("ptr4: %ld\n", ptr4 - start2);

    // return context;
}

int main(void)
{
    MemoryContext *context = createSetContext("context");
    MemoryContext *context_child_1 = createSetContext("child1");
    MemoryContext *context_child_2 = createSetContext("child2");
    printf("%p %p %p\n", (void *)context, (void *)context_child_1, (void *)context_child_2);

    SwitchTo(context_child_1);
    Delete();
    SwitchTo(context);
    Delete();

    return 0;
}