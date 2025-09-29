
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
    std::ofstream f("insertion_sort_O3.csv", std::ios::out);

    for (long n = 500; n < 1000000000; n *= 2) {
        int a[n];
        for(auto i = 0; i < n; i++) {
            a[i] = rand_uns(1, 10000000);
        }
        auto start = std::chrono::high_resolution_clock::now();
        insertionSort(a, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto nsec = end - start;

        f << n << ' ' << float(nsec.count()) / 1000000000 << std::endl;
    }

    return 0;
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

