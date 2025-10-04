import time
import random
import matplotlib.pyplot as plt
import numpy as np


def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]


def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key


def test_sorting_algorithms():
    sizes = [1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000]
    bubble_times = []
    insertion_times = []

    print("Sorting Algorithms Performance:")
    print("Size\t\tBubble Sort\t\tInsertion Sort")
    print("-" * 50)

    for size in sizes:
        arr = [random.randint(1, 10000) for _ in range(size)]

        arr_copy = arr.copy()
        start_time = time.time()
        bubble_sort(arr_copy)
        bubble_time = time.time() - start_time
        bubble_times.append(bubble_time)

        arr_copy = arr.copy()
        start_time = time.time()
        insertion_sort(arr_copy)
        insertion_time = time.time() - start_time
        insertion_times.append(insertion_time)

        print(f"{size}\t\t{bubble_time:.6f}\t\t{insertion_time:.6f}")

    return sizes, bubble_times, insertion_times


def plot_results(sizes, bubble_times, insertion_times):
    plt.figure(figsize=(12, 8))

    # Линейный график
    plt.subplot(2, 1, 1)
    plt.plot(sizes, bubble_times, 'ro-', label='Bubble Sort', linewidth=2, markersize=6)
    plt.plot(sizes, insertion_times, 'bo-', label='Insertion Sort', linewidth=2, markersize=6)
    plt.xlabel('Array Size (N)')
    plt.ylabel('Time (seconds)')
    plt.title('Sorting Algorithms Performance - Linear Scale')
    plt.legend()
    plt.grid(True, alpha=0.3)

    # Логарифмический график для лучшего отображения
    plt.subplot(2, 1, 2)
    plt.loglog(sizes, bubble_times, 'ro-', label='Bubble Sort', linewidth=2, markersize=6)
    plt.loglog(sizes, insertion_times, 'bo-', label='Insertion Sort', linewidth=2, markersize=6)
    plt.xlabel('Array Size (N)')
    plt.ylabel('Time (seconds)')
    plt.title('Sorting Algorithms Performance - Log-Log Scale')
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('sorting_performance.png', dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    sizes, bubble_times, insertion_times = test_sorting_algorithms()
    plot_results(sizes, bubble_times, insertion_times)
    compare_with_theoretical(sizes, bubble_times, insertion_times)