#include "../core/vecteur.hpp"

#include <cstdio>
#include <cstdlib>
#include <ostream>

using std::cout;
using std::endl;

void test_vecteur() {
    
    cout << "-- 1. Test de l'opérateur d'accession --" << endl ;
    cout << "Construction d'un vecteur a trois elements : " << endl ;
    Vecteur<3> v1 ;
    cout << "On va acceder a ces elements en utilisant les opérateurs () et <<" << endl ;
    cout << v1 << endl ;

    Vecteur<2> v2 ;
    v2 (1) = 1.5 ;
    v2 (2) = 0.5 ;
    Vecteur<3> v3 ;
    v3 (1) = 2.5 ;
    v3 (3) = -1 ;

    cout << "-- 2. Test des opérateurs standard --" << endl ;
    cout << "- Test de l'addition par un reel : on a v = " << endl ;
    cout << v3 << endl ;
    cout << "On ajoute 2 :" << endl ;
    Vecteur<3> v4 = 2.0 + v3 ;
    cout << v4 << endl ;

    cout << "On ajoute encore 2 en utilisant la commutativité de l'addition :" << endl ;
    Vecteur<3> v5 = v4 + 2.0 ;
    cout << v5 << endl ;
    cout << "On va diviser un réel (25.0) par le vecteur precedent :" << endl ;
    Vecteur<3> v6 = 25.0 / v5 ;
    cout << v6 << endl ;
    cout << endl ;

    cout << "- Test de l'addition de deux vecteurs :" << endl ;
    cout << "Test avec deux vecteurs de tailles egales :" << endl ;
    Vecteur<3> v7 = v1 + v3 ;
    cout << v7 << endl ;
    cout << "- Test du moins unaire :" << endl ;
    Vecteur<3> v8 = -v7 ;
    cout << v8 << endl ;

    cout << "-- 5. Test des operateurs +=, -=, *=, /= --" << endl ;
    cout << "On part de v1 :" << endl ;
    cout << v1 << endl ;
    cout << "Et de v3 :" << endl ;
    cout << v3 << endl ;
    cout << "On realise une addition de vecteur a vecteur. Resultat :" << endl ;
    v1 += v3 ;
    cout << v1 << endl ;

    cout << "-- 6. Test de l'operateur d'affectation = --" << endl ;
    cout << "On va affecter le vecteur :" << endl ;
    cout << v3 ;
    cout << "au vecteur :" << endl ;
    cout << v1 ;
    cout << "Le resultat :" << endl ;
    v1 = v3 ;
    cout << v1 << endl ;
    cout << endl ;

    cout << "Comparons les membres gauche et droit de l'affectation precedente" << endl ;
    if (v1 == v3) {
	cout << "Ils sont bien egaux" << endl ;
    } else {
	cout << "Erreur : non egalite des vecteurs" << endl ;
	exit (-1) ;
    }   

    cout << "-- 7. Test du calcul de la norme --" << endl ;
    cout << v2 << endl;
    cout << v2.norme() << endl;

    cout << v3 << endl;
    cout << v3.norme() << endl;
}
