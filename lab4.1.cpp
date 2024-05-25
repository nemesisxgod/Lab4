#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
#include <tuple>

using namespace std;

double func(double x) { //Функция исходная
    return cos(x + 0.5) - x - 2;
}

double dfunc(double x) {//Производная функции для метода Ньютона
    return -sin(x+0.5)-1;
}

double g(double x) {//Итерационная функция для метода простых итераций
    return cos(x + 0.5) - 2;
}
//Метод половинного деления
void bisection(double a, double b, double E, vector<tuple<double, double, double, double>>& bi, double& res) {
    int N = 0;
    while ((b - a) >= E && N < 100) {
        double c = (a + b) / 2;
        bi.push_back({ N, a, b, b - a });
        if (func(c) == 0) {
            break;
        }
        else if (func(a) * func(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        N++;
        res = c;
    }
}

//Метод Ньютона
void Newton(double x_null, double eps, vector<tuple<double, double, double, double>>& nt, double& res) {
    int N = 0;
    while (abs(func(x_null)) >= eps && N < 100) {
        double x_1 = x_null - func(x_null) / dfunc(x_null);
        double razn = abs(x_1 - x_null);
        if (razn < 0.0001) razn = 0.0001;
        nt.push_back({ N, x_null, x_1, razn });
        if (abs(x_1 - x_null) <= eps) {
            break;
        }
        x_null = x_1;
        N++;
        res = x_null;
    }
}

//Метод простых итераций
void simple(double x_null, double eps, vector<tuple<double, double, double, double>>& smpl, double& res) {
    int N = 0;
    while (abs(g(x_null)) >= eps && N < 100) {
        double x_1 = g(x_null);
        if (abs(x_1 - x_null) < eps) {
            break;
        }
        smpl.push_back({ N, x_null, x_1, abs(x_1 - x_null) });
        x_null = x_1;
        N++;
        res = x_null;
    }
}

int main() {
    double a = -3, b = 1, E = 0.0001;
    double res;
    vector<tuple<double, double, double, double>> bi;
    vector<tuple<double, double, double, double>> nt;
    vector<tuple<double, double, double, double>> smpl;

    ofstream outfile("result.txt");
    if (!outfile.is_open()) {
        cout << "При открытии файла произошла ошибка" << endl;
        return 1;
    }

    bisection(a, b, E, bi, res);
    outfile << "Метод половинного деления:" << endl;
    outfile << "N" << setw(20) << "a" << setw(20) << "b" << setw(20) << "b - a" << endl;
    for (tuple<double, double, double, double> i : bi) {
        outfile << get<0>(i) << setw(20) << get<1>(i) << setw(20) << get<2>(i) << setw(20) << get<3>(i) << endl;
    }
    outfile << endl << "Корень: " << res << endl << "---------------------------------------------------------------"<<endl;
    double x_null = -2;
    Newton(x_null, E, nt, res);
    outfile << "Метод Ньютона:" << endl;
    outfile << "N" << setw(20) << "x_null" << setw(20) << "x_1" << setw(20) << "x_1 - x_null" << endl;
    for (tuple<double, double, double, double> i : nt) {
        outfile << get<0>(i) << setw(20) << get<1>(i) << setw(20) << get<2>(i) << setw(20) << get<3>(i) << endl;
    }
    outfile << endl << "Корень: " << res << endl << "---------------------------------------------------------------"<<endl; 
    simple(x_null, E, smpl, res);
    outfile << "Метод простых итераций:" << endl;
    outfile << "N" << setw(20) << "x_null" << setw(20) << "x_1" << setw(20) << "x_1 - x_null" << endl;
    for (tuple<double, double, double, double> i : smpl) {
        outfile << get<0>(i) << setw(20) << get<1>(i) << setw(20) << get<2>(i) << setw(20) << get<3>(i) << endl;
    }
    outfile << endl << "Корень: " << res << endl << "---------------------------------------------------------------"<<endl;
}
