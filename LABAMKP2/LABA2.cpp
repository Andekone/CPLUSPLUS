#include <iostream>
#include <cmath>
#include <fstream>

# define epsilon      1e-7 
# define PI           3.14159265358979323846 

using namespace std;

double Iteration_metod(double M, double e) {
    
    double E = M;
    double E_next;

    for (int i = 0; i <= 30; i++)                      //���� ��� ������ ���-�� �������� � �������� �������
    {
        E_next = e * sin(E) + M;                       // ��������� �������� E
        if (fabs(E_next - E) < epsilon)
            return E_next;

        E = E_next;                                    // ��������� ����� �������� E_next
    }
    return E_next;                                     // ��������� ����������� E
}

double Halfdivision_metod(double M, double e) {

    double f = M - 2.0;
    double u = M + 1.0;
    double c = (f + u) / 2.0;

    do { //�������� ����������
        if ((f - e * sin(f) - M) * (c - e * sin(c) - M) < 0) {
            u = c;
        }
        else {
            f = c;
        }

        // ��������� �������� ����� c
        c = (f + u) / 2.0;

    } while (fabs(u - f) < 2 * epsilon || fabs(c - e * sin(c) - M < epsilon));
    return c; // ���������� ��������� ��������
}

double GoldSection_metod(double M, double e) {

    double phi = (sqrt(5) + 1) / 2; // ������� �������

    double f = M - 3.0;
    double u = M + 3.0;
    double c, fc;

    do {
        // ��������� ����� ����� �� ������� �������� �������
        c = (f + (u - f) / phi);

        // ��������� �������� ������� � ����� c
        fc = (c - e * sin(c) - M);

        // ��������� ���� ��������� ������� � ��������� ������� ���������
        if ((f - e * sin(f) - M) * fc < 0)
            u = c;
        else
            f = c;

    } while ((fabs(u - f)) > epsilon && (fabs(c - e * sin(c) - M) > epsilon));

    return c; // ���������� ��������� ��������
}

double Newton_metod(double M, double e) {

    double E = M; // ��������� ����������� ��� E

    for (int i = 0; i < 40; i++)
    {
        double f = E - e * sin(E) - M; // �������� �������
        double f1 = 1 + e * cos(E); // �������� ����������� �������

        E -= f / f1; // ���������� ���������� ����������� ��� E

        if (abs(f) < epsilon) // �������� ������� ����������
        {
            break;
        }
    }

    return abs(E);
}


int main() {
    // ������ ������
    double r_a = 12739;                      // ������ ��������� � ��
    double r_p = 2639;                       // ������ ���������� � ��
    double T = 43200;                        // ������ ��������� �� � ��������

    double a = (r_a + r_p) / 2;              // ������� ������� � ��
    double e = ((r_a - r_p) / (2 * a));      // ������������� ������
    double n = 2 * PI / T;                   // ������� ������� �������� � ��/�

    // �������� ������ � �������
    ofstream data;
    data.open("Data_Halfdivision_metod.txt");

    // ���������� �������� ������� ������� � ����
    data << "t, c\t";
    data << "M(t), ���\t";
    data << "E(t), ���\t";
    data << "Theta(t), ���\t" << endl;

    // ��������� � ���������� �������� � ����
    for (int t = 0; t <= T; t++) {
        double M = n * t;                                                               // ������� ��������
        double E = Halfdivision_metod(M, e);                                               // ��������������� �������� - ����� ��������
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2;           // �������� ��������
        if (true_anomaly < 0) { true_anomaly += 2 * PI; }                               

        data << t << "\t" << M << "\t" << E << "\t" << true_anomaly << endl;
    }

    data.close();
    cout << "GOTOVO";

   /* ������ ��� �������� ������ � �������
    data.open("Data_Iteration_metod.txt");
    data.open("Data_Halfdivision_metod.txt");
    data.open("Data_GoldSection_metod.txt");
    data.open("Data_Newton_metod.txt");*/

    /* ������ ��� ���������� �
    double E = Iteration_metod(M, e)
    double E = Halfdivision_method(M, e)
    double E = GoldSection_metod(M, e)
    double E = Newton_metod(M, e)
    */


    return 0;
}
    