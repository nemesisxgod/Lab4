package main

import (
	"fmt"
	"math"
	"os"
	"text/tabwriter"
)

// Исходная функция
func funcF(x float64) float64 {
	return math.Cos(x+0.5) - x - 2
}

// Производная функции для метода Ньютона
func dfunc(x float64) float64 {
	return -math.Sin(x+0.5) - 1
}

// Итерационная функция для метода простых итераций
func g(x float64) float64 {
	return math.Cos(x+0.5) - 2
}

// Метод половинного деления
func bisection(a, b, E float64, bi *[]tuple, res *float64) {
	N := 0
	for (b-a) >= E && N < 100 {
		c := (a + b) / 2
		*bi = append(*bi, tuple{N, a, b, b - a})
		if funcF(c) == 0 {
			break
		} else if funcF(a)*funcF(c) < 0 {
			b = c
		} else {
			a = c
		}
		N++
		*res = c
	}
}

// Метод Ньютона
func Newton(x0, eps float64, nt *[]tuple, res *float64) {
	N := 0
	for math.Abs(funcF(x0)) >= eps && N < 100 {
		x1 := x0 - funcF(x0)/dfunc(x0)
		razn := math.Abs(x1 - x0)
		if razn < 0.0001 {
			razn = 0.0001
		}
		*nt = append(*nt, tuple{N, x0, x1, razn})
		if math.Abs(x1-x0) <= eps {
			break
		}
		x0 = x1
		N++
		*res = x0
	}
}

// Метод простых итераций
func simple(x0, eps float64, smpl *[]tuple, res *float64) {
	N := 0
	for math.Abs(g(x0)) >= eps && N < 100 {
		x1 := g(x0)
		if math.Abs(x1-x0) < eps {
			break
		}
		*smpl = append(*smpl, tuple{N, x0, x1, math.Abs(x1 - x0)})
		x0 = x1
		N++
		*res = x0
	}
}

type tuple struct {
	N    int
	a, b float64
	ba   float64
}

func main() {
	a := -3.0
	b := 1.0
	E := 0.0001
	var res float64
	bi := []tuple{}
	nt := []tuple{}
	smpl := []tuple{}

	outfile, err := os.Create("res.txt")
	if err != nil {
		fmt.Println("При открытии файла произошла ошибка")
		return
	}
	defer outfile.Close()

	writer := tabwriter.NewWriter(outfile, 0, 0, 1, ' ', tabwriter.Debug)

	bisection(a, b, E, &bi, &res)
	fmt.Fprintln(writer, "Метод половинного деления:")
	fmt.Fprintln(writer, "N\t\ta\t\tb\t\tb - a\t\t")
	for _, v := range bi {
		fmt.Fprintf(writer, "%d\t\t%.10f\t\t%.10f\t\t%.10f\t\t\n", v.N, v.a, v.b, v.ba)
	}
	fmt.Fprintln(writer, "\nКорень:", res)
	fmt.Fprintln(writer, "---------------------------------------------------------------")

	x_null := -2.0
	Newton(x_null, E, &nt, &res)
	fmt.Fprintln(writer, "Метод Ньютона:")
	fmt.Fprintln(writer, "N\t\tx_null\t\tx_1\t\tx_1 - x_null\t\t")
	for _, v := range nt {
		fmt.Fprintf(writer, "%d\t\t%.10f\t\t%.10f\t\t%.10f\t\t\n", v.N, v.a, v.b, v.ba)
	}
	fmt.Fprintln(writer, "\nКорень:", res)
	fmt.Fprintln(writer, "---------------------------------------------------------------")

	simple(x_null, E, &smpl, &res)
	fmt.Fprintln(writer, "Метод простых итераций:")
	fmt.Fprintln(writer, "N\t\tx_null\t\tx_1\t\tx_1 - x_null\t\t")
	for _, v := range smpl {
		fmt.Fprintf(writer, "%d\t\t%.10f\t\t%.10f\t\t%.10f\t\t\n", v.N, v.a, v.b, v.ba)
	}
	fmt.Fprintln(writer, "\nКорень:", res)
	fmt.Fprintln(writer, "---------------------------------------------------------------")

	writer.Flush()
}
