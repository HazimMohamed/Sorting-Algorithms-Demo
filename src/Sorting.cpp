#include <iostream>
#include "../include/Sorting.h"

long Sorting::quickSortSplit(std::vector<int> &toSplit, long start, long end, long &pivot) {
    long comparisons = 0;
    long i = start;

    swap(toSplit, pivot, end);
    pivot = toSplit[end];

    for(long j = start; j < end; j++){
        if(toSplit[j] <= pivot){
            swap(toSplit, i, j);
            i++;
        }
        comparisons++;
    }

    swap(toSplit, i, end);
    pivot = i;
    return comparisons;
}

long Sorting::quickSort(std::vector<int> &toSort, long start, long end, bool randomPivot) {
    long comparisons = 0;

    if(end <= start){
        return comparisons;
    }
    comparisons++;

    long pivot;
    srand(time(NULL));

    if(randomPivot){
        pivot = (rand() % (end-start)) + start;
    } else {
        pivot = start;
    }

    comparisons += quickSortSplit(toSort, start, end, pivot);
    comparisons += quickSort(toSort, start, pivot - 1, randomPivot);
    comparisons += quickSort(toSort, pivot + 1, end, randomPivot);

    return comparisons;
}

long Sorting::selectionSort(std::vector<int> &toSort, long start, long end) {
    if(end <= start){
        return 0;
    }

    long minIndex = start;
    long comparisons = 0;

    for(long i = start; i < end; i++) {
        if(toSort[i] < toSort[minIndex]){
            minIndex = i;
        }
        comparisons++;
    }

    swap(toSort, start, minIndex);

    comparisons += selectionSort(toSort, start+1, end);
    return comparisons;
}

long Sorting::heapSort(std::vector<int> &toSort, long start, long end) {
    long comparisons = 0;
    long numValues = end - start;

    for(long index = numValues/2 - 1; index >= 0; index--){
        comparisons += reheapDown(toSort, index, numValues-1);
    }

    for(long index = numValues-1; index > 0; index--){
        swap(toSort, 0, index);
        comparisons += reheapDown(toSort, 0, index-1);
    }

    return comparisons;
}


long Sorting::reheapDown(std::vector<int> &toHeapDown, long toMove, long end) {
    long comparisons = 0;

    long leftChildIndex = toMove * 2 + 1;
    long rightChildIndex = toMove * 2 + 2;
    long maxChild;

    if (leftChildIndex > end) {
        return comparisons;
    }
    comparisons++;

    if(leftChildIndex == end) {
        maxChild = leftChildIndex;
    } else {
        if(toHeapDown[leftChildIndex] <= toHeapDown[rightChildIndex]){
            maxChild = rightChildIndex;
        } else {
            maxChild = leftChildIndex;
        }
        comparisons++;
    }
    comparisons++;
    if(toHeapDown[toMove] < toHeapDown[maxChild]){
        swap(toHeapDown, toMove, maxChild);
        comparisons += reheapDown(toHeapDown, maxChild, end);
    }
    comparisons++;

    return comparisons;
}

long Sorting::merge(std::vector<int> &toMerge, long start, long end, long div) {
    long i = start;
    long j = div;
    long k = 0;
    long comparisons = 0;

    int temp[end-start];
    while(i < div && j < end) {
        if (toMerge[i] <= toMerge[j]) {
            temp[k++] = toMerge[i++];
        } else {
            temp[k++] = toMerge[j++];
        }
        comparisons++;
    }

    while(j < end){
        temp[k++] = toMerge[j++];
    }

    while(i < div){
        temp[k++] = toMerge[i++];
    }

    k = 0;
    while((k + start) < end){
        toMerge[k + start] = temp[k];
        k++;
    }

    for(long i = start; i < end; i++){
        toMerge[i] = temp[i-start];
    }

    return comparisons;
}

long Sorting::mergeSort(std::vector<int> &toSort, long start, long end) {
    long comparisons = 0;

    if(end <= start) {
        return 0;
    }
    comparisons ++;

    long divisionPoint = ((end+start)/2);

    comparisons += mergeSort(toSort, start, divisionPoint);
    comparisons += mergeSort(toSort, divisionPoint+1, end);
    comparisons += merge(toSort, start, end, divisionPoint);

    return comparisons;
}

void Sorting::swap(std::vector<int> &toSwap, long a, long b) {
    int temp = toSwap[b];
    toSwap[b] = toSwap[a];
    toSwap[a] = temp;
}