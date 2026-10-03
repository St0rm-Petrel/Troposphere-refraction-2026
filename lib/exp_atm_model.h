#ifndef EXP_ATM_MODEL_H
#define EXP_ATM_MODEL_H

#include "atm_model.h"

// SRC: (2.31) from citation:

constexpr double hb15 = 12192;
constexpr double Nb15 = 66.65;

// SRC: (2.32) from citation:   
constexpr double hb10 = 9144;
constexpr double Nb10 = 102.9;


class ExpAtmModel: public AtmModel
{
    public:

    double N_h(double h, double N_s, double h_s, double N1 = 318) override;

    // auxiliary function for finding the Hb value
    // SRC : (2.30) from citation

    double H_b(double h, double N_s, double h_s);
};

#endif //EXP_ATM_MODEL_H