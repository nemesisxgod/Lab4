package main

import (
	"fmt"
	"math/rand"
	"time"
)

// Алгоритм 1: Непредсказуемый
func unpredictable(roundNumber int, selfChoices, enemyChoices []bool) bool {
	return rand.Intn(2) == 1
}

// Алгоритм 2: Злопамятный
func grimTrigger(roundNumber int, selfChoices, enemyChoices []bool) bool {
	if roundNumber == 0 {
		return true // Начинаем с сотрудничества
	}
	// Если противник когда-либо предал, всегда предаем
	for _, choice := range enemyChoices {
		if !choice {
			return false
		}
	}
	return true
}

// Алгоритм 3: Зеркало
func mirror(roundNumber int, selfChoices, enemyChoices []bool) bool {
	if roundNumber == 0 {
		return true // Начинаем с сотрудничества
	}
	return enemyChoices[roundNumber-1] // Повторяем предыдущий ход противника
}

// Проведение одного раунда игры
func playRound(choiceA, choiceB bool) (int, int) {
	if choiceA && choiceB {
		return 24, 24 // Оба сотрудничают
	} else if !choiceA && !choiceB {
		return 4, 4 // Оба предают
	} else if choiceA && !choiceB {
		return 0, 20 // A сотрудничает, B предает
	} else {
		return 20, 0 // A предает, B сотрудничает
	}
}

// Проведение игры
func playGame(algoA, algoB func(int, []bool, []bool) bool) (int, int) {
	rand.Seed(time.Now().UnixNano())
	rounds := rand.Intn(101) + 100 // Генерация случайного числа раундов от 100 до 200

	choicesA := []bool{}
	choicesB := []bool{}
	scoreA, scoreB := 0, 0

	for round := 0; round < rounds; round++ {
		choiceA := algoA(round, choicesA, choicesB)
		choiceB := algoB(round, choicesA, choicesB)
		choicesA = append(choicesA, choiceA)
		choicesB = append(choicesB, choiceB)

		scoreRoundA, scoreRoundB := playRound(choiceA, choiceB)
		scoreA += scoreRoundA
		scoreB += scoreRoundB
	}

	return scoreA, scoreB
}

func main() {
	// Установка кодировки для корректного отображения русских символов в консоли Windows
	// Это эквивалентно system("chcp 1251") в C++
	// Это не обязательно для систем, где кодировка уже установлена правильно

	// Список всех алгоритмов
	algorithms := []func(int, []bool, []bool) bool{unpredictable, grimTrigger, mirror}
	algorithmNames := []string{"Непредсказуемый", "Злопамятный", "Зеркальный"}

	// Проведение игр между всеми парами алгоритмов
	for i := 0; i < len(algorithms); i++ {
		for j := i + 1; j < len(algorithms); j++ {
			fmt.Printf("Игра между %s и %s:\n", algorithmNames[i], algorithmNames[j])
			scoreA, scoreB := playGame(algorithms[i], algorithms[j])
			fmt.Printf("%s набрал %d очков.\n", algorithmNames[i], scoreA)
			fmt.Printf("%s набрал %d очков.\n", algorithmNames[j], scoreB)

			if scoreA > scoreB {
				fmt.Printf("%s победил.\n", algorithmNames[i])
			} else if scoreA < scoreB {
				fmt.Printf("%s победил.\n", algorithmNames[j])
			} else {
				fmt.Println("Ничья.")
			}
			fmt.Println("-------------------------------------")
		}
	}
}
