#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <chrono>
#include <sys/ioctl.h>
#include <unistd.h>


template<class T>
class basic_demo {
private:
  int max;  // Max element in collection,
            // need for cumpute column height
  int wait; // Delay

protected:
  std::vector<T>* v;

public:
  basic_demo(std::vector<T>* iv, const int& iw = 17) 
    : v(iv), wait(iw), max(*max_element(iv->begin(), iv->end())) {}

  void setArr(const std::vector<int>* iv) { v = iv; }

  void demo() const {
      // Find console size
      struct winsize w;
      if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
          perror("ioctl");
          return;
      }
      int width_screen = w.ws_col, height_screen = w.ws_row - 1;

      // Edge padding
      const int border = (width_screen - v->size() * 3) / 2;
      // Create empty screen
      std::vector<char> screen(height_screen * width_screen, ' ');

      int index = 0;
      bool flag = false;
      for (int i = 0; i < width_screen; ++i) {
          // Paddings
          if (i < border || i > width_screen - border + (1 * (v->size() % 2 != 0)) || (i - border) % 3 == 0) {
              if (flag && index < v->size()) ++index;
              flag = false;
          } else {
              flag = true;
          }
          //Columns
          for (int j = 0; j < height_screen; ++j) {
              if (flag && static_cast<float>(height_screen - j) / height_screen <= static_cast<float>((*v)[index]) / max) {
                  screen[i + j * width_screen] = '#';
              } else {
                  screen[i + j * width_screen] = ' ';
              }
          }
      }

      // Screen output
      for (int j = 0; j < height_screen; ++j) {
          for (int i = 0; i < width_screen; ++i) {
              std::cout << screen[i + j * width_screen];
          }
          std::cout << '\n';
      }
      // Display delay 
      std::this_thread::sleep_for(std::chrono::milliseconds(wait));
  }
};


struct SortDemo : basic_demo<int>{
  SortDemo(std::vector<int>* iv) : basic_demo<int>(iv) {};

  // Sorting helpers
  bool isSorted();
  void countSort(int exp);
  int  getMax();

  // Sorting methods
  void bubbleSort();
  void shakerSort();
  void combSort();
  void bogoSort();
  void radixSort();
};

void SortDemo::bubbleSort() {
  int n = v->size();
  bool swapped;

  for (int i = 0; i < n - 1; i++) {
    swapped = false;
    for (int j = 0; j < n - i - 1; j++) {
        if ((*v)[j] > (*v)[j + 1]) {
           std::swap((*v)[j], (*v)[j + 1]);
           swapped = true;
        }
        demo();
    }
    if (!swapped) break;
  }
}

void SortDemo::shakerSort() {
  if (v->empty()) {
    return;
  }
  int left = 0;
  int right = v->size() - 1;
  while (left <= right) {
    for (int i = right; i > left; --i) {
      if ((*v)[i - 1] > (*v)[i]) {
        std::swap((*v)[i - 1], (*v)[i]);
      }
      demo();
    }
    ++left;
    for (int i = left; i < right; ++i) {
      if ((*v)[i] > (*v)[i + 1]) {
        std::swap((*v)[i], (*v)[i + 1]);
      }
      demo();
    }
    --right;
  }
}

void SortDemo::combSort() {
  const double factor = 1.247;
  double step = v->size() - 1;

  while (step >= 1) {
    for (int i = 0; i + step < v->size(); ++i) {
      if ((*v)[i] > (*v)[i + step]) {
        std::swap((*v)[i], (*v)[i + step]);
      }
      demo();
    }
    step /= factor;
  }
}

bool SortDemo::isSorted() {
    for (size_t i = 1; i < v->size(); ++i) {
        if ((*v)[i] < (*v)[i - 1]) {
            return false;
        }
    }
    return true;
}

void SortDemo::bogoSort() {
    while (!isSorted()) {
        for (size_t i = 0; i < v->size(); ++i) {
            size_t j = rand() % v->size();
            std::swap((*v)[i], (*v)[j]);
            demo();
        }
    }
}

int SortDemo::getMax(){
    int mx = (*v)[0];
    for (int i = 1; i < v->size(); i++)
        if ((*v)[i] > mx)
            mx = (*v)[i];
    return mx;
}

void SortDemo::countSort(int exp){
    int output[v->size()];
    int i, count[10] = { 0 };

    for (i = 0; i < v->size(); i++) count[((*v)[i] / exp) % 10]++;
    for (i = 1; i < 10; i++) count[i] += count[i - 1];
    for (i = v->size() - 1; i >= 0; i--) {
        output[count[((*v)[i] / exp) % 10] - 1] = (*v)[i];
        count[((*v)[i] / exp) % 10]--;
    }
    for (i = 0; i < v->size(); i++) {
      (*v)[i] = output[i];
      demo();
    }
}

void SortDemo::radixSort(){
    int m = getMax();

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(exp);
}