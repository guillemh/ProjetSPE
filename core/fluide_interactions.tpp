template <unsigned int Dim>
bool Fluide<Dim>::changerParam() {
    cout << endl << "Quels paramètres voulez-vous modifier?" << endl;
    cout << " 1. Paramètres de la boîte de collision" << endl;
    cout << " 2. Vitesse initiale des particules" << endl;
    cout << " 3. Masse volumique initiale des particules" << endl;
    cout << " 4. Nombre de particules sur les différentes dimensions" << endl;
    cout << " 5. Écart initial entre les particules" << endl;
    cout << " 6. Seuil de dynamique restreinte (ARPS)" << endl;
    cout << " 7. Écart entre les seuils de dynamique restreinte et entière (ARPS)" << endl;
    int numero;
    cin >> numero;
    Vecteur<Dim> vec;
    int on;
    switch (numero) {
    case 1:
        cout << "ATTENTION : après ces modifications, la simulation sera reprise depuis le début;" << endl
             << "êtes-vous sûr(e) de vouloir continuer?" << endl;
        cout << " 1 => Oui" << endl << " 0 => Non" << endl;
        cin >> on;
        if (on == 1) {
            cout << "Nouvelles dimensions de la boîte entourant le fluide?" << endl;
            double c;
            cout << "x_min (actuel = " << x_min << ")" << endl;
            cin >> c;
            x_min = c;
            cout << "x_max (actuel = " << x_max << ")" << endl;
            cin >> c;
            x_max = c;
            cout << "y_min (actuel = " << y_min << ")" << endl;
            cin >> c;
            y_min = c;
            cout << "y_max (actuel = " << y_max << ")" << endl;
            cin >> c;
            y_max = c;
            cout << "z_min (actuel = " << z_min << ")" << endl;
            cin >> c;
            z_min = c;
            return true;
        }
        break;
    case 2:
        cout << "ATTENTION : après ces modifications, la simulation sera reprise depuis le début;" << endl
             << "êtes-vous sûr(e) de vouloir continuer?" << endl;
        cout << " 1 => Oui" << endl << " 0 => Non" << endl;
        cin >> on;
        if (on == 1) {
            cout << "Nouvelles composantes de la vitesse initiale des particules (actuelle = "
                 << vitInit << " m.s-1)?" << endl;
            cout << "En x :" << endl;
            cin >> vec(1);
            cout << "En y :" << endl;
            cin >> vec(2);
            if (Dim == 3) {
                cout << "En z :" << endl;
                cin >> vec(3);
            }
            vitInit = vec;
            return true;
        }
        break;
    case 3:
        cout << "ATTENTION : après ces modifications, la simulation sera reprise depuis le début;" << endl
             << "êtes-vous sûr(e) de vouloir continuer?" << endl;
        cout << " 1 => Oui" << endl << " 0 => Non" << endl;
        cin >> on;
        if (on == 1) {
            cout << "Nouvelle masse volumique initiale des particules (actuelle = "
                 << densiteInit << " kg.m-3)?" << endl;
            double rho;
            cin >> rho;
            densiteInit = rho;
            return true;
        }
        break;
    case 4:
        cout << "ATTENTION : après ces modifications, la simulation sera reprise depuis le début;" << endl
             << "êtes-vous sûr(e) de vouloir continuer?" << endl;
        cout << " 1 => Oui" << endl << " 0 => Non" << endl;
        cin >> on;
        if (on == 1) {
            cout << "Nouvelle répartition des particules?" << endl;
            cout << "En x (actuel = " << nbPart(1) << ")" << endl;
            cin >> vec(1);
            cout << "En y (actuel = " << nbPart(2) << ")" << endl;
            cin >> vec(2);
            if (Dim == 3) {
                cout << "En z (actuel = " << nbPart(3) << ")" << endl;
                cin >> vec(3);
            }
            nbPart = vec;
            return true;
        }
        break;
    case 5:
        cout << "ATTENTION : après ces modifications, la simulation sera reprise depuis le début;" << endl
             << "êtes-vous sûr(e) de vouloir continuer?" << endl;
        cout << " 1 => Oui" << endl << " 0 => Non" << endl;
        cin >> on;
        if (on == 1) {
            cout << "Nouvel écart initial entre les particules (actuel = "
                 << ecart << " m)?" << endl;
            double e;
            cin >> e;
            ecart = e;
            return true;
        }
        break;
    case 6:
        cout << "Nouveau seuil de dynamique restreinte (actuel = "
             << epsilonR << ")?" << endl;
        double eps;
        cin >> eps;
        epsilonR = eps;
        break;
    case 7:
        cout << "Nouvel écart entre les seuils de dynamique restreinte et entière (actuel = "
             << epsilonF - epsilonR << ")?" << endl;
        double delta;
        cin >> delta;
        epsilonF = epsilonR + delta;
        break;
    default:
        cout << "retour" << endl;
        break;
    }
    return false;
}


template<unsigned int Dim>
void Fluide<Dim>::changerAffichage() {
    cout << endl << "Quel affichage désirez-vous ?" << endl;
    cout << " 1. Particules assimilées à des billes" << endl;
    cout << " 2. Particules assimilées à des points" << endl;
    cout << " 3. Surfaces générées grâce aux marching cubes" << endl;
    int numero;
    cin >> numero;
    switch (numero) {
    case (1):
        afficheMetaballs = true;
        ball->initColoration(particules);
        break;
    case (2):
        afficheMetaballs = false;
        affichePoint = true;
        break;
    case (3):
        afficheMetaballs = false;
        affichePoint = false;
        break;
    default:
        cout << "retour" << endl;
        break;
    }
}


template<unsigned int Dim>
void Fluide<Dim>::changerAffichageAuto() {

    if (afficheMetaballs) {
        afficheMetaballs = false;
        affichePoint = true;
    } else if (affichePoint) {
        afficheMetaballs = false;
        affichePoint = false;
    } else {
        afficheMetaballs = true;
        ball->initColoration(particules);
    }
    
}


template <unsigned int Dim>
void Fluide<Dim>::changerArps() {
    
    cout << "Nouveau seuil de dynamique restreinte (actuel = "
         << epsilonR << ")?" << endl;
    double eps;
    cin >> eps;
    epsilonR = eps;
    cout << "Nouvel écart entre les seuils de dynamique restreinte et entière (actuel = "
         << epsilonF - epsilonR << ")?" << endl;
    double delta;
    cin >> delta;
    epsilonF = epsilonR + delta;

}
