#include "../core/noyauLissage.hpp"

#include <cstdio>
#include <cstdlib>
#include <ostream>
#include <assert.h>

using std::cout;
using std::endl;

void test_noyauLissage() {
    cout << "- Lissage par défaut pour noyau par défaut : ";
    NoyauLissageDefaut<3> w = NoyauLissageDefaut<3>(5);
    Vecteur<3> r(1.5);
    double res1 = w.defaut(r);
    if ((res1 <= 0.0049) && (res1 >= 0.0048))
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Lissage gradient pour noyau par défaut : ";
    Vecteur<3>  res2 = w.gradient(r);
    if ((res2(1) <= -0.0024) && (res2(1) >= -0.0025))
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

        
    cout << "- Lissage laplacien pour noyau par défaut : ";
    double res3 = w.laplacien(r);
    if ((res3 <= -0.0024) && (res3 >= -0.0025))
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Lissage par défaut pour noyau pression : ";
    NoyauLissagePression<3> w2 = NoyauLissagePression<3>(5);
    double res4 = w2.defaut(r);
    if ((res4 <= 0.0043) && (res4 >= 0.0042))
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Lissage gradient pour noyau pression : ";
    Vecteur<3> res5 = w2.gradient(r);
    if ((res5(1) <= -0.003) && (res5(1) >= -0.0031))
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
        
    cout << "- Lissage laplacien pour noyau pression : ";
    double res6 = w2.laplacien(r);
    if ((res6 <= 0.00034) && (res6 >= 0.00033))
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

        
    cout << "- Lissage par defaut pour noyau viscosite : ";
    NoyauLissageViscosite<3> w3 = NoyauLissageViscosite<3>(5);
    double res7 = w3.defaut(r);
    if ((res7 <= 0.0031) && (res7 >= 0.0030))
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Lissage laplacien pour noyau pression : ";
    Vecteur<3> res8 = w3.gradient(r);
    if ((res8(1) <= -0.0026) && (res8(1) >= -0.0027))
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;

    cout << "- Lissage laplacien pour noyau pression : ";
    double res9 = w3.laplacien(r);
    if ((res9 <= 0.0023) && (res9 >= 0.0022))
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
        
}
