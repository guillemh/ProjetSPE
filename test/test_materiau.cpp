#include "../core/materiau.hpp"
#include <iostream>
using std::cout;
using std::endl;

void test_materiau() {

    cout << "1 - Création du matériau eau" << endl;
    Materiau<3> mateau = Materiau<3>(EAU);
    Vecteur<3> v1 = Vecteur<3>(0, 0, -9.82);
    if (mateau.getAccGrav() == v1
     && mateau.getTemperature() == 293.15
     && mateau.getPression() == 101325
     && mateau.getDensiteRepos() == 998.29
     && mateau.getMasseParticules() == 0.02
     && mateau.getCoeffFlott() == 0
     && mateau.getViscosite() == 3.5
     && mateau.getTensionSurface() == 0.0728
     && mateau.getSeuilSurface() == 7.065
     && mateau.getRigiditeGaz() == 3
     && mateau.getCoeffRestitution() == 0
     && mateau.getNbrPartNoyau() == 20
     && mateau.getRayonNoyau() == 0.0457)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "2 - Création du matériau mucus" << endl;
    Materiau<2> matmucus = Materiau<2>(MUCUS);
    Vecteur<2> v2 = Vecteur<2>(0, -9.82);
    if (matmucus.getAccGrav() == v2
     && matmucus.getTemperature() == 293.15
     && matmucus.getPression() == 101325
     && matmucus.getDensiteRepos() == 1000
     && matmucus.getMasseParticules() == 0.04
     && matmucus.getCoeffFlott() == 0
     && matmucus.getViscosite() == 36
     && matmucus.getTensionSurface() == 6
     && matmucus.getSeuilSurface() == 5
     && matmucus.getRigiditeGaz() == 5
     && matmucus.getCoeffRestitution() == 0.5
     && matmucus.getNbrPartNoyau() == 40
     && matmucus.getRayonNoyau() == 0.0726)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
    cout << "3 - Création du matériau vapeur" << endl;
    Materiau<3> matvapeur = Materiau<3>(VAPEUR);
    if (matvapeur.getAccGrav() == v1
     && matvapeur.getTemperature() == 293.15
     && matvapeur.getPression() == 101325
     && matvapeur.getDensiteRepos() == 0.59
     && matvapeur.getMasseParticules() == 0.00005
     && matvapeur.getCoeffFlott() == 5
     && matvapeur.getViscosite() == 0.01
     && matvapeur.getTensionSurface() == 0
     && matvapeur.getSeuilSurface() == -1
     && matvapeur.getRigiditeGaz() == 4
     && matvapeur.getCoeffRestitution() == 0
     && matvapeur.getNbrPartNoyau() == 12
     && matvapeur.getRayonNoyau() == 0.0624)
        cout<<"OK"<<endl;
    else
        cout<<"ERREUR !"<<endl;
    
}
