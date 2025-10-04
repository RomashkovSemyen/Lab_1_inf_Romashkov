import matplotlib.pyplot as plt
import numpy as np
import os

# Настройка графиков
plt.style.use('default')
plt.rcParams['figure.figsize'] = (15, 10)

# Список всех сортировок
sortings = ['bubble', 'selection', 'insertion', 'comb', 'heap', 'quick']
# Все типы данных
data_types = ['int', 'char', 'small', 'medium', 'large']
# Русские названия для легенды
type_names = {
    'int': 'int (4 байта)',
    'char': 'char (1 байт)',
    'small': 'SmallStruct (8 байт)',
    'medium': 'MediumStruct (28 байт)',
    'large': 'LargeStruct (72 байта)'
}
# Цвета для типов данных
colors = ['red', 'blue', 'green', 'orange', 'purple']
# Маркеры для типов данных
markers = ['o', 's', '^', 'D', 'v']


def read_data(sorting_name, data_type):
    """Читает данные из файла CSV"""
    filename = f"{sorting_name}_{data_type}.csv"
    N = []
    Time = []

    if os.path.exists(filename):
        try:
            with open(filename, 'r') as f:
                for line in f:
                    parts = line.strip().split()
                    if len(parts) >= 2:
                        try:
                            n_val = float(parts[0])
                            t_val = float(parts[1])
                            if t_val > 0:  # Игнорируем нулевые и отрицательные значения
                                N.append(n_val)
                                Time.append(t_val)
                        except ValueError:
                            continue
        except Exception as e:
            print(f"Ошибка чтения файла {filename}: {e}")
    else:
        print(f"Файл {filename} не найден")

    return N, Time


def plot_all_sortings_comparison():
    """Строит 6 графиков, на каждом по 5 типов данных"""

    # Создаем сетку 2x3 для 6 графиков
    fig, axes = plt.subplots(2, 3, figsize=(20, 12))
    axes = axes.flatten()

    # Для каждой сортировки строим свой график
    for idx, sorting in enumerate(sortings):
        ax = axes[idx]

        # Для каждой сортировки рисуем все типы данных
        for type_idx, data_type in enumerate(data_types):
            N, Time = read_data(sorting, data_type)

            if len(N) > 0 and len(Time) > 0:
                ax.plot(N, Time,
                        marker=markers[type_idx],
                        color=colors[type_idx],
                        label=type_names[data_type],
                        markersize=4,
                        linewidth=2,
                        alpha=0.8)

        # Настройки графика
        ax.set_xlabel('Размер массива (N)')
        ax.set_ylabel('Время (секунды)')
        ax.set_title(f'{sorting.capitalize()} Sort')
        ax.legend()
        ax.grid(True, alpha=0.3)
        ax.set_xlim(0, None)
        ax.set_ylim(0, None)

    plt.tight_layout()
    plt.savefig('all_sortings_comparison.png', dpi=300, bbox_inches='tight')
    plt.show()


def plot_log_scale_comparison():
    """Строит графики в логарифмическом масштабе"""

    fig, axes = plt.subplots(2, 3, figsize=(20, 12))
    axes = axes.flatten()

    for idx, sorting in enumerate(sortings):
        ax = axes[idx]

        for type_idx, data_type in enumerate(data_types):
            N, Time = read_data(sorting, data_type)

            if len(N) > 0 and len(Time) > 0:
                # Фильтруем нулевые значения для логарифма
                valid_N = []
                valid_Time = []
                for n, t in zip(N, Time):
                    if t > 1e-10:  # Избегаем логарифма от нуля
                        valid_N.append(n)
                        valid_Time.append(t)

                if len(valid_N) > 0:
                    ax.loglog(valid_N, valid_Time,
                              marker=markers[type_idx],
                              color=colors[type_idx],
                              label=type_names[data_type],
                              markersize=4,
                              linewidth=2,
                              alpha=0.8)

        ax.set_xlabel('Размер массива (N)')
        ax.set_ylabel('Время (секунды)')
        ax.set_title(f'{sorting.capitalize()} Sort (log scale)')
        ax.legend()
        ax.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('all_sortings_log_scale.png', dpi=300, bbox_inches='tight')
    plt.show()


def plot_by_data_type():
    """Строит графики группированные по типам данных"""

    for data_type in data_types:
        plt.figure(figsize=(12, 8))

        # Для каждого типа данных рисуем все сортировки
        for sort_idx, sorting in enumerate(sortings):
            N, Time = read_data(sorting, data_type)

            if len(N) > 0 and len(Time) > 0:
                plt.plot(N, Time,
                         marker=markers[sort_idx % len(markers)],
                         color=plt.cm.Set1(sort_idx / len(sortings)),
                         label=sorting.capitalize(),
                         markersize=4,
                         linewidth=2,
                         alpha=0.8)

        plt.xlabel('Размер массива (N)')
        plt.ylabel('Время (секунды)')
        plt.title(f'Сравнение сортировок для {type_names[data_type]}')
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.tight_layout()
        plt.savefig(f'comparison_{data_type}.png', dpi=300, bbox_inches='tight')
        plt.show()


def plot_performance_ratio():
    """Строит графики относительной производительности"""

    # Базовый тип - int
    base_type = 'int'

    fig, axes = plt.subplots(2, 3, figsize=(20, 12))
    axes = axes.flatten()

    for idx, sorting in enumerate(sortings):
        ax = axes[idx]

        # Читаем базовые данные (int)
        base_N, base_Time = read_data(sorting, base_type)
        if len(base_N) == 0:
            continue

        # Для каждого другого типа вычисляем отношение времени к int
        for type_idx, data_type in enumerate(data_types):
            if data_type == base_type:
                continue

            N, Time = read_data(sorting, data_type)

            if len(N) > 0 and len(Time) > 0:
                # Вычисляем отношение времени для одинаковых N
                ratios = []
                valid_N = []

                for i, n in enumerate(N):
                    if i < len(base_N) and base_N[i] == n and Time[i] > 0 and base_Time[i] > 0:
                        ratio = Time[i] / base_Time[i]
                        ratios.append(ratio)
                        valid_N.append(n)

                if len(valid_N) > 0:
                    ax.plot(valid_N, ratios,
                            marker=markers[type_idx],
                            color=colors[type_idx],
                            label=f'{data_type}/int',
                            markersize=4,
                            linewidth=2,
                            alpha=0.8)

        ax.set_xlabel('Размер массива (N)')
        ax.set_ylabel('Отношение времени')
        ax.set_title(f'{sorting.capitalize()} Sort: Отн. производительность')
        ax.legend()
        ax.grid(True, alpha=0.3)
        ax.axhline(y=1, color='red', linestyle='--', alpha=0.5)  # Линия для отношения = 1

    plt.tight_layout()
    plt.savefig('performance_ratio.png', dpi=300, bbox_inches='tight')
    plt.show()


def print_data_statistics():
    """Выводит статистику по данным"""
    print("=" * 60)
    print("СТАТИСТИКА ДАННЫХ")
    print("=" * 60)

    for sorting in sortings:
        print(f"\n{sorting.upper()} SORT:")
        print("-" * 40)

        for data_type in data_types:
            N, Time = read_data(sorting, data_type)
            if len(N) > 0:
                max_time = max(Time) if Time else 0
                min_time = min(Time) if Time else 0
                avg_time = sum(Time) / len(Time) if Time else 0
                print(f"  {type_names[data_type]:<25} | N: {len(N):>3} | "
                      f"Время: {min_time:.2e} - {max_time:.2e} | "
                      f"Ср: {avg_time:.2e}")
            else:
                print(f"  {type_names[data_type]:<25} | Нет данных")


def main():
    print("Анализ производительности сортировок на разных типах данных")
    print("=" * 70)

    # Выводим статистику
    print_data_statistics()

    print("\n" + "=" * 70)
    print("ПОСТРОЕНИЕ ГРАФИКОВ...")
    print("=" * 70)

    # 1. Основные графики - все сортировки и все типы данных
    print("1. Строим основные графики...")
    plot_all_sortings_comparison()

    # 2. Логарифмическая шкала
    print("2. Строим графики в логарифмическом масштабе...")
    plot_log_scale_comparison()

    # 3. Группировка по типам данных
    print("3. Строим графики по типам данных...")
    plot_by_data_type()

    # 4. Относительная производительность
    print("4. Строим графики относительной производительности...")
    plot_performance_ratio()

    print("\n" + "=" * 70)
    print("ВСЕ ГРАФИКИ ПОСТРОЕНЫ!")
    print("=" * 70)
    print("\nСозданные файлы:")
    print("• all_sortings_comparison.png - 6 графиков с сравнением типов данных")
    print("• all_sortings_log_scale.png - то же в логарифмическом масштабе")
    print("• comparison_int.png, comparison_char.png, ... - по типам данных")
    print("• performance_ratio.png - относительная производительность")


if __name__ == "__main__":
    main()