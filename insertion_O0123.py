import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def plot_insertion_sort_optimizations():
    """
    Строит график с четырьмя кривыми для insertion sort с разными оптимизациями
    """
    # Список ваших CSV файлов
    csv_files = [
        'insertion_sort_O0.csv',
        'insertion_sort_O1.csv',
        'insertion_sort_O2.csv',
        'insertion_sort_O3.csv'
    ]

    # Названия для легенды (можете изменить под ваши оптимизации)
    legend_names = [
        'Базовая версия',
        'Оптимизация 1\n(бинарный поиск)',
        'Оптимизация 2\n(guard элемент)',
        'Оптимизация 3\n(шелл-вставки)'
    ]

    # Цвета для разных кривых
    colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']
    markers = ['o', 's', '^', 'D']

    # Создаем график
    plt.figure(figsize=(12, 8))

    # Читаем и строим данные из каждого файла
    for i, csv_file in enumerate(csv_files):
        try:
            # Чтение данных из CSV (предполагается формат: размер_массива время)
            data = pd.read_csv(csv_file, delim_whitespace=True, header=None,
                               names=['n', 'time'])

            # Сортировка по размеру массива для правильного построения графика
            data = data.sort_values('n')

            # Построение графика
            plt.plot(data['n'], data['time'],
                     color=colors[i],
                     marker=markers[i],
                     markersize=6,
                     linewidth=2,
                     label=legend_names[i])

            print(f"Файл {csv_file}: {len(data)} точек данных")

        except FileNotFoundError:
            print(f"Ошибка: Файл {csv_file} не найден")
        except Exception as e:
            print(f"Ошибка при чтении {csv_file}: {e}")

    # Настройка внешнего вида графика
    plt.xlabel('Размер массива (N)', fontsize=12)
    plt.ylabel('Время выполнения (секунды)', fontsize=12)
    plt.title('Оптимизации Insertion Sort: Сравнение производительности', fontsize=14, fontweight='bold')
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)

    # Добавляем сетку и улучшаем читаемость
    plt.tight_layout()

    # Сохраняем график
    plt.savefig('insertion_sort_optimizations.png', dpi=300, bbox_inches='tight')
    print("График сохранен как 'insertion_sort_optimizations.png'")

    # Показываем график
    plt.show()


def plot_with_log_scales():
    """
    Версия с логарифмическими осями для лучшего отображения
    """
    csv_files = [
        'insertion_sort_O0.csv',
        'insertion_sort_O1.csv',
        'insertion_sort_O2.csv',
        'insertion_sort_O3.csv'
    ]

    legend_names = [
        'Базовая версия',
        'Оптимизация 1',
        'Оптимизация 2',
        'Оптимизация 3'
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
    plt.savefig('insertion_sort_comparison_log.png', dpi=300, bbox_inches='tight')
    plt.show()


# Если имена файлов отличаются, укажите их здесь:
def plot_custom_files(file_names, legend_names=None):
    """
    Функция для произвольных имен файлов
    """
    if legend_names is None:
        legend_names = [f'Версия {i + 1}' for i in range(len(file_names))]

    plt.figure(figsize=(12, 8))

    for i, csv_file in enumerate(file_names):
        try:
            data = pd.read_csv(csv_file, delim_whitespace=True, header=None,
                               names=['n', 'time'])
            data = data.sort_values('n')

            plt.plot(data['n'], data['time'],
                     marker='o', markersize=5, linewidth=2,
                     label=legend_names[i])

        except Exception as e:
            print(f"Ошибка: {csv_file} - {e}")

    plt.xlabel('Размер массива (N)', fontsize=12)
    plt.ylabel('Время выполнения (секунды)', fontsize=12)
    plt.title('Сравнение оптимизаций Insertion Sort', fontsize=14)
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig('custom_insertion_sort_plot.png', dpi=300)
    plt.show()


# Запуск основной функции
if __name__ == "__main__":
    # Основной вариант
    #plot_insertion_sort_optimizations()

    #Дополнительно: вариант с логарифмическими осями
    plot_with_log_scales()

    # Если имена файлов другие, используйте:
    # custom_files = ['file1.csv', 'file2.csv', 'file3.csv', 'file4.csv']
    # custom_legends = ['Базовый', 'Опт 1', 'Опт 2', 'Опт 3']
    # plot_custom_files(custom_files, custom_legends)