import matplotlib.pyplot as plt

# Список всех сортировок (6 штук)
sortings = ['bubble', 'insert', 'select', 'heap', 'comb', 'quick']

# Создаем 6 графиков (2 строки по 3 графика)
fig, axes = plt.subplots(2, 3, figsize=(18, 12))
axes = axes.flatten()  # Преобразуем в одномерный массив для удобства

# Для каждой сортировки
for idx, sorting in enumerate(sortings):
    # Создаем список из 3 файлов для текущей сортировки
    files = [f'{sorting}_best.csv', f'{sorting}_rand.csv', f'{sorting}_worst.csv']

    # На одном графике рисуем все 3 файла для этой сортировки
    for i, file in enumerate(files):
        N = []
        Time = []

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
                            Time.append(t_val)
                        except:
                            continue
        except FileNotFoundError:
            print(f"Файл {file} не найден")
            continue

        # Рисуем на соответствующем графике
        if len(N) > 0:
            axes[idx].plot(N, Time, 'o-', label=f'Test {i + 1}', markersize=2, linewidth=1)

    # Настраиваем график
    axes[idx].set_xlabel('N')
    axes[idx].set_ylabel('Time')
    axes[idx].set_title(f'{sorting.capitalize()} Sort')
    axes[idx].legend()
    axes[idx].grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('all_sortings.png', dpi=300, bbox_inches='tight')
plt.show()