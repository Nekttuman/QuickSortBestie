import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Читаем CSV
df = pd.read_csv("thresholds.csv")

thresholds = df['threshold'].values
avg_times = df['avg_time_ns'].values

# Находим минимум
min_index = np.argmin(avg_times)
best_threshold = thresholds[min_index]
best_time = avg_times[min_index]

plt.figure(figsize=(12, 6))
plt.plot(thresholds, avg_times, marker='o', linestyle='-', color='blue', label='Avg Time')
plt.scatter(best_threshold, best_time, color='red', s=100, label=f'Minimum: {best_threshold}')
plt.title("Average Time vs INSERTION_SORT_THRESHOLD")
plt.xlabel("INSERTION_SORT_THRESHOLD")
plt.ylabel("Average time (ns)")
plt.legend()
plt.grid(True)
plt.show()


import matplotlib.pyplot as plt
import numpy as np

# Конфигурации оптимизаций
configs = [
    "All Off",
    "MOVE ON",
    "MEDIAN ON",
    "INSERTION ON",
    "TAIL ON",
    "All ON"
]

# Среднее время (ns) по типам данных для каждой конфигурации
# Убираем 'nearly sorted' и 'duplicates'
times = np.array([
    [753780, 887600, 5751640, 4084960],  # All Off
    [753900, 877520, 5638880, 3956520],  # MOVE ON
    [810520, 871380, 6290020, 4358960],  # MEDIAN ON
    [805280, 871140, 5540580, 3895120],  # INSERTION ON
    [791840, 914820, 5479480, 4448920],  # TAIL ON
    [753400, 872180, 5751720, 4019660]   # All ON
])

types = ["int rnd", "double rnd", "string rnd", "struct"]

# Параметры для гистограммы
x = np.arange(len(types))
width = 0.13  # ширина колонок

plt.figure(figsize=(12, 6))

for i, config in enumerate(configs):
    plt.bar(x + i*width, times[i], width, label=config)

plt.xticks(x + width*2.5, types, rotation=15)
plt.ylabel("Average time (ns)")
plt.title("QuickSort performance vs optimization flags")
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()

