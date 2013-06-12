#include "../core/particule.hpp"
#include "../core/vecteur.hpp"
#include "../core/materiau.hpp"
#include "../core/fluide.hpp"
#include <iostream>
using std::cout;
using std::endl;

void test_voisins() {
    
    bool succes = true;
    double dist;

    cout << endl << "** Test recherche de voisins **" << endl;
    
    /* 2D impossible actuellement a cause des metaballs */
    
/*
    cout << " Avec 2 particules" << endl;
    Materiau<2> mateau2d = Materiau<2>(EAU);
    double rayon2d = mateau2d.getRayonNoyau();
    cout << " Rayon du noyau : " << rayon2d << endl;
    list<Particule<2>*>::iterator it;
    set<Particule<2>*> voisins;
    set<Particule<2>*>::iterator v_it;
    Vecteur<2> tab2d = Vecteur<2>(0, 2);
    rayon2d *= 2;  // car le noyau prend les particules dans un rayon 2*rnoyau
    
    dist = rayon2d+0.1;
    Fluide<2> f = Fluide<2>(&mateau2d, tab2d, dist, mateau2d.getDensiteRepos(), mateau2d.getPression(), Vecteur<2>());
    cout << " Distance entre particules " << dist << endl;
    it = f.particules.begin();
    while (it != f.particules.end()) {
        voisins = f.voisinage(*(*it));
        if (!voisins.empty()) {
            cout << "Pas de voisins : KO" << endl;
            cout << (*it)->getPosition() << endl;
            for (v_it = voisins.begin(); v_it != voisins.end(); ++v_it) {
                cout << " " << (*v_it)->getPosition() << endl;
        	cout << " Distance : " << ((*it)->getPosition() - (*v_it)->getPosition()).norme() << endl;
            }
        }
        succes = succes && voisins.empty();
        ++it;
    }
    if (succes) {
        cout << " BILAN : Pas de voisins ok" << endl;
    } else {
        cout << " BILAN : Pas de voisins KO" << endl;
    }

    succes = true;
    dist = rayon2d-0.02;
    Fluide<2> fp = Fluide<2>(&mateau2d, tab2d, dist, mateau2d.getDensiteRepos(), mateau2d.getPression(), Vecteur<2>());
    cout << " Distance entre particules " << dist << endl;
    it = fp.particules.begin();
    while (it != fp.particules.end()) {
        voisins = fp.voisinage(*(*it));
        if (voisins.empty()) {
            cout << "Voisins : KO" << endl;
            cout << (*it)->getPosition() << endl;
        }
        succes = succes && (!voisins.empty());
        ++it;
    }
    if (succes) {
        cout << " BILAN : Voisins ok" << endl;
    } else {
        cout << " BILAN : Voisins KO" << endl;
    }
*/
    
    cout << "Avec plus de particules, en 3 dimensions" << endl;
    Materiau<3> mateau3d = Materiau<3>(EAU);
    double rayon3d = mateau3d.getRayonNoyau();
    cout << "Rayon du noyau : " << rayon3d << endl;

    list<Particule<3>*>::iterator part_it;
    set<Particule<3>*> vois;
    set<Particule<3>*>::iterator vois_it;
    Vecteur<3> tab3d = Vecteur<3>(2, 2, 2);
    rayon3d *= 2;

    succes = true;
    dist = rayon3d*10;
    Fluide<3> f1 = Fluide<3>(&mateau3d, tab3d, dist, mateau3d.getDensiteRepos(), mateau3d.getPression(), Vecteur<3>());
    cout << "1.Distance entre particules " << dist << endl;
    //f1.afficher_hash();
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
    dist = rayon3d+rayon3d/2;
    Fluide<3> f2 = Fluide<3>(&mateau3d, tab3d, dist, mateau3d.getDensiteRepos(), mateau3d.getPression(), Vecteur<3>());
    cout << "2.Distance entre particules " << dist << endl;
    //f2.afficher_hash();
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
    dist = rayon3d+0.02;
    Fluide<3> f3 = Fluide<3>(&mateau3d, tab3d, dist, mateau3d.getDensiteRepos(), mateau3d.getPression(), Vecteur<3>());
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
    dist = rayon3d-0.01;
    Fluide<3> f4 = Fluide<3>(&mateau3d, tab3d, dist, mateau3d.getDensiteRepos(), mateau3d.getPression(), Vecteur<3>());
    cout << "4.Distance entre particules " << dist << endl;
    //f4.afficher_hash();
    part_it = f4.particules.begin();
    while (part_it != f4.particules.end()) {
        vois = f4.voisinage(*(*part_it));
        if (vois.empty()) {
            cout << "Voisins : KO" << endl;
            cout << (*part_it)->getPosition() << endl;
        } // else {
        //     cout << "Voisins de " << (*part_it)->getPosition() << " :" << endl;
        //     for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
        //         cout << " " << (*vois_it)->getPosition();
        // 	cout << " Distance : " << ((*part_it)->getPosition() - (*vois_it)->getPosition()).norme() << endl;
        //     }
        // }

        succes = succes && !vois.empty();
        ++part_it;
    }
    if (succes) {
        cout << "BILAN 4 : Voisins ok" << endl;
    } else {
        cout << "BILAN 4 : Voisins KO" << endl;
    }

    cout << endl << "** Test mise à jour de la table **" << endl;
    
    succes = true;
    f1.majDensitePression();
    f1.majPositionVitesse();
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
    f2.majDensitePression();
    f2.majPositionVitesse();
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
    f3.majDensitePression();
    f3.majPositionVitesse();
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
    f4.majDensitePression();
    f4.majPositionVitesse();
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
