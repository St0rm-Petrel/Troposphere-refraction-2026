#ifndef REFRACTION_MODEL_H
#define REFRACTION_MODEL_H

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
protected:
    double k = 1.0;   // значение по умолчанию, чтобы не было мусора
public:
    RefractionModelWithCurvature() = default;   // конструктор без k
    void setK(double k);                        // ← вот он, метод
    double getK() const { return k; }           // полезно для проверок
    CalculatedResult calculate(double h_a, double h_s, double R) override;
};

class RefractionModelK43 : public RefractionModelWithCurvature {
public:
    RefractionModelK43();
};

class RefractionModelK1 : public RefractionModelWithCurvature {
public:
    RefractionModelK1();
};

#endif  // REFRACTION_MODEL_H