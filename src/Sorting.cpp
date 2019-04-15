#include "../include/Sorting.h"

long Sorting::quickSort(std::vector<int> &toSort, long start, long end, long pivot, bool randomPivot) {

}

long Sorting::selectionSort(std::vector<int> &toSort, long start, long end) {
    if(end - start == 1){
        return 0;
    }

    int min = toSort[0];
    long minIndex = 0;
    long comparisons = 0;

    for(long i = start; i < end; i++) {
        if(toSort[i] < min){
            min = toSort[i];
            minIndex = i;
            comparisons++;
        }
    }

    swap(toSort, start, minIndex);

    comparisons += selectionSort(toSort, start+1, end);
    return comparisons;
}

long Sorting::heapSort(std::vector<int> &toSort, long start, long end) {

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

    return comparisons;
}

long Sorting::mergeSort(std::vector<int> &toSort, long start, long end) {
    if(end - start == 1) {
        return 0;
    }

    if(end - start == 2){
        if(toSort[start] > toSort[end]){
            swap(toSort, start, end - 1);
            return 1;
        }
    }

    long comparisons = 0;
    long divisionPoint = (end-start/2);

    comparisons += mergeSort(toSort, start, divisionPoint);
    comparisons += mergeSort(toSort, divisionPoint, end);
    comparisons += merge(toSort, start, end, divisionPoint);

    return comparisons;
}

void Sorting::swap(std::vector<int> &toSwap, long a, long b) {
    int temp = toSwap[b];
    toSwap[b] = toSwap[a];
    toSwap[a] = temp;
}