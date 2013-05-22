//#include "test_particules.cpp"
#include "test_materiau.cpp"
#include "test_vecteur.cpp"
#include "test_noyauLissage.cpp"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    cout << "***** Test particules : *****" << endl;
    //tests_unitaires_particules();

    cout << "***** Test materiau : *****" << endl;
    //test_materiau();
    
    cout <<  "***** Test vecteur : *****" << endl;
    //test_vecteur();

    cout <<  "***** Test noyauLissage : *****" << endl;
    test_noyauLissage();    
}
