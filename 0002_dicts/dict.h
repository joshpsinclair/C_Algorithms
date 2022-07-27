#ifndef DICT_HEADER_FILE
#define DICT_HEADER_FILE

#include <stdbool.h>
#include <assert.h>

typedef struct IntHashmapItem IntHashmapItem;
struct IntHashmapItem {
  char* key;
  int value;
};

typedef struct IntHashmap IntHashmap;
struct IntHashmap {
  float g_factor;
  int capacity;
  int size;
  IntHashmapItem* items;
};

unsigned long djb2_hash(char *key);
void ihm_fill_empty(IntHashmapItem* items, int start_index, int end_index);
int ihm_hash(unsigned long (*hashing_func)(char*), int capacity, char* key);
void ihm_ensure_realloc_success(void *p);
bool ihm_does_need_growth(IntHashmap *ihm);
void ihm_grow(IntHashmap* ihm);
bool ihm_is_index_collision(IntHashmap* ihm, int index);
int ihm_resolve_collision(IntHashmap* ihm, int index);
void ihm_insert(IntHashmap* ihm, char* key, int value);
void ihm_print(IntHashmap* ihm);
void ihm_delete(IntHashmap* ihm, char* key);
int ihm_get(IntHashmap* ihm, char* key);
int ihm_size(IntHashmap *ihm);
IntHashmap* ihm_new(int i_size, float g_factor);
char* int_to_charp(int i);
void run_ihm_tests();


#endif
