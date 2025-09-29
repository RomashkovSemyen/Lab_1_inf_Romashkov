import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
def plot_with_log_scales():
    csv_files = [
        'insertion_sort_O0.csv',
        'insertion_sort_O1.csv',
        'insertion_sort_O2.csv',
        'insertion_sort_O3.csv'
    ]

    legend_names = [
        'Базовая версия(O0)',
        'Оптимизация O1',
        'Оптимизация O2',
        'Оптимизация O3'
    ]

    colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))

    for i, csv_file in enumerate(csv_files):
        try:
            data = pd.read_csv(csv_file, delim_whitespace=True, header=None,
                               names=['n', 'time'])
            data = data.sort_values('n')

            # Линейные оси
            ax1.plot(data['n'], data['time'],
                     color=colors[i], marker='o', markersize=4,
                     linewidth=2, label=legend_names[i])

            # Логарифмические оси
            ax2.loglog(data['n'], data['time'],
                       color=colors[i], marker='o', markersize=4,
                       linewidth=2, label=legend_names[i])

        except Exception as e:
            print(f"Ошибка при чтении {csv_file}: {e}")

    # Настройка первого графика (линейные оси)
    ax1.set_xlabel('Размер массива (N)', fontsize=12)
    ax1.set_ylabel('Время выполнения (секунды)', fontsize=12)
    ax1.set_title('Insertion Sort: Линейные оси', fontsize=14)
    ax1.legend()
    ax1.grid(True, alpha=0.3)

    # Настройка второго графика (логарифмические оси)
    ax2.set_xlabel('Размер массива (N)', fontsize=12)
    ax2.set_ylabel('Время выполнения (секунды)', fontsize=12)
    ax2.set_title('Insertion Sort: Логарифмические оси', fontsize=14)
    ax2.legend()
    ax2.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('insertion_sort_O123.png', dpi=300, bbox_inches='tight')
    plt.show()



# Запуск основной функции
if __name__ == "__main__":
    plot_with_log_scales()
