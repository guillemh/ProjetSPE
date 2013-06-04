#include "../core/particule.hpp"
#include "../core/vecteur.hpp"
#include "../core/materiau.hpp"
#include "../core/fluide.hpp"
#include <iostream>
using std::cout;
using std::endl;

void test_voisins() {
    
    bool succes = true;

    Materiau<3> mateau3d = Materiau<3>(EAU);

    list<Particule<3>*>::iterator part_it;
    list<Particule<3>*> vois;
    list<Particule<3>*>::iterator vois_it;

    int tab3d[3] = {20, 20, 20};

    Fluide<3> f1 = Fluide<3>(&mateau3d, tab3d, 1., mateau3d.getDensiteRepos(), mateau3d.getPression());
    part_it = f1.particules.begin();
    while (part_it != f1.particules.end()) {
        vois = f1.voisinage(*(*part_it));
        if (!vois.empty()) {
            cout << "Pas de voisins : KO" << endl;
            cout << (*part_it)->getPosition() << endl;
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                cout << " " << (*vois_it)->getPosition() << endl;
            }
        }
        succes = succes && vois.empty();
        ++part_it;
    }
    
    if (succes) {
        cout << "BILAN 1 : Pas de voisins ok" << endl;
    } else {
        cout << "BILAN 1 : Pas de voisins KO" << endl;
    }

    succes = true;
    Fluide<3> f2 = Fluide<3>(&mateau3d, tab3d, 0.1, mateau3d.getDensiteRepos(), mateau3d.getPression());
    part_it = f2.particules.begin();
    while (part_it != f2.particules.end()) {
        vois = f2.voisinage(*(*part_it));
        if (!vois.empty()) {
            cout << "Pas de voisins : KO" << endl;
            cout << (*part_it)->getPosition() << endl;
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                cout << " " << (*vois_it)->getPosition() << endl;
            }
        }
        succes = succes && vois.empty();
        ++part_it;
    }
    if (succes) {
        cout << "BILAN 2 : Pas de voisins ok" << endl;
    } else {
        cout << "BILAN 2 : Pas de voisins KO" << endl;
    }

    succes = true;
    Fluide<3> f3 = Fluide<3>(&mateau3d, tab3d, 0.05, mateau3d.getDensiteRepos(), mateau3d.getPression());
    part_it = f3.particules.begin();
    while (part_it != f3.particules.end()) {
        vois = f3.voisinage(*(*part_it));
        if (!vois.empty()) {
            cout << "Pas de voisins : KO" << endl;
            cout << (*part_it)->getPosition() << endl;
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                cout << " " << (*vois_it)->getPosition() << endl;
            }
        }
        succes = succes && vois.empty();
        ++part_it;
    }
    if (succes) {
        cout << "BILAN 3 : Pas de voisins ok" << endl;
    } else {
        cout << "BILAN 3 : Pas de voisins KO" << endl;
    }

    succes = true;
    Fluide<3> f4 = Fluide<3>(&mateau3d, tab3d, 0.04, mateau3d.getDensiteRepos(), mateau3d.getPression());
    //cout << "Longueur hashtable " << f4.lgrHash << endl;
    //f4.afficher_hash();
    part_it = f4.particules.begin();
    while (part_it != f4.particules.end()) {
    vois = f4.voisinage(*(*part_it));
    if (vois.empty()) {
        cout << "Voisins : KO" << endl;
        cout << (*part_it)->getPosition() << endl;
    } 
    succes = succes && !vois.empty();
    ++part_it;
    }
    if (succes) {
        cout << "BILAN 4 : Voisins ok" << endl;
    } else {
        cout << "BILAN 4 : Voisins KO" << endl;
    }

}
