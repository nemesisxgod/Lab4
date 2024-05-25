#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
#include <string>
#include <map>

using namespace std;

// Функция для генерации массива случайных чисел
void randomNum(int* arr, int n, int low, int high) {
    minstd_rand generator(random_device{}());
    uniform_int_distribution<int> distribution(low, high);

    for (int i = 0; i < n; ++i) {
        arr[i] = distribution(generator);
    }
}

// Поиск самой длинной последовательности чисел, упорядоченных по убыванию
int* longestPosled(const int* arr, int n, int& length) {
    int maxL = 0;
    int maxIt = 0;
    int currentL = 1;
    int currentIt = 0;

    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1]) {
            ++currentL;
        }
        else {
            if (currentL > maxL) {
                maxL = currentL;
                maxIt = currentIt;
            }
            currentIt = i;
            currentL = 1;
        }
    }
    if (currentL > maxL) {
        maxL = currentL;
        maxIt = currentIt;
    }
    length = maxL;
    return const_cast<int*>(arr + maxIt);
}

// Инициализация нового массива, состоящего из чисел, меньших среднеарифметического значения массива
void menSrZn(const int* arr, int n, int*& result, int& resultSize) {
    double average = accumulate(arr, arr + n, 0.0) / n;
    int* temp = new int[n];//Временный массив для хранения нужных элементов и их подсчета
    int count = 0;

    for (int i = 0; i < n; ++i) {
        if (arr[i] < average) {
            temp[count++] = arr[i];
        }
    }
    resultSize = count;
    result = new int[resultSize];
    copy(temp, temp + resultSize, result);
    delete[] temp;
}

// Модификация массива случайных символов
void modCharArray(char* arr, int n) { 
    rotate(arr, arr + 2, arr + n); 
}

// Подсчет количества вхождений каждой цифры в массиве
map<int, int> cntDigits(const int* arr, int n) {
    map<int, int> digitCount;
    for (int i = 0; i < n; ++i) {
        int num = arr[i];
        while (num > 0) {
            int digit = num % 10;
            digitCount[digit]++;
            num /= 10;
        }
    }
    return digitCount;
}

int main() {
    system("chcp 1251");
    // Пункт 1
    const int n = 10;
    int arr[n];
    randomNum(arr, n, 150, 300);

    cout << "1. Массив: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Пункт 2
    int length;
    int* longestPosl = longestPosled(arr, n, length);
    cout << "2. Наибольшая убывающая последовательность: ";
    for (int i = 0; i < length; ++i) {
        cout << longestPosl[i] << " ";
    }
    cout << endl;

    // Пункт 3
    int* menSrZnach;
    int menSrZnachSize;
    menSrZn(arr, n, menSrZnach, menSrZnachSize);
    cout << "3. Новый массив: с числами меньше ср знач: ";
    for (int i = 0; i < menSrZnachSize; ++i) {
        cout << menSrZnach[i] << " ";
    }
    cout << endl;
    delete[] menSrZnach;

    // Пункт 4
    const int m = 6;
    char charArr[m] = { '0', 'I', 'D', 'Q', 'I', 'A' };
    modCharArray(charArr, m);
    cout << "4. Модифицированный массив символов : ";
    for (int i = 0; i < m; ++i) {
        cout << charArr[i] << " ";
    }
    cout << endl;

    // Пункт 5
    int randomNumbers[n];
    randomNum(randomNumbers, n, 100, 900);
    sort(randomNumbers, randomNumbers + n, greater<int>());
    cout << "5. Отсортированный массив чисел: ";
    for (int i = 0; i < n; ++i) {
        cout << randomNumbers[i] << " ";
    }
    cout << endl;

    map<int, int> digitCounts = cntDigits(randomNumbers, n);
    cout << "   Сколько раз цифра встречалась в массиве: ";
    for (const auto& pair : digitCounts) {
        cout << pair.first << ": " << pair.second << ", ";
    }
    cout << endl;

    return 0;
}