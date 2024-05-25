#include <iostream>
#include <numeric>
#include <random>
#include <cmath>
#include <map>
#include <iomanip>

using namespace std;

// Функция для генерации массива случайных чисел в диапазоне [low, high]
void generateRandomNumbers(int* arr, int n, int low, int high) {
    minstd_rand generator(random_device{}());
    uniform_int_distribution<int> distribution(low, high);

    for (int i = 0; i < n; ++i) {
        arr[i] = distribution(generator);
    }
}

// Функция для вычисления среднего арифметического значения массива
double SrZnach(const int* arr, int n) {
    return accumulate(arr, arr + n, 0.0) / n;
}

// Функция для вычисления значения хи-квадрат
double hiKvadrat(const int* arr, int n, int low, int high, int numBins) {
    double expCount = n / numBins; // Ожидаемое кол-во чисел в каждом интервале
    int* bins = new int[numBins]();// Массив для количества чисел для каждого интервала

    // Распределение элементов массива по корзинам (bins)
    for (int i = 0; i < n; ++i) {
        int binIndex = (arr[i] - low) * numBins / (high - low + 1);
        bins[binIndex]++;
    }

    // Вычисление значения хи-квадрат
    double hiKv = 0.0;
    for (int i = 0; i < numBins; ++i) {
        hiKv += pow(bins[i] - expCount, 2) / expCount;
    }

    delete[] bins;
    return hiKv;
}

// Функция для проверки гипотезы с использованием значения хи-квадрат и критического значения
bool hiKvadratTest(int degreesOfFreedom, double hiKvValue) {
    double krit = 0.0;
    // Значения критических точек для различных степеней свободы и уровня значимости
    map<int, double> hiKvKrit = {
        {9, 16.92}  // для 9 степеней свободы и уровня значимости 0.05
    };
    krit = hiKvKrit[degreesOfFreedom];

    return hiKvValue < krit;
}

int main() {
    system("chcp 1251");
    // Создание массивов размером 50, 100 и 1000
    const int sizes[] = { 50, 100, 1000 };
    int* arrays[3];

    for (int i = 0; i < 3; ++i) {
        arrays[i] = new int[sizes[i]];
        generateRandomNumbers(arrays[i], sizes[i], 1, 100);
    }

    // Проверка гипотезы для каждого массива
    for (int i = 0; i < 3; ++i) {
        const int* arr = arrays[i];
        int size = sizes[i];
        double sredn = SrZnach(arr, size);
        double hiKvValue = hiKvadrat(arr, size, 1, 100, 10); // 10 интервалов

        cout << "Размер массива: " << size << endl;
        cout << "Ожидаемое мат. ожидание: 50.5" << endl;
        cout << "Реальное мат. ожидание: " << hiKvValue << endl;
        cout << "Кол-во степеней свободы: " << 9 << endl;
        cout << "Значение хи квадрата: " << hiKvValue << endl;

        bool proverkaGipotezi = hiKvadratTest(9, hiKvValue);
        if (proverkaGipotezi) {
            cout << "Гипотеза подтверждается." << endl;
        }
        else {
            cout << "Гипотеза отвергается." << endl;
        }
        cout << "-------------------------------------" << endl;

        delete[] arrays[i];
    }

    return 0;
}
