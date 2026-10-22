#ifndef LINEAR_INTERPOLATION
#define LINEAR_INTERPOLATION

#include <stdexcept>
#include <vector>

class Linear_interpolation {
public:
  Linear_interpolation(std::vector<double> *hs, std::vector<double> *vs)
      : hs_(hs), vs_(vs) {
    if (hs->size() != vs->size())
      throw std::invalid_argument(
          "Size of height and values' vectors should be equal");
  };

  double operator()(double h);

private:
  std::vector<double> *hs_;
  std::vector<double> *vs_;
};

#endif // LINEAR_INTERPOLATION