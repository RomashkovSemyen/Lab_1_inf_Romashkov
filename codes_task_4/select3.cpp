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
    std::ofstream f1("select_best.csv", std::ios::out);
    std::ofstream f2("select_rand.csv", std::ios::out);
    std::ofstream f3("select_worst.csv", std::ios::out);

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
        selectionSort(best, n);
        auto end1 = std::chrono::high_resolution_clock::now();
        auto nsec1 = end1 - start1;
        f1 << n << ' ' << float(nsec1.count()) / 1000000000 << std::endl;

        auto start2 = std::chrono::high_resolution_clock::now();
        selectionSort(rand, n);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto nsec2 = end2 - start2;
        f2 << n << ' ' << float(nsec2.count()) / 1000000000 << std::endl;

        auto start3 = std::chrono::high_resolution_clock::now();
        selectionSort(worst, n);
        auto end3 = std::chrono::high_resolution_clock::now();
        auto nsec3 = end3 - start3;
        f3 << n << ' ' << float(nsec3.count()) / 1000000000 << std::endl;
    }

    return 0;
}












