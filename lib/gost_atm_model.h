#ifndef GOST_ATM_MODEL_H
#define GOST_ATM_MODEL_H

class GOSTAtmModel {
public:
  // Get N(h) - refractive index depending on height according to GOST
  // SRC : (2.23) - (2.24) from citation
  // h - studied height, m
  // hs - pointer to vector of known heights, m
  // ptr_P - pointer to the vector P(h), mbar
  // ptr_T - pointer to the vector T(h), K
  double N_h(double h, std::vector<double> *hs, std::vector<double> *P,
             std::vector<double> *T);
};

#endif // GOST_ATM_MODEL_H