#include <iostream>
using std::cerr;
using std::endl;
using std::cin;

template<unsigned int Dim>
Materiau<Dim>::Materiau(
                        Vecteur<Dim> g, 
                        double dt,
                        double t,
                        double p,
                        double rho,
                        double mp,
                        double b,
                        double mu,
                        double sigma,
                        double l,
                        double k,
                        double cr,
                        unsigned int x,
                        double h,
                        double cs,
                        double a
                        ) {
    acc_gravitation = g;
    pas_temps = dt;
    temperature = t;
    pression_atm = p;

    densite_repos = rho;
    masse_particules = mp;
    coeff_flottabilite = b;
    viscosite = mu;
    tension_surface = sigma;
    seuil_surface = l;
    rigidite_gaz = k;
    coeff_restitution = cr;
    nbr_noyau = x;
    rayon_noyau = h;
    celerite_son = cs;
    alpha = a;
}

template<unsigned int Dim>
Materiau<Dim>::Materiau(TypeFluide type) {
    switch(Dim) {
    case 2 :
        acc_gravitation = Vecteur<Dim>(0, -9.82);
        break;
    case 3 :
        acc_gravitation = Vecteur<Dim>(0, 0, -9.82);
        break;
    default :
        cerr << "Gestion qu'en dimensions 2 ou 3" << endl;
        exit(EXIT_FAILURE);
        break;
    }
    pas_temps = 0.001;
    temperature = 293.15;
    pression_atm = 101325;

    switch(type) {
    case EAU :
        //densite_repos = 998.29;
        densite_repos = 160;
        masse_particules = 0.02;
        //masse_particules = 0.0065;
        coeff_flottabilite = 0;
        viscosite = 3.5;
        tension_surface = 0.0728;
        seuil_surface = 7.065;
        rigidite_gaz = 3;
        //coeff_restitution = 0;
        coeff_restitution = 0.25;
        nbr_noyau = 20;
        //rayon_noyau = 0.0457;
        rayon_noyau = 0.03;
        //celerite_son = 1480;
        celerite_son = 88.5;
        //alpha = 0.5;
        //alpha = 1;
        alpha = 0.08;
        break;
    case MUCUS :
        densite_repos = 1000;
        masse_particules = 0.04;
        coeff_flottabilite = 0;
        viscosite = 36;
        tension_surface = 6;
        seuil_surface = 5;
        rigidite_gaz = 5;
        coeff_restitution = 0.5;
        nbr_noyau = 40;
        rayon_noyau = 0.0726;
        celerite_son = 1480; // approximation
        alpha = 0.5;
        break;
    case VAPEUR :
        densite_repos = 0.59;
        masse_particules = 0.00005;
        coeff_flottabilite = 5;
        viscosite = 0.01;
        tension_surface = 0;
        seuil_surface = -1;
        rigidite_gaz = 4;
        coeff_restitution = 0;
        nbr_noyau = 12;
        rayon_noyau = 0.0624;
        celerite_son = 340; 
        // approximation : on récupère la vitesse du son dans l'atmosphère en
        // se prévalant du fait que l'hygrométrie influence peu dans le calcul pratique
        alpha = 0.5;
        break;
    default :
        cerr << "Type de fluide non existant" << endl;
        exit(EXIT_FAILURE);
        break;
    }
}

template <unsigned int Dim>
Vecteur<Dim> Materiau<Dim>::getAccGrav() {
    return acc_gravitation;
}

template <unsigned int Dim>
double Materiau<Dim>::getPasTemps() {
    return pas_temps;
}

template <unsigned int Dim>
double Materiau<Dim>::getTemperature() {
    return temperature;
}

template <unsigned int Dim>
double Materiau<Dim>::getPression() {
    return pression_atm;
}

template <unsigned int Dim>
double Materiau<Dim>::getDensiteRepos() {
    return densite_repos;
}

template <unsigned int Dim>
double Materiau<Dim>::getMasseParticules() {
    return masse_particules;
}

template <unsigned int Dim>
double Materiau<Dim>::getCoeffFlott() {
    return coeff_flottabilite;
}

template <unsigned int Dim>
double Materiau<Dim>::getViscosite() {
    return viscosite;
}

template <unsigned int Dim>
double Materiau<Dim>::getTensionSurface() {
    return tension_surface;
}

template <unsigned int Dim>
double Materiau<Dim>::getSeuilSurface() {
    return seuil_surface;
}

template <unsigned int Dim>
double Materiau<Dim>::getRigiditeGaz() {
    return rigidite_gaz;
}

template <unsigned int Dim>
double Materiau<Dim>::getCoeffRestitution() {
    return coeff_restitution;
}

template <unsigned int Dim>
unsigned int Materiau<Dim>::getNbrPartNoyau() {
    return nbr_noyau;
}

template <unsigned int Dim>
double Materiau<Dim>::getRayonNoyau() {
    return rayon_noyau;
}

template <unsigned int Dim>
double Materiau<Dim>::getCeleriteSon() {
    return celerite_son;
}

template <unsigned int Dim>
double Materiau<Dim>::getConstanteViscosite() {
    return alpha;
}

template <unsigned int Dim>
void Materiau<Dim>::changerNature(TypeFluide type) {
    switch(Dim) {
    case 2 :
        acc_gravitation = Vecteur<Dim>(0, -9.82);
        break;
    case 3 :
        acc_gravitation = Vecteur<Dim>(0, 0, -9.82);
        break;
    default :
        cerr << "Gestion qu'en dimensions 2 ou 3" << endl;
        exit(EXIT_FAILURE);
        break;
    }
    pas_temps = 0.001;
    temperature = 293.15;
    pression_atm = 101325;

    switch(type) {
    case EAU :
        //densite_repos = 998.29;
        densite_repos = 160;
        masse_particules = 0.02;
        //masse_particules = 0.0065;
        coeff_flottabilite = 0;
        viscosite = 3.5;
        tension_surface = 0.0728;
        seuil_surface = 7.065;
        rigidite_gaz = 3;
        //coeff_restitution = 0;
        coeff_restitution = 0.5;
        nbr_noyau = 20;
        //rayon_noyau = 0.0457;
        rayon_noyau = 0.03;
        //celerite_son = 1480;
        celerite_son = 88.5;
        //alpha = 0.5;
        //alpha = 1;
        alpha = 0.08;
        break;
    case MUCUS :
        densite_repos = 1000;
        masse_particules = 0.04;
        coeff_flottabilite = 0;
        viscosite = 36;
        tension_surface = 6;
        seuil_surface = 5;
        rigidite_gaz = 5;
        coeff_restitution = 0.5;
        nbr_noyau = 40;
        rayon_noyau = 0.0726;
        celerite_son = 1480; // approximation
        alpha = 0.5;
        break;
    case VAPEUR :
        densite_repos = 0.59;
        masse_particules = 0.00005;
        coeff_flottabilite = 5;
        viscosite = 0.01;
        tension_surface = 0;
        seuil_surface = -1;
        rigidite_gaz = 4;
        coeff_restitution = 0;
        nbr_noyau = 12;
        rayon_noyau = 0.0624;
        celerite_son = 340; 
        // approximation : on récupère la vitesse du son dans l'atmosphère en
        // se prévalant du fait que l'hygrométrie influence peu dans le calcul pratique
        alpha = 0.5;
        break;
    default :
        cerr << "Type de fluide non existant" << endl;
        exit(EXIT_FAILURE);
        break;
    }
}

template <unsigned int Dim>
void Materiau<Dim>::changerParam() {
    cout << "Quel paramètre voulez-vous changer?" << endl;
    cout << " 1. Masse des particules" << endl;
    cout << " 2. Densité au repos" << endl;
    cout << " 3. Coefficient de restitution" << endl;
    cout << " 4. Rayon du noyau" << endl;
    int numero;
    cin >> numero;
    switch (numero) {
    case 1:
        double m;
        cout << "Nouvelle masse des particules (actuelle = "
             << masse_particules << " kg)?" << endl;
        cin >> m;
        masse_particules = m;
        break;
    case 2:
        double d;
        cin >> d;
        densite_repos = d;
        break;
    case 3:
        double cr;
        cin >> cr;
        coeff_restitution = cr;
        break;
    case 4:
        double r;
        cin >> r;
        rayon_noyau = r;
        break;
    others:
        cout << "retour" << endl;
        return;
    }
}
