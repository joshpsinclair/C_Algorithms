#ifndef QUICKSORT_HEADER_FILE
#define QUICKSORT_HEADER_FILE

#include <assert.h>
#include <stdbool.h>

void quicksort(int array[], int lo, int hi, bool reverse);
int partition(int array[], int lo, int hi, bool reverse);

#endif
