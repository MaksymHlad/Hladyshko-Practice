#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <future>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;

// Генерація
vector<int> generateArray(int n, int minV, int maxV) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(minV, maxV);

    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = dist(gen);
    return a;
}

// Вивід (5 + 5)
void printArray(const vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < std::min(5, n); i++) cout << a[i] << " ";
    if (n > 10) cout << "... ";
    for (int i = std::max(5, n - 5); i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

// Bubble
void bubbleSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
                std::swap(a[j], a[j + 1]);
}

// Counting
void countingSort(vector<int>& a) {
    int minV = *std::min_element(a.begin(), a.end());
    int maxV = *std::max_element(a.begin(), a.end());

    int range = maxV - minV + 1;
    vector<int> count(range, 0);

    for (int x : a) count[x - minV]++;

    int idx = 0;
    for (int i = 0; i < range; i++)
        while (count[i]--)
            a[idx++] = i + minV;
}

// Shell
void shellSort(vector<int>& a) {
    int n = a.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
                a[j] = a[j - gap];
            a[j] = temp;
        }
    }
}

// Binary Search
int binarySearch(const vector<int>& a, int key) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == key) return m;
        if (a[m] < key) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

// Замір одного сорту
long long measureSortUs(void (*sortFunc)(vector<int>&), const vector<int>& base) {
    vector<int> tmp = base;
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(tmp);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// Sync
long long measureSync(const vector<int>& base) {
    auto a1 = base;
    auto a2 = base;

    auto start = std::chrono::high_resolution_clock::now();

    bubbleSort(a1);
    shellSort(a2);

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// Async
long long measureAsync(const vector<int>& base) {
    auto start = std::chrono::high_resolution_clock::now();

    auto f1 = std::async(std::launch::async, [&base]() {
        auto a1 = base;
        bubbleSort(a1);
        });

    auto f2 = std::async(std::launch::async, [&base]() {
        auto a2 = base;
        shellSort(a2);
        });

    f1.get();
    f2.get();

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    vector<int> ns = { 8, 80, 1200, 4000, 25000, 100000 };

    std::ofstream fout("results.csv");
    fout << "n,Bubble,Counting,Shell,Sync,Async\n";

    cout << "n\tBubble\tCounting\tShell\tSync\tAsync\n";

    for (int size : ns) {
        auto base = generateArray(size, 0, 1000);

        long long t1 = measureSortUs(bubbleSort, base);
        long long t2 = measureSortUs(countingSort, base);
        long long t3 = measureSortUs(shellSort, base);

        long long syncTime = measureSync(base);
        long long asyncTime = measureAsync(base);

        cout << size << "\t" << t1 << "\t" << t2 << "\t"
            << t3 << "\t" << syncTime << "\t" << asyncTime << "\n";

        fout << size << "," << t1 << "," << t2 << "," << t3
            << "," << syncTime << "," << asyncTime << "\n";
    }

    fout.close();

    cout << "\nSaved to results.csv\n\n";

    return 0;
}