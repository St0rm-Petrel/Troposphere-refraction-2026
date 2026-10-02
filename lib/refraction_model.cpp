#include "refraction_model.h"
#include <cmath>

using namespace std;

calculated_result RefractionModelNoCurvature::calculate(double h_a, double h_s, double R) {
    double d2 = R*R - pow(h_s - h_a, 2);
    double d = pow(d2, 0.5);
    calculated_result answer;
    answer.d = d;
    answer.psi_d = -1;
    answer.psi_g = -1;
    return answer;
}

RefractionModelYesCurvature::RefractionModelYesCurvature(double k) : k(k) {}

calculated_result RefractionModelYesCurvature::calculate(double h_a, double h_s, double R) {
    // here we use this->k — k of this object
    double sin_psi_d = (h_a - h_s) / R * (1 - (h_a - h_s) / (2 * (k * 6371 + h_a)))
                     + R / (2 * (k * 6371 + h_a));
    double sin_psi_g = (h_a - h_s) / R * (1 - (h_a - h_s) / (2 * (k * 6371 + h_s)))
                     - R / (2 * (k * 6371 + h_s));
    double psi_d = asin(sin_psi_d);
    double psi_g = asin(sin_psi_g);
    calculated_result answer;
    answer.d = 6371.0 * (psi_d - psi_g);
    answer.psi_d = psi_d;
    answer.psi_g = psi_g;
    return answer;
}

RefractionModelK43::RefractionModelK43() : RefractionModelYesCurvature(4.0 / 3.0) {}
RefractionModelK1::RefractionModelK1()   : RefractionModelYesCurvature(1.0)       {}
