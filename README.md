# Segment Tree

Templated segment tree implementaion in C++

## Example

```c++
int main()
{
    int data[8] = { 5, 8, 4, 3, 7, 2, 1, 6 };
    SegmentTree<int> tree{ data, Combine, 0 };

    int sum = tree.Query(2, 6); // 16

    return 0;
}
```

## Building
- Install [CMake](https://cmake.org/install/)
- Ensure CMake is in the system `PATH`
- Clone the repository `git clone https://github.com/Sopiro/segment-tree`
- Run CMake build script depend on your system
  - Visual Studio: Run `build.bat`
  - Otherwise: Run `build.sh`