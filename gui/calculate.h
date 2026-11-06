#include "refraction_model.h"
#include "atm_model.h"
#ifndef CALCULATE_H
#define CALCULATE_H

struct CalculationResult
{
    double d;
    double psi_d;
    double psi_g;
};

class Calculate
{
public:
    Calculate();

    CalculationResult calculate_direct(
        double h_a,
        double h_s,
        double r,
        RefractionModel *refr_model,
        AtmModel *atm_model);
};

#endif // CALCULATE_H
