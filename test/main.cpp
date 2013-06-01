#include "test_vecteur.cpp"
#include "test_particules.cpp"
#include "test_materiau.cpp"
#include "test_fluide.cpp"
#include "test_noyauLissage.cpp"
#include "test_map.cpp"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    // cout << "***** Test vecteur : *****" << endl;
    // test_vecteur();
    
    // cout << endl << endl;
    // cout << "***** Test particules : *****" << endl;
    // tests_unitaires_particules();

    // cout << endl << endl;
    // cout << "***** Test materiau : *****" << endl;
    // test_materiau();
 
    // cout << endl << endl;
    // cout << "***** Test Fluide : *****" << endl;
    // tests_unitaires_fluide();

    // cout << endl << endl;
    // cout << "***** Test noyauLissage : *****" << endl;
    // test_noyauLissage();    

    cout << endl << endl;
    cout << "***** Test Map : *****" << endl;
    test_map();    
}
