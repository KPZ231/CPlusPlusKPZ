#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <windows.h>
#include <chrono>

using namespace std;

void swap(vector<int>& arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void showProgressBar(int iteration, int total) {
    const int barWidth = 50;
    float progress = (float)iteration / total;
    int barProgress = barWidth * progress;

    cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < barProgress) {
            cout << "=";
        }
        else if (i == barProgress) {
            cout << ">";
        }
        else {
            cout << " ";
        }
    }
    cout << "] " << int(progress * 100.0) << "%\r";
    cout.flush();
}

void Sortowanie(string nameFile) {
    ifstream file;
    vector<int> tab;
    int lineCount = 0;

    file.open(nameFile);

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            lineCount++;
            tab.insert(tab.begin(), stoi(line));
        }

        file.close();
    }

    auto start = chrono::steady_clock::now(); // Pomiar czasu rozpoczêcia sortowania

    for (int i = 0; i < lineCount - 1; i++) {
        for (int j = 0; j < lineCount - i - 1; j++) {
            if (tab.at(j) > tab.at(j + 1)) {
                swap(tab, j, j + 1);
            }
        }
        showProgressBar(i + 1, lineCount - 1);
    }

    auto end = chrono::steady_clock::now(); // Pomiar czasu zakoñczenia sortowania

    cout << endl;

    for (int i = 0; i < lineCount; i++) {
        cout << tab.at(i) << " ";
    }
    cout << "\n";

    // Obliczenie i wyœwietlenie czasu trwania sortowania
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Czas sortowania: " << duration << " ms" << endl;
}

void WriteRandomData(string nameFile, int fileLines) {
    ofstream file(nameFile);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, 99999);

    for (int i = 0; i < fileLines; ++i) {
        int randInt = distribution(gen);
        file << randInt << endl;
    }

    file.close();
}

int main() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    unsigned short operation = 0;
    int fileLines = 0;
    string fileToUse = "data.txt";

    SetConsoleTextAttribute(hConsole, 2);
    cout << "Operations: \n";
    cout << "    1: Sort\n";
    cout << "    2: Write Random Data\n";
    SetConsoleTextAttribute(hConsole, 3);
    cout << "Select Operation: ";
    cin >> operation;

    switch (operation) {
    case 1:
        SetConsoleTextAttribute(hConsole, 2);
        cout << "Selected Operation Is: Sort \n";
        SetConsoleTextAttribute(hConsole, 3);
        cout << "Select File To Sort: ";
        cin >> fileToUse;
        SetConsoleTextAttribute(hConsole, 15);
        Sortowanie(fileToUse);
        break;
    case 2:
        SetConsoleTextAttribute(hConsole, 2);
        cout << "Selected Operation Is: Write Random Data \n";
        SetConsoleTextAttribute(hConsole, 3);
        cout << "Select File To Write In: ";
        cin >> fileToUse;
        SetConsoleTextAttribute(hConsole, 3);
        cout << "Select The Length Of File: ";
        cin >> fileLines;
        SetConsoleTextAttribute(hConsole, 15);
        WriteRandomData(fileToUse, fileLines);
        break;
    default:
        SetConsoleTextAttribute(hConsole, 4);
        cerr << "Invalid Option";
    }

    return 0;
}
