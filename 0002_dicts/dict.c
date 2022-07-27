#import <string.h>
#include <math.h>

//from https://stackoverflow.com/questions/3437404/min-and-max-in-c
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/*
  Uses djb2 hashing function
  Uses IntHashmapItems with a NULL key to represent an empty index in the hash table
  Uses linear probing for collision resolution
*/

unsigned long djb2_hash(char *key) {
  unsigned long h = 5381;
  int c;
  while ((c = *key++)) {
    h=((h<<5) + h) + c;
  }

  return h;
}

void ihm_fill_empty(IntHashmapItem* items, int start_index, int end_index) {
  for (int i=start_index; i < end_index; i++) {
    IntHashmapItem* item = (IntHashmapItem* ) malloc(sizeof(IntHashmapItem));
    item->key=NULL;
    item->value=0;
    items[i]=*item;
  }
}

int ihm_hash(unsigned long (*hashing_func)(char*), int capacity, char* key) {
  return (*hashing_func)(key) % capacity;
}

void ihm_ensure_realloc_success(void *p) {
  if (p == NULL) {
    fprintf(stderr, "Failure. realloc failed\n");
    exit(EXIT_FAILURE);
  }
}

bool ihm_does_need_growth(IntHashmap *ihm) {
  if (ihm->capacity == ihm->size) { return true; } else { return false; }
}

void ihm_grow(IntHashmap* ihm) {
  int o_capacity = ihm->capacity;
  int n_capacity = ceil(ihm->capacity * ihm->g_factor);
  IntHashmapItem* temp = realloc(ihm->items, sizeof(IntHashmapItem) * n_capacity);
  ihm_ensure_realloc_success(temp);
  ihm->items=temp;
  ihm->capacity=n_capacity;
  ihm_fill_empty(ihm->items, o_capacity, n_capacity);
}


bool ihm_is_index_collision(IntHashmap* ihm, int index) {
  if (index > ihm->capacity) {
    fprintf(stderr, "Failure, index out of bounds\n");
    exit(EXIT_FAILURE);
  }
  if (ihm->items[index].key == NULL) { return false; } else { return true; }
}


int ihm_resolve_collision(IntHashmap* ihm, int index) {
  for (int i=index+1; i<ihm->capacity; i++) {
    if (ihm->items[i].key == NULL) {
      return i;
    }
  }
  return ihm->capacity;
}

void ihm_insert(IntHashmap* ihm, char* key, int value) {
  IntHashmapItem* item = (IntHashmapItem*) malloc(sizeof(IntHashmapItem));
  item->key=key;
  item->value=value;

  if (key == NULL) {
    fprintf(stderr, "Failure, key cannot be NULL \n");
    exit(EXIT_FAILURE);
  }

  if (ihm_does_need_growth(ihm) == true) {
    ihm_grow(ihm);
  }

  int index = ihm_hash(*djb2_hash, ihm->capacity, key);
  if (ihm_is_index_collision(ihm, index)) {
    index = ihm_resolve_collision(ihm, index);
    if (index == ihm->capacity) {
      ihm_grow(ihm);
    }
  }
  ihm->items[index]=*item;
  ihm->size+=1;
}

void ihm_print(IntHashmap* ihm) {
  for (int i=0; i < ihm->capacity; i++) {
    IntHashmapItem item = ihm->items[i];
    if (item.key != NULL) {
      printf("key: %s value: %d index: %d \n", item.key, item.value, i);
    }
  }
}

void ihm_delete(IntHashmap* ihm, char* key) {
  int index = ihm_hash(*djb2_hash, ihm->capacity, key);
  for (int i=index; i < ihm->capacity; i++) {
    IntHashmapItem item = ihm->items[i];
    if (strcmp(item.key, key) == 0) {
      ihm_fill_empty(ihm->items, i, i+1);
    }
  }
}

int ihm_get(IntHashmap* ihm, char* key) {
  int index = ihm_hash(*djb2_hash, ihm->capacity, key);
  for (int i=index; i < ihm->capacity; i++) {
    IntHashmapItem item = ihm->items[i];
    if (strcmp(item.key, key) == 0) {
      return item.value;
    }
  }
  fprintf(stderr, "Failure, key does not exist \n");
  exit(EXIT_FAILURE);
}

int ihm_size(IntHashmap *ihm) {
  return ihm->size;
}

IntHashmap* ihm_new(int i_size, float g_factor) {
  if (i_size <= 0) {
    fprintf(stderr, "Failure. i_size must be >=1 \n");
    exit(EXIT_FAILURE);
  }

  if (g_factor <= 0) {
    fprintf(stderr, "Failure. g_factor must be > 0 \n");
    exit(EXIT_FAILURE);
  }

  IntHashmapItem* items = (IntHashmapItem*)malloc(sizeof(IntHashmapItem) * i_size);
  IntHashmap* ihm = (IntHashmap*) malloc(sizeof(IntHashmap));

  ihm->items=items;
  ihm->g_factor=g_factor;
  ihm->capacity=i_size;
  ihm->size=0;

  ihm_fill_empty(items, 0, i_size);

  return ihm;
}

void ihm_dealloc(IntHashmap *ihm) {
  free(ihm->items);
  free(ihm);
}

char* int_to_charp(int i) {
  int length = snprintf(NULL, 0, "%d", i);
  char* c = malloc(length+1);
  snprintf(c, length+1, "%d", i);
  return c;
}

void test_ihm_is_index_collision() {
  IntHashmap *ihm = ihm_new(1, 1.5);
  assert (ihm_is_index_collision(ihm, 0) == false);

  IntHashmapItem* item = (IntHashmapItem* ) malloc(sizeof(IntHashmapItem));
  item->key="key";
  item->value=0;
  ihm->items[0]=*item;
  assert(ihm_is_index_collision(ihm, 0) == true);
}

void test_ihm_resolve_collision() {
  IntHashmap *ihm = ihm_new(5, 1.5);
  IntHashmapItem *item1 = (IntHashmapItem* ) malloc(sizeof(IntHashmapItem));
  item1->key="1";
  item1->value=0;

  IntHashmapItem *item2 = (IntHashmapItem* ) malloc(sizeof(IntHashmapItem));
  item2->key="1";
  item2->value=0;

  ihm->items[0]=*item1;
  ihm->items[1]=*item2;
  assert(ihm_resolve_collision(ihm, 0) == 2);
  assert(ihm_resolve_collision(ihm, 1) == 2);
}

void test_ihm_does_need_growth() {
  IntHashmap *ihm = ihm_new(1, 1.5);
  IntHashmapItem *item1 = (IntHashmapItem* ) malloc(sizeof(IntHashmapItem));
  item1->key="1";
  item1->value=0;

  assert(ihm_does_need_growth(ihm) == false);
  ihm->items[0]=*item1;
  ihm->size=1;
  assert(ihm_does_need_growth(ihm) == true);
}

void test_ihm_grow() {
  IntHashmap *ihm = ihm_new(1, 1.5);
  int initial_capacity=ihm->capacity;
  assert (ihm->capacity == initial_capacity);
  ihm_grow(ihm);
  assert(ihm->capacity > initial_capacity);
}

void test_ihm_insert() {
  IntHashmap *ihm = ihm_new(1, 1.5);
  assert(ihm->size == 0);
  ihm_insert(ihm, "somekey", 1);
  assert(ihm->items[0].key == "somekey");
  assert(ihm->items[0].value == 1);
  assert(ihm->size == 1);

  for (int i=1; i < 100; i++) {
    ihm_insert(ihm, int_to_charp(i), i);
  }

  assert(ihm->size == 100);
}

void test_ihm_get() {
  IntHashmap *ihm = ihm_new(1, 1.5);
  assert(ihm->size == 0);
  int i_value = 1;
  ihm_insert(ihm, "somekey", i_value);
  int a_value = ihm_get(ihm, "somekey");
  assert(i_value == a_value);

  for (int i=1; i < 100; i++) {
    ihm_insert(ihm, int_to_charp(i), i);
  }
  assert(ihm_get(ihm, "56") == 56);
}

void test_ihm_delete() {
  IntHashmap *ihm = ihm_new(1, 1.5);
  ihm_insert(ihm, "key", 0);
  assert(strcmp(ihm->items[0].key, "key") == 0);
  ihm_delete(ihm, "key");
  assert(ihm->items[0].key == NULL);
}


void run_ihm_tests() {
  test_ihm_is_index_collision();
  test_ihm_resolve_collision();
  test_ihm_does_need_growth();
  test_ihm_grow();
  test_ihm_insert();
  test_ihm_get();
  test_ihm_delete();
}
