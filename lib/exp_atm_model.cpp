#include <cmath>
#include "exp_atm_model.h"

double ExpAtmModel::H_b(double h, double N_s, double h_s)
    {
        if (h <= 10000)
        {
            return ((hb10 - h_s)/std::log(N_s / Nb10));
        }
        else if (h <= 15000)
        {
            return((hb15 - h_s)/std::log(N_s / Nb15));
        }
    }

double ExpAtmModel::N_h(double h, double N_s, double h_s, double N1 = 318)
{
    if (h <= 3000)
        {
            double delta_N = (0 - 0.00732) * std::exp(0.005577 * N_s);
            double He = (1000/std::log(N_s/(N_s + 1000 * delta_N)));
            return(N_s * std::exp(-(h - h_s)/He));
        }

        double Hb = H_b(h, N_s, h_s);
        return(N_s * std::exp(-(h - h_s)/Hb));
}


