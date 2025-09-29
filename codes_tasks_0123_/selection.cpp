#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

int rand_uns(int min, int max) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        // Ќаходим индекс минимального элемента в неотсортированной части
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // ћен€ем местами найденный минимальный элемент с первым неотсортированным
        if (minIndex != i) {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}
int main() {
    std::ofstream f("selecion_sort.csv", std::ios::out);

    for (long n = 500; n < 1000000000; n *= 2) {
        int a[n];
        for(auto i = 0; i < n; i++) {
            a[i] = rand_uns(1, 10000000);
        }
        auto start = std::chrono::high_resolution_clock::now();
        selectionSort(a, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto nsec = end - start;

        f << n << ' ' << float(nsec.count()) / 1000000000 << std::endl;
    }

    return 0;
}











