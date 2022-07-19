#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h"
#include "linkedlist.c"


int random_range(int min, int max) {
  return rand() % (max + 1 - min) + min;
}

void benchmark_ill_delete(int n_nodes) {
  IntLinkedList* ill1 = ill_new();
  IntLinkedList* ill2 = ill_new();
  for (int i=0; i<n_nodes; i++) {
    ill_insert(ill1, ill1->size, i);
    ill_insert(ill2, ill2->size, i);
  }

  float old_delete_start = clock() / (float) CLOCKS_PER_SEC;
  for (int i=0; i<n_nodes; i++) {
    int index=random_range(0, ill1->size-1);
    _ill_delete_old(ill1, index);
  }
  float old_delete_end = clock() / (float) CLOCKS_PER_SEC;
  printf("ill_old_delete took: %f to delete: %d nodes\n",
          (old_delete_end-old_delete_start),
          n_nodes);

  float new_delete_start = clock() / (float) CLOCKS_PER_SEC;
  for (int i=0; i<n_nodes; i++) {
    int index=random_range(0, ill2->size-1);
    ill_delete(ill2, index);
  }

  float new_delete_end = clock() / (float) CLOCKS_PER_SEC;
  printf("ill_delete took: %f to delete: %d nodes\n",
          (new_delete_end-new_delete_start),
          n_nodes);
}

void benchmark_ill_insert(int n_nodes) {
  IntLinkedList* ill1 = ill_new();
  IntLinkedList* ill2 = ill_new();

  float old_insert_start = clock() / (float) CLOCKS_PER_SEC;
  for (int i=0; i<n_nodes; i++) {
    int index=random_range(0, ill1->size);
    _ill_insert_old(ill1, index, i);
  }
  float old_insert_end = clock() / (float) CLOCKS_PER_SEC;
  printf("ill_old_insert took: %f to insert %d nodes\n",
        (old_insert_end - old_insert_start),
        n_nodes);


  float new_insert_start = clock() / (float) CLOCKS_PER_SEC;
  for (int i=0; i<n_nodes; i++) {
    int index=random_range(0, ill2->size);
    ill_insert(ill2, index, i);
  }

  float new_insert_end = clock() / (float) CLOCKS_PER_SEC;
  printf("ill_new_insert took: %f to insert %d nodes\n",
        (new_insert_end - new_insert_start),
        n_nodes);
}


int main(int argc, char* argv[] ) {
  printf("running tests \n");
  run_ill_tests();
  printf("ran tests \n");
}
