#include "calculate.h"
#include "refractionselection.h"

Calculate::Calculate()
{
}

CalculationResult Calculate::calculate_direct(double h_a, double h_s, double R,
                                              RefractionModel *refr_model, AtmModel *atm_model)
{

    CalculatedResult res = refr_model->calculate(h_a, h_s, R);

    CalculationResult result;
    result.d = res.d;
    result.psi_d = res.psi_d;
    result.psi_g = res.psi_g;

    return result;
}
