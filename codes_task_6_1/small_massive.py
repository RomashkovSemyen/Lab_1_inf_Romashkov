import matplotlib.pyplot as plt

# Список всех сортировок (6 штук)
sortings = ['bubble.csv', 'insertion.csv', 'selection.csv', 'heap.csv', 'comb.csv', 'quick.csv']

# Создаем 6 графиков (2 строки по 3 графика)
fig, axes = plt.subplots(2, 3, figsize=(18, 12))
axes = axes.flatten()  # Преобразуем в одномерный массив для удобства

# Проходим по всем файлам и строим графики
for idx, file in enumerate(sortings):
    N = []
    Time = []

    # Получаем название сортировки из имени файла
    sorting_name = file.replace('.csv', '').capitaёize() + ' Sort'

    # Читаем файл
    try:
        with open(file, 'r') as f:
            for line in f:
                parts = line.strip().split()
                if len(parts) >= 2:
                    try:
                        n_val = float(parts[0])
                        t_val = float(parts[1])
                        N.append(n_val)
    except FileNotFoundError:
        print(f"Файл {file} не найден")
        # Если файл не найден, создаем пустой график
        axes[idx].text(0.5, 0.5, f'Файл {file} не найден',
                       ha='center', va='center', transform=axes[idx].transAxes)
        axes[idx].set_title(f'{sorting_name}')
        continue

    # Рисуем на соответствующем графике
    if len(N) > 0:
        axes[idx].plot(N, Time, 'o-', label=sorting_name, markersize=4, linewidth=2)
        axes[idx].set_xlabel('N (размер массива)')
        axes[idx].set_ylabel('Time (секунды)')
        axes[idx].set_title(f'{sorting_name}')
        axes[idx].legend()
        axes[idx].grid(True, alpha=0.3)
                        Time.append(t_val)
                    except:
                        continue
    else:
        axes[idx].text(0.5, 0.5, 'Нет данных',
                       ha='center', va='center', transform=axes[idx].transAxes)
        axes[idx].set_title(f'{sorting_name}')

plt.tight_layout()
plt.savefig('small_massive.png', dpi=300, bbox_inches='tight')
plt.show()