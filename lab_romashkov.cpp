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

void bubble(int* arr, int n) {
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < n - 1; j++)
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
}

int main() {
    // Открываем файл ОДИН раз перед циклом
    std::ofstream f("bubble.csv", std::ios::out);

    for (long n = 1000; n < 1000000000; n *= 2) {
        int a[n];
        for(auto i = 0; i < n; i++) {
            a[i] = rand_uns(1, 10000000);
        }
        auto start = std::chrono::high_resolution_clock::now();
        bubble(a, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto nsec = end - start;

        // Записываем в уже открытый файл
        f << n << ' ' << float(nsec.count()) / 1000000000 << std::endl;
    }

    // Файл закроется автоматически при выходе из области видимости
    return 0;
}
