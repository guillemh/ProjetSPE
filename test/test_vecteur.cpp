#include "../core/vecteur.hpp"

#include <cstdio>
#include <cstdlib>
#include <ostream>

using std::cout;
using std::endl;

void test_vecteur() {
    
    cout << "-- 1. Test des opérateurs d'accession, d'affectation et de comparaison --" << endl;
    Vecteur<3> v1;
    v1(2);
    Vecteur<3> v2;
    Vecteur<3> v3;
    v3(1) = 2.5;
    v3(3) = -1;
    v2 = v3;
    
    Vecteur<3> vcomp = Vecteur<3>(2.5, 0, -1);
    if (v3 == vcomp && v3 != v1 && not (v3 == v1) && v2 == v3)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    

    cout << "-- 2. Test des opérateurs standards --" << endl;
    
    cout << "- Moins unaire : ";
    v3 = Vecteur<3>(-2.5, 0, 1);
    Vecteur<3> v4 = -v3;
    vcomp = Vecteur<3>(2.5, 0, -1);
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "- Addition par un reel : ";
    v3 = Vecteur<3>(2.5, 0, -1);
    v4 = v3 + 2.0;
    vcomp = Vecteur<3>(4.5, 2, 1);
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
        
    cout << "- Addition depuis un réel :";
    v3 = Vecteur<3>(2.5, 0, -1);
    v4 = 2.0 + v3;
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "- Soustraction par un reel : ";
    v3 = Vecteur<3>(2.5, 0, -1);
    v4 = v3 - 2.0;
    vcomp = Vecteur<3>(0.5, -2, -3);
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "- Soustraction depuis un réel :";
    v3 = Vecteur<3>(2.5, 0, -1);
    v4 = 2.0 - v3;
    vcomp = -vcomp;
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Multiplication par un réel : ";
    v3 = Vecteur<3>(7, 0, 10);
    v4 = v3 * 4;
    vcomp = Vecteur<3>(28, 0, 40);
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "- Multiplication depuis un réel : ";
    v3 = Vecteur<3>(2, 3, 6);
    v4 = 4 * v3;
    vcomp = Vecteur<3>(8, 12, 24);
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Division par un réel : ";
    v3 = Vecteur<3>(25, 0, 150);
    v4 = v3 / 25.0;
    vcomp = Vecteur<3>(1, 0, 6);
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "- Division depuis un réel : ";
    v3 = Vecteur<3>(2, 3, 6);
    v4 = 12 / v3;
    vcomp = Vecteur<3>(6, 4, 2);
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Addition de deux vecteurs :";
    v1 = Vecteur<3>(3.3, 2, 1.2);
    v3 = Vecteur<3>(4.2, 5.1, 0.3);
    vcomp = Vecteur<3>(7.5, 7.1, 1.5);
    v4 = v1 + v3;
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Soustraction de deux vecteurs :";
    v4 = v4 - v3;
    if (v4 == v1)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Multiplication de deux vecteurs :";
    v1 = Vecteur<3>(3, 2, 1);
    v3 = Vecteur<3>(4, 5, 0);
    vcomp = Vecteur<3>(12, 10, 0);
    v4 = v1 * v3;
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Division de deux vecteurs :";
    v1 = Vecteur<3>(33, 20, 1);
    v3 = Vecteur<3>(11, 10, 1);
    vcomp = Vecteur<3>(3, 2, 1);
    v4 = v1 / v3;
    if (v4 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Opérateur += :";
    v1 = Vecteur<3>(3.3, 2, 1.2);
    v3 = Vecteur<3>(-4.2, 5.1, 0.3);
    vcomp = Vecteur<3>(-0.9, 7.1, 1.5);
    v1 += v3;
    if (v1 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Opérateur -= :";
    v1 = Vecteur<3>(3.2, 2, 1.2);
    v3 = Vecteur<3>(4.1, 5.1, 0.2);
    vcomp = Vecteur<3>(-0.9, -3.1, 1);
    v1 -= v3;
    if (v1 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Opérateur *= :";
    v1 = Vecteur<3>(3, 2, 1);
    v3 = Vecteur<3>(4, 5, 0);
    vcomp = Vecteur<3>(12, 10, 0);
    v1 *= v3;
    if (v1 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Opérateur /= :";
    v1 = Vecteur<3>(33, 20, 1);
    v3 = Vecteur<3>(11, 10, 1);
    vcomp = Vecteur<3>(3, 2, 1);
    v1 /= v3;
    if (v1 == vcomp)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    

    cout << "-- 3. Test du calcul de la norme --" << endl;
    v1 = Vecteur<3>(4, 3, 0);
    if (v1.norme() == 5)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    

    cout << "-- 4. Test du calcul du produit scalaire --" << endl;
    v3 = Vecteur<3>(6.0, 12.3, 1.2);
    if (std::abs(v3.scalaire(v1) - 60.9) < 0.0000000001)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
}
