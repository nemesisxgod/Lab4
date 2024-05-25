package main

import (
	"fmt"
	"math/rand"
	"sort"
	"time"
)

// Функция для генерации массива случайных чисел
func randomNum(arr []int, low, high int) {
	rand.Seed(time.Now().UnixNano())
	for i := range arr {
		arr[i] = rand.Intn(high-low+1) + low
	}
}

// Поиск самой длинной последовательности чисел, упорядоченных по убыванию
func longestPosled(arr []int) []int {
	maxL := 0
	maxIt := 0
	currentL := 1
	currentIt := 0

	for i := 1; i < len(arr); i++ {
		if arr[i] < arr[i-1] {
			currentL++
		} else {
			if currentL > maxL {
				maxL = currentL
				maxIt = currentIt
			}
			currentIt = i
			currentL = 1
		}
	}
	if currentL > maxL {
		maxL = currentL
		maxIt = currentIt
	}

	return arr[maxIt : maxIt+maxL]
}

// Инициализация нового массива, состоящего из чисел, меньших среднеарифметического значения массива
func menSrZn(arr []int) []int {
	sum := 0.0
	for _, num := range arr {
		sum += float64(num)
	}
	average := sum / float64(len(arr))

	temp := []int{}
	for _, num := range arr {
		if float64(num) < average {
			temp = append(temp, num)
		}
	}

	return temp
}

// Модификация массива случайных символов
func modCharArray(arr []rune) {
	copy(arr, append(arr[2:], arr[:2]...))
}

// Подсчет количества вхождений каждой цифры в массиве
func cntDigits(arr []int) map[int]int {
	digitCount := make(map[int]int)
	for _, num := range arr {
		for num > 0 {
			digit := num % 10
			digitCount[digit]++
			num /= 10
		}
	}
	return digitCount
}

func main() {
	// Пункт 1
	n := 10
	arr := make([]int, n)
	randomNum(arr, 150, 300)

	fmt.Print("1. Массив: ")
	for _, num := range arr {
		fmt.Print(num, " ")
	}
	fmt.Println()

	// Пункт 2
	longestPosl := longestPosled(arr)
	fmt.Print("2. Наибольшая убывающая последовательность: ")
	for _, num := range longestPosl {
		fmt.Print(num, " ")
	}
	fmt.Println()

	// Пункт 3
	menSrZnach := menSrZn(arr)
	fmt.Print("3. Новый массив: с числами меньше ср знач: ")
	for _, num := range menSrZnach {
		fmt.Print(num, " ")
	}
	fmt.Println()

	// Пункт 4
	charArr := []rune{'0', 'I', 'D', 'Q', 'I', 'A'}
	modCharArray(charArr)
	fmt.Print("4. Модифицированный массив символов: ")
	for _, c := range charArr {
		fmt.Print(string(c), " ")
	}
	fmt.Println()

	// Пункт 5
	randomNumbers := make([]int, n)
	randomNum(randomNumbers, 100, 900)
	sort.Sort(sort.Reverse(sort.IntSlice(randomNumbers)))
	fmt.Print("5. Отсортированный массив чисел: ")
	for _, num := range randomNumbers {
		fmt.Print(num, " ")
	}
	fmt.Println()

	digitCounts := cntDigits(randomNumbers)
	fmt.Print("   Сколько раз цифра встречалась в массиве: ")
	for digit, count := range digitCounts {
		fmt.Printf("%d: %d, ", digit, count)
	}
	fmt.Println()
}
