#include <iostream>
#include "../header/Vector3D.h"

using namespace std;

int main() {
    Vector3D nullVector(0,0,0);
    Vector3D a(1, 2, -0.1);
    Vector3D epsilonVector(.00000000001, -.00000000001,.00000000001);
    Vector3D b(2.6, 3.5, 4.1);
    Vector3D c(3.9, 3.8, 3.7);
    component scal(3);

    if(a == a){
        cout << a << " is equal to " << a << endl;
    } else {
        cout << a << " isn't equal to " << a << endl;

    }
    if(a == b){
        cout << a << " is equal to " << b << endl;
    } else {
        cout << a << " isn't equal to " << b << endl;

    }
    if(a == (a + epsilonVector)){
        cout << a << " is equal to " << a << " + " << epsilonVector << endl;
    } else {
        cout << a << " isn't equal to " << a << " + " << epsilonVector << endl;

    }

    cout << a << " + " << b << " = " << a + b << endl;
    cout <<  nullVector << " + " << a << " = " << nullVector + a << endl;
    cout << a << " - " << b << " = " << a - b << endl;
    cout << a << " - " << a << " = " << a - a << endl;
    cout << "The opposite of " << a << " is " << -a << endl;
    cout << a << " + (-" << -b << ") = " << a + (-b) << endl;
    cout << scal << " * " << a << " = " << scal * a << endl;
    cout << a << " * " << b << " = " << a * b << endl;
    cout << a << " ^ " << b << " = " << (a ^ b) << endl;
    cout << "||" << a << "||^2 = " << a.normSquared() << endl;
    cout << a << " * " << a << " = " << a * a << endl;
    cout << "||" << a << "|| = " << a.norm() << endl;
    cout << "||" << b << "||^2 = " << b.normSquared() << endl;
    cout << "The unit colinear vector of " << b << " is " << b.unit() << endl;
    cout << "The triple product of " << a << ", " << b << " and " << c << " has value " << a.tripleProduct(b, c) << endl;
    cout << "The triple product of " << b << ", " << a << " and " << c << " has value " << b.tripleProduct(a, c) << endl;
    cout << "The triple product of " << a << ", " << a << " and " << c << " has value " << a.tripleProduct(a, c) << endl;


    return 0;
}