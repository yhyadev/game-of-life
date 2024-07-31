#include <stdlib.h>

#include "common.h"

float frand(void) { return (float)rand() / (float)RAND_MAX; }
size_t mod(size_t a, size_t b) { return ((a % b) + b) % b; }
