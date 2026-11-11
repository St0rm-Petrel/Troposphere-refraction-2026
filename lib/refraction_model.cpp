#include "refraction_model.h"
#include <cmath>
#include <numbers>

using namespace std;

CalculatedResult RefractionModelWithoutCurvature::calculate(double h_a, double h_s, double R) {
    double d2 = R * R - pow(h_s - h_a, 2.0);
    double d = pow(d2, 0.5);
    CalculatedResult answer;
    answer.d = d;
    answer.psi_d = asin(abs(h_a - h_s) / R);
    answer.psi_g = answer.psi_d;
    return answer;
}

double RefractionModelWithCurvature::K(double h_a, double h_s, double R) {
    return this->k;
}

double RefractionModelK43::K(double h_a, double h_s, double R) {
    return 4.0 / 3.0;
}

double RefractionModelK1::K(double h_a, double h_s, double R) {
    return 1.0;
}

double RefractionModelAnaliticalType1::K(double h_a, double h_s, double R) {
    double part_1, part_2, part_3, part_4, part_5;
    double N_s, psi_g, H_b, h_b, N_b;
    N_s = 324.8;
    h_b = 12192.0;
    N_b = 66.65;
    H_b = (h_b - h_s) / std::log(N_s / N_b);
    double sin_psi_g = (h_a - h_s) / R * (1.0 - (h_a - h_s) / (2.0 * (k * 6371.0 + h_s)))
                     - R / (2.0 * (k * 6371.0 + h_s));
    psi_g = asin(sin_psi_g);

    part_1 = pow(10, -6) * N_s * cos(psi_g) * 6371.0 / H_b;
    part_2 = (pow(2.718, (h_a - h_s) / H_b) - part_1) / (1 - part_1);
    part_3 = std::log(part_1);
    part_4 = H_b / (h_a - h_s) * part_3;

    return part_4;
}

double RefractionModelAnaliticalType2::K(double h_a, double h_s, double R) {
    double part_1, part_2, part_3, part_4, part_5;
    double N_s, psi_g, H_b, h_b, N_b;
    N_s = 324.8;
    h_b = 12192.0;
    N_b = 66.65;
    H_b = (h_b - h_s) / std::log(N_s / N_b);
    double sin_psi_g = (h_a - h_s) / R * (1.0 - (h_a - h_s) / (2.0 * (k * 6371.0 + h_s)))
                     - R / (2.0 * (k * 6371.0 + h_s));
    psi_g = asin(sin_psi_g);

    part_1 = pow(2.718, (h_a - h_s) / H_b) - 1;
    part_2 = ((h_a - h_s) / H_b) / part_1;
    part_3 = pow(10, -6) * N_s * cos(psi_g) * 6371.0 / H_b;
    part_4 = 1 - part_3 * part_2;
    part_5 = 1 / part_4;

    return part_5;
}

CalculatedResult RefractionModelWithCurvature::calculate(double h_a, double h_s, double R) {
    k = K(h_a, h_s, R);
    double sin_psi_d = (h_a - h_s) / R * (1.0 - (h_a - h_s) / (2.0 * (k * 6371.0 + h_a)))
                     + R / (2.0 * (k * 6371.0 + h_a));
    double sin_psi_g = (h_a - h_s) / R * (1.0 - (h_a - h_s) / (2.0 * (k * 6371.0 + h_s)))
                     - R / (2.0 * (k * 6371.0 + h_s));
    double psi_d = asin(sin_psi_d);
    double psi_g = asin(sin_psi_g);
    CalculatedResult answer;
    answer.d = 6371.0 * (psi_d - psi_g);
    answer.psi_d = psi_d;
    answer.psi_g = psi_g;
    return answer;
}

CalculatedResult RefractionModelAnaliticalType1::calculate(double h_a, double h_s, double R) {
    k = K(h_a, h_s, R);
    double sin_psi_d = (h_a - h_s) / R * (1.0 - (h_a - h_s) / (2.0 * (k * 6371.0 + h_a)))
                     + R / (2.0 * (k * 6371.0 + h_a));
    double sin_psi_g = (h_a - h_s) / R * (1.0 - (h_a - h_s) / (2.0 * (k * 6371.0 + h_s)))
                     - R / (2.0 * (k * 6371.0 + h_s));
    double psi_d = asin(sin_psi_d);
    double psi_g = asin(sin_psi_g);
    CalculatedResult answer;
    answer.d = 6371.0 * (psi_d - psi_g);
    answer.psi_d = psi_d;
    answer.psi_g = psi_g;
    return answer;
}

CalculatedResult RefractionModelAnaliticalType2::calculate(double h_a, double h_s, double R) {
    k = K(h_a, h_s, R);
    double sin_psi_d = (h_a - h_s) / R * (1.0 - (h_a - h_s) / (2.0 * (k * 6371.0 + h_a)))
                     + R / (2.0 * (k * 6371.0 + h_a));
    double sin_psi_g = (h_a - h_s) / R * (1.0 - (h_a - h_s) / (2.0 * (k * 6371.0 + h_s)))
                     - R / (2.0 * (k * 6371.0 + h_s));
    double psi_d = asin(sin_psi_d);
    double psi_g = asin(sin_psi_g);
    CalculatedResult answer;
    answer.d = 6371.0 * (psi_d - psi_g);
    answer.psi_d = psi_d;
    answer.psi_g = psi_g;
    return answer;
}

RefractionModelK43::RefractionModelK43() {}
RefractionModelK1::RefractionModelK1()   {}
RefractionModelAnaliticalType1::RefractionModelAnaliticalType1() {}
RefractionModelAnaliticalType2::RefractionModelAnaliticalType2() {}