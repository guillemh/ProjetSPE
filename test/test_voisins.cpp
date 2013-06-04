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
    double rayon = mateau3d.getRayonNoyau();
    cout << "Rayon du noyau : " << rayon << endl;

    list<Particule<3>*>::iterator part_it;
    set<Particule<3>*> vois;
    set<Particule<3>*>::iterator vois_it;

    int tab3d[3] = {4, 4, 4};
    double dist;

    dist = rayon*10;
    Fluide<3> f1 = Fluide<3>(&mateau3d, tab3d, dist, mateau3d.getDensiteRepos(), mateau3d.getPression());
    cout << "1.Distance entre particules " << dist << endl;
    part_it = f1.particules.begin();
    while (part_it != f1.particules.end()) {
        vois = f1.voisinage(*(*part_it));
        if (!vois.empty()) {
            cout << "Pas de voisins : KO" << endl;
            cout << (*part_it)->getPosition() << endl;
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                cout << " " << (*vois_it)->getPosition() << endl;
		cout << " Distance : " << ((*part_it)->getPosition() - (*vois_it)->getPosition()).norme() << endl;
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
    dist = rayon+rayon/2;
    Fluide<3> f2 = Fluide<3>(&mateau3d, tab3d, dist, mateau3d.getDensiteRepos(), mateau3d.getPression());
    cout << "2.Distance entre particules " << dist << endl;
    part_it = f2.particules.begin();
    while (part_it != f2.particules.end()) {
        vois = f2.voisinage(*(*part_it));
        if (!vois.empty()) {
            cout << "Pas de voisins : KO" << endl;
            cout << (*part_it)->getPosition() << endl;
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                cout << " " << (*vois_it)->getPosition() << endl;
		cout << " Distance : " << ((*part_it)->getPosition() - (*vois_it)->getPosition()).norme() << endl;
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
    dist = rayon+0.02;
    Fluide<3> f3 = Fluide<3>(&mateau3d, tab3d, dist, mateau3d.getDensiteRepos(), mateau3d.getPression());
    cout << "3.Distance entre particules " << dist << endl;
    //f3.afficher_hash();
    part_it = f3.particules.begin();
    while (part_it != f3.particules.end()) {
        vois = f3.voisinage(*(*part_it));
        if (!vois.empty()) {
            cout << "Pas de voisins : KO" << endl;
            cout << (*part_it)->getPosition() << endl;
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                cout << " " << (*vois_it)->getPosition() << endl;
		cout << " Distance : " << ((*part_it)->getPosition() - (*vois_it)->getPosition()).norme() << endl;
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
    dist = rayon-0.01;
    Fluide<3> f4 = Fluide<3>(&mateau3d, tab3d, dist, mateau3d.getDensiteRepos(), mateau3d.getPression());
    cout << "4.Distance entre particules " << dist << endl;
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
