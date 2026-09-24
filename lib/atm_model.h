#ifndef ATM_MODEL_H
#define ATM_MODEL_H

class AtmModel
{
   
    public:

    virtual ~AtmModel() = default;

    // Get N(h) - refractive index depending on height
    // SRC : (2.27) - (2.30) from citation
    // N_h : refractive index, dimensionless quantity
    // h : studied height, m
    // N_s : refractive index at the Earth's surface, dimensionless quantity
    // h_s : height of the target above the surface of the spherical Earth, m
    // N1 : refractive index at a height of 1 km above the Earth's surface, dimensionless quantity

    virtual double N_h(double h, double N_s, double h_s, double N1 = 318); 
};


#endif // ATM_MODEL_H