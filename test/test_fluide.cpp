#include "../core/particule.hpp"
#include "../core/vecteur.hpp"
#include "../core/materiau.hpp"
#include "../core/fluide.hpp"
#include <iostream>
using std::cout;
using std::endl;

void tests_unitaires_fluide() {

    Vecteur<2> vec2d1 = Vecteur<2>(5.0, 8.0);
    Vecteur<2> vec2d2 = Vecteur<2>(1.0, 3.0);
    Particule<2> * p1 = new Particule<2>(vec2d1, vec2d2, 1000, 100000);
    Particule<2> * p3 = new Particule<2>(vec2d1, vec2d2, 1000, 100000);
    Materiau<2> mateau2d = Materiau<2>(EAU);
    
    Vecteur<3> vec3d1 = Vecteur<3>(2.0, 1.0, 3.0);
    Vecteur<3> vec3d2 = Vecteur<3>();
    Particule<3> * p2 = new Particule<3>(vec3d1, vec3d2, 950, 101558);
    Particule<3> * p4 = new Particule<3>(vec3d1, vec3d2, 950, 101558);
    Materiau<3> mateau3d = Materiau<3>(EAU);


    cout << "1 − Creation d'un fluide 2D vide :" << endl;
    Fluide<2> f1 = Fluide<2>(&mateau2d);
    f1.affiche();
    
    cout << "->Ajout d'une particule :" << endl;
    f1.ajouteParticule(p1);
    f1.affiche();
    
    cout << "->Mise a jour de la pression et de la masse volumique :" << endl;
    f1.majDensitePression();
    f1.affiche();
    
    cout << "->Mise a jour de la position et de la vitesse :" << endl;
    f1.majPositionVitesse();
    f1.affiche();


    cout << "2 − Creation d'un fluide 2D carré :" << endl;
    int tab2d[2] = {3, 3};
    Fluide<2> f2 = Fluide<2>(&mateau2d, tab2d, 1.0);
    f2.affiche();
    
    cout << "->Ajout d'une particule :" << endl;
    f2.ajouteParticule(p3);
    f2.affiche();
    
    cout << "->Mise a jour de la pression et de la masse volumique :" << endl;
    f2.majDensitePression();
    f2.affiche();
    
    cout << "->Mise a jour de la position et de la vitesse :" << endl;
    f2.majPositionVitesse();
    f2.affiche();
    
    
    cout << "3 − Creation d'un fluide 3D vide :" << endl;
    Fluide<3> f3 = Fluide<3>(&mateau3d);
    f3.affiche();
    
    cout << "->Ajout d'une particule :" << endl;
    f3.ajouteParticule(p2);
    f3.affiche();
    
    cout << "->Mise a jour de la pression et de la masse volumique :" << endl;
    f3.majDensitePression();
    f3.affiche();
    
    cout << "->Mise a jour de la position et de la vitesse :" << endl;
    f3.majPositionVitesse();
    f3.affiche();


    cout << "4 − Creation d'un fluide 3D carré :" << endl;
    int tab3d[3] = {3, 3, 3};
    Fluide<3> f4 = Fluide<3>(&mateau3d, tab3d, 1.0, 900.0, 100000.0);
    f4.affiche();
    
    cout << "->Ajout d'une particule :" << endl;
    f4.ajouteParticule(p4);
    f4.affiche();
    
    cout << "->Mise a jour de la pression et de la masse volumique :" << endl;
    f4.majDensitePression();
    f4.affiche();
    
    cout << "->Mise a jour de la position et de la vitesse :" << endl;
    f4.majPositionVitesse();
    f4.affiche();

}
