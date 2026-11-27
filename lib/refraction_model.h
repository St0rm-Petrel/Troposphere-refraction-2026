#ifndef REFRACTION_MODEL_H
#define REFRACTION_MODEL_H

#include<exp_atm_model.h>

struct CalculatedResult {
    double d;
    double psi_d;
    double psi_g;
};

class RefractionModel {
public:
    virtual CalculatedResult calculate(double h_a, double h_s, double R) = 0;
    virtual ~RefractionModel() = default;
};

class RefractionModelWithoutCurvature : public RefractionModel {
public:
    CalculatedResult calculate(double h_a, double h_s, double R) override;
};

class RefractionModelWithCurvature : public RefractionModel {
public:
    RefractionModelWithCurvature() = default;   // конструктор без k
    virtual double K(double h_a, double h_s, double R) = 0;
    CalculatedResult calculate(double h_a, double h_s, double R) override;

    static constexpr double R_e = 6378000;
};

class RefractionModelK43 : public RefractionModelWithCurvature {
public:
    RefractionModelK43() {};
    double K(double h_a, double h_s, double R) override;
};

class RefractionModelK1 : public RefractionModelWithCurvature {
public:
    RefractionModelK1() {};
    double K(double h_a, double h_s, double R) override;
};

/*
class RefractionModelAnaliticalType1: public RefractionModelWithCurvature {
public:
    RefractionModelAnaliticalType1(ExpAtmModel& atmosphere) : atmosphere(atmosphere) {};
    double K(double h_a, double h_s, double R) override;
private:
    ExpAtmModel& atmosphere;
};

class RefractionModelAnaliticalType2: public RefractionModelWithCurvature {
public:
    RefractionModelAnaliticalType2(ExpAtmModel& atmosphere) : atmosphere(atmosphere) {};
    double K(double h_a, double h_s, double R) override;
private:
    ExpAtmModel& atmosphere;
};
*/
#endif  // REFRACTION_MODEL_H
