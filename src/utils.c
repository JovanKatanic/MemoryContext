#include "context.h"
#include <stdio.h>
#include <stdlib.h>

void panic(const char *msg);

void panic(const char *msg)
{
    fprintf(stderr, "PANIC: %s\n", msg);
    exit(1);
}
