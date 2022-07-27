#import <string.h>
#include <math.h>


/*
  The stack can be implemented using an array or a linked list.
  Arrays have more efficient memory complexities, but can be slower
  in the worst case with time complexity
  Linked lists are faster in the best case with response time but use
  more space
*/

IntLifoStack* ils_new() {
  IntLifoStack* ils = (IntLifoStack*) malloc(sizeof(IntLifoStack));
  ils->size=0;
  ils->head=NULL;
  return ils;
}

void ils_push(IntLifoStack* ils, int data) {
  IntLifoStackNode *node = (IntLifoStackNode*) malloc(sizeof(IntLifoStackNode));
  node->data=data;
  if (ils->size > 0) {
    IntLifoStackNode *previous_head = ils->head;
    previous_head->previous=node;
    node->previous=previous_head;
  } else {
    node->previous=NULL;
  }
  ils->size++;
  ils->head=node;
}

int ils_pop(IntLifoStack *ils) {
  if (ils->size <= 0) {
    fprintf(stderr, "Failure, stack is empty");
    exit(EXIT_FAILURE);
  }

  IntLifoStackNode *top_node = ils->head;
  ils->head=top_node->previous;

  ils->size--;
  return top_node->data;
}

int ils_size(IntLifoStack *ils) {
  return ils->size;
}

void ils_dealloc(IntLifoStack *ils) {
  IntLifoStackNode *curr = ils->head;
  for (int i=0; i < ils->size; i++) {
    IntLifoStackNode *prev = curr->previous;
    free(curr);
    curr=prev->previous;
  }
  free(ils);
}

void test_push() {
  IntLifoStack *ils = ils_new();
  ils_push(ils, 5);
  assert(ils->head->data==5);
  ils_push(ils, 10);
  assert(ils->head->data==10);
  assert(ils->head->previous->data=5);
}

void test_pop() {
  IntLifoStack *ils = ils_new();
  ils_push(ils, 5);
  int res = ils_pop(ils);
  assert(res == 5);
}

void run_ils_tests() {
  test_push();
  test_pop();
}
