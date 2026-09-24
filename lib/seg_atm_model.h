#ifndef SEG_ATM_MODEL_H
#define SEG_ATM_MODEL_H
#include "atm_model.h"

class SegAtmModel: public AtmModel 
{
    public:

    double N_h(double h, double N_s, double h_s, double N1 = 318) override;
};



#endif // SEG_ATM_MODEL_H