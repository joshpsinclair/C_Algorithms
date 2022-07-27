#ifndef LIFOSTACK_HEADER_FILE
#define LIFOSTACK_HEADER_FILE

#include <assert.h>

typedef struct IntLifoStackNode IntLifoStackNode;
struct IntLifoStackNode {
  IntLifoStackNode* previous;
  int data;
};

typedef struct IntLifoStack IntLifoStack;
struct IntLifoStack {
  IntLifoStackNode* head;
  int size;
};

IntLifoStack* ils_new() ;
void ils_push(IntLifoStack* ils, int data);
int ils_pop(IntLifoStack *ils);
int ils_size(IntLifoStack *ils);
void ils_dealloc(IntLifoStack *ils);
void run_ils_tests();

#endif
