#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "array.c"

/*
K Largest Elements
https://www.codingninjas.com/codestudio/problems/k-largest-element_1062624?topList=top-array-coding-interview-questions

You are given an unsorted array containing ‘N’ integers. You need to find ‘K’
largest elements from the given array. Also, you need to return the elements
in non-decreasing order.

Can you solve this in less than O(N*log(N)) time complexity
*/

DynamicIntArray* k_largest(DyanamicIntArray* arr, k) {
  // 1. arr will be unsorted, so first step will be to sort it
  // 2. 
}


int main(int argc, char* argv[] ) {
  run_dia_tests();

  DynamicIntArray* arr = dia_new(1, 1.5);
  dia_append(arr, 25);
  dia_print(arr);
  dia_insert(arr,0,100);
  dia_print(arr);
  dia_append(arr, 200);
  dia_print(arr);
  dia_append(arr, 300);
  dia_print(arr);
}
