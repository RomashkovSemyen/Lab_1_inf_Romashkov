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

void quickSort(int* arr, int low, int high) {
    if (low < high) {
        // Разделение массива и получение индекса опорного элемента
        int pivot = arr[(low + high) / 2]; // выбор среднего элемента как опорного
        int i = low;
        int j = high;

        while (i <= j) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;

            if (i <= j) {
                std::swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }

        // Рекурсивная сортировка частей
        if (low < j) quickSort(arr, low, j);
        if (i < high) quickSort(arr, i, high);
    }
}
int main() {
    std::ofstream f("xoar.csv", std::ios::out);

    for (long n = 500; n < 1000000000; n *= 2) {
        int a[n];
        for(auto i = 0; i < n; i++) {
            a[i] = rand_uns(1, 10000000);
        }
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(a, 0, n/2);
        auto end = std::chrono::high_resolution_clock::now();
        auto nsec = end - start;

        f << n << ' ' << float(nsec.count()) / 1000000000 << std::endl;
    }

    return 0;
}


