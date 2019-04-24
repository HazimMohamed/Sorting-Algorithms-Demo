#ifndef SORTING
#define SORTING

#include <vector>

class Sorting{
    static void swap(std::vector<int> &toSwap, long a, long b);

    static long merge(std::vector<int> &toMerge, long start, long end, long divisionPoint);

    static long reheapDown(std::vector<int> &toHeapDown, long toMove, long end);

    static long quickSortSplit(std::vector<int> &toSplit, long start, long end, long &pivot);

public:
    static long mergeSort(std::vector<int> &toSort, long start, long end);

    static long quickSort(std::vector<int> &toSort, long start, long end, bool randomPivot);

    static long heapSort(std::vector<int> &toSort, long start, long end);

    static long selectionSort(std::vector<int> &toSort, long start, long end);
};
#endif