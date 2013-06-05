#include "../core/particule.hpp"
#include "../core/vecteur.hpp"
#include "../core/materiau.hpp"
#include <iostream>
using std::cout;
using std::endl;

void tests_unitaires_particules() {

    Vecteur<2> vec2d1 = Vecteur<2>(-5.2, 8.0);
    Vecteur<2> vec2d2 = Vecteur<2>(1.0, -3.2);
    Vecteur<2> vec2d3 = Vecteur<2>(8.7, 1.1);
    Vecteur<2> vec2d4 = Vecteur<2>(6.1, 4.0);
    Vecteur<2> vec2d5 = Vecteur<2>(1.0, 1.0);
    Vecteur<2> vec2d6 = Vecteur<2>(9.7, 2.1);
    Vecteur<2> vec2d7 = Vecteur<2>(7.1, 5.0);
    Vecteur<3> vec3d1 = Vecteur<3>(2.0, 1.0, 3.0);
    Vecteur<3> vec3d2 = Vecteur<3>();
    Vecteur<3> vec3d3 = Vecteur<3>(-3.5, 5.0, 2.0);
    Vecteur<3> vec3d4 = Vecteur<3>(4.0, -2.2, 7.1);
    Vecteur<3> vec3d5 = Vecteur<3>(1.0, 1.0, 1.0);
    Vecteur<3> vec3d6 = Vecteur<3>(-2.5, 6.0, 3.0);
    Vecteur<3> vec3d7 = Vecteur<3>(5.0, -1.2, 8.1);

    Materiau<2>* mat = new Materiau<2>(EAU);

    cout << "1 − Particule en dimension 2 :" << endl;
    Particule<2> p1 = Particule<2>(0, vec2d1, vec2d2, 1000, 100000);
    
    cout << "->Création de la particule :";
    if (p1.getPosition() == vec2d1 && p1.getVitesse() == vec2d2
        && p1.getMasseVolumique() == 1000 && p1.getPression() == 100000)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Changement de position :";
    p1.setPosition(vec2d3);
    if (p1.getPosition() == vec2d3)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Changement de vitesse :";
    p1.setVitesse(vec2d4);
    if (p1.getVitesse() == vec2d4)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Changement d'acceleration :";
    p1.setAcceleration(vec2d4);
    if (p1.getAcceleration() == vec2d4)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Changement de masse volumique :";
    p1.setMasseVolumique(900);
    if (p1.getMasseVolumique() == 900)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Changement de pression :";
    p1.setPression(172633);
    if (p1.getPression() == 172633)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Incrément de position :";
    p1.incrPosition(vec2d5);
    if (p1.getPosition() == vec2d6)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Incrément de vitesse :";
    p1.incrVitesse(vec2d5);
    if (p1.getVitesse() == vec2d7)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    
    cout << "2 - Creation d'une particule en dimension 3 :" << endl;

    Materiau<3>* mat2 = new Materiau<3>(EAU);
    Particule<3> p2 = Particule<3>(0, vec3d1, vec3d2, 950, 101558);
    
    cout << "->Création de la particule : ";
    if (p2.getPosition() == vec3d1 && p2.getVitesse() == vec3d2
        && p2.getMasseVolumique() == 950 && p2.getPression() == 101558)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Changement de position :";
    p2.setPosition(vec3d3);
    if (p2.getPosition() == vec3d3)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Changement de vitesse :";
    p2.setVitesse(vec3d4);
    if (p2.getVitesse() == vec3d4)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Changement d'acceleration :";
    p2.setAcceleration(vec3d4);
    if (p2.getAcceleration() == vec3d4)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Changement de masse volumique :";
    p2.setMasseVolumique(917);
    if (p2.getMasseVolumique() == 917)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Changement de pression :";
    p2.setPression(101225);
    if (p2.getPression() == 101225)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Incrément de position :";
    p2.incrPosition(vec3d5);
    if (p2.getPosition() == vec3d6)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "->Incrément de vitesse :";
    p2.incrVitesse(vec3d5);
    if (p2.getVitesse() == vec3d7)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
 
    delete mat;
    delete mat2;   
}
