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
        coeff_restitution = 0.75;
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
void Materiau<Dim>::changerSysteme() {
    cout << endl << "Quel paramètre voulez-vous changer?" << endl;
    cout << " 1. Accélération de la gravité" << endl;
    cout << " 2. Pas de temps" << endl;
    cout << " 3. Température ambiente" << endl;
    cout << " 4. Pression atmosphérique" << endl;
    int numero;
    cin >> numero;
    Vecteur<Dim> ag;
    switch (numero) {
    case 1:
        cout << "Nouvelles composantes de la force de gravité (actuelle = "
             << acc_gravitation << " m.s-2)?" << endl;
        cout << "En x :" << endl;
        cin >> ag(1);
        cout << "En y :" << endl;
        cin >> ag(2);
        if (Dim == 3) {
            cout << "En z :" << endl;
            cin >> ag(3);
        }
        acc_gravitation = ag;
        break;
    case 2:
        cout << "Nouveau pas de temps (actuel = "
             << pas_temps << " s)?" << endl;
        double pt;
        cin >> pt;
        pas_temps = pt;
        break;
    case 3:
        cout << "Nouvelle température ambiente (actuelle = "
             << temperature << " K)?" << endl;
        double t;
        cin >> t;
        temperature = t;
        break;
    case 4:
        cout << "Nouvelle pression atmosphérique (actuelle = "
             << pression_atm << " Pa)?" << endl;
        double pa;
        cin >> pa;
        pression_atm = pa;
        break;
    default:
        cout << "retour" << endl;
        break;
    }
}
    

template <unsigned int Dim>
void Materiau<Dim>::changerParam() {
    cout << endl << "Quel paramètre voulez-vous changer?" << endl;
    cout << " 1. Masse des particules" << endl;
    cout << " 2. Densité au repos" << endl;
    cout << " 3. Coefficient de flottabilité" << endl;
    cout << " 4. Viscosité" << endl;
    cout << " 5. Tension de surface" << endl;
    cout << " 6. Seuil pour la tension de surface" << endl;
    cout << " 7. Rigidité du gaz" << endl;
    cout << " 8. Coefficient de restitution" << endl;
    cout << " 9. Nombre de particules dans le noyau" << endl;
    cout << " 10. Rayon du noyau" << endl;
    cout << " 11. Vitesse du son dans le fluide" << endl;
    cout << " 12. Alpha" << endl;
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
        cout << "Nouvelle densité au repos (actuelle = "
             << densite_repos << " kg.m-3)?" << endl;
        cin >> d;
        densite_repos = d;
        break;
    case 3:
        double cf;
        cout << "Nouveau coefficient de flottabilité (actuel = "
             << coeff_flottabilite << ")?" << endl;
        cin >> cf;
        coeff_flottabilite = cf;
        break;
    case 4:
        double v;
        cout << "Nouvelle viscosité (actuelle = "
             << viscosite << " Pa.s)?" << endl;
        cin >> v;
        viscosite = v;
        break;
    case 5:
        double t;
        cout << "Nouvelle tension de surface (actuelle = "
             << tension_surface << " N.m-1)?" << endl;
        cin >> t;
        tension_surface = t;
        break;
    case 6:
        double s;
        cout << "Nouveau seuil pour la tension de surface (actuel = "
             << seuil_surface << ")?" << endl;
        cin >> s;
        seuil_surface = s;
        break;
    case 7:
        double rg;
        cout << "Nouvelle rigidité du gaz parfait (actuelle = "
             << rigidite_gaz << " J)?" << endl;
        cin >> rg;
        rigidite_gaz = rg;
        break;
    case 8:
        double cr;
        cout << "Nouveau coefficient de restitution (actuel = "
             << coeff_restitution << ")?" << endl;
        cin >> cr;
        coeff_restitution = cr;
        break;
    case 9:
        double n;
        cout << "Nouveau nombre de particules dans le noyau (actuel = "
             << nbr_noyau << ")?" << endl;
        cin >> n;
        nbr_noyau = n;
        break;
    case 10:
        double r;
        cout << "Nouveau rayon du noyau (actuel = "
             << rayon_noyau << " m)?" << endl;
        cin >> r;
        rayon_noyau = r;
        break;
    case 11:
        double c;
        cout << "Nouvelle célérité du son dans le fluide (actuelle = "
             << celerite_son << " m.s-1)?" << endl;
        cin >> c;
        celerite_son = c;
        break;
    case 12:
        double a;
        cout << "Nouveau coefficient alpha (actuel = "
             << alpha << ")?" << endl;
        cin >> a;
        alpha = a;
        break;
    default:
        cout << "retour" << endl;
        break;
    }
}
