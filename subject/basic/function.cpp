#include "header.h"

int sum(int a, int b) {
  return a + b;
}

int sub(int a, int b) {
  return a - b;
}

void test_func_pointer(int a, int b, int (*pf)(int, int)) {
  cout << "get result: " << (*pf)(a,b) << endl;
}

void test_function() {
  int a = 10, b = 5;
  test_func_pointer(a, b, sum);
  test_func_pointer(a, b, sub);
}
