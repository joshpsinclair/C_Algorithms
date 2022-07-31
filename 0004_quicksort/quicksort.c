
void print_array(int array[], int lo, int hi) {
    printf("[");
  for (int i = lo; i < hi+1; i++) {
    printf("%d", array[i]);
    if (i < hi) {
      printf(", ");
    }
  }
  printf("]\n");
}

bool compare_reverse(int a, int b, bool reverse) {
  if (reverse == true) {
    return (a > b);
  } else {
    return (a < b);
  }
}

int partition(int array[], int lo, int hi, bool reverse) {
  // Use the last element as the pivot, other methods exists
  // such as the median method, or randomly selecting
  int pivot = array[hi];
  int i = lo-1;
  int j = i+1;

  // move all elements that are less
  // then the pivot
  while (j < hi) {
    if (compare_reverse(array[j], pivot, reverse)) {
      i++;
      int temp = array[i];
      array[i]=array[j];
      array[j]=temp;
    }
    j++;
  }

  // swap pivot with position i
  // as we know its place
  int temp = array[i+1];
  array[i+1]=array[hi];
  array[hi]=temp;
  return i+1;
}

void quicksort(int array[], int lo, int hi, bool reverse) {
  if (lo >= hi || lo < 0) {
    return;
  }

  // recursivly sort using the lower and upper arrays
  // from the pivot
  int pivot=partition(array, lo, hi, reverse);
  quicksort(array, 0, pivot-1, reverse);
  quicksort(array, pivot, hi, reverse);
}

void test_standard_quicksort() {
  int array[] = {5,0,2,4,1,3};
  quicksort(array, 0, 5, false);
  assert (array[0]==0);
  assert (array[1]==1);
  assert (array[2]==2);
  assert (array[3]==3);
  assert (array[4]==4);
  assert (array[5]==5);
}

void test_reverse_quicksort() {
  int array[] = {5,0,2,4,1,3};
  quicksort(array, 0, 5, true);
  assert (array[0]==5);
  assert (array[1]==4);
  assert (array[2]==3);
  assert (array[3]==2);
  assert (array[4]==1);
  assert (array[5]==0);
}

void run_quicksort_tests() {
  test_standard_quicksort();
  test_reverse_quicksort();
}
