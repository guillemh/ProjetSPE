#include "../core/particule.hpp"
#include "../core/vecteur.hpp"
#include <iostream>
using std::cout;
using std::endl;

void tests_unitaires_particules() {

    Vecteur<2> vec2d1 = Vecteur<2>(5.0, 8.0);
    Vecteur<2> vec2d2 = Vecteur<2>(1.0, 3.0);
    Vecteur<3> vec3d1 = Vecteur<3>(2.0, 1.0, 3.0);
    Vecteur<3> vec3d2 = Vecteur<3>();


    cout << "Creation d'une particule en dimension 2 :" << endl;
    Particule<2> p1 = Particule<2>(vec2d1, vec2d2, 1000, 100000);
    cout<<p1<<endl;
    
    cout << "Creation d'une particule en dimension 3 :" << endl;
    Particule<3> p2 = Particule<3>(vec3d1, vec3d2, 950, 101558);
    cout<<p1<<endl;
    
}
