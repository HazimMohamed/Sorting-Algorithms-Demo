#include <iostream>
#include "include/Sorting.h"
#include <fstream>
#include <vector>

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
    std::vector<std::string> validCommands = {"s", "m", "h", "r", "p"};
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
                comparisons = Sorting::quickSort(toSort, 0, toSort.size(), 0, false);
                break;
            case 'p': {
                long randomPivot = random() % (toSort.size() - 1);
                comparisons = Sorting::quickSort(toSort, 0, toSort.size(), randomPivot, true);
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

int main(int argc, char** argv) {
    if(argc != 2){
        cout << "Incorrect usage. Correct way to run the program: ./main <path to input file>" << endl;
        return 1;
    }

    std::string filePath = argv[1];

    std::vector<int> toSort;
    init(toSort, filePath);
    showOptions();

    //Main program loop
    char input = promptUser();
    executeCommand(input, toSort);
}