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

CalculatedResult RefractionModelWithCurvature::calculate(double h_a, double h_s, double R) {
    double k = K(h_a, h_s, R);
    double sin_psi_d = (h_a - h_s) / R * (1.0 - (h_a - h_s) / (2.0 * (k * R_e + h_a)))
                       + R / (2.0 * (k * R_e + h_a));
    double sin_psi_g = (h_a - h_s) / R * (1.0 - (h_a - h_s) / (2.0 * (k * R_e + h_s)))
                       - R / (2.0 * (k * R_e + h_s));
    double psi_d = asin(sin_psi_d);
    double psi_g = asin(sin_psi_g);
    CalculatedResult answer;
    answer.d = R_e * (psi_d - psi_g);
    answer.psi_d = psi_d;
    answer.psi_g = psi_g;
    return answer;
}

double RefractionModelK43::K(double h_a, double h_s, double R) {
    return 4.0 / 3.0;
}

double RefractionModelK1::K(double h_a, double h_s, double R) {
    return 1.0;
}


double RefractionModelAnaliticalType1::K(double h_a, double h_s, double R) {
    // Get values from atmosphere model
    double N_s = atmosphere.N_s();
    double H_b = atmosphere.H();
    // Get angle from simpler 4/3 model
    RefractionModelK43 simple_model;
    double psi_g = simple_model.calculate(h_a, h_s,  R).psi_d;

    // Calculate, 2.38
    double part_1 = pow(10, -6) * N_s * cos(psi_g) * R_e / H_b;
    double part_2 = (exp((h_a - h_s) / H_b) - part_1) / (1 - part_1);
    double part_3 = std::log(part_2);
    double part_4 = H_b / (h_a - h_s) * part_3;

    return part_4;
}

double RefractionModelAnaliticalType2::K(double h_a, double h_s, double R) {
    // Get values from atmosphere model
    double N_s = atmosphere.N_s();
    double H_b = atmosphere.H();
    // Get angle from simpler 4/3 model
    RefractionModelK43 simple_model;
    double psi_g = simple_model.calculate(h_a, h_s,  R).psi_d;

    // Calculate, 2.40
    double part_1 = exp((h_a - h_s) / H_b) - 1;
    double part_2 = ((h_a - h_s) / H_b) / part_1;
    double part_3 = pow(10, -6) * N_s * cos(psi_g) * R_e / H_b;
    double part_4 = 1 - part_3 * part_2;
    double part_5 = 1 / part_4;

    return part_5;
}
