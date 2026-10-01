#include <iostream>
#include "models.h"

using namespace std;

int main() {
    RefractionModelK1  m1;
    RefractionModelK43 m43;

    cout << "k1  = " << m1.count_d(1274.0, 1274.0, 2.1 * 1274.0)  << "\n";
    std::cout << "k43 = " << m43.count_d(200.0, 200.0, 10.770)          << "\n";
    return 0;
}
