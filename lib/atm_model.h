#ifndef ATM_MODEL_H
#define ATM_MODEL_H

class AtmModel {

public:
  virtual ~AtmModel() = default;

  // Get N(h) - refractive index depending on height
  // SRC : (2.27) - (2.30) from citation
  virtual double N_h(double h);
};

#endif // ATM_MODEL_H