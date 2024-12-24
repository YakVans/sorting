#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <float.h>

struct elem
{
    double inf;
    struct elem *link;
};
typedef struct elem Elem;

struct my_queue
{
    Elem *BegQ;
    Elem *EndQ;
};
typedef struct my_queue Queue;

void declar_queue(Queue*);
void add_to_queue(Queue*, double);
void remove_from_queue(Queue*);

#endif // COMMON_H_INCLUDED
