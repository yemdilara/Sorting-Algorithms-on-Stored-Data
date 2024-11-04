#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

void writeToFile(const string& filename, int numCount) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Dosya açilamadi!" << endl;
        return;
    }
    for (int i = 0; i < numCount; ++i) {
        file << randomInt(1, 1000) << endl;
    }
    file.close();
}

vector<int> readFromFile(const string& filename) {
    vector<int> numbers;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Dosya açilamadi!" << endl;
        return numbers;
    }
    int num;
    while (file >> num) {
        numbers.push_back(num);
    }
    file.close();
    return numbers;
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int main() {
    srand(time(0));

    const string filename = "numbers.txt";
    const int numCount = 1000;

    writeToFile(filename, numCount);

    vector<int> numbers = readFromFile(filename);

    vector<int> selectionSortNumbers = numbers;
    clock_t selectionStart = clock();
    selectionSort(selectionSortNumbers);
    clock_t selectionEnd = clock();
    double selectionTime = double(selectionEnd - selectionStart) / CLOCKS_PER_SEC;

    vector<int> insertionSortNumbers = numbers;
    clock_t insertionStart = clock();
    insertionSort(insertionSortNumbers);
    clock_t insertionEnd = clock();
    double insertionTime = double(insertionEnd - insertionStart) / CLOCKS_PER_SEC;

    vector<int> mergeSortNumbers = numbers;
    clock_t mergeStart = clock();
    mergeSort(mergeSortNumbers, 0, mergeSortNumbers.size() - 1);
    clock_t mergeEnd = clock();
    double mergeTime = double(mergeEnd - mergeStart) / CLOCKS_PER_SEC;

    cout << "Selection Sort Süresi: " << selectionTime << " saniye" << endl;
    cout << "Insertion Sort Süresi: " << insertionTime << " saniye" << endl;
    cout << "Merge Sort Süresi: " << mergeTime << " saniye" << endl;

    return 0;
}