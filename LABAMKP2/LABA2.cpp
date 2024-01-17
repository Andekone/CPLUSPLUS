#include <iostream>
#include <cmath>
#include <fstream>

# define epsilon      1e-7 
# define PI           3.14159265358979323846 

using namespace std;

double Iteration_metod(double M, double e) {
    
    double E = M;
    double E_next;

    for (int i = 0; i <= 30; i++)                      //цикл для поиска кол-ва действий с вводными данными
    {
        E_next = e * sin(E) + M;                       // Обновляем значение E
        if (fabs(E_next - E) < epsilon)
            return E_next;

        E = E_next;                                    // Вычисляем новое значение E_next
    }
    return E_next;                                     // найденное приближение E
}

double Halfdivision_metod(double M, double e) {

    double f = M - 2.0;
    double u = M + 1.0;
    double c = (f + u) / 2.0;

    do { //точность вычислений
        if ((f - e * sin(f) - M) * (c - e * sin(c) - M) < 0) {
            u = c;
        }
        else {
            f = c;
        }

        // Обновляем значение точки c
        c = (f + u) / 2.0;

    } while (fabs(u - f) < 2 * epsilon || fabs(c - e * sin(c) - M < epsilon));
    return c; // Возвращаем найденное значение
}

double GoldSection_metod(double M, double e) {

    double phi = (sqrt(5) + 1) / 2; // Золотое сечение

    double f = M - 3.0;
    double u = M + 3.0;
    double c, fc;

    do {
        // Вычисляем новую точку по формуле золотого сечения
        c = (f + (u - f) / phi);

        // Вычисляем значение функции в точке c
        fc = (c - e * sin(c) - M);

        // Проверяем знак изменения функции и обновляем границы интервала
        if ((f - e * sin(f) - M) * fc < 0)
            u = c;
        else
            f = c;

    } while ((fabs(u - f)) > epsilon && (fabs(c - e * sin(c) - M) > epsilon));

    return c; // Возвращаем найденное значение
}

double Newton_metod(double M, double e) {

    double E = M; // Начальное приближение для E

    for (int i = 0; i < 40; i++)
    {
        double f = E - e * sin(E) - M; // Значение функции
        double f1 = 1 + e * cos(E); // Значение производной функции

        E -= f / f1; // Вычисление следующего приближения для E

        if (abs(f) < epsilon) // Проверка условия сходимости
        {
            break;
        }
    }

    return abs(E);
}


int main() {
    // задаем орбиту
    double r_a = 12739;                      // радиус апоцентра в км
    double r_p = 2639;                       // радиус перицентра в км
    double T = 43200;                        // период обращения КА в секундах

    double a = (r_a + r_p) / 2;              // большая полуось в км
    double e = ((r_a - r_p) / (2 * a));      // эсцентриситет орбиты
    double n = 2 * PI / T;                   // средняя угловая скорость в км/с

    // Создание файлов с данными
    ofstream data;
    data.open("Data_Halfdivision_metod.txt");

    // Записываем названия искомых величин в файл
    data << "t, c\t";
    data << "M(t), рад\t";
    data << "E(t), рад\t";
    data << "Theta(t), рад\t" << endl;

    // Вычисляем и записываем значения в файл
    for (int t = 0; t <= T; t++) {
        double M = n * t;                                                               // Средняя аномалия
        double E = Halfdivision_metod(M, e);                                               // Эксцентрическая аномалия - метод итераций
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2;           // Истинная аномалия
        if (true_anomaly < 0) { true_anomaly += 2 * PI; }                               

        data << t << "\t" << M << "\t" << E << "\t" << true_anomaly << endl;
    }

    data.close();
    cout << "GOTOVO";

   /* шаблон для создания файлов с данными
    data.open("Data_Iteration_metod.txt");
    data.open("Data_Halfdivision_metod.txt");
    data.open("Data_GoldSection_metod.txt");
    data.open("Data_Newton_metod.txt");*/

    /* шаблон для вычисления Е
    double E = Iteration_metod(M, e)
    double E = Halfdivision_method(M, e)
    double E = GoldSection_metod(M, e)
    double E = Newton_metod(M, e)
    */


    return 0;
}
    