//from https://stackoverflow.com/questions/3437404/min-and-max-in-c
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


IntLinkedList* ill_new() {
  // First node is NULL, empty ill
  IntLinkedList* ill = (IntLinkedList*) malloc(sizeof(IntLinkedList));
  ill->size=0;
  ill->head=NULL;

  return ill;
}

Node* ill_node(IntLinkedList* ill, int index) {
  if (index >= ill->size || index < 0) {
    fprintf(stderr, "Failure. Index %d is out of bounds for size %d \n", index, ill->size);
    exit(EXIT_FAILURE);
  }
  Node *curr = ill->head;
  for (int i=0; i < index; i++) {
    curr=curr->next;
  }
  return curr;
}

void _ill_insert_old(IntLinkedList* ill, int index, int data) {
  // Old implementation that was  looping more than required
  // using ill_node
  if (index > ill->size || index < 0) {
    fprintf(stderr, "Failure. Index %d is out of bounds for insert for size %d \n", index, ill->size);
    exit(EXIT_FAILURE);
  }

  Node* n_node = (Node*) malloc(sizeof(Node));
  n_node->data=data;

  // Update new node
  if (index == ill->size) {
    n_node->next=NULL;
  } else {
    n_node->next=ill_node(ill, index);
  }

  // Update prior node
  if (index == 0) {
    ill->head=n_node;
  } else {
    Node* prior_node=ill_node(ill, index-1);
    prior_node->next=n_node;
  }

  ill->size+=1;
}

void ill_insert(IntLinkedList *ill, int index, int data) {
  if (index > ill->size || index < 0) {
    fprintf(stderr, "Failure. Index %d is out of bounds for insert for size %d \n", index, ill->size);
    exit(EXIT_FAILURE);
  }

  Node* n_node = (Node*) malloc(sizeof(Node));
  n_node->data=data;
  n_node->next=NULL;
  if (ill->size == 0) {
    ill->head=n_node;
  }
  else if (index == 0) {
    n_node->next=ill->head;
    ill->head=n_node;
  } else {
    Node* prev=NULL;
    Node* curr=ill->head;
    for (int i=0; i < index; i++) {
      prev=curr;
      curr=curr->next;
    }
    prev->next=n_node;
    n_node->next=curr;
  }

  ill->size+=1;
}

void ill_append(IntLinkedList* ill, int data) {
  ill_insert(ill, ill->size, data);
}

void _ill_delete_old(IntLinkedList* ill, int index) {
  // Old implementation that was looping more than necessary
  // using ill_node
  if (index >= ill->size  || index < 0) {
    fprintf(stderr, "Failure, Index %d is out of bounds for delete for size %d \n", index, ill->size);
    exit(EXIT_FAILURE);
  }
  Node *tbd=ill_node(ill, index);
  if (index == 0) {
    ill->head=tbd->next;
  } else {
    Node* prior_node=ill_node(ill, index-1);
    prior_node->next=tbd->next;
  }

  free(tbd);
  ill->size=ill->size-1;
}

void ill_delete(IntLinkedList* ill, int index) {
  Node* tbd;
  if (index == 0) {
    tbd=ill->head;
    ill->head=tbd->next;
  } else {
    Node* prev=NULL;
    tbd=ill->head;
    for (int i=0; i<index; i++) {
      prev=tbd;
      tbd=tbd->next;
    }
    prev->next=tbd->next;
  }
  free(tbd);
  ill->size=ill->size-1;
}

void ill_pop(IntLinkedList* ill) {
  ill_delete(ill, ill->size-1);
}

Node* ill_find(IntLinkedList* ill, int data) {
  Node *curr = ill->head;
  while (curr != NULL) {
    if (curr->data == data) {
      return curr;
    } else {
      curr=curr->next;
    }
  }
  return NULL;
}

void ill_reverse(IntLinkedList* ill) {
  if (ill->size <= 1) {
    return;
  } else {
    Node* prior=NULL;
    Node* curr=ill->head;
    while(curr != NULL) {
      Node *next=curr->next;
      curr->next=prior;
      prior=curr;
      curr=next;
    }
    ill->head=prior;
  }
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

IntLinkedList* ill_slice(IntLinkedList* ill, int start, int end) {
  // Python style slice implementation
  int l=_l_slice_index(_slice_index(ill->size, start));
  int u=_u_slice_index(ill->size, _slice_index(ill->size, end));

  IntLinkedList *n_ill = ill_new();
  Node* curr=ill->head;
  for (int i=0; i<u; i++) {
    if (i >= l) {
      ill_append(n_ill, curr->data);
    }
    curr=curr->next;
  }
  return n_ill;
}

void ill_dealloc(IntLinkedList* ill) {
  Node *curr=ill->head;
  for (int i=0; i<ill->size; i++) {
    curr=curr->next;
    free(curr);
  }
  free(ill);
}

void ill_print(IntLinkedList* ill) {
  printf("Size: %d\n", ill->size);

  for (int i=0; i < ill->size; i++) {
    Node *node=ill_node(ill, i);
    printf("Index: %d Value: %d Next: %p\n", i, node->data, node->next);
  }
}

// Tests
//--------------------------------------------------------

void test_ill_new() {
  IntLinkedList* ill=ill_new();
  assert (ill->size == 0);
  assert (ill->head == NULL);
}

void test_ill_node() {
  IntLinkedList* ill = ill_new();
  Node* f_node = (Node*) malloc(sizeof(Node));
  f_node->data=0;

  Node* s_node = (Node*) malloc(sizeof(Node));
  s_node->data=1;

  ill->head=f_node;
  f_node->next=s_node;
  s_node->next=NULL;

  ill->size=2;

  assert(ill_node(ill, 0) == f_node);
  assert(ill_node(ill, 1) == s_node);
}

void test_ill_insert() {
  IntLinkedList* ill = ill_new();
  ill_insert(ill, 0, 0);
  ill_insert(ill, 1, 1);
  assert (ill->size == 2);
  assert (ill_node(ill, 1)->data == 1);
  ill_insert(ill, 0, 100);
  assert (ill_node(ill, 0)->data == 100);
  ill_insert(ill, ill->size, 100);
  assert (ill_node(ill, ill->size-1)->data == 100);
}

void test_ill_append() {
  IntLinkedList* ill = ill_new();
  ill_append(ill, 0);
  ill_append(ill, 100);
  ill_append(ill, 1000);
  assert(ill->size == 3);
  assert(ill_node(ill, 2)->data==1000);
}

void test_ill_delete() {
  IntLinkedList* ill = ill_new();
  ill_append(ill, 0);
  ill_append(ill, 100);
  ill_append(ill, 1000);
  ill_append(ill, 10000);
  ill_append(ill, 100000);
  ill_delete(ill, 0);
  ill_delete(ill, ill->size-1);
  ill_delete(ill, 1);
  assert(ill->size == 2);
  assert(ill_node(ill, 0)->data==100);
  assert(ill_node(ill, 1)->data==10000);
}

void test_ill_find() {
  IntLinkedList *ill = ill_new();
  ill_append(ill, 0);
  ill_append(ill, 100);
  ill_append(ill, 1000);
  Node *node = ill_find(ill, 100);
  assert(node->data == 100);
  Node *node2 = ill_find(ill, 200);
  assert(node2 == NULL);
}

void test_ill_reverse() {
  IntLinkedList *ill = ill_new();
  ill_append(ill, 0);
  ill_append(ill, 100);
  ill_append(ill, 1000);
  ill_append(ill, 10000);
  ill_append(ill, 100000);
  ill_reverse(ill);
}

void test_ill_slice() {
  printf("test_ill_slice\n");
  IntLinkedList *ill = ill_new();
  ill_append(ill, 0);
  ill_append(ill, 100);
  ill_append(ill, 1000);
  ill_append(ill, 10000);

  IntLinkedList *s_ill = ill_slice(ill, 1, 5);
  assert(s_ill->head->data==100);
  assert(ill_node(s_ill, s_ill->size-1)->data==10000);

  IntLinkedList *t_ill = ill_slice(ill, -5, 2);
  assert(t_ill->head->data==0);
  assert(t_ill->size==2);
}

void run_ill_tests() {
  test_ill_new();
  test_ill_node();
  test_ill_insert();
  test_ill_append();
  test_ill_delete();
  test_ill_find();
  test_ill_reverse();
  test_ill_slice();
}
