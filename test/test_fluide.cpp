#include "../core/particule.hpp"
#include "../core/vecteur.hpp"
#include "../core/materiau.hpp"
#include "../core/fluide.hpp"
#include <iostream>
using std::cout;
using std::endl;

void tests_unitaires_fluide() {

    cout << "## Rq : ce test ne peut pas vérifier les résultats mais ##" << endl
         << "## seulement la bonne exécution (décommenter affiche()) ##" << endl;

    Materiau<2> mateau2d = Materiau<2>(EAU);
    Vecteur<2> vec2d1 = Vecteur<2>(5.0, 8.0);
    Vecteur<2> vec2d2 = Vecteur<2>(1.0, 3.0);
    Particule<2> * p1 = new Particule<2>(vec2d1, vec2d2, 1000, 100000);
    Particule<2> * p3 = new Particule<2>(vec2d1, vec2d2, 1000, 100000);
    
    Materiau<3> mateau3d = Materiau<3>(EAU);
    Vecteur<3> vec3d1 = Vecteur<3>(2.0, 1.0, 3.0);
    Vecteur<3> vec3d2 = Vecteur<3>();
    Particule<3> * p2 = new Particule<3>(vec3d1, vec3d2, 950, 101558);
    Particule<3> * p4 = new Particule<3>(vec3d1, vec3d2, 950, 101558);


    cout << "1 − Creation d'un fluide 2D vide : ";
    Fluide<2> f1 = Fluide<2>(&mateau2d);
    cout<<"OK"<<endl;
    //f1.affiche();
    
    cout << "->Ajout d'une particule : ";
    f1.ajouteParticule(p1);
    cout<<"OK"<<endl;
    //f1.affiche();
    
    cout << "->Mise a jour de la pression et de la masse volumique : ";
    f1.majDensitePression();
    cout<<"OK"<<endl;
    //f1.affiche();
    
    cout << "->Mise a jour de la position et de la vitesse : ";
    f1.majPositionVitesse();
    cout<<"OK"<<endl;
    //f1.affiche();


    cout << "2 − Creation d'un fluide 2D carré : ";
    int tab2d[2] = {3, 3};
    Fluide<2> f2 = Fluide<2>(&mateau2d, tab2d, 1.0, mateau2d.getDensiteRepos(), mateau2d.getPression());
    cout<<"OK"<<endl;
    //f2.affiche();
    
    cout << "->Ajout d'une particule : ";
    f2.ajouteParticule(p3);
    cout<<"OK"<<endl;
    //f2.affiche();
    
    cout << "->Mise a jour de la pression et de la masse volumique : ";
    f2.majDensitePression();
    cout<<"OK"<<endl;
    //f2.affiche();
    
    cout << "->Mise a jour de la position et de la vitesse : ";
    f2.majPositionVitesse();
    cout<<"OK"<<endl;
    //f2.affiche();
    
    
    cout << "3 − Creation d'un fluide 3D vide : ";
    Fluide<3> f3 = Fluide<3>(&mateau3d);
    cout<<"OK"<<endl;
    //f3.affiche();
    
    cout << "->Ajout d'une particule : ";
    f3.ajouteParticule(p2);
    cout<<"OK"<<endl;
    //f3.affiche();
    
    cout << "->Mise a jour de la pression et de la masse volumique : ";
    f3.majDensitePression();
    cout<<"OK"<<endl;
    //f3.affiche();
    
    cout << "->Mise a jour de la position et de la vitesse : ";
    f3.majPositionVitesse();
    cout<<"OK"<<endl;
    //f3.affiche();


    cout << "4 − Creation d'un fluide 3D carré : ";
    int tab3d[3] = {3, 3, 3};
    Fluide<3> f4 = Fluide<3>(&mateau3d, tab3d, 1.0, 900.0, 100000.0);
    cout<<"OK"<<endl;
    //f4.affiche();
    
    cout << "->Ajout d'une particule : ";
    f4.ajouteParticule(p4);
    cout<<"OK"<<endl;
    //f4.affiche();
    
    cout << "->Mise a jour de la pression et de la masse volumique : ";
    f4.majDensitePression();
    cout<<"OK"<<endl;
    //f4.affiche();
    
    cout << "->Mise a jour de la position et de la vitesse : ";
    f4.majPositionVitesse();
    cout<<"OK"<<endl;
    //f4.affiche();

}
