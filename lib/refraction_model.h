#ifndef REFRACTION_MODEL_H
#define REFRACTION_MODEL_H

struct calculated_result{
    double d;
    double psi_d;
    double psi_g;
};

class RefractionModel {
    virtual calculated_result calculate(double h_a, double h_s, double R) = 0;
};

class RefractionModelNoCurvature : public RefractionModel {
public:
    calculated_result calculate(double h_a, double h_s, double R);
};

class RefractionModelYesCurvature : public RefractionModel {
protected:
    double k;
public:
    RefractionModelYesCurvature(double k);
    calculated_result calculate(double h_a, double h_s, double R) override;
};

class RefractionModelK43 : public RefractionModelYesCurvature {
public:
    RefractionModelK43();
};

class RefractionModelK1 : public RefractionModelYesCurvature {
public:
    RefractionModelK1();
};

#endif  // REFRACTION_MODEL_H
