#include <iostream>
#include <vector>

using namespace std;

// Функция для генерации последовательности LCG
vector<int> generateLCG(int seed, int A, int B, int C, int& repeatIndex) {
    vector<int> seenValues; // для хранения встречавшихся элементов

    int Xi = seed;
    int index = 0;

    for (int i=0; i<10; i++) {
        // Проверяем, встречалось ли значение Xi ранее
        if (find(seenValues.begin(), seenValues.end(), Xi) != seenValues.end() and (repeatIndex==0)) {
            repeatIndex = i+1; // Находим индекс начала повторения

        }

        seenValues.push_back(Xi);

        Xi = (A * Xi + B) % C; // Генерация следующего значения последовательности
        ++index;
    }

    return seenValues;
}

int main() {
    // Пример 1
    int seed = 2;
    int A = 3;
    int B = 5;
    int C = 10;
    int repeatIndex=0;

    vector<int> seenValues = generateLCG(seed, A, B, C, repeatIndex);

    for (int num : seenValues) {
        cout << num << " ";
    }
    cout << endl << repeatIndex << endl;

    // Пример 2
    seed = 5;
    A = 3;
    B = 3;
    C = 7;
    repeatIndex = 0;
    seenValues = generateLCG(seed, A, B, C, repeatIndex);

    for (int num : seenValues) {
        cout << num << " ";
    }
    cout << endl << repeatIndex << endl;

    return 0;
}