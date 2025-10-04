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

void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(arr[i], arr[minIndex]);
        }
    }
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

void combSort(int* arr, int n) {
    int gap = n;
    bool swapped = true;

    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1)
            gap = 1;

        swapped = false;

        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pivot = arr[(low + high) / 2];
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

        if (low < j) quickSort(arr, low, j);
        if (i < high) quickSort(arr, i, high);
    }
}

int main() {
    std::ofstream f_bub("bubble.csv", std::ios::out);
    std::ofstream f_sel("selection.csv", std::ios::out);
    std::ofstream f_ins("insertion.csv", std::ios::out);
    std::ofstream f_comb("comb.csv", std::ios::out);
    std::ofstream f_heap("heap.csv", std::ios::out);
    std::ofstream f_quick("quick.csv", std::ios::out);

    const int NUM_REPEATS = 10000; // 10,000 повторений

    for (long n = 1; n < 1000; n += 10) {
        // Выделяем память для исходного массива и рабочего массива
        int* original_arr = new int[n];
        int* work_arr = new int[n];

        // Генерируем случайный массив ОДИН РАЗ перед всеми измерениями
        for(auto i = 0; i < n; i++) {
            original_arr[i] = rand_uns(1, 10000000);
        }

        // Bubble Sort
        double total_time_bubble = 0.0;
        for (int repeat = 0; repeat < NUM_REPEATS; repeat++) {
            // Копируем исходный массив в рабочий
            for (int i = 0; i < n; i++) {
                work_arr[i] = original_arr[i];
            }

            auto start = std::chrono::high_resolution_clock::now();
            bubble(work_arr, n);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = end - start;
            total_time_bubble += std::chrono::duration<double>(duration).count();
        }
        f_bub << n << ' ' << total_time_bubble / NUM_REPEATS << std::endl;

        // Selection Sort
        double total_time_selection = 0.0;
        for (int repeat = 0; repeat < NUM_REPEATS; repeat++) {
            for (int i = 0; i < n; i++) {
                work_arr[i] = original_arr[i];
            }

            auto start = std::chrono::high_resolution_clock::now();
            selectionSort(work_arr, n);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = end - start;
            total_time_selection += std::chrono::duration<double>(duration).count();
        }
        f_sel << n << ' ' << total_time_selection / NUM_REPEATS << std::endl;

        // Insertion Sort
        double total_time_insertion = 0.0;
        for (int repeat = 0; repeat < NUM_REPEATS; repeat++) {
            for (int i = 0; i < n; i++) {
                work_arr[i] = original_arr[i];
            }

            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(work_arr, n);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = end - start;
            total_time_insertion += std::chrono::duration<double>(duration).count();
        }
        f_ins << n << ' ' << total_time_insertion / NUM_REPEATS << std::endl;

        // Comb Sort
        double total_time_comb = 0.0;
        for (int repeat = 0; repeat < NUM_REPEATS; repeat++) {
            for (int i = 0; i < n; i++) {
                work_arr[i] = original_arr[i];
            }

            auto start = std::chrono::high_resolution_clock::now();
            combSort(work_arr, n);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = end - start;
            total_time_comb += std::chrono::duration<double>(duration).count();
        }
        f_comb << n << ' ' << total_time_comb / NUM_REPEATS << std::endl;

        // Heap Sort
        double total_time_heap = 0.0;
        for (int repeat = 0; repeat < NUM_REPEATS; repeat++) {
            for (int i = 0; i < n; i++) {
                work_arr[i] = original_arr[i];
            }

            auto start = std::chrono::high_resolution_clock::now();
            heapSort(work_arr, n);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = end - start;
            total_time_heap += std::chrono::duration<double>(duration).count();
        }
        f_heap << n << ' ' << total_time_heap / NUM_REPEATS << std::endl;

        // Quick Sort
        double total_time_quick = 0.0;
        for (int repeat = 0; repeat < NUM_REPEATS; repeat++) {
            for (int i = 0; i < n; i++) {
                work_arr[i] = original_arr[i];
            }

            auto start = std::chrono::high_resolution_clock::now();
            quickSort(work_arr, 0, n - 1); // Исправлено: от 0 до n-1
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = end - start;
            total_time_quick += std::chrono::duration<double>(duration).count();
        }
        f_quick << n << ' ' << total_time_quick / NUM_REPEATS << std::endl;

    }
    return 0;
}
