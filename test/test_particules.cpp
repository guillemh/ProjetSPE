#include "../core/particule.hpp"
#include "../core/vecteur.hpp"
#include <iostream>
using std::cout;
using std::endl;

void tests_unitaires_particules() {

    Vecteur<2> vec2d1 = Vecteur<2>(5.0, 8.0);
    Vecteur<2> vec2d2 = Vecteur<2>(1.0, 3.0);
    Vecteur<2> vec2d3 = Vecteur<2>(8.0, 1.0);
    Vecteur<2> vec2d4 = Vecteur<2>(6.0, 4.0);
    Vecteur<2> vec2d5 = Vecteur<2>(1.0, 1.0);
    Vecteur<3> vec3d1 = Vecteur<3>(2.0, 1.0, 3.0);
    Vecteur<3> vec3d2 = Vecteur<3>();
    Vecteur<3> vec3d3 = Vecteur<3>(3.0, 5.0, 2.0);
    Vecteur<3> vec3d4 = Vecteur<3>(4.0, 2.0, 7.0);
    Vecteur<3> vec3d5 = Vecteur<3>(1.0, 1.0, 1.0);


    cout << "1 − Creation d'une particule en dimension 2 :" << endl;
    Particule<2> p1 = Particule<2>(vec2d1, vec2d2, 1000, 100000);
    cout<<p1<<endl;
    
    cout << "->Changement de position :" << endl;
    p1.setPosition(vec2d3);
    cout<<p1<<endl;
    
    cout << "->Changement de vitesse :" << endl;
    p1.setVitesse(vec2d4);
    cout<<p1<<endl;
    
    cout << "->Changement de masse volumique :" << endl;
    p1.setMasseVolumique(900);
    cout<<p1<<endl;
    
    cout << "->Changement de pression :" << endl;
    p1.setPression(172633);
    cout<<p1<<endl;
    
    cout << "->Incrément de position :" << endl;
    p1.incrPosition(vec2d5);
    cout<<p1<<endl;
    
    cout << "->Incrément de vitesse :" << endl;
    p1.incrVitesse(vec2d5);
    cout<<p1<<endl;
    
    
    cout << "2 - Creation d'une particule en dimension 3 :" << endl;
    Particule<3> p2 = Particule<3>(vec3d1, vec3d2, 950, 101558);
    cout<<p2<<endl;
    
    cout << "->Changement de position :" << endl;
    p2.setPosition(vec3d3);
    cout<<p2<<endl;
    
    cout << "->Changement de vitesse :" << endl;
    p2.setVitesse(vec3d4);
    cout<<p2<<endl;
    
    cout << "->Changement de masse volumique :" << endl;
    p2.setMasseVolumique(990);
    cout<<p2<<endl;
    
    cout << "->Changement de pression :" << endl;
    p2.setPression(117366);
    cout<<p2<<endl;
    
    cout << "->Incrément de position :" << endl;
    p2.incrPosition(vec3d5);
    cout<<p2<<endl;
    
    cout << "->Incrément de vitesse :" << endl;
    p2.incrVitesse(vec3d5);
    cout<<p2<<endl;
    
}
