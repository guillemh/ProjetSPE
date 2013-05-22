#include "../core/materiau.hpp"
#include <iostream>
using std::cout;
using std::endl;

void test_materiau() {

    cout << "1 - Création du matériau eau" << endl;
    Materiau<3> mateau = Materiau<3>(EAU);
    cout << "gravité      : " << mateau.getAccGrav() << endl;
    cout << "pas          : " << mateau.getPasTemps() << endl;
    cout << "temperature  : " << mateau.getTemperature() << endl;
    cout << "pression     : " << mateau.getPression() << endl;
    cout << "densité      : " << mateau.getDensiteRepos() << endl;
    cout << "masse        : " << mateau.getMasseParticules() << endl;
    cout << "flottabilité : " << mateau.getCoeffFlott() << endl;
    cout << "viscosité    : " << mateau.getViscosite() << endl;
    cout << "tension surf : " << mateau.getTensionSurface() << endl;
    cout << "seuil surf   : " << mateau.getSeuilSurface() << endl;
    cout << "rigidité gaz : " << mateau.getRigiditeGaz() << endl;
    cout << "restitution  : " << mateau.getCoeffRestitution() << endl;
    cout << "part noyau   : " << mateau.getNbrPartNoyau() << endl;
    cout << "rayon noyau  : " << mateau.getRayonNoyau() << endl;
    
    cout << "2 - Création du matériau mucus" << endl;
    Materiau<2> matmucus = Materiau<2>(MUCUS);
    cout << "gravité      : " << matmucus.getAccGrav() << endl;
    cout << "pas          : " << matmucus.getPasTemps() << endl;
    cout << "temperature  : " << matmucus.getTemperature() << endl;
    cout << "pression     : " << matmucus.getPression() << endl;
    cout << "densité      : " << matmucus.getDensiteRepos() << endl;
    cout << "masse        : " << matmucus.getMasseParticules() << endl;
    cout << "flottabilité : " << matmucus.getCoeffFlott() << endl;
    cout << "viscosité    : " << matmucus.getViscosite() << endl;
    cout << "tension surf : " << matmucus.getTensionSurface() << endl;
    cout << "seuil surf   : " << matmucus.getSeuilSurface() << endl;
    cout << "rigidité gaz : " << matmucus.getRigiditeGaz() << endl;
    cout << "restitution  : " << matmucus.getCoeffRestitution() << endl;
    cout << "part noyau   : " << matmucus.getNbrPartNoyau() << endl;
    cout << "rayon noyau  : " << matmucus.getRayonNoyau() << endl;
    
    cout << "3 - Création du matériau vapeur" << endl;
    Materiau<3> matvapeur = Materiau<3>(VAPEUR);
    cout << "gravité      : " << matvapeur.getAccGrav() << endl;
    cout << "pas          : " << matvapeur.getPasTemps() << endl;
    cout << "temperature  : " << matvapeur.getTemperature() << endl;
    cout << "pression     : " << matvapeur.getPression() << endl;
    cout << "densité      : " << matvapeur.getDensiteRepos() << endl;
    cout << "masse        : " << matvapeur.getMasseParticules() << endl;
    cout << "flottabilité : " << matvapeur.getCoeffFlott() << endl;
    cout << "viscosité    : " << matvapeur.getViscosite() << endl;
    cout << "tension surf : " << matvapeur.getTensionSurface() << endl;
    cout << "seuil surf   : " << matvapeur.getSeuilSurface() << endl;
    cout << "rigidité gaz : " << matvapeur.getRigiditeGaz() << endl;
    cout << "restitution  : " << matvapeur.getCoeffRestitution() << endl;
    cout << "part noyau   : " << matvapeur.getNbrPartNoyau() << endl;
    cout << "rayon noyau  : " << matvapeur.getRayonNoyau() << endl;
    
}
