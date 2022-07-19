#ifndef ARRAY_HEADER_FILE
#define ARRAY_HEADER_FILE

#include <stdbool.h>
#include <assert.h>
typedef struct DynamicIntArray DynamicIntArray;
struct DynamicIntArray {
  float g_factor;
  int capacity;
  int size;
  int* data;
};

void dia_ensure_realloc_success(void* p);
void dia_ensure_index_exists(DynamicIntArray* arr, int index);
void dia_grow(DynamicIntArray* arr);
bool dia_requires_growth(DynamicIntArray* arr);
void dia_ensure_enough_capacity(DynamicIntArray* arr);
void dia_insert(DynamicIntArray* arr, int index, int value);
void dia_append(DynamicIntArray* arr, int value);
void dia_delete(DynamicIntArray* arr, int index);
void dia_pop(DynamicIntArray* arr);
int dia_value(DynamicIntArray* arr, int index);
int dia_size(DynamicIntArray* arr);
void dia_dealloc(DynamicIntArray* arr);
DynamicIntArray* dia_slice(DynamicIntArray* arr, int l, int u);
void dia_print(DynamicIntArray* arr);
DynamicIntArray* dia_new(int i_size, float g_factor);


void test_dia_grow();
void test_dia_requires_growth();
void test_dia_ensure_enough_capacity();
void test_dia_insert();
void test_dia_append();
void test_dia_delete();
void test_dia_pop();
void test_dia_value();
void test_dia_size();
void test_dia_slice();
void run_dia_tests();

#endif
