rmdir /s /q build
mkdir build
cd build
cmake ..
cmake --build .
start segment-tree.sln