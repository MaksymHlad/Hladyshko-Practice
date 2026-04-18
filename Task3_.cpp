#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// 🔹 створення матриці
int** createMatrix(int n) {
    int** arr = new int* [n];
    for (int i = 0; i < n; i++)
        arr[i] = new int[n];
    return arr;
}

// 🔹 видалення матриці
void deleteMatrix(int** arr, int n) {
    for (int i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;
}

// 🔹 заповнення випадковими числами
void fillMatrix(int** arr, int n, int variant) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = rand() % (20 + 2 * variant + 1) - (10 + variant);
}

// 🔹 вивід матриці
void printMatrix(int** arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(5) << arr[i][j];
        cout << endl;
    }
}

// 🔹 сектор 2 (з діагоналями)
int countSector2(int** arr, int n, int k) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            // ✔ сектор 2 з діагоналями
            if (i >= j && i + j <= n - 1) {
                if (arr[i][j] < k)
                    count++;
            }

        }
    }
    return count;
}

// 🔹 середнє додатних елементів
double averagePositive(int** arr, int n) {
    int sum = 0;
    int count = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (arr[i][j] > 0) {
                sum += arr[i][j];
                count++;
            }

    if (count == 0) return 0;
    return (double)sum / count;
}

// 🔹 сектор 9
int processSector9(int** arr, int n, double avg) {
    int count = 0;

    for (int i = n / 2 + 1; i < n; i++) {
        for (int j = 0; j < n; j++) {

            count++;
            arr[i][j] = (int)avg;

        }
    }
    return count;
}

// 🔹 main
int main() {
    srand(time(0));

    int n, k, variant;

    cout << "Enter n: ";
    cin >> n;

    cout << "Enter variant number: ";
    cin >> variant;

    cout << "Enter k: ";
    cin >> k;

    int** matrix = createMatrix(n);

    fillMatrix(matrix, n, variant);

    cout << "\nMatrix:\n";
    printMatrix(matrix, n);

    // 🔹 сектор 2
    int count2 = countSector2(matrix, n, k);
    cout << "\nSector 2 (elements < k): " << count2 << endl;

    // 🔹 середнє
    double avg = averagePositive(matrix, n);
    cout << "Average of positive elements: " << avg << endl;

    // 🔹 сектор 9
    int count9 = processSector9(matrix, n, avg);
    cout << "Sector 9 elements count: " << count9 << endl;

    cout << "\nMatrix after processing sector 9:\n";
    printMatrix(matrix, n);

    deleteMatrix(matrix, n);

    return 0;
}