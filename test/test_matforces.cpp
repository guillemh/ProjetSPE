#include "../core/matriceForces.hpp"

void test_matforces() {

    cout << "Constructeur avec nombre particules" << endl;
    MatriceForces<3> m0 = MatriceForces<3>(5);
    cout << "Accès au premier élément" << endl;
    cout << m0(1,2) << endl;
    cout << m0(2,1) << endl;
    
    cout << "Constructeur par défaut" << endl;
    MatriceForces<3> m1;
    cout << "Affectation" << endl;
    m1 = MatriceForces<3>(5);
    cout << "Affichage" << endl;
    m1.afficher();

    cout << "Remplissage" << endl;
    MatriceForces<3> m2 = MatriceForces<3>(3);
    m2(1,2) = Vecteur<3>(1);
    m2(1,3) = Vecteur<3>(2);
    m2(2,3) = Vecteur<3>(3);
    m2.afficher();
    cout << "ReRemplissage en échangeant les indices" << endl;
    m2(2,1) = Vecteur<3>(1);
    m2(3,1) = Vecteur<3>(2);
    m2(3,2) = Vecteur<3>(3);
    m2.afficher();

}
