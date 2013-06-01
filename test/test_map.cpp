#include "../core/fluide.hpp"
#include "../core/particule.hpp"
#include "../core/vecteur.hpp"
#include "../core/materiau.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::pair;

typedef multimap<int, Particule<3> > mymap;

void test_map() {

    Materiau<3> mateau3d = Materiau<3>(EAU);
    Vecteur<3> vec3d1 = Vecteur<3>(2.0, 1.0, 3.0);
    Vecteur<3> vec3d3 = Vecteur<3>(2.0, 2.0, 3.0);
    Vecteur<3> vec3d5 = Vecteur<3>(1.0, 4.0, 5.0);
    Vecteur<3> vec3d7 = Vecteur<3>(3.0, 2.0, 3.0);
    Vecteur<3> vec3d9 = Vecteur<3>(1.0, 4.0, 6.0);
    Vecteur<3> vec3d2 = Vecteur<3>();
    Particule<3> * p2 = new Particule<3>(vec3d1, vec3d2, 950, 101558);
    Particule<3> * p4 = new Particule<3>(vec3d3, vec3d2, 950, 101558);
    Particule<3> * p6 = new Particule<3>(vec3d5, vec3d2, 950, 101558);
    Particule<3> * p8 = new Particule<3>(vec3d7, vec3d2, 950, 101558);
    Particule<3> * p10 = new Particule<3>(vec3d9, vec3d2, 950, 101558);

    Fluide<3> f3 = Fluide<3>(&mateau3d);
    f3.ajouteParticule(p2);
    f3.ajouteParticule(p4);
    f3.ajouteParticule(p6);
    f3.ajouteParticule(p8);
    f3.ajouteParticule(p10);

    cout << endl;

    int hash;
    hash = f3.fonction_hashage(p2->getPosition());
    cout << "Clé insertion : " << hash << endl;
    f3.hash_voisins.insert(pair<int, Particule<3> >(hash, *p2));
    hash = f3.fonction_hashage(p4->getPosition());
    cout << "Clé insertion : " << hash << endl;
    f3.hash_voisins.insert(pair<int, Particule<3> >(hash, *p4));
    hash = f3.fonction_hashage(p6->getPosition());
    cout << "Clé insertion : " << hash << endl;
    f3.hash_voisins.insert(pair<int, Particule<3> >(hash, *p6));
    hash = f3.fonction_hashage(p8->getPosition());
    cout << "Clé insertion : " << hash << endl;
    f3.hash_voisins.insert(pair<int, Particule<3> >(hash, *p8));
    hash = f3.fonction_hashage(p10->getPosition());
    cout << "Clé insertion : " << hash << endl;
    f3.hash_voisins.insert(pair<int, Particule<3> >(hash, *p10));
}
