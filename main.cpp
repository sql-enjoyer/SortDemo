#include "SortDemo.h"
#include <vector>
using namespace std;

int main (int argc, char *argv[]) {
  const int height = 30, width = 120;
  vector<int> arr{11, 12, 23, 10, 29, 19, 8, 4, 26, 30, 2, 6, 27, 18, 22, 1, 13, 9, 25, 20, 17, 7, 28, 3, 5, 16, 14, 15, 24, 21};
  SortDemo root(arr, height, width);
  root.radixSort();
  return 0;
}