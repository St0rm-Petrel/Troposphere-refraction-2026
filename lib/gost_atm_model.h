#ifndef GOST_ATM_MODEL_H
#define GOST_ATM_MODEL_H

class GOSTAtmModel {
public:
  // Get N(h) - refractive index depending on height according to GOST
  // SRC : (2.23) - (2.24) from citation
  // h : studied height, m
  // ptr_P : pointer to the array P(h), mbar
  // ptr_T : pointer to the array T(h), K
  double N_h(double h, double *ptr_P, double *ptr_T);
};

#endif // GOST_ATM_MODEL_H