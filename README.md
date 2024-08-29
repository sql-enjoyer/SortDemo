# SortDemo
A simple application to display the sorting process in the console
![](https://github.com/sql-enjoyer/SortDemo/blob/master/image.png)
## Main Files
**SortDemo.h** - header with main class **SortDemo**.

**main.cpp** - file with included class and default calls.
## Guide
1. Сreate a class object with the argument as a `vector`: 
```
vector<int> arr{11, 12, 23, 10, 29, 19, 8, 4, 26, 30};
SortDemo root(arr);
```
_`void setArr(const vector<int>& inp)`_ - for set another vector.

2. Call sort function: `root.bogoSort()`

## Current Sorting Algorithms:
- `*.bogoSort()`
- `*.combSort()`
- `*.bubbleSort()`
- `*.shakerSort()`
- `*.radixSort()`
