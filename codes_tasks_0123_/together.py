import matplotlib.pyplot as plt

# Считываем и рисуем все 6 CSV файлов на одном графике
files = [
    'comb.csv', 'xoar.csv', 'heap.csv',  # пункт 2
    'bubble.csv', 'insertion_sort.csv', 'selecion_sort.csv'  # пункт 0
]

labels = [
    'Comb', 'Quick', 'Heap',
    'Bubble', 'Insert', 'Selection'
]

# Создаем график
plt.figure(figsize=(12, 8))

# Читаем и рисуем каждый файл
for i, file in enumerate(files):
    N = []
    Time = []

    # Читаем файл
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

    # Рисуем на графике
    if len(N) > 0:
        plt.plot(N, Time, 'o-', label=labels[i], markersize=3, linewidth=1)

plt.xlabel('N')
plt.ylabel('Time')
plt.title('All Algorithms: Point 0 vs Point 2')
plt.legend()
plt.grid(True, alpha=0.3)

plt.savefig('all_algorithms.png', dpi=300, bbox_inches='tight')
plt.show()