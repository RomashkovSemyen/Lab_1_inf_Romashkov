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

void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
int main() {
    std::ofstream f1("insert_best.csv", std::ios::out);
    std::ofstream f2("insert_rand.csv", std::ios::out);
    std::ofstream f3("insert_worst.csv", std::ios::out);

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
        insertionSort(best, n);
        auto end1 = std::chrono::high_resolution_clock::now();
        auto nsec1 = end1 - start1;
        f1 << n << ' ' << float(nsec1.count()) / 1000000000 << std::endl;

        auto start2 = std::chrono::high_resolution_clock::now();
        insertionSort(rand, n);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto nsec2 = end2 - start2;
        f2 << n << ' ' << float(nsec2.count()) / 1000000000 << std::endl;

        auto start3 = std::chrono::high_resolution_clock::now();
        insertionSort(worst, n);
        auto end3 = std::chrono::high_resolution_clock::now();
        auto nsec3 = end3 - start3;
        f3 << n << ' ' << float(nsec3.count()) / 1000000000 << std::endl;
    }

    return 0;
}
