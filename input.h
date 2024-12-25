#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <ctype.h>

#include "queue_operations.h"

#define DOUBLE_MAX_DIGIT 309

int processing_c_symb(char, int*, int*, int*, int*, char*, int*, Queue*);
int input();

#endif // INPUT_H_INCLUDED
