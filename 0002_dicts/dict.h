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
