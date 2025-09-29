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
    std::ofstream f1("quick_best.csv", std::ios::out);
    std::ofstream f2("quick_rand.csv", std::ios::out);
    std::ofstream f3("quick_worst.csv", std::ios::out);

    for (long n = 1000; n < 1000000000; n *= 2) {
        int best[n], rand[n], worst[n];
        for (auto i = 0; i < n; i ++){
            best[i] = i;
        }
        for(auto i = 0; i < n; i++) {
            rand[i] = rand_uns(1, 10000000);
        }
        for (auto i = 0; i < n; i++){
            worst[i] = n - i;
        }
        auto start1 = std::chrono::high_resolution_clock::now();
        quickSort(best, 0, n - 1);
        auto end1 = std::chrono::high_resolution_clock::now();
        auto nsec1 = end1 - start1;
        f1 << n << ' ' << float(nsec1.count()) / 1000000000 << std::endl;

        auto start2 = std::chrono::high_resolution_clock::now();
        quickSort(rand, 0, n - 1);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto nsec2 = end2 - start2;
        f2 << n << ' ' << float(nsec2.count()) / 1000000000 << std::endl;

        auto start3 = std::chrono::high_resolution_clock::now();
        quickSort(worst, 0, n - 1);
        auto end3 = std::chrono::high_resolution_clock::now();
        auto nsec3 = end3 - start3;
        f3 << n << ' ' << float(nsec3.count()) / 1000000000 << std::endl;
    }

    return 0;
}



