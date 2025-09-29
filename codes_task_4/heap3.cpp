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


void heapify(int* arr, int n, int i) {
    int largest = i;        // �������������� ���������� ������� ��� ������
    int left = 2 * i + 1;   // ����� �������� �������
    int right = 2 * i + 2;  // ������ �������� �������

    // ���� ����� �������� ������� ������ �����
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // ���� ������ �������� ������� ������, ��� ����� ������� ������� �� ������ ������
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // ���� ����� ������� ������� �� ������
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // ���������� ����������� � ���� ���������� ���������
        heapify(arr, n, largest);
    }
}

void heapSort(int* arr, int n) {
    // ���������� ���� (�������������� ������)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // ���� �� ������ ��������� �������� �� ����
    for (int i = n - 1; i > 0; i--) {
        // ���������� ������� ������ � �����
        std::swap(arr[0], arr[i]);

        // �������� heapify �� ����������� ����
        heapify(arr, i, 0);
    }
}

int main() {
    std::ofstream f1("heap_best.csv", std::ios::out);
    std::ofstream f2("heap_rand.csv", std::ios::out);
    std::ofstream f3("heap_worst.csv", std::ios::out);

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
        heapSort(best, n);
        auto end1 = std::chrono::high_resolution_clock::now();
        auto nsec1 = end1 - start1;
        f1 << n << ' ' << float(nsec1.count()) / 1000000000 << std::endl;

        auto start2 = std::chrono::high_resolution_clock::now();
        heapSort(rand, n);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto nsec2 = end2 - start2;
        f2 << n << ' ' << float(nsec2.count()) / 1000000000 << std::endl;

        auto start3 = std::chrono::high_resolution_clock::now();
        heapSort(worst, n);
        auto end3 = std::chrono::high_resolution_clock::now();
        auto nsec3 = end3 - start3;
        f3 << n << ' ' << float(nsec3.count()) / 1000000000 << std::endl;
    }
}




