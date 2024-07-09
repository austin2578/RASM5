#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "bubbleSortC.h"

using namespace std;
using namespace std::chrono;

extern "C" void bubbleSortA(int*, int size);

void loadIntegers(const char* filename, int arr[], int size) {
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size && inFile >> arr[i]; ++i) {
        // Load elements from the file to the array
    }

    inFile.close();
}

void saveIntegers(const char* filename, const int arr[], int size) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i) {
        outFile << arr[i] << " ";
    }

    outFile.close();
}

int main() {
    const char* inputFile = "input.txt";
    const char* cOutputFile = "c_bubblesort.txt";
    const char* aOutputFile = "a_bubblesort.txt";
    const int elementCount = 200000;
    duration<double> durationC(0);
    duration<double> durationA(0);
    int choice;
    int* arr = new int[elementCount];

    do {
        cout << "------------------------------------------------\n";
        cout << "               MASM5 C vs Assembly\n";
        cout << "              File Element Count: " << elementCount << "\n";
        cout << "------------------------------------------------\n";
        cout << fixed << setprecision(2) << "C        Bubblesort Time: " << durationC.count() << " secs\n";
        cout << fixed << setprecision(2) << "Assembly Bubblesort Time: " << durationA.count() << " secs\n";
        cout << "------------------------------------------------\n";
        cout << "<1> Load input file (integers)\n";
        cout << "<2> Sort using C Bubblesort algorithm\n";
        cout << "<3> Sort using Assembly Bubblesort algorithm\n";
        cout << "<4> Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                loadIntegers(inputFile, arr, elementCount);
                cout << "Input file loaded successfully.\n";
                break;
            case 2:
            {
                auto startC = high_resolution_clock::now();
                bubbleSortC(arr, elementCount);
                auto stopC = high_resolution_clock::now();
                durationC += duration_cast<duration<double>>(stopC - startC);
                cout << fixed << setprecision(2) << "Sorted using C Bubblesort algorithm in " << durationC.count() << " secs.\n";
                saveIntegers(cOutputFile, arr, elementCount);
                break;
            }
            case 3:
            {
                auto startAssembly = high_resolution_clock::now();
                bubbleSortA(arr, elementCount);
                auto stopAssembly = high_resolution_clock::now();
                durationA += duration_cast<duration<double>>(stopAssembly - startAssembly);
                cout << fixed << setprecision(2) << "Sorted using Assembly Bubblesort algorithm in " << durationA.count() << " secs.\n";
                saveIntegers(aOutputFile, arr, elementCount);
                break;
            }
            case 4:
                cout << "Quitting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    delete[] arr;
    return 0;
}
