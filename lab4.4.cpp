#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <functional>

using namespace std;

// Алгоритм 1: Непредсказуемый
bool unpredictable(int round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    return rand()%2;
}

// Алгоритм 2: Злопамятный
bool grimTrigger(int round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    if (round_number == 0) {
        return true; // Начинаем с сотрудничества
    }
    // Если противник когда-либо предал, всегда предаем
    return find(enemy_choices.begin(), enemy_choices.end(), false) == enemy_choices.end();
}

// Алгоритм 3: Зеркало
bool mirror(int round_number, const vector<bool>& self_choices, const vector<bool>& enemy_choices) {
    if (round_number == 0) {
        return true; // Начинаем с сотрудничества
    }
    return enemy_choices[round_number - 1]; // Повторяем предыдущий ход противника
}

// Проведение одного раунда игры
pair<int, int> playRound(bool choiceA, bool choiceB) {
    if (choiceA && choiceB) {
        return { 24, 24 }; // Оба сотрудничают
    }
    else if (!choiceA && !choiceB) {
        return { 4, 4 };   // Оба предают
    }
    else if (choiceA && !choiceB) {
        return { 0, 20 };  // A сотрудничает, B предает
    }
    else {
        return { 20, 0 };  // A предает, B сотрудничает
    }
}

// Проведение игры
pair<int, int> playGame(function<bool(int, const vector<bool>&, const vector<bool>&)> algoA,
    function<bool(int, const vector<bool>&, const vector<bool>&)> algoB) {
    minstd_rand generator(random_device{}());
    uniform_int_distribution<int> distribution(100, 200);
    int rounds = distribution(generator);

    vector<bool> choicesA;
    vector<bool> choicesB;
    int scoreA = 0;
    int scoreB = 0;

    for (int round = 0; round < rounds; ++round) {
        bool choiceA = algoA(round, choicesA, choicesB);
        bool choiceB = algoB(round, choicesA, choicesB);
        choicesA.push_back(choiceA);
        choicesB.push_back(choiceB);

        auto scores = playRound(choiceA, choiceB);
        scoreA += scores.first;
        scoreB += scores.second;
    }

    return { scoreA, scoreB };
}

int main() {
    system("chcp 1251");

    // Список всех алгоритмов
    vector<function<bool(int, const vector<bool>&, const vector<bool>&)>> algorithms = { unpredictable, grimTrigger, mirror };
    vector<string> algorithmNames = { "Непредсказуемый", "Злопамятный", "Зеркальный" };

    // Проведение игр между всеми парами алгоритмов
    for (size_t i = 0; i < algorithms.size(); ++i) {
        for (size_t j = i + 1; j < algorithms.size(); ++j) {
            cout << "Игра между " << algorithmNames[i] << " и " << algorithmNames[j] << ":" << endl;
            auto scores = playGame(algorithms[i], algorithms[j]);
            cout << algorithmNames[i] << " набрал " << scores.first << " очков." << endl;
            cout << algorithmNames[j] << " набрал " << scores.second << " очков." << endl;

            if (scores.first > scores.second) {
                cout << algorithmNames[i] << " победил." << endl;
            }
            else if (scores.first < scores.second) {
                cout << algorithmNames[j] << " победил." << endl;
            }
            else {
                cout << "Ничья." << endl;
            }
            cout << "-------------------------------------" << endl;
        }
    }

    return 0;
}
