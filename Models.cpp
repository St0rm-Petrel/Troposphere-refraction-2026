#include <iostream>
#include <cmath>
using namespace std;

class RefractionModel {};

class RefractionModelNoCurvature : public RefractionModel {
public:
    double a;
    double b;
    // a, b - основания трапеции
    double c;
    // c - наклонная сторона трапеции
    double phi;
    // phi - угол между c и d (между наклонной стороной и землёй)
    double d;
    // d - высота трапеции (расстояние по земле)

    RefractionModelNoCurvature(double _a, double _b, double _c, double _phi) {
        a = _a;
        b = _b;
        c = _c;
        phi = _phi;
        d = count_d();
    }

    double count_d() {
        return cos(phi) * c;
    }
};

class RefractionModelYesCurvature : public RefractionModel {
public:
    double k;
    double psi_d;
    double psi_g;
    double h_a;
    double h_s;
    double R;
    double R_e = 6371; // радиус Земли в км
    double phi_e;      // угол
    double d;          // искомая дуга

    RefractionModelYesCurvature(double _k, double _h_a, double _h_s, double _R) {
        k = _k;
        h_a = _h_a;
        h_s = _h_s;
        R = _R;
        d = count_d();
    }

    double count_sin_psi_d() {
        double sin_psi_d = (h_a - h_s) / R * (1 - (h_a - h_s) / (2 * (k * R_e + h_a)))
                         + R / (2 * (k * R_e + h_a));
        return sin_psi_d;
    }

    double count_sin_psi_g() {
        double sin_psi_g = (h_a - h_s) / R * (1 - (h_a - h_s) / (2 * (k * R_e + h_s)))
                         - R / (2 * (k * R_e + h_s));
        return sin_psi_g;
    }

    double count_d() {
        double sin_psi_d = count_sin_psi_d();
        double sin_psi_g = count_sin_psi_g();
        psi_d = asin(sin_psi_d);
        psi_g = asin(sin_psi_g);
        phi_e = psi_d - psi_g;
        d = R_e * phi_e;
        return d;
    }

    double get_k() {
        return k;
    }
};

class RefractionModelK43 : public RefractionModelYesCurvature {
public:
    RefractionModelK43(double _h_a, double _h_s, double _R)
        : RefractionModelYesCurvature(4.0 / 3.0, _h_a, _h_s, _R) {}
};

class RefractionModelK1 : public RefractionModelYesCurvature {
public:
    RefractionModelK1(double _h_a, double _h_s, double _R)
        : RefractionModelYesCurvature(1.0, _h_a, _h_s, _R) {}
};

int main() {
    //RefractionModelK43 m43(200.0, 200.0, 10.770);
    //RefractionModelK1  m1 (200.0, 200.0, 10.770);
    RefractionModelK1  m1 (1274.0, 1274.0, 2.1 * 1274.0);

    //cout << "k43 = " << m43.get_k() << ", d = " << m43.count_d() << endl;
    cout << "k1  = " << m1.get_k()  << ", d = " << m1.count_d()  << endl;



    return 0;
}
