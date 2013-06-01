#include "test_vecteur.cpp"
#include "test_particules.cpp"
#include "test_materiau.cpp"
#include "test_fluide.cpp"
#include "test_noyauLissage.cpp"
#include "test_premier.cpp"
#include "test_performances_premier.cpp"
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

    return 0;
}
