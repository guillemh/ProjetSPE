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
    Vecteur<3> vec3d1 = Vecteur<3>(2.0, 1.0, 3.0);
    Vecteur<3> vec3d2 = Vecteur<3>();
    Particule<3> * p2 = new Particule<3>(vec3d1, vec3d2, 950, 101558);
    Particule<3> * p4 = new Particule<3>(vec3d1, vec3d2, 950, 101558);

    int tab3d[3] = {10, 10, 10};
    Fluide<3> f = Fluide<3>(&mateau3d, tab3d, 1., mateau3d.getDensiteRepos(), mateau3d.getPression());

    vector<Particule<3>*>::iterator part_it = f.particules.begin();
    list<Particule<3>*> vois;

    while (succes && part_it != f.particules.end()) {
	vois = f.voisinage(*(*part_it));
	succes = succes && (!vois.empty());
	++part_it;
    }
    if (succes) {
	cout << "Pas de voisins : ok" << endl;
    } else {
	cout << "Pas de voisins : KO" << endl;
    }

}
