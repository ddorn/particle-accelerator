#include <iostream>
#include "../header/Vector3D.h"

using namespace std;

int main() {
    Vector3D nullVector;
    Vector3D a(1, 2, -0.1);
    Vector3D epsilonVector(1e-8, -1e-8,1e-8);
    Vector3D b(2.6, 3.5, 4.1);
    Vector3D c(3.9, 3.8, 3.7);
    Vector3D nice(5, 0, 5);
    Vector3D xAxis(1,0,0);
    Vector3D vertical(0, 0, 1);
    component scal(3);
    double pi(3.14159265358979323846);

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
    Vector3D::setPrecision(1e-7);
    cout << "Setting the precision at 1e-7 :" << endl;
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
    cout << "The unit colinear vector of " << b << " is " << ~b << endl;
    cout << "The triple product of " << a << ", " << b << " and " << c << " has value " << a.tripleProduct(b, c) << endl;
    cout << "The triple product of " << b << ", " << a << " and " << c << " has value " << b.tripleProduct(a, c) << endl;
    cout << "The triple product of " << a << ", " << a << " and " << c << " has value " << a.tripleProduct(a, c) << endl;
    cout << nice << " rotated by pi rad around the x axis is " << nice.rotate(xAxis, pi) << endl;
    cout << nice << " rotated by pi/3 rad around the vertical axis is " << nice.rotate(vertical, pi/3) << endl;
    cout << "The vector " << a << " divided by the scalar 0 is " << a / 0 << endl;
    return 0;
}