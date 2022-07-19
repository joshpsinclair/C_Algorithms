#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "array.c"

int main(int argc, char* argv[] ) {
  run_dia_tests();

  DynamicIntArray *arr = dia_new(1, 1.5);
  dia_append(arr, 25);
  dia_print(arr);
  dia_insert(arr,0,100);
  dia_print(arr);
  dia_append(arr, 200);
  dia_print(arr);
  dia_append(arr, 300);
  dia_print(arr);
}
