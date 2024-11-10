Instructions:

Compile the C code on a linux system with GCC:

> gcc -o sort_performance sort_performance.c

Adjust the array_sizes list within test_sort_performance.py to hold all intended test points.

> array_sizes = [100, 500, 1000, 5000] 
> array_sizes = [10 * n for n in range(10, 5000, 25)] # default

Run test_sort_performance.py and wait for visualization to appear.

> python3 test_sort_performance.py

