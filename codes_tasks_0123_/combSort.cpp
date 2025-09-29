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
    std::ofstream f("comb.csv", std::ios::out);

    for (long n = 500; n < 1000000000; n *= 2) {
        int a[n];
        for(auto i = 0; i < n; i++) {
            a[i] = rand_uns(1, 10000000);
        }
        auto start = std::chrono::high_resolution_clock::now();
        combSort(a, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto nsec = end - start;

        f << n << ' ' << float(nsec.count()) / 1000000000 << std::endl;
    }

    return 0;
}











