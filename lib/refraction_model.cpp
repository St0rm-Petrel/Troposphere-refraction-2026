#include "refraction_model.h"
#include <cmath>

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

void RefractionModelWithCurvature::setK(double k) {
    this->k = k;
}

CalculatedResult RefractionModelWithCurvature::calculate(double h_a, double h_s, double R) {
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

RefractionModelK43::RefractionModelK43() { setK(4.0 / 3.0); }
RefractionModelK1::RefractionModelK1()   { setK(1.0);        }