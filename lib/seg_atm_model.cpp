#include <cmath>
#include "seg_atm_model.h"

double SegAtmModel::N_h(double h, double N_s, double h_s, double N1 = 318)
{
    if (h_s <= h <= (h_s + 1000))
        {
            double delta_N = (0 - 0.00732) * std::exp(0.005577 * N_s);
            return(N_s + (h - h_s) * delta_N);
        }
        else if (h_s + 1000 <= h <= 9000)
        {
            double H = (8000 - h_s) / std::log(N1/105);
            return(N1 * std::exp(-(h - h_s - 1000)/H));
        }
        else if (h > 9000)
        {
            return(105 * std::exp(-(h - 9000)/7023));
        }
}

