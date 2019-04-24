#include <iostream>
#include "include/Sorting.h"
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//Initializes the binary tree by reading data from the file
void init(std::vector<int>& itemList, const std::string& filePath) {
    int input;

    //Opens the filestream
    std::fstream fs;
    fs.open(filePath, std::fstream::in);

    //Reads from the filestream
    if (!fs.is_open()) {
        std::cout << "Failed to open the input file" << std::endl;
        exit(1);
    }

    fs >> input;
    while (!fs.eof()) {
        itemList.push_back(input);
        fs >> input;
    }
    itemList.push_back(input);
}

//Prints the possible commands
void showOptions() {
    cout << "selection-sort (s)" << ", ";
    cout << "merge-sort (m)" << ", ";
    cout << "heap-sort (h)" << ", ";
    cout << "quick-sort-fp (q)" << ", ";
    cout << "quick-sort-rp (n)" ;
}

//Prompts the user and validates the command
char promptUser(){
    std::vector<std::string> validCommands = {"s", "m", "h", "q", "n"};
    while(true) {
        cout << std::endl << "Enter the algorithm: ";
        string command;
        cin >> command;
        for (auto& validCommand : validCommands) {
            if(validCommand == command){
                return command.at(0);
            }
        }
        cout << "Invalid input" << endl;
    }
}

void executeCommand(char command, std::vector<int> &toSort) {
    long comparisons = 0;
    for(auto val: toSort) {
        std::cout << val << " ";
    }
    std::cout << std::endl;


    try {
        switch (command) {
            case 's':
                comparisons = Sorting::selectionSort(toSort, 0, toSort.size());
                break;
            case 'm':
                comparisons = Sorting::mergeSort(toSort, 0, toSort.size());
                break;
            case 'h':
                comparisons = Sorting::heapSort(toSort, 0, toSort.size());
                break;
            case 'q':
                comparisons = Sorting::quickSort(toSort, 0, toSort.size()-1, false);
                break;
            case 'n': {
                comparisons = Sorting::quickSort(toSort, 0, toSort.size()-1, true);
            }
                break;
            default:
                throw std::runtime_error("Internal Error: Invalid command recognized as valid");
        }

        for(const int& i : toSort){
            std::cout << i << " ";
        }
        std::cout << std::endl << "\t# of comparisons: " << comparisons << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << e.what();
    }
}

std::vector<int> genRandomInts(int quantity){
    std::vector<int> out;

    srand(time(NULL));
    for(int i = 0; i < quantity; i++){
        out.push_back(rand() % 10000);
    }

    return out;
}

std::vector<int> genSortedInts(int quantity){
    long current = 0;
    std::vector<int> out;

    srand(time(NULL));
    for(int i = 0; i < quantity; i++){
        current += rand() % 10;
        out.push_back(current);
    }

    return out;
}

std::vector<int> genReverseInts(int quantity){
    std::vector<int> out = genSortedInts(quantity);
    std::reverse(out.begin(), out.end());
    return out;
}


int main(int argc, char** argv) {
    if(argc != 2){
        cout << "Incorrect usage. Correct way to run the program: ./main <path to input file>" << endl;
        return 1;
    }

    if(std::string(argv[1]) == "-g"){

        std::fstream selectionSort;
        selectionSort.open("/Users/Hazim/CLionProjects/DataStructuresAssignment5/output/selectionSort.txt");

        std::fstream mergeSort;
        mergeSort.open("/Users/Hazim/CLionProjects/DataStructuresAssignment5/output/mergeSort.txt");

        std::fstream quickSortRandom;
        quickSortRandom.open("/Users/Hazim/CLionProjects/DataStructuresAssignment5/output/quickSortRandom.txt");

        std::fstream quickSortFirst;
        quickSortFirst.open("/Users/Hazim/CLionProjects/DataStructuresAssignment5/output/quickSortFirst.txt");

        std::fstream heapSort;
        heapSort.open("/Users/Hazim/CLionProjects/DataStructuresAssignment5/output/heapSort.txt");


        //Reads from the filestream
        if (!(selectionSort.is_open() && mergeSort.is_open() && quickSortRandom.is_open()
            && quickSortFirst.is_open() && heapSort.is_open())) {
            std::cout << "Failed to open the output files" << std::endl;
            exit(1);
        }

        for(int i = 1000; i <= 9000; i+= 1000){
            std::vector<int> arr = genRandomInts(i);

            selectionSort << Sorting::selectionSort(arr, 0, arr.size()) << " ";
            arr = genRandomInts(i);

            mergeSort << Sorting::mergeSort(arr, 0, arr.size()) << " ";
            arr = genRandomInts(i);

            quickSortRandom << Sorting::quickSort(arr, 0, arr.size()-1, true) << " ";
            arr = genRandomInts(i);

            quickSortFirst << Sorting::quickSort(arr, 0, arr.size()-1, false) << " ";
            arr = genRandomInts(i);

            heapSort << Sorting::heapSort(arr, 0, arr.size()) << " ";
        }

        selectionSort << std::endl;
        mergeSort << std::endl;
        quickSortFirst << std::endl;
        quickSortRandom << std::endl;
        heapSort << std::endl;

        for(int i = 1000; i <= 9000; i+= 1000){
            std::vector<int> arr = genSortedInts(i);

            selectionSort << Sorting::selectionSort(arr, 0, arr.size()) << " ";
            arr = genRandomInts(i);

            mergeSort << Sorting::mergeSort(arr, 0, arr.size()) << " ";
            arr = genRandomInts(i);

            quickSortRandom << Sorting::quickSort(arr, 0, arr.size()-1, true) << " ";
            arr = genRandomInts(i);

            quickSortFirst << Sorting::quickSort(arr, 0, arr.size()-1, false) << " ";
            arr = genRandomInts(i);

            heapSort << Sorting::heapSort(arr, 0, arr.size()) << " ";
        }

        selectionSort << std::endl;
        mergeSort << std::endl;
        quickSortFirst << std::endl;
        quickSortRandom << std::endl;
        heapSort << std::endl;

        for(int i = 1000; i <= 9000; i+= 1000){
            std::vector<int> arr = genReverseInts(i);

            selectionSort << Sorting::selectionSort(arr, 0, arr.size()) << " ";
            arr = genRandomInts(i);

            mergeSort << Sorting::mergeSort(arr, 0, arr.size()) << " ";
            arr = genRandomInts(i);

            quickSortRandom << Sorting::quickSort(arr, 0, arr.size()-1, true) << " ";
            arr = genRandomInts(i);

            quickSortFirst << Sorting::quickSort(arr, 0, arr.size()-1, false) << " ";
            arr = genRandomInts(i);

            heapSort << Sorting::heapSort(arr, 0, arr.size()) << " ";
        }

        selectionSort << std::endl;
        mergeSort << std::endl;
        quickSortFirst << std::endl;
        quickSortRandom << std::endl;
        heapSort << std::endl;

        return 0;
    }

    std::string filePath = argv[1];

    std::vector<int> toSort(0);
    init(toSort, filePath);
    showOptions();

    //Main program loop
    char input = promptUser();
    executeCommand(input, toSort);
}