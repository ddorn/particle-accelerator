//
// Created by diego on 3/17/19.
//

#include "../header/Accelerator.h"
#include "../header/constants.h"
using namespace std;
using namespace constants;

int main() {
    Accelerator a;
    a.add(Particle(M_PROTON, PROTON_CHARGE, Vector3D(), Vector3D(0.8, 0, 0), nullptr));
    cout << a;
    auto p = a.Particles().front();
    p.evolve(1);
        cout << a;

    return 0;
}