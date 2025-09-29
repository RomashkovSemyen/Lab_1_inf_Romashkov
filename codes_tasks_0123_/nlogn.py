import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit


# Функция для моделирования сложности O(n log n)
def n_log_n(x, a, b):
    return a * x * np.log(x) + b


# Считываем CSV файлы напрямую
files = ['comb.csv', 'xoar.csv', 'heap.csv']
labels = ['Comb Sort', 'Quick Sort', 'Heap Sort']
all_data = []

for file in files:
    N = []
    Time = []
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
    all_data.append((N, Time))
    print(f"{file}: N={N}, Time={Time}")

# Создаем 3 графика
fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(18, 5))

# 1. Обычный график: N vs Time
for i, (N, Time) in enumerate(all_data):
    if len(N) > 0:
        ax1.plot(N, Time, 'o-', label=labels[i], markersize=3, linewidth=1)
ax1.set_xlabel('N')
ax1.set_ylabel('Time (seconds)')
ax1.set_title('Time vs N')
ax1.legend()
ax1.grid(True, alpha=0.3)

# 2. График Time/(N log N) vs N
for i, (N, Time) in enumerate(all_data):
    if len(N) > 0:
        N_arr = np.array(N)
        Time_arr = np.array(Time)
        mask = (N_arr > 1) & (Time_arr > 0)

        N_filtered = N_arr[mask]
        Time_filtered = Time_arr[mask]

        if len(N_filtered) > 0:
            normalized_time = Time_filtered / (N_filtered * np.log(N_filtered))
            ax2.plot(N_filtered, normalized_time, 'o-', label=labels[i], markersize=3, linewidth=1)
ax2.set_xlabel('N')
ax2.set_ylabel('Time / (N log N)')
ax2.set_title('Time/(N log N) vs N\n(Constant = O(N log N))')
ax2.legend()
ax2.grid(True, alpha=0.3)

# 3. Аппроксимация кривой N log N
for i, (N, Time) in enumerate(all_data):
    if len(N) > 0:
        N_arr = np.array(N)
        Time_arr = np.array(Time)
        mask = (N_arr > 1) & (Time_arr > 0)

        N_filtered = N_arr[mask]
        Time_filtered = Time_arr[mask]

        if len(N_filtered) > 2:
            try:
                # Аппроксимируем данные
                popt, _ = curve_fit(n_log_n, N_filtered, Time_filtered, maxfev=5000)
                a, b = popt

                # Строим данные и аппроксимацию
                ax3.plot(N_filtered, Time_filtered, 'o', label=f'{labels[i]} data', markersize=3)

                x_fit = np.linspace(min(N_filtered), max(N_filtered), 100)
                y_fit = n_log_n(x_fit, a, b)
                ax3.plot(x_fit, y_fit, '-', label=f'{labels[i]} fit: {a:.2e}NlogN', linewidth=2)

            except:
                # Если аппроксимация не удалась, просто строим данные
                ax3.plot(N_filtered, Time_filtered, 'o-', label=labels[i], markersize=3)

ax3.set_xlabel('N')
ax3.set_ylabel('Time')
ax3.set_title('N log N Approximation')
ax3.legend()
ax3.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('nlogn.png', dpi=300, bbox_inches='tight')
plt.show()