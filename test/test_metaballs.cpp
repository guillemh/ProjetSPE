#include "../core/particule.hpp"
#include "../core/vecteur.hpp"
#include "../core/metaballs.hpp"
#include <iostream>
using std::cout;
using std::endl;

// La classe metaballs est une classe pour le rendu 3D
// Elle est donc principalement testee lors de multiples rendus
// Ici, nous allons tout de meme faire quelques tests unitaires
void test_metaballs() {

    Vecteur<3> vec0 = Vecteur<3>();
    Vecteur<3> vec1 = Vecteur<3>(-0.5, 0.1, 0.5);
    Vecteur<3> vec2 = Vecteur<3>(0.0, -0.2, 0.7);
    
    list<Particule<3> *> particules;
    Particule<3> * p1 = new Particule<3>(vec1, vec0, 1000, 100000);
    Particule<3> * p2 = new Particule<3>(vec2, vec0, 1000, 100000);
    particules.push_back(p1);
    particules.push_back(p2);
    
    Metaballs ball = Metaballs(vec0, 0.01, 0.04);
    
    cout << "Coloration : ";
    ball.coloration(particules);
    cout << "OK" << endl;
    
    cout << "Association de point : ";
    Vecteur<3> test1 = ball.associerPoint(vec0, 0.05, 3);
    Vecteur<3> test2 = ball.associerPoint(vec1, 0.1, 10);
    Vecteur<3> comp1 = Vecteur<3>(0.025, 0.0, 0.0);
    Vecteur<3> comp2 = Vecteur<3>(-0.4, 0.2, 0.55);
    if (test1 == comp1 && test2 == comp2)
        cout << "OK" << endl;
    else
        cout << "ERREUR !" << endl;
    
}
