#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Item {
public:
    string name;
    int quantity;
    int maxCapacity;
    bool isOut;

    void InitializeEmptyClass() {
        name = "";
        quantity = 0;
        maxCapacity = 0;
        isOut = false;
    }

    void InitializeClass(string cName, int cQuan, int cMax, bool cOut) {
        name = cName;
        quantity = cQuan;
        maxCapacity = cMax;
        isOut = cOut;
    }
};

void SaveToFile(Item* item) {
    ofstream File("data.txt", ios::app | ios::binary); // Append mode and binary mode

    if (File.is_open()) {
        File << "Nazwa: " << item->name << endl;
        File << "Ilosc: " << item->quantity << endl;
        File << "Max Ilosc: " << item->maxCapacity << endl;
        File << "Czy Jest W Magazynie: " << item->isOut << endl;
        File << "----" << endl; // Separator between items
        File.close();
    } else {
        cerr << "Failed to open file for writing." << endl;
    }
}

int returnLength() {
    ifstream file("data.txt", ios::binary | ios::ate); // Open in binary mode, seek to the end
    streamsize size = 0;

    if (file.is_open()) {
        size = file.tellg(); // Get file size
        file.close();
    } else {
        cerr << "Failed to open the file!" << endl;
    }

    return static_cast<int>(size);
}

void ReadFromFile() {
    ifstream File("data.txt");

    if (File.is_open()) {
        string line;
        while (getline(File, line)) {
            cout << line << endl; // Output each line
        }
        File.close();
    } else {
        cerr << "Failed to open file for reading." << endl;
    }
}

void AddData() {
    Item item; // Allocate item on stack

    cout << "Witam w systemie inwentaryzacji w sekcji dodawanie \n";
    cout << "------------------------------------------------------- \n";
    cout << "Podaj nazwe produktu ktory chcesz dodac: ";
    cin >> item.name;
    cout << "Podaj ilosc danego produktu: ";
    cin >> item.quantity;
    cout << "Podaj makymalna ilosc do przechowania: ";
    cin >> item.maxCapacity;

    item.isOut = false; // Initialize isOut

    SaveToFile(&item);
}

int main() {
    AddData();
    cout << "\nZawartosc pliku: \n";
    ReadFromFile();
    return 0;
}
