import matplotlib.pyplot as plt
import numpy as np
from scipy import stats


def calculate_slope(x_data, y_data):
    """Вычисляет коэффициент наклона в логарифмических координатах"""
    if len(x_data) < 2:
        return 0, 0

    # Линейная регрессия в логарифмических координатах
    log_x = np.log10(x_data)
    log_y = np.log10(y_data)

    slope, intercept, r_value, p_value, std_err = stats.linregress(log_x, log_y)
    return slope, r_value ** 2  # возвращаем наклон и R²


def plot_multiple_from_csv(filenames, labels=None, xlabel='X', ylabel='Y', title='Graph'):

    if labels is None:
        labels = [f.split('.')[0] for f in filenames]

    # Цвета для разных графиков
    colors = ['blue', 'red', 'green', 'orange', 'purple', 'brown']
    markers = ['o', 's', '^', 'D', 'v', '<']

    # Чтение данных из всех файлов
    all_data = []

    for filename in filenames:
        x_data = []
        y_data = []

        try:
            with open(filename, 'r') as file:
                for line_num, line in enumerate(file, 1):
                    line = line.strip()
                    if not line:
                        continue

                    parts = line.split()
                    if len(parts) >= 2:
                        try:
                            x = float(parts[0])
                            y = float(parts[1])
                            x_data.append(x)
                            y_data.append(y)
                        except ValueError:
                            print(f"Предупреждение: нечисловые данные в файле {filename}, строка {line_num}")

        except FileNotFoundError:
            print(f"Ошибка: файл '{filename}' не найден")
            continue
        except Exception as e:
            print(f"Ошибка при чтении файла {filename}: {e}")
            continue

        if x_data and y_data:
            all_data.append({
                'x': x_data,
                'y': y_data,
                'filename': filename
            })

    # Создание графиков
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))

    # График 1: обычные оси
    for i, data in enumerate(all_data):
        color = colors[i % len(colors)]
        marker = markers[i % len(markers)]
        label = labels[i] if i < len(labels) else data['filename']

        ax1.plot(data['x'], data['y'], marker='', linestyle='-',
                 color=color, linewidth=2, label=label)
        ax1.plot(data['x'], data['y'], marker=marker, linestyle='',
                 color=color, markersize=6, markerfacecolor=color)

    ax1.set_xlabel(xlabel)
    ax1.set_ylabel(ylabel)
    ax1.set_title(f'{title}\n(Линейные оси)')
    ax1.legend()
    ax1.grid(True, alpha=0.3)

    # График 2: логарифмические оси с коэффициентами наклона
    slope_info = []  # для хранения информации о наклонах

    for i, data in enumerate(all_data):
        color = colors[i % len(colors)]
        marker = markers[i % len(markers)]

        # Вычисляем коэффициент наклона
        slope, r_squared = calculate_slope(data['x'], data['y'])

        label_base = labels[i] if i < len(labels) else data['filename']
        label_with_slope = f'{label_base} (k={slope:.2f})'
        slope_info.append(f"{label_base}: k = {slope:.3f}, R² = {r_squared:.3f}")

        ax2.loglog(data['x'], data['y'], marker='', linestyle='-',
                   color=color, linewidth=2, label=label_with_slope)
        ax2.loglog(data['x'], data['y'], marker=marker, linestyle='',
                   color=color, markersize=6, markerfacecolor=color)

    ax2.set_xlabel(xlabel)
    ax2.set_ylabel(ylabel)
    ax2.set_title(f'{title}\n(Логарифмические оси)')
    ax2.legend()
    ax2.grid(True, alpha=0.3)

    plt.tight_layout()

    # Вывод информации о коэффициентах наклона
    print("\n" + "=" * 50)
    print("КОЭФФИЦИЕНТЫ НАКЛОНА В ЛОГАРИФМИЧЕСКИХ КООРДИНАТАХ:")
    print("=" * 50)
    for info in slope_info:
        print(info)

    # Сохранение графиков
    output_filename = 'N2.png'
    plt.savefig(output_filename, dpi=300, bbox_inches='tight')
    print(f"\nГрафики сохранены в файл: '{output_filename}'")

    plt.show()

    return fig, slope_info


if __name__ == "__main__":
    # Список файлов для построения
    filenames = ['bubble.csv', 'selecion_sort.csv', 'insertion_sort.csv']

    # Метки для легенды
    labels = ['Bubble Sort', 'Selection Sort', 'Insertion Sort']

    # Построение графиков
    fig, slopes = plot_multiple_from_csv(
        filenames=filenames,
        labels=labels,
        xlabel='Размер массива (N)',
        ylabel='Время выполнения (нс)',
        title='Сравнение производительности алгоритмов сортировки'
    )