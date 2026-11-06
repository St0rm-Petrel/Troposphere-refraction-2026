#include "calculate.h"
#include "refractionselection.h"

Calculate::Calculate()
{
}

CalculatedResult Calculate::calculate_direct(double h_a, double h_s, double R,
                                              RefractionModel *refr_model, AtmModel *atm_model)
{

    CalculatedResult result = refr_model->calculate(h_a, h_s, R);
    return result;
}
