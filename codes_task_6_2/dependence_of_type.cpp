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

// Структуры
struct SmallStruct {
    int a;
    int b;
};

struct MediumStruct {
    int a, b, c;
    double x, y;
};

struct LargeStruct {
    int a, b, c, d, e;
    double x, y, z;
    int arr[8];
};

// Операторы сравнения для структур
bool operator<(const SmallStruct& left, const SmallStruct& right) { return left.a < right.a; }
bool operator>(const SmallStruct& left, const SmallStruct& right) { return left.a > right.a; }

bool operator<(const MediumStruct& left, const MediumStruct& right) { return left.a < right.a; }
bool operator>(const MediumStruct& left, const MediumStruct& right) { return left.a > right.a; }

bool operator<(const LargeStruct& left, const LargeStruct& right) { return left.a < right.a; }
bool operator>(const LargeStruct& left, const LargeStruct& right) { return left.a > right.a; }

// Функции сортировки для int
void bubble_int(int* arr, int n) {
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < n - 1; j++)
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
}

void selectionSort_int(int* arr, int n) {
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

void insertionSort_int(int* arr, int n) {
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

void combSort_int(int* arr, int n) {
    int gap = n;
    bool swapped = true;
    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void heapify_int(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify_int(arr, n, largest);
    }
}

void heapSort_int(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_int(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify_int(arr, i, 0);
    }
}

void quickSort_int(int* arr, int low, int high) {
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
        if (low < j) quickSort_int(arr, low, j);
        if (i < high) quickSort_int(arr, i, high);
    }
}

// Функции сортировки для char
void bubble_char(char* arr, int n) {
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < n - 1; j++)
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
}

void selectionSort_char(char* arr, int n) {
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

void insertionSort_char(char* arr, int n) {
    for (int i = 1; i < n; i++) {
        char key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void combSort_char(char* arr, int n) {
    int gap = n;
    bool swapped = true;
    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void heapify_char(char* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify_char(arr, n, largest);
    }
}

void heapSort_char(char* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_char(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify_char(arr, i, 0);
    }
}

void quickSort_char(char* arr, int low, int high) {
    if (low < high) {
        char pivot = arr[(low + high) / 2];
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
        if (low < j) quickSort_char(arr, low, j);
        if (i < high) quickSort_char(arr, i, high);
    }
}

// Функции сортировки для SmallStruct
void bubble_small(SmallStruct* arr, int n) {
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < n - 1; j++)
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
}

void selectionSort_small(SmallStruct* arr, int n) {
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

void insertionSort_small(SmallStruct* arr, int n) {
    for (int i = 1; i < n; i++) {
        SmallStruct key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void combSort_small(SmallStruct* arr, int n) {
    int gap = n;
    bool swapped = true;
    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void heapify_small(SmallStruct* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify_small(arr, n, largest);
    }
}

void heapSort_small(SmallStruct* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_small(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify_small(arr, i, 0);
    }
}

void quickSort_small(SmallStruct* arr, int low, int high) {
    if (low < high) {
        SmallStruct pivot = arr[(low + high) / 2];
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
        if (low < j) quickSort_small(arr, low, j);
        if (i < high) quickSort_small(arr, i, high);
    }
}

// Функции сортировки для MediumStruct
void bubble_medium(MediumStruct* arr, int n) {
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < n - 1; j++)
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
}

void selectionSort_medium(MediumStruct* arr, int n) {
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

void insertionSort_medium(MediumStruct* arr, int n) {
    for (int i = 1; i < n; i++) {
        MediumStruct key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void combSort_medium(MediumStruct* arr, int n) {
    int gap = n;
    bool swapped = true;
    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void heapify_medium(MediumStruct* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify_medium(arr, n, largest);
    }
}

void heapSort_medium(MediumStruct* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_medium(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify_medium(arr, i, 0);
    }
}

void quickSort_medium(MediumStruct* arr, int low, int high) {
    if (low < high) {
        MediumStruct pivot = arr[(low + high) / 2];
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
        if (low < j) quickSort_medium(arr, low, j);
        if (i < high) quickSort_medium(arr, i, high);
    }
}

// Функции сортировки для LargeStruct
void bubble_large(LargeStruct* arr, int n) {
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < n - 1; j++)
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
}

void selectionSort_large(LargeStruct* arr, int n) {
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

void insertionSort_large(LargeStruct* arr, int n) {
    for (int i = 1; i < n; i++) {
        LargeStruct key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void combSort_large(LargeStruct* arr, int n) {
    int gap = n;
    bool swapped = true;
    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void heapify_large(LargeStruct* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify_large(arr, n, largest);
    }
}

void heapSort_large(LargeStruct* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_large(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify_large(arr, i, 0);
    }
}

void quickSort_large(LargeStruct* arr, int low, int high) {
    if (low < high) {
        LargeStruct pivot = arr[(low + high) / 2];
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
        if (low < j) quickSort_large(arr, low, j);
        if (i < high) quickSort_large(arr, i, high);
    }
}

int main() {
    // Создаем файлы для всех типов данных
    std::string types[] = {"int", "char", "small", "medium", "large"};

    // Создаем все файлы
    std::ofstream files[6][5]; // 6 сортировок × 5 типов данных

    for (int s = 0; s < 6; s++) {
        std::string sort_names[] = {"bubble", "selection", "insertion", "comb", "heap", "quick"};
        for (int t = 0; t < 5; t++) {
            std::string filename = sort_names[s] + "_" + types[t] + ".csv";
            files[s][t].open(filename);
        }
    }

    // Основной цикл тестирования
    for (long n = 100; n <= 1000000; n *= 2) {
        std::cout << "Testing n = " << n << std::endl;

        // TEST INT
        int* a_int = new int[n];
        for(auto i = 0; i < n; i++) {
            a_int[i] = rand_uns(1, 10000000);
        }

        // Bubble int
        auto start = std::chrono::high_resolution_clock::now();
        bubble_int(a_int, n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;
        files[0][0] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

        // Selection int
        for(auto i = 0; i < n; i++) a_int[i] = rand_uns(1, 10000000);
        start = std::chrono::high_resolution_clock::now();
        selectionSort_int(a_int, n);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        files[1][0] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

        // Insertion int
        for(auto i = 0; i < n; i++) a_int[i] = rand_uns(1, 10000000);
        start = std::chrono::high_resolution_clock::now();
        insertionSort_int(a_int, n);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        files[2][0] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

        // Comb int
        for(auto i = 0; i < n; i++) a_int[i] = rand_uns(1, 10000000);
        start = std::chrono::high_resolution_clock::now();
        combSort_int(a_int, n);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        files[3][0] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

        // Heap int
        for(auto i = 0; i < n; i++) a_int[i] = rand_uns(1, 10000000);
        start = std::chrono::high_resolution_clock::now();
        heapSort_int(a_int, n);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        files[4][0] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

        // Quick int
        for(auto i = 0; i < n; i++) a_int[i] = rand_uns(1, 10000000);
        start = std::chrono::high_resolution_clock::now();
        quickSort_int(a_int, 0, n-1);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        files[5][0] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

        delete[] a_int;

        // TEST CHAR (только до 5000)
        // TEST CHAR для всех сортировок
if (n <= 1000000) {
    char* a_char = new char[n];
    for(auto i = 0; i < n; i++) {
        a_char[i] = rand_uns('A', 'Z');
    }

    // Bubble char
    start = std::chrono::high_resolution_clock::now();
    bubble_char(a_char, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[0][1] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Selection char
    for(auto i = 0; i < n; i++) a_char[i] = rand_uns('A', 'Z');
    start = std::chrono::high_resolution_clock::now();
    selectionSort_char(a_char, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[1][1] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Insertion char
    for(auto i = 0; i < n; i++) a_char[i] = rand_uns('A', 'Z');
    start = std::chrono::high_resolution_clock::now();
    insertionSort_char(a_char, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[2][1] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Comb char
    for(auto i = 0; i < n; i++) a_char[i] = rand_uns('A', 'Z');
    start = std::chrono::high_resolution_clock::now();
    combSort_char(a_char, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[3][1] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Heap char
    for(auto i = 0; i < n; i++) a_char[i] = rand_uns('A', 'Z');
    start = std::chrono::high_resolution_clock::now();
    heapSort_char(a_char, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[4][1] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Quick char
    for(auto i = 0; i < n; i++) a_char[i] = rand_uns('A', 'Z');
    start = std::chrono::high_resolution_clock::now();
    quickSort_char(a_char, 0, n-1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[5][1] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    delete[] a_char;
}

// TEST SMALL STRUCT для всех сортировок
if (n <= 1000000) {
    SmallStruct* a_small = new SmallStruct[n];
    for(auto i = 0; i < n; i++) {
        a_small[i].a = rand_uns(1, 1000000);
        a_small[i].b = rand_uns(1, 1000000);
    }

    // Bubble small
    start = std::chrono::high_resolution_clock::now();
    bubble_small(a_small, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[0][2] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Selection small
    for(auto i = 0; i < n; i++) {
        a_small[i].a = rand_uns(1, 1000000);
        a_small[i].b = rand_uns(1, 1000000);
    }
    start = std::chrono::high_resolution_clock::now();
    selectionSort_small(a_small, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[1][2] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Insertion small
    for(auto i = 0; i < n; i++) {
        a_small[i].a = rand_uns(1, 1000000);
        a_small[i].b = rand_uns(1, 1000000);
    }
    start = std::chrono::high_resolution_clock::now();
    insertionSort_small(a_small, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[2][2] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Comb small
    for(auto i = 0; i < n; i++) {
        a_small[i].a = rand_uns(1, 1000000);
        a_small[i].b = rand_uns(1, 1000000);
    }
    start = std::chrono::high_resolution_clock::now();
    combSort_small(a_small, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[3][2] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Heap small
    for(auto i = 0; i < n; i++) {
        a_small[i].a = rand_uns(1, 1000000);
        a_small[i].b = rand_uns(1, 1000000);
    }
    start = std::chrono::high_resolution_clock::now();
    heapSort_small(a_small, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[4][2] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Quick small
    for(auto i = 0; i < n; i++) {
        a_small[i].a = rand_uns(1, 1000000);
        a_small[i].b = rand_uns(1, 1000000);
    }
    start = std::chrono::high_resolution_clock::now();
    quickSort_small(a_small, 0, n-1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[5][2] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    delete[] a_small;
}

// TEST MEDIUM STRUCT для всех сортировок
if (n <= 1000000) {
    MediumStruct* a_medium = new MediumStruct[n];
    for(auto i = 0; i < n; i++) {
        a_medium[i].a = rand_uns(1, 1000000);
        a_medium[i].b = rand_uns(1, 1000000);
        a_medium[i].c = rand_uns(1, 1000000);
        a_medium[i].x = (double)rand_uns(1, 1000);
        a_medium[i].y = (double)rand_uns(1, 1000);
    }

    // Bubble medium
    start = std::chrono::high_resolution_clock::now();
    bubble_medium(a_medium, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[0][3] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Selection medium
    for(auto i = 0; i < n; i++) {
        a_medium[i].a = rand_uns(1, 1000000);
        a_medium[i].b = rand_uns(1, 1000000);
        a_medium[i].c = rand_uns(1, 1000000);
        a_medium[i].x = (double)rand_uns(1, 1000);
        a_medium[i].y = (double)rand_uns(1, 1000);
    }
    start = std::chrono::high_resolution_clock::now();
    selectionSort_medium(a_medium, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[1][3] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Insertion medium
    for(auto i = 0; i < n; i++) {
        a_medium[i].a = rand_uns(1, 1000000);
        a_medium[i].b = rand_uns(1, 1000000);
        a_medium[i].c = rand_uns(1, 1000000);
        a_medium[i].x = (double)rand_uns(1, 1000);
        a_medium[i].y = (double)rand_uns(1, 1000);
    }
    start = std::chrono::high_resolution_clock::now();
    insertionSort_medium(a_medium, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[2][3] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Comb medium
    for(auto i = 0; i < n; i++) {
        a_medium[i].a = rand_uns(1, 1000000);
        a_medium[i].b = rand_uns(1, 1000000);
        a_medium[i].c = rand_uns(1, 1000000);
        a_medium[i].x = (double)rand_uns(1, 1000);
        a_medium[i].y = (double)rand_uns(1, 1000);
    }
    start = std::chrono::high_resolution_clock::now();
    combSort_medium(a_medium, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[3][3] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Heap medium
    for(auto i = 0; i < n; i++) {
        a_medium[i].a = rand_uns(1, 1000000);
        a_medium[i].b = rand_uns(1, 1000000);
        a_medium[i].c = rand_uns(1, 1000000);
        a_medium[i].x = (double)rand_uns(1, 1000);
        a_medium[i].y = (double)rand_uns(1, 1000);
    }
    start = std::chrono::high_resolution_clock::now();
    heapSort_medium(a_medium, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[4][3] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Quick medium
    for(auto i = 0; i < n; i++) {
        a_medium[i].a = rand_uns(1, 1000000);
        a_medium[i].b = rand_uns(1, 1000000);
        a_medium[i].c = rand_uns(1, 1000000);
        a_medium[i].x = (double)rand_uns(1, 1000);
        a_medium[i].y = (double)rand_uns(1, 1000);
    }
    start = std::chrono::high_resolution_clock::now();
    quickSort_medium(a_medium, 0, n-1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[5][3] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    delete[] a_medium;
}

// TEST LARGE STRUCT для всех сортировок
if (n <= 1000000) {
    LargeStruct* a_large = new LargeStruct[n];
    for(auto i = 0; i < n; i++) {
        a_large[i].a = rand_uns(1, 1000000);
        a_large[i].b = rand_uns(1, 1000000);
        a_large[i].c = rand_uns(1, 1000000);
        a_large[i].d = rand_uns(1, 1000000);
        a_large[i].e = rand_uns(1, 1000000);
        a_large[i].x = (double)rand_uns(1, 1000);
        a_large[i].y = (double)rand_uns(1, 1000);
        a_large[i].z = (double)rand_uns(1, 1000);
        for(int k = 0; k < 8; k++) {
            a_large[i].arr[k] = rand_uns(1, 1000);
        }
    }

    // Bubble large
    start = std::chrono::high_resolution_clock::now();
    bubble_large(a_large, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[0][4] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Selection large
    for(auto i = 0; i < n; i++) {
        a_large[i].a = rand_uns(1, 1000000);
        a_large[i].b = rand_uns(1, 1000000);
        a_large[i].c = rand_uns(1, 1000000);
        a_large[i].d = rand_uns(1, 1000000);
        a_large[i].e = rand_uns(1, 1000000);
        a_large[i].x = (double)rand_uns(1, 1000);
        a_large[i].y = (double)rand_uns(1, 1000);
        a_large[i].z = (double)rand_uns(1, 1000);
        for(int k = 0; k < 8; k++) {
            a_large[i].arr[k] = rand_uns(1, 1000);
        }
    }
    start = std::chrono::high_resolution_clock::now();
    selectionSort_large(a_large, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[1][4] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Insertion large
    for(auto i = 0; i < n; i++) {
        a_large[i].a = rand_uns(1, 1000000);
        a_large[i].b = rand_uns(1, 1000000);
        a_large[i].c = rand_uns(1, 1000000);
        a_large[i].d = rand_uns(1, 1000000);
        a_large[i].e = rand_uns(1, 1000000);
        a_large[i].x = (double)rand_uns(1, 1000);
        a_large[i].y = (double)rand_uns(1, 1000);
        a_large[i].z = (double)rand_uns(1, 1000);
        for(int k = 0; k < 8; k++) {
            a_large[i].arr[k] = rand_uns(1, 1000);
        }
    }
    start = std::chrono::high_resolution_clock::now();
    insertionSort_large(a_large, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[2][4] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Comb large
    for(auto i = 0; i < n; i++) {
        a_large[i].a = rand_uns(1, 1000000);
        a_large[i].b = rand_uns(1, 1000000);
        a_large[i].c = rand_uns(1, 1000000);
        a_large[i].d = rand_uns(1, 1000000);
        a_large[i].e = rand_uns(1, 1000000);
        a_large[i].x = (double)rand_uns(1, 1000);
        a_large[i].y = (double)rand_uns(1, 1000);
        a_large[i].z = (double)rand_uns(1, 1000);
        for(int k = 0; k < 8; k++) {
            a_large[i].arr[k] = rand_uns(1, 1000);
        }
    }
    start = std::chrono::high_resolution_clock::now();
    combSort_large(a_large, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[3][4] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Heap large
    for(auto i = 0; i < n; i++) {
        a_large[i].a = rand_uns(1, 1000000);
        a_large[i].b = rand_uns(1, 1000000);
        a_large[i].c = rand_uns(1, 1000000);
        a_large[i].d = rand_uns(1, 1000000);
        a_large[i].e = rand_uns(1, 1000000);
        a_large[i].x = (double)rand_uns(1, 1000);
        a_large[i].y = (double)rand_uns(1, 1000);
        a_large[i].z = (double)rand_uns(1, 1000);
        for(int k = 0; k < 8; k++) {
            a_large[i].arr[k] = rand_uns(1, 1000);
        }
    }
    start = std::chrono::high_resolution_clock::now();
    heapSort_large(a_large, n);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[4][4] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    // Quick large
    for(auto i = 0; i < n; i++) {
        a_large[i].a = rand_uns(1, 1000000);
        a_large[i].b = rand_uns(1, 1000000);
        a_large[i].c = rand_uns(1, 1000000);
        a_large[i].d = rand_uns(1, 1000000);
        a_large[i].e = rand_uns(1, 1000000);
        a_large[i].x = (double)rand_uns(1, 1000);
        a_large[i].y = (double)rand_uns(1, 1000);
        a_large[i].z = (double)rand_uns(1, 1000);
        for(int k = 0; k < 8; k++) {
            a_large[i].arr[k] = rand_uns(1, 1000);
        }
    }
    start = std::chrono::high_resolution_clock::now();
    quickSort_large(a_large, 0, n-1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    files[5][4] << n << ' ' << std::chrono::duration<double>(duration).count() << std::endl;

    delete[] a_large;
}
    }

    std::cout << "Тестирование завершено!" << std::endl;
    return 0;
}
