#include "test_vecteur.cpp"
#include "test_particules.cpp"
#include "test_materiau.cpp"
#include "test_fluide.cpp"
#include "test_noyauLissage.cpp"
#include "test_map.cpp"
#include "test_premier.cpp"
#include "test_performances_premier.cpp"
#include "test_voisins.cpp"
#include "test_metaballs.cpp"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    cout << "***** Test vecteur : *****" << endl;
    test_vecteur();
    
    cout << endl << endl;
    cout << "***** Test particules : *****" << endl;
    tests_unitaires_particules();

    cout << endl << endl;
    cout << "***** Test materiau : *****" << endl;
    test_materiau();
 
    cout << endl << endl;
    cout << "***** Test Fluide : *****" << endl;
    tests_unitaires_fluide();

    cout << endl << endl;
    cout << "***** Test noyauLissage : *****" << endl;
    test_noyauLissage();    

    cout << endl << endl;
    cout << "***** Test premier : *****" << endl;
    test_premier();    

    cout << endl << endl;
    cout << "***** Test performances_premier : *****" << endl;
    test_performances_premier();    

    cout << endl << endl;
    cout << "***** Test Map : *****" << endl;
    test_map();

    cout << endl << endl;
    cout << "***** Test voisins : *****" << endl;
    test_voisins();

    cout << endl << endl;
    cout << "***** Test metaballs : *****" << endl;
    test_metaballs();

    return 0;
}
