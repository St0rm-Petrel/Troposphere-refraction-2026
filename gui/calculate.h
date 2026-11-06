#include "refraction_model.h"
#include "atm_model.h"
#ifndef CALCULATE_H
#define CALCULATE_H

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
