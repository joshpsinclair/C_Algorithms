#ifndef LINKEDLIST_HEADER_FILE
#define LINKEDLIST_HEADER_FILE

#include <assert.h>

typedef struct Node Node;
struct Node {
  Node* next;
  int data;
};

typedef struct IntLinkedList IntLinkedList;
struct IntLinkedList {
  int size;
  Node* head;
};

IntLinkedList* ill_new();
void ill_print(IntLinkedList* ill);


void _ill_insert_old(IntLinkedList* ill, int index, int data);
void ill_insert(IntLinkedList* ill, int index, int data);
void ill_append(IntLinkedList* ill, int data);
void ill_delete(IntLinkedList* ill, int index);
void _ill_delete_old(IntLinkedList* ill, int index);
void ill_pop(IntLinkedList* ill);
void ill_dealloc(IntLinkedList* ill);


void ill_reverse(IntLinkedList* ill);
Node* ill_find(IntLinkedList* ill, int data);
Node* ill_node(IntLinkedList* ill, int index);

IntLinkedList* ill_slice(IntLinkedList* ill, int start, int end);


#endif
