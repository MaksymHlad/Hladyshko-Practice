#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Phone {
    string name;
    int memory;
    double price;
    int camera;
    string manufacturer;
};

void addPhone() {
    Phone p;

    cin.ignore();

    cout << "\nEnter name: ";
    getline(cin, p.name);

    cout << "Enter memory (GB): ";
    cin >> p.memory;

    cout << "Enter price: ";
    cin >> p.price;

    cout << "Enter camera (MP): ";
    cin >> p.camera;

    cin.ignore();

    cout << "Enter manufacturer: ";
    getline(cin, p.manufacturer);

    ofstream fout("phones.txt", ios::app);

    if (!fout.is_open()) {
        cout << "File error\n";
        return;
    }

    fout << p.name << "|"
        << p.memory << "|"
        << p.price << "|"
        << p.camera << "|"
        << p.manufacturer << endl;

    fout.close();

    cout << "Phone added!\n";
}

void showAll() {
    ifstream fin("phones.txt");

    if (!fin.is_open()) {
        cout << "File not found\n";
        return;
    }

    string line;

    cout << "\n--- ALL PHONES ---\n";

    while (getline(fin, line)) {
        cout << line << endl;
    }

    fin.close();
}

void showSamsungApple() {
    ifstream fin("phones.txt");

    if (!fin.is_open()) {
        cout << "File not found\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\n--- SAMSUNG & APPLE ---\n";

    while (getline(fin, line)) {
        if (line.find("Samsung") != string::npos ||
            line.find("Apple") != string::npos) {
            cout << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No Samsung or Apple phones found\n";
    }

    fin.close();
}

int main() {
    int choice;

    do {
        cout << "\n1 - Add phone\n";
        cout << "2 - Show all phones\n";
        cout << "3 - Show Samsung & Apple phones\n";
        cout << "0 - Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPhone();
            break;
        case 2:
            showAll();
            break;
        case 3:
            showSamsungApple();
            break;
        case 0:
            cout << "Program ended\n";
            break;
        default:
            cout << "Wrong choice\n";
        }

    } while (choice != 0);

    return 0;
}