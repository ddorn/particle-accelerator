//
// Created by Gabin on 18.03.2019.
//

#include "..\header\Element.h"
#include "..\header\StraightElement.h"
#include "..\header\CurvedElement.h"
#include <iostream>
using namespace std;
using namespace constants;

/* Ne compile plus car le prototype des particules a changé :
 * il faut maintenant donner un pointeur vers un élément à la
 * création de la particule.
 * */

int main(){
    Particle particleIn(1, 1, Vector3D(0.3, 0.1, 0.15), Vector3D(0,0,0));
    Particle particleOut(1, 1, Vector3D(1.1, 0.12, 0.1), Vector3D(0,0,0));
    Particle particleCollide(1, 1, Vector3D(0.8, 0.45, 0.3), Vector3D(0,0,0));
    StraightElement element(Vector3D(0,0,0), Vector3D(1,0,0), 0.5, nullptr);
    cout << element << endl;
    cout << "Creation of particuleIn :" << endl << particleIn;
    if(element.isOut(particleIn.position())){
        cout << "particuleIn is in the next element." << endl;
    } else{
        cout << "particuleIn is in the element." << endl;
    }
    cout << "Creation of particuleOut :" << endl << particleOut;
    if(element.isOut(particleOut.position())){
        cout << "particuleOut is in the next element." << endl;
    } else{
        cout << "particuleOut is in the element." << endl;
    }

    cout << "Creation of particuleCollide :" << endl << particleCollide;
    if(element.collideBorder(particleIn.position())){
        cout << "particuleIn collided with the border." << endl;
    } else {
        cout << "particuleIn didn't collide with the border." << endl;
    }
    if(element.collideBorder(particleCollide.position())){
        cout << "particuleCollide collided with the border." << endl;
    } else {
        cout << "particuleCollide didn't collide with the border." << endl;
    }


    return 0;
}
