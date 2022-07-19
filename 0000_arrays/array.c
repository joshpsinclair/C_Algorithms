#import <string.h>
#include <math.h>

//from https://stackoverflow.com/questions/3437404/min-and-max-in-c
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


void dia_ensure_realloc_success(void* p) {
  if (p == NULL) {
    fprintf(stderr, "Failure. realloc failed\n");
    exit(EXIT_FAILURE);
  }
}

void dia_ensure_index_exists(DynamicIntArray* arr, int index) {
  if (index > arr->size || index < 0) {
    fprintf(stderr, "Failure. Index %d is out of bounds for size %d \n", index, arr->size);
    exit(EXIT_FAILURE);
  }
}

void dia_grow(DynamicIntArray* arr) {
  int n_capacity=ceil(arr->capacity * arr->g_factor);
  int *temp=(int*) realloc(arr->data, sizeof(int) * n_capacity);
  dia_ensure_realloc_success(temp);
  arr->data=temp;
  arr->capacity=n_capacity;
}

bool dia_requires_growth(DynamicIntArray* arr) {
  if (arr->size == arr->capacity) { return true; } else { return false; }
}

void dia_ensure_enough_capacity(DynamicIntArray* arr) {
  if (dia_requires_growth(arr) == true) { dia_grow(arr); }
}

void dia_insert(DynamicIntArray* arr, int index, int value) {
  dia_ensure_index_exists(arr, index);
  dia_ensure_enough_capacity(arr);
  memmove(arr->data+index+1, arr->data+index, sizeof(int) * (arr->size - index));
  arr->data[index]=value;
  arr->size+=1;
}

void dia_append(DynamicIntArray* arr, int value) {
  dia_ensure_enough_capacity(arr);
  arr->data[arr->size]=value;
  arr->size=arr->size+1;
}

void dia_delete(DynamicIntArray* arr, int index) {
  dia_ensure_index_exists(arr, index);
  memmove(arr->data+index, arr->data+index+1, sizeof(int) * (arr->size - index - 1));
  arr->size=arr->size-1;
}

void dia_pop(DynamicIntArray* arr) {
  arr->size=arr->size-1;
}

int dia_value(DynamicIntArray* arr, int index) {
  dia_ensure_index_exists(arr, index);
  return arr->data[index];
}

int dia_size(DynamicIntArray* arr) {
  return arr->size;
}

void dia_dealloc(DynamicIntArray* arr) {
  free(arr->data);
  free(arr);
}

int _slice_index(int size, int slice_value) {
  if (slice_value < 0) { return size+slice_value; } else { return slice_value; }
}

int _l_slice_index(int slice_value) {
  return MAX(slice_value, 0);
}

int _u_slice_index(int size, int slice_value) {
  return MIN(slice_value, size);
}

DynamicIntArray* dia_slice(DynamicIntArray* arr, int l, int u) {
  // Python style slice implementation
  l=_l_slice_index(_slice_index(arr->size, l));
  u=_u_slice_index(arr->size, _slice_index(arr->size, u));
  dia_ensure_index_exists(arr, l);
  dia_ensure_index_exists(arr, u);

  int n_size=u-l;
  int *n_data = (int*) malloc(sizeof(int) * n_size);
  for (int i=l; i<u; i++) {
    n_data[i-l]=arr->data[i];
  }

  DynamicIntArray* n_arr = (DynamicIntArray*) malloc(sizeof(DynamicIntArray));
  n_arr->data=n_data;
  n_arr->size=n_size;
  n_arr->capacity=ceil(n_size*arr->g_factor);
  n_arr->g_factor=arr->g_factor;
  return n_arr;
}

void dia_print(DynamicIntArray* arr) {
  printf("Size: %d\n", arr->size);
  printf("Max Size: %d\n", arr->capacity);
  for (int i = 0; i<arr->size; i++) {
    printf("Index %d: %d\n", i, arr->data[i]);
  }
  printf("--------------------------------------\n");
}

DynamicIntArray* dia_new(int i_size, float g_factor) {
  if (i_size <=  0) {
    fprintf(stderr, "Failure. i_size must be >= 1 \n");
    exit(EXIT_FAILURE);
  }
  int *data=(int*) malloc(i_size * sizeof(int));
  DynamicIntArray* arr=(DynamicIntArray*) malloc(sizeof(DynamicIntArray));
  arr->data=data;
  arr->size=0;
  arr->g_factor=g_factor;
  arr->capacity=MAX(i_size, 1);
  return arr;
}

void test_dia_grow() {
  DynamicIntArray* arr=dia_new(5, 2.0);
  assert(arr->capacity == 5);
  dia_grow(arr);
  assert(arr->capacity == 10);
}

void test_dia_requires_growth() {
  DynamicIntArray* arr=dia_new(1,3.0);
  dia_append(arr, 1);
  assert(dia_requires_growth(arr) == true);
  dia_append(arr, 1);
  assert(dia_requires_growth(arr) == false);
}

void test_dia_ensure_enough_capacity() {
  DynamicIntArray* arr=dia_new(1, 2.0);
  dia_append(arr, 1);
  int initial_capacity=arr->capacity;
  dia_ensure_enough_capacity(arr);
  assert(initial_capacity < arr->capacity);
  arr=dia_new(2, 2.0);
  dia_append(arr, 1);
  initial_capacity=arr->capacity;
  assert(initial_capacity == arr->capacity);
}

void test_dia_insert() {
  DynamicIntArray* arr=dia_new(1, 1.5);
  dia_insert(arr, 0, 1);
  assert(dia_value(arr, 0) == 1);
  dia_insert(arr, 0, 2);
  assert(dia_value(arr, 0) == 2);
}

void test_dia_append() {
  DynamicIntArray* arr=dia_new(1, 1.5);
  dia_append(arr, 1);
  assert(dia_value(arr, 0) == 1);
  dia_append(arr, 2);
  assert(dia_value(arr, 1) == 2);
}

void test_dia_delete()  {
  DynamicIntArray* arr=dia_new(1, 1.5);
  dia_append(arr, 1);
  dia_append(arr, 2);
  dia_delete(arr, 1);
  assert(dia_size(arr)==1);
}

void test_dia_pop() {
  DynamicIntArray* arr=dia_new(1, 1.5);
  dia_append(arr, 1);
  dia_append(arr, 2);
  dia_pop(arr);
  assert(dia_value(arr, dia_size(arr)-1)==1);
}

void test_dia_value() {
  DynamicIntArray* arr=dia_new(1, 1.5);
  dia_append(arr, 1);
  assert(dia_value(arr, dia_size(arr)-1)==1);
}

void test_dia_size() {
  DynamicIntArray* arr=dia_new(1, 1.5);
  dia_append(arr, 1);
  assert(dia_size(arr)==arr->size);
  dia_pop(arr);
  assert(dia_size(arr)==arr->size);
}

void test_dia_slice() {
  DynamicIntArray* arr=dia_new(1, 1.5);
  dia_append(arr, 1);
  dia_append(arr, 2);
  dia_append(arr, 3);
  DynamicIntArray* n_arr=dia_slice(arr, 0, 1);
  assert(dia_value(n_arr, 0)==1);
  assert(dia_size(n_arr)==1);

  dia_dealloc(n_arr);
  n_arr=dia_slice(arr, -1, dia_size(arr));
  assert(dia_value(n_arr, 0)==3);
  assert(dia_size(n_arr)==1);

  dia_dealloc(n_arr);
  n_arr=dia_slice(arr, 0, -1);
  assert(dia_value(n_arr, 1) == 2);
  assert(dia_size(n_arr)==2);

  dia_dealloc(n_arr);
  n_arr=dia_slice(arr, 0, 0);
  assert(dia_size(n_arr)==0);
}

void run_dia_tests() {
  test_dia_grow();
  test_dia_requires_growth();
  test_dia_ensure_enough_capacity();
  test_dia_insert();
  test_dia_append();
  test_dia_delete();
  test_dia_pop();
  test_dia_value();
  test_dia_size();
  test_dia_slice();
}
