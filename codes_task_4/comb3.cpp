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

void combSort(int* arr, int n) {
    // Инициализация gap
    int gap = n;

    // Флаг для отслеживания, были ли обмены
    bool swapped = true;

    // Продолжаем, пока gap > 1 или был выполнен обмен
    while (gap != 1 || swapped) {
        // Находим следующий gap
        gap = (gap * 10) / 13; // фактор уменьшения 1.3
        if (gap < 1)
            gap = 1;

        swapped = false;

        // Сравниваем элементы с текущим gap
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

int main() {
    std::ofstream f1("comb_best.csv", std::ios::out);
    std::ofstream f2("comb_rand.csv", std::ios::out);
    std::ofstream f3("comb_worst.csv", std::ios::out);

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
        combSort(best, n);
        auto end1 = std::chrono::high_resolution_clock::now();
        auto nsec1 = end1 - start1;
        f1 << n << ' ' << float(nsec1.count()) / 1000000000 << std::endl;

        auto start2 = std::chrono::high_resolution_clock::now();
        combSort(rand, n);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto nsec2 = end2 - start2;
        f2 << n << ' ' << float(nsec2.count()) / 1000000000 << std::endl;

        auto start3 = std::chrono::high_resolution_clock::now();
        combSort(worst, n);
        auto end3 = std::chrono::high_resolution_clock::now();
        auto nsec3 = end3 - start3;
        f3 << n << ' ' << float(nsec3.count()) / 1000000000 << std::endl;
    }
}












