#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <sys/ioctl.h>
#include <unistd.h>
using namespace std;

class SortDemo{
  public:
    SortDemo(vector<int> inp):arr(inp) {};
    void setArr(const vector<int>& inp) { arr = inp; }

    void const demo(const vector<int>& arr, const int& wait);

    //sorting helpers
    bool isSorted();
    void countSort(int exp);
    int getMax();

    // sorting methods
    void bubbleSort();
    void shakerSort();
    void combSort();
    void bogoSort();
    void radixSort();

  private:
    vector<int> arr;
};

void const SortDemo::demo(const vector<int>& arr, const int& wait){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int width_screen = w.ws_col, height_screen = w.ws_row-1;

  const int border = (width_screen - arr.size()*3) / 2;
  char screen[height_screen*width_screen];

  int max = arr[0];
  for(int i=1; i < arr.size(); ++i) if (arr[i] > max) max = arr[i];

  int index = 0;
  bool flag = false;
  for(int i=0; i<width_screen; ++i){
    if(i < border || i > width_screen-border+(1*(arr.size()%2!=0)) || (i-border)%3 == 0) {
      if(flag) ++index;
      flag = false;
    }
    else flag = true;
    for(int j=0; j<height_screen; ++j){
      if(flag && (float) (height_screen-j)/height_screen <= (float) arr[index]/max) screen[i + j*width_screen] = '#';
      else screen[i + j*width_screen] = ' ';
    }
  }
  for(char i : screen) cout << i;
  cout << endl;
  this_thread::sleep_for(chrono::milliseconds(wait));
}

void SortDemo::bubbleSort() {
  int n = arr.size();
  bool swapped;

  for (int i = 0; i < n - 1; i++) {
    swapped = false;
    for (int j = 0; j < n - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
           swap(arr[j], arr[j + 1]);
           swapped = true;
        }
        demo(arr, 17);
    }
    if (!swapped) break;
  }
}

void SortDemo::shakerSort() {
  if (arr.empty()) {
    return;
  }
  int left = 0;
  int right = arr.size() - 1;
  while (left <= right) {
    for (int i = right; i > left; --i) {
      if (arr[i - 1] > arr[i]) {
        swap(arr[i - 1], arr[i]);
      }
      demo(arr, 17);
    }
    ++left;
    for (int i = left; i < right; ++i) {
      if (arr[i] > arr[i + 1]) {
        swap(arr[i], arr[i + 1]);
      }
      demo(arr, 17);
    }
    --right;
  }
}

void SortDemo::combSort() {
  const double factor = 1.247;
  double step = arr.size() - 1;

  while (step >= 1) {
    for (int i = 0; i + step < arr.size(); ++i) {
      if (arr[i] > arr[i + step]) {
        swap(arr[i], arr[i + step]);
      }
      demo(arr, 17);
    }
    step /= factor;
  }
}

bool SortDemo::isSorted() {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void SortDemo::bogoSort() {
    while (!isSorted()) {
        for (size_t i = 0; i < arr.size(); ++i) {
            size_t j = rand() % arr.size();
            swap(arr[i], arr[j]);
            demo(arr, 17);
        }
    }
}

int SortDemo::getMax(){
    int mx = arr[0];
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void SortDemo::countSort(int exp){
    int output[arr.size()];
    int i, count[10] = { 0 };

    for (i = 0; i < arr.size(); i++) count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++) count[i] += count[i - 1];
    for (i = arr.size() - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < arr.size(); i++) {
      arr[i] = output[i];
      demo(arr, 17);
    }
}

void SortDemo::radixSort(){
    int m = getMax();

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(exp);
}