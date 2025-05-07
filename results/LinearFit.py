import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression

# Dane wejściowe
sizes = np.array([1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]).reshape(-1, 1)

# Czas wyszukiwania dla każdej struktury danych
#array_times = np.array([4.98e-8, 5.56e-8, 5.62e-8, 5.74e-8, 5.98e-8, 6.10e-8, 5.86e-8, 6.26e-8, 5.84e-8, 5.86e-8])
#dlist_times = np.array([1.07e-6, 2.64e-6, 4.31e-6, 5.79e6, 6.95e6, 8.69e6, 1.05e-5, 1.21e-5, 1.40e-5, 1.63e-5])

#dlist_times = np.array([6.62e-8, 1.19e-7, 1.61e-7, 1.74e-7, 1.77e-7, 2.12e-7, 2.54e-7, 2.73e-7, 3.08e-7, 3.58e-7])
#array_times = np.array([4.64e-8, 6.26e-8, 6.46e-8, 6.56e-8, 6.90e-8, 6.68e-8, 7.26e-8, 7.54e-8, 7.42e-8, 7.60e-8])


dlist_times = np.array([1.17e-6, 3.43e-6, 5.93e-6, 7.27e-6, 1.02e-5, 1.36e-5, 1.78e-5, 2.08e-5, 2.32e-5, 2.77e-5])
array_times = np.array([2.06e-7, 6.22e-7, 6.91e-7, 5.99e-7, 7.17e-7, 8.18e-7, 8.56e-7, 1.00e-6, 1.11e-6, 1.13e-6])

# Modele regresji
reg_array = LinearRegression().fit(sizes, array_times)
reg_dlist = LinearRegression().fit(sizes, dlist_times)

# Przewidywane wartości
sizes_flat = sizes.flatten()
pred_array = reg_array.predict(sizes)
pred_dlist = reg_dlist.predict(sizes)

# Funkcja do rysowania wykresów
def plot_with_fit(x, y, y_pred, title, label, color):
    plt.figure(figsize=(8, 5))
    plt.scatter(x, y, color=color, label=f'Czas ({label})', marker='o')
    plt.plot(x, y_pred, color='black', linestyle='--', label='Dopasowanie liniowe')
    plt.title(title)
    plt.xlabel('Rozmiar struktury danych')
    plt.ylabel('Czas [s]')
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.legend()
    plt.tight_layout()
    plt.show()

# Rysowanie wykresów
plot_with_fit(sizes_flat, array_times, pred_array, 'Czas wyszukiwania - Kopiec binarny', 'Kopiec', 'blue')
plot_with_fit(sizes_flat, dlist_times, pred_dlist, 'Czas wyszukiwania - Lista dwukierunkowa', 'Lista dwukierunkowa', 'green')
