#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

#include "fluide.hpp"
#include "noyauLissage.hpp"
using std::cout;
using std::endl;
using std::pair;

#define EPS 5.5

/* ** Constructeurs ** */

template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m)
    : mat(m),
      ball (Metaballs(Vecteur<3>(-0.5, -0.5, 0.0), 0.05, mat->getRayonNoyau(), 1, 1, 0.5)),
      nbrParticules(0),
      debutAnim(true),
      hash_voisins(),
      lgrHash(0),
      epsilonR(EPS),
      epsilonF(EPS+40)
{
    // Initilisation de la liste vide
    particules = list<Particule<Dim> *>();
    lignedEau = list<Particule<Dim> *>();
    
    // Definition des dimensions et de la metaball suivant la dimension
    if (Dim == 2) {
        x_min = -0.5;
        x_max = 0.5;
        y_min = 0.0;
        y_max = 1.0;
        z_min = 0.0;
    } else if (Dim == 3) {
        x_min = -0.5;
        x_max = 0.5;
        y_min = -0.5;
        y_max = 0.5;
        z_min = 0.0;
        
        //        Vecteur<3> orig = Vecteur<3>(x_min, y_min, z_min);
        //        ball = Metaballs(orig, 0.01, mat->getRayonNoyau(), x_max - x_min, y_max - y_min, y_max - y_min);
    }
}


template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m, int nb[Dim], double ecart, double rho, double p)
    : mat(m),
      ball (Metaballs(Vecteur<3>(-0.2, -0.2, 0.0), 0.1, mat->getRayonNoyau(), 0.5, 0.5, 1)),
      debutAnim(true),
      hash_voisins(),
      epsilonR(EPS),
      epsilonF(EPS+40)
{
    // Initialisation de la liste vide
    particules = list<Particule<Dim> *>();
    lignedEau = list<Particule<Dim> *>();

    /* 
     * Création d'une table des nombres premiers 
     * pour calculer la dimension de la table de hashage 
     */
    //    Premier<Dim> table = Premier<Dim>();

    /* Pour la conversion des coordonnées de la particule dans la grille de voxels */
    Vecteur<Dim> noeud_grille;

    /* Compteur pour numéroter les particules */
    unsigned int cpt = 0;

    if (Dim == 2) {
    
        nbrParticules = nb[0]*nb[1];
        lgrHash = table.getPremier(2*nbrParticules);

        // Ici, on est en dimension 2
        // On va ajouter des particules regulierement disposees sur les deux dimensions
        // On définit la largeur de la boîte
        x_min = -0.5;
        x_max = 0.5;
        y_min = 0.0;
        y_max = 1.0;
        z_min = 0.0;
        
        // On définit ensuite la position des particules
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j < nb[1]; j++) {
                ++cpt;
                Vecteur<Dim> vec = Vecteur<Dim>((i-nb[0]/2)*ecart, 0.1 + j*ecart);
                Particule<Dim> *part = new Particule<Dim>(cpt, vec, Vecteur<Dim>(), mat->getMasseParticules(), rho, p);
                particules.push_back(part);
                noeud_grille(1) = int(floor(part->getPosition()(1)/mat->getRayonNoyau()));
                noeud_grille(2) = int(floor(part->getPosition()(2)/mat->getRayonNoyau()));
                hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(noeud_grille), part));
            }
        }
        
    } else if (Dim == 3) {
    
        nbrParticules = nb[0]*nb[1]*nb[2];
        lgrHash = table.getPremier(2*nbrParticules);

        // Ici, on est en dimension 3
        // On va ajouter des particules regulierement disposees sur les trois dimensions
        // On définit la largeur de la boîte
        x_min = -0.2;
        x_max = 0.2;
        y_min = -0.2;
        y_max = 0.2;
        z_min = 0.0;
        
        // On definit enduite la metaball
        //        Vecteur<3> orig = Vecteur<3>(x_min, y_min, z_min);
        //        ball = Metaballs(orig, 0.01, mat->getRayonNoyau(), x_max - x_min, y_max - y_min, y_max - y_min);
        
        // On définit ensuite la position des particules
        double largeur_x = x_max - x_min;
        double largeur_y = y_max - y_min;
        
        if (largeur_x < nb[0]*ecart || largeur_y < nb[1]*ecart)
            cout << "Attention (fluide.tpp) : trop de particules pour les dimensions de la boîte" << endl;
        
        Vecteur<Dim> vec;
        Particule<Dim> *part;
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j < nb[1]; j++) {
                for (int k = 0; k < nb[2]; k++) {
                    ++cpt;
                    // On ajoute de l'alea pour rendre le fluide plus realiste
	
                     double x = 0.02 * (rand() / double(RAND_MAX) - 0.5);
                     double y = 0.02 * (rand() / double(RAND_MAX) - 0.5);
                     double z = 0.02 * (rand() / double(RAND_MAX) - 0.5);
                     Vecteur<Dim> alea = Vecteur<Dim>(x,y,z);

                    
                     vec = Vecteur<Dim>((i-nb[0]/2)*ecart, (j-nb[1]/2)*ecart, 0.1 + k*ecart) + alea;
                    //vec = Vecteur<Dim>((i-nb[0]/2)*ecart, (j-nb[1]/2)*ecart, 0.1 + k*ecart);
                    part = new Particule<Dim>(cpt, vec, Vecteur<Dim>(), mat->getMasseParticules(), rho, p);
                    particules.push_back(part);
                    noeud_grille(1) = int(floor(part->getPosition()(1)/mat->getRayonNoyau()));
                    noeud_grille(2) = int(floor(part->getPosition()(2)/mat->getRayonNoyau()));
                    noeud_grille(3) = int(floor(part->getPosition()(3)/mat->getRayonNoyau()));
                    hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(noeud_grille), part));               
                }
            }
        }

	// Ligne rigide de particules
	// int nb_x = largeur_x/0.03;
	// int nb_y = largeur_y/0.03;
	// for (int i = 0; i <= nb_x; i++) {
	//     for (int j = 0; j <= nb_y; j++) {
	// 	vec = Vecteur<Dim>((x_min + largeur_x*(double(i)/double(nb_x))),
	// 			   (y_min + largeur_y*(double(j)/double(nb_y))),
	// 			   z_min);
	// 	part = new Particule<Dim> (vec, Vecteur<Dim>(), 0.0, rho, p);
	// 	lignedEau.push_back(part);
	// 	hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(part->getPosition()), part));
	//     }
	// }
        
    } else {
        cout << "Erreur (Fluide) : la dimension de l'espace doit être 2 ou 3" << endl;
        exit(1);
    }
}


template<unsigned int Dim>
Fluide<Dim>::~Fluide() {
    typename list<Particule<Dim> *>::iterator it;
    // On libere toutes les particules
    for (it = particules.begin(); it != particules.end();it++) {
        delete (*it);
    }
    for (it = lignedEau.begin(); it != lignedEau.end();it++) {
        delete (*it);
    }
    hash_voisins.clear();
}



/* Fonction de hashage */

template<>
inline int Fluide<2>::fonction_hashage(Vecteur<2> pos) {
    int p1 = 73856093;
    int p2 = 19349663;
    return (int(pos(1))*p1 
            ^ int(pos(2))*p2) 
        % lgrHash;
}


template<>
inline int Fluide<3>::fonction_hashage(Vecteur<3> pos) {
    int p1 = 73856093;
    int p2 = 19349663;
    int p3 = 83492791;
    return (int(pos(1))*p1 
            ^ int(pos(2))*p2
            ^ int(pos(3))*p3) 
        % lgrHash;
}

/* Affichage de la table de hashage */
template<unsigned int Dim>
void Fluide<Dim>::afficher_hash() {
    typename multimap<int, Particule<Dim>*>::iterator mmap_it;
    cout << "Multimap des voisins :" << endl;
    for (mmap_it = hash_voisins.begin(); mmap_it != hash_voisins.end(); ++mmap_it) {
        cout << " " << (*mmap_it).first << " => " << ((*mmap_it).second)->getPosition() << endl;
    }
}



/* ** Méthodes ** */

template<unsigned int Dim>
void Fluide<Dim>::ajouteParticule(Particule<Dim> * part) {
    ++nbrParticules;
    particules.push_back(part);
    lgrHash = table.getPremier(2*nbrParticules);
    hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(part->getPosition()), part));
}

template<unsigned int Dim>
inline void Fluide<Dim>::majTableHashage() {
    hash_voisins.clear();

    typename list<Particule<Dim>*>::iterator part_it;
    int hash_key;
    Vecteur<Dim> noeud_grille;
    for (part_it = particules.begin(); part_it != particules.end(); part_it++) {
        for (unsigned int i = 1; i <= Dim; i++) {
            noeud_grille(i) = int(floor((*part_it)->getPosition()(i)/mat->getRayonNoyau()));
        }
        hash_key = fonction_hashage(noeud_grille);
        hash_voisins.insert(pair<int, Particule<Dim>*>(hash_key, *part_it));
    }
    // for (part_it = lignedEau.begin(); part_it != lignedEau.end(); part_it++) {
    // 	for (unsigned int i = 1; i <= Dim; i++) {
    // 	    noeud_grille(i) = int(floor((*part_it)->getPosition()(i)/mat->getRayonNoyau()));
    // 	}
    //     hash_key = fonction_hashage(noeud_grille);
    //     hash_voisins.insert(pair<int, Particule<Dim>*>(hash_key, *part_it));
    // }
}

template<>
inline set<Particule<2>*> Fluide<2>::voisinage(Particule<2>& p) {
    set<Particule<2>*> res;
    double rnoyau = mat->getRayonNoyau();
    /* Noeuds correspondant à la bounding box de la particule */
    int bbmin[2] = {int(floor((p.getPosition()(1)-2*rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(2)-2*rnoyau)/rnoyau))};
    int bbmax[2] = {int(floor((p.getPosition()(1)+2*rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(2)+2*rnoyau)/rnoyau))};
    /* Paire d'itérateurs (début et fin) sur les particules de clé hash_key */
    pair<multimap<int, Particule<2>*>::iterator,  multimap<int, Particule<2>*>::iterator> part_pit;
    multimap<int, Particule<2>*>::iterator part_it;
    int hash_key;

    /* On boucle sur tous les noeuds de la bounding box */
    for (int i = bbmin[0]; i <= bbmax[0]; ++i) {
        for (int j = bbmin[1]; j <= bbmax[1]; ++j) {
            hash_key = fonction_hashage(Vecteur<2>(i, j));
            part_pit = hash_voisins.equal_range(hash_key);

            /* On rajoute les particules trouvées dans la liste */
            for (part_it = part_pit.first; part_it != part_pit.second; ++part_it) {
                res.insert(part_it->second);
            }
        }
    }

    /* Dans ces voisins, on ne garde que ceux qui sont dans la sphère */
    set<Particule<2>*>::iterator set_it;
    set<Particule<2>*>::iterator a_suppr;
    for (set_it = res.begin(); set_it != res.end(); ) {
        if ((p.getPosition() == (*set_it)->getPosition())
            || (p.getPosition() - (*set_it)->getPosition()).norme() > 2*rnoyau) {
            a_suppr = set_it;
            ++set_it;
            res.erase(a_suppr);
        } else {
            ++set_it;
        }
    }
    return res;
}


template<>
inline set<Particule<3>*> Fluide<3>::voisinage(Particule<3>& p) {
    set<Particule<3>*> res;
    double rnoyau = mat->getRayonNoyau();
    /* Noeuds correspondant à la bounding box de la particule */
    int bbmin[3] = {int(floor((p.getPosition()(1)-2*rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(2)-2*rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(3)-2*rnoyau)/rnoyau))};
    int bbmax[3] = {int(floor((p.getPosition()(1)+2*rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(2)+2*rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(3)+2*rnoyau)/rnoyau))};
    /* Paire d'itérateurs (début et fin) sur les particules de clé hash_key */
    pair<multimap<int, Particule<3>*>::iterator, multimap<int, Particule<3>*>::iterator> part_pit;
    multimap<int, Particule<3>*>::iterator part_it;
    int hash_key;

    /* On boucle sur tous les noeuds de la bounding box */
    for (int i = bbmin[0]; i <= bbmax[0]; ++i) {
        for (int j = bbmin[1]; j <= bbmax[1]; ++j) {
            for (int k = bbmin[2]; k <= bbmax[2]; ++k) {
                hash_key = fonction_hashage(Vecteur<3>(i, j, k));
                part_pit = hash_voisins.equal_range(hash_key);

                /* On rajoute les particules trouvées dans la liste */
                for (part_it = part_pit.first; part_it != part_pit.second; ++part_it) {
                    res.insert(part_it->second);
                }
            }
        }
    }

    /* Dans ces voisins, on ne garde que ceux qui sont dans la sphère */
    set<Particule<3>*>::iterator set_it;
    set<Particule<3>*>::iterator a_suppr;
    for (set_it = res.begin(); set_it != res.end(); ) {
        if ((p.getPosition() == (*set_it)->getPosition())
            || (p.getPosition() - (*set_it)->getPosition()).norme() > 2*rnoyau) {
            a_suppr = set_it;
            ++set_it;
            res.erase(a_suppr);
        } else {
            ++set_it;
        }
    }
    return res;
}


template<unsigned int Dim>
list<Particule<Dim> *> Fluide<Dim>::getParticulesMobiles() {
    return particules;
}


template<unsigned int Dim>
list<Particule<Dim> *> Fluide<Dim>::getParticulesImmobiles() {
    return lignedEau;
}


template<unsigned int Dim>
Materiau<Dim>* Fluide<Dim>::getMateriau() {
    return mat;
}


template<unsigned int Dim>
void Fluide<Dim>::majDensitePression() {

    typename list<Particule<Dim> *>::iterator it1;
    NoyauLissageMonaghan<Dim> noyau = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());
    set<Particule<Dim>*> voisins;    
    typename set<Particule<Dim>*>::iterator it2;
    //typename list<Particule<Dim>*>::iterator it2;

    // On boucles sur toutes les particules
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
    
        // On met leur masse volumique à jour
        //double somme = 0.0; // "particules"
	double somme = noyau.defaut(Vecteur<Dim>()); // "voisins"
        voisins = voisinage(*(*it1));
        
        //cout << "Rayon noyau " << mat->getRayonNoyau() << endl;
        for (it2 = voisins.begin(); it2 != voisins.end(); it2++) {
            //cout << "voisin " << (*it2)->getIndice() << " " << ((*it1)->getPosition() - (*it2)->getPosition()).norme() << endl;
            //for (it2 = particules.begin(); it2 != particules.end(); it2++) {
            // if (noyau.defaut((*it1)->getPosition() - (*it2)->getPosition()) != 0
            //     && ((*it1)->getPosition() - (*it2)->getPosition()).norme() != 0) {
            //    cout << (*it2)->getIndice() << " " << ((*it1)->getPosition() - (*it2)->getPosition()).norme() << endl;
            // }
            somme += noyau.defaut((*it1)->getPosition() - (*it2)->getPosition());
        }
        (*it1)->setMasseVolumique((mat->getMasseParticules())*somme);
        
        // On met leur pression à jour
        (*it1)->majPression(mat->getDensiteRepos());
        //cout << endl;
    }

    // for (it1 = lignedEau.begin(); it1 != lignedEau.end(); it1++) {

    //     // On met leur masse volumique à jour
    //     double somme = noyau.defaut(Vecteur<Dim>());
    //     voisins = voisinage(*(*it1));
    //     for (it2 = voisins.begin(); it2 != voisins.end(); it2++)
    //         somme += noyau.defaut((*it1)->getPosition() - (*it2)->getPosition());
    //     (*it1)->setMasseVolumique((mat->getMasseParticules())*somme);   
    //     // On met la pression a jour
    //     (*it1)->majPression(mat->getCeleriteSon(), mat->getDensiteRepos());
    // }
}


// Fonction interne appelee lors de la detection de collisions
// Elle detecte une collision avec les plans X=x_min, X=x_max, Y=y_min, Y=y_max et Z=z_min
// Elle renvoie le point de contact s'il y a collision, le Vecteur v sinon
template<unsigned int Dim>
Vecteur<Dim> Fluide<Dim>::collision(const Vecteur<Dim> & v) {
    Vecteur<Dim> res = Vecteur<Dim>(v);

    if (Dim == 2) {
        if (v(1) < x_min)
            res(1) = x_min;
        if (v(1) > x_max)
            res(1) = x_max;
        if (v(2) < y_min)
            res(2) = y_min;
        if (v(2) > y_max)
            res(2) = y_max;
    } else {
        if (v(1) < x_min)
            res(1) = x_min;
        if (v(1) > x_max)
            res(1) = x_max;
        if (v(2) < y_min)
            res(2) = y_min;
        if (v(2) > y_max)
            res(2) = y_max;
        if (v(3) < z_min)
            res(3) = z_min;
    }
    
    return res;
}


template<unsigned int Dim>
void Fluide<Dim>::majPositionVitesse() {

    typename list<Particule<Dim> *>::iterator it1;
    NoyauLissageMonaghan<Dim> noyauMonaghan = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());

    // On boucles sur toutes les particules
    // Ci-dessous, factorisation de calculs
    double masse = mat->getMasseParticules();
    double nu_numerateur = 2*mat->getRayonNoyau()*mat->getConstanteViscosite()*mat->getCeleriteSon();

    set<Particule<Dim>*> voisins;

    typename set<Particule<Dim>*>::iterator it2;
    //typename list<Particule<Dim>*>::iterator it2;
    
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
 
        // Definition de toutes les forces
        Vecteur<Dim> fPression = Vecteur<Dim>();
        Vecteur<Dim> fViscosite = Vecteur<Dim>();
        Vecteur<Dim> fGravite = Vecteur<Dim>();
        // Vecteur<Dim> fSurface = Vecteur<Dim>();
        // double colorfield = 0;
        
        // Calcul des sommes utiles aux forces de pression, de viscosite et de surface,
        // selon l'article de Becker et Teschner (WCSPH). Ci-dessous, quelques variables
        // ayant pour but la factorisation des calculs, même si le résultat peut sembler
        // moins clair qu'en écrivant des choses (*it1)->... dans les calculs 
        double termePressionDensite_a = (*it1)->getPression() / pow((*it1)->getMasseVolumique(), 2);
        double masseVolumique_a = (*it1)->getMasseVolumique();

        voisins = voisinage(*(*it1));
        for (it2 = voisins.begin(); it2 != voisins.end(); it2++) {
            //for (it2 = particules.begin(); it2 != particules.end(); it2++) {
            // Quelques variables locales pour factoriser le calcul
            Vecteur<Dim> x_ab = (*it1)->getPosition() - (*it2)->getPosition();
            Vecteur<Dim> v_ab = (*it1)->getVitesse() - (*it2)->getVitesse();
            double termePressionDensite_b = (*it2)->getPression() / pow((*it2)->getMasseVolumique(), 2);
            double masseVolumique_b = (*it2)->getMasseVolumique();

            // Expression des forces
            fPression -= noyauMonaghan.gradient(x_ab) * (termePressionDensite_a + termePressionDensite_b);

            double prodScal = (v_ab).scalaire(x_ab);
            if (prodScal < 0) {
                double nu = nu_numerateur / (masseVolumique_a + masseVolumique_b);
                double coeffTest = pow(mat->getRayonNoyau(), 2)/4;
                fViscosite += noyauMonaghan.gradient(x_ab) * nu * (prodScal / ( (0.01*coeffTest) + pow(x_ab.norme(), 2)));
            }

            //colorfield += noyauMonaghan.laplacien(x_ab) / masseVolumique_b;
            //fSurface += noyauMonaghan.gradient(x_ab) / masseVolumique_b;
        }
        
        // Calcul des forces de gravité, de pression, de viscosite et de surface
        fGravite = masseVolumique_a * mat->getAccGrav();
        //fPression *= masse * masse;
        fPression *= masse * masseVolumique_a /100;
        fViscosite *= masse * masseVolumique_a;
        //fViscosite *= masse * masse;
        
	// fSurface *= masse;
	// double norme = fSurface.norme();
	// if (norme >= mat->getSeuilSurface()) {
	//     colorfield *= masse;
	//     fSurface *= -colorfield * mat->getTensionSurface() / norme;
	// } else {
	//     fSurface = Vecteur<Dim>();
	// }
                
        // Calcul de l'acceleration
	//if (it1 == particules.begin()) {
        // cout << "fPression : " << fPression << endl;
        // cout << "fViscosite : "<< fViscosite << endl;
        // cout << "fGravite : " << fGravite << endl;
        // cout << "fSurface : " << fSurface << endl;
	//}
        //(*it1)->setAcceleration((fPression + fViscosite + fGravite + fSurface) / masseVolumique_a);

        //cout << "forces " << (fPression + fViscosite + fGravite) << endl;
        (*it1)->setAcceleration((fPression + fViscosite + fGravite) / masseVolumique_a);

    }
    
    // On boucle une nouvelle fois sur toutes les particules pour mettre leur position
    // et leur vitesse a jour et tester les collisions
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
        // Calcul de la nouvelle vitesse (qu'on retient au temps t+Dt/2)
        if (debutAnim) {
            //(*it1)->incrVitesse(mat->getPasTemps() * (*it1)->getAcceleration() / 2);
            //cout << "Vitesse " << mat->getPasTemps() * (*it1)->getAcceleration() << endl;
            (*it1)->incrVitesse(mat->getPasTemps() * (*it1)->getAcceleration());
            debutAnim = false;
        } else {
            //cout << "Vitesse " << mat->getPasTemps() * (*it1)->getAcceleration() << endl;
            (*it1)->incrVitesse(mat->getPasTemps() * (*it1)->getAcceleration());
        }
        
        // Calcul de la nouvelle position (au temps t+Dt)
        (*it1)->incrPosition(mat->getPasTemps() * (*it1)->getVitesse());
        
        // Detection des collisions
        Vecteur<Dim> pos = (*it1)->getPosition();
        Vecteur<Dim> contact = collision(pos);
        
        // Si il y a collision, on met a jour la position et la vitesse
        if (contact != pos) {
            pos = contact - pos;
            double dist = pos.norme();
            Vecteur<Dim> normale = pos / dist;
        
            // Mise a jour de la position
            (*it1)->setPosition(contact);
            
            // Mise a jour de la vitesse
           // (*it1)->setVitesse((*it1)->getVitesse()
           //                    - (1 + mat->getCoeffRestitution() * dist
           //                       / (mat->getPasTemps() * ((*it1)->getVitesse()).norme()))
           //                    * (((*it1)->getVitesse()).scalaire(normale)) * normale);
double vitesse = (*it1)->getVitesse().scalaire(normale);
(*it1)->setVitesse(-vitesse*normale + (*it1)->getVitesse() - vitesse*normale);
        }
    }

    /* On met la table de hachage à jour */
    majTableHashage();
}


template<unsigned int Dim>
void Fluide<Dim>::draw() {
     //typename list<Particule<Dim> *>::const_iterator it;
     //for (it = particules.begin (); it != particules.end (); it++) {
     //    (*it)->draw ();
     //}
    // for (it = lignedEau.begin (); it != lignedEau.end (); it++) {
    //     (*it)->draw ();
    // }
   
    ball.coloration(particules);
    ball.draw();
}


template<unsigned int Dim>
void Fluide<Dim>::affiche() {
    typename list<Particule<Dim> *>::iterator it;
    int i = 0;
    for (it = particules.begin(); it != particules.end(); it++) {
        cout << "P" << i << " : " << endl;
        cout << "    " << (**it) << endl;
        i++;
    }
}

template<unsigned int Dim>
Vecteur<Dim> Fluide<Dim>::calculForcesInteraction(Particule<Dim>* p1, Particule<Dim>* p2) {
    
    NoyauLissageMonaghan<Dim> noyauMonaghan = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());

    /* Factorisations pour les calculs */
    double masse = mat->getMasseParticules();
    double nu_numerateur = 2*mat->getRayonNoyau()*mat->getConstanteViscosite()*mat->getCeleriteSon();

    /* Définition de toutes les forces d'interaction */
    Vecteur<Dim> fPression = Vecteur<Dim>();
    Vecteur<Dim> fViscosite = Vecteur<Dim>();
    // Vecteur<Dim> fSurface = Vecteur<Dim>();
    // double colorfield = 0;  // pour seuiller les forces de surface

    /* Variables locales */
    Vecteur<Dim> x_1_2 = p2->getPosition() - p1->getPosition();
    Vecteur<Dim> v_1_2 = p2->getVitesse() - p1->getVitesse();
    double termePressionDensite_1 = p1->getPression() / pow(p1->getMasseVolumique(), 2);
    double masseVolumique_1 = p1->getMasseVolumique();
    double termePressionDensite_2 = p2->getPression() / pow(p2->getMasseVolumique(), 2);
    double masseVolumique_2 = p2->getMasseVolumique();

    /* **Expressions des forces** */

    /* Force de pression */
    fPression -= noyauMonaghan.gradient(x_1_2) * (termePressionDensite_1 + termePressionDensite_2);

    /* Force de viscosité */
    double prodScal = (v_1_2).scalaire(x_1_2);
    if (prodScal < 0) {
        double nu = nu_numerateur / (masseVolumique_1 + masseVolumique_2);
        double coeffTest = pow(mat->getRayonNoyau(), 2)/4;
        fViscosite += noyauMonaghan.gradient(x_1_2) * nu * (prodScal / ( (0.01*coeffTest) + pow(x_1_2.norme(), 2)));
    }

    /* Force de tension de surface */
    // colorfield += noyauMonaghan.laplacien(x_1_2) / masseVolumique_2;
    // fSurface += noyauMonaghan.gradient(x_1_2) / masseVolumique_2;
    // double norme = fSurface.norme();
    // if (norme >= mat->getSeuilSurface()) {
    //     colorfield *= masse;
    //     fSurface *= -colorfield * mat->getTensionSurface() / norme;
    // } else {
    //     fSurface = Vecteur<Dim>();
    // }

    /* Multiplications par les facteurs constants */
    fPression *= masse * masseVolumique_1 / 100;
    fViscosite *= masse * masseVolumique_1;
    // fSurface *= masse;

    //cout << "fPression : " << fPression << endl;
    
    return fPression + fViscosite; //+ fSurface;
}

template<unsigned int Dim>
Vecteur<Dim> Fluide<Dim>::calculForcesInteractionPrec(Particule<Dim>* p1, Particule<Dim>* p2) {
    
    NoyauLissageMonaghan<Dim> noyauMonaghan = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());

    /* Factorisations pour les calculs */
    double masse = mat->getMasseParticules();
    double nu_numerateur = 2*mat->getRayonNoyau()*mat->getConstanteViscosite()*mat->getCeleriteSon();

    /* Définition de toutes les forces d'interaction */
    Vecteur<Dim> fPression = Vecteur<Dim>();
    Vecteur<Dim> fViscosite = Vecteur<Dim>();
    // Vecteur<Dim> fSurface = Vecteur<Dim>();
    // double colorfield = 0;  // pour seuiller les forces de surface

    /* Variables locales */
    Vecteur<Dim> x_1_2 = p2->getPositionPrec() - p1->getPositionPrec();
    Vecteur<Dim> v_1_2 = p2->getVitessePrec() - p1->getVitessePrec();
    double termePressionDensite_1 = p1->getPression() / pow(p1->getMasseVolumique(), 2);
    double masseVolumique_1 = p1->getMasseVolumique();
    double termePressionDensite_2 = p2->getPression() / pow(p2->getMasseVolumique(), 2);
    double masseVolumique_2 = p2->getMasseVolumique();

    /* **Expressions des forces** */

    /* Force de pression */
    fPression -= noyauMonaghan.gradient(x_1_2) * (termePressionDensite_1 + termePressionDensite_2);

    /* Force de viscosité */
    double prodScal = (v_1_2).scalaire(x_1_2);
    if (prodScal < 0) {
        double nu = nu_numerateur / (masseVolumique_1 + masseVolumique_2);
        double coeffTest = pow(mat->getRayonNoyau(), 2)/4;
        fViscosite += noyauMonaghan.gradient(x_1_2) * nu * (prodScal / ( (0.01*coeffTest) + pow(x_1_2.norme(), 2)));
    }

    /* Force de tension de surface */
    // colorfield += noyauMonaghan.laplacien(x_1_2) / masseVolumique_2;
    // fSurface += noyauMonaghan.gradient(x_1_2) / masseVolumique_2;
    // double norme = fSurface.norme();
    // if (norme >= mat->getSeuilSurface()) {
    //     colorfield *= masse;
    //     fSurface *= -colorfield * mat->getTensionSurface() / norme;
    // } else {
    //     fSurface = Vecteur<Dim>();
    // }

    /* Multiplications par les facteurs constants */
    fPression *= masse * masseVolumique_1 / 100;
    fViscosite *= masse * masseVolumique_1;
    // fSurface *= masse;

    //cout << "fPression : " << fPression << endl;
    
    return fPression + fViscosite; //+ fSurface;
    //return Vecteur<Dim>();
}

template<unsigned int Dim>
void Fluide<Dim>::integrationForces() {
    set<Particule<Dim>*> vois;
    typename set<Particule<Dim>*>::iterator vois_it;
    typename list<Particule<Dim> *>::iterator part_it;
    
    if (debutAnim) {
        affiche();
        /* Premier pas de l'animation */
        for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
            /* On boucle sur toutes les particules */
            vois = voisinage(*(*part_it));
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur tous les voisins de la particule */
                if ((*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* On ne veut considérer les couples qu'une fois */
                    /* Ajouter interactions */
                    Vecteur<Dim> forces = calculForcesInteraction(*part_it, *vois_it);
                    (*part_it)->incrForces(forces);
                    (*vois_it)->decrForces(forces);
                }
            }
            /* Ajout des forces non interactives */
            (*part_it)->incrForces((*part_it)->getMasseVolumique() * mat->getAccGrav());   // force de gravité
            cout << "forces début : " << (*part_it)->getForces() << endl;
        }
        debutAnim = false;

    } else {
        /* Au milieu de l'algorithme incrémental */
        double rho;
        Vecteur<Dim> drho;
        
        /* On se base sur les anciennes positions pour enlever les anciennes forces */
        cout << "Forces enlevées :" << endl;
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On boucle sur les particules actives */
            vois = voisinage(*(*part_it));
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur tous les voisins de la particule */
                restriction((*vois_it)->getVitesse(), rho, drho);
                if (rho == 1  // la particule voisine n'est pas active : il faut quand même
                              // mettre à jour les forces d'interaction entre elles,
                              // mais vois_it ne pourra pas le faire
                    || (*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* Enlever interactions */
                    Vecteur<Dim> forcesPrec = calculForcesInteractionPrec(*part_it, *vois_it);
                    (*part_it)->decrForces(forcesPrec);
                    (*vois_it)->incrForces(forcesPrec);
                    cout << " " << (*part_it)->getIndice() << " " << (*vois_it)->getIndice()
                         << " " << forcesPrec << endl;
                }
            }
            cout << "forces avant : " << (*part_it)->getForces() << endl;
        }

        /*
         * On met à jour les positions dans la grille de voxels :
         * on met à jour la hashtable, uniquement pour les particules actives,
         * car les autres n'ont pas modifié leur position
         */
        /* Paire d'itérateurs (début et fin) sur les particules de clé hash_key */
        pair<typename multimap<int, Particule<Dim>*>::iterator, typename multimap<int, Particule<Dim>*>::iterator> part_pit;
        typename multimap<int, Particule<Dim>*>::iterator hash_it;
        int hash_key;
        Vecteur<Dim> noeud_grille;
        /* On boucle sur les particules actives */
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On récupère les particules de même clé que la particule courante */
            for (unsigned int i = 1; i <= Dim; i++) {
                noeud_grille(i) = int(floor((*part_it)->getPositionPrec()(i)/mat->getRayonNoyau()));
            }
            hash_key = fonction_hashage(noeud_grille);
            part_pit = hash_voisins.equal_range(hash_key);
            /* On récupère la particule courante */
            hash_it = part_pit.first;
            while (hash_it != part_pit.second && (*hash_it).second != *part_it) {
                ++hash_it;
            }
            /* On enlève la particule de la table des voisins */
            hash_voisins.erase(hash_it);

            /* On la réinsère avec sa clé mise à jour avec sa nouvelle position */
            for (unsigned int i = 1; i <= Dim; i++) {
                noeud_grille(i) = int(floor((*part_it)->getPosition()(i)/mat->getRayonNoyau()));
            }
            hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(noeud_grille), *part_it));
        }
        
        /* On ajoute les forces correspondant aux nouvelles positions */
        cout << "Forces ajoutées :" << endl;
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On boucle sur les particules actives */
            vois = voisinage(*(*part_it));
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur tous les voisins de la particule */
                restriction((*vois_it)->getVitesse(), rho, drho);
                if (rho == 1  // la particule voisine n'est pas active : il faut quand même
                              // mettre à jour les forces d'interaction entre elles,
                              // mais vois_it ne pourra pas le faire
                    || (*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* */
                    /* Ajouter interactions */
                    Vecteur<Dim> forces = calculForcesInteraction(*part_it, *vois_it);
                    (*part_it)->incrForces(forces);
                    (*vois_it)->decrForces(forces);
                    cout << " " << (*part_it)->getIndice() << " " << (*vois_it)->getIndice()
                         << " " << forces << endl;
                }
            }
            cout << "forces : " << (*part_it)->getForces() << endl;
        }

    }
}

template <unsigned int Dim>
double Fluide<Dim>::calculCritere(const Vecteur<Dim>& moment) {
    double critere = 0;
    for (unsigned int i = 1; i <= Dim; ++i) {
        critere += moment(i)*moment(i);
    }
    critere /= (2.0*mat->getMasseParticules());
    return critere;
}

template <unsigned int Dim>
void Fluide<Dim>::restriction(const Vecteur<Dim>& moment, double &rho, Vecteur<Dim>& drho) {
    double critere = calculCritere(moment); 

    /* Calcul Rho */
    if(critere <= this->epsilonR) {
        rho = 1.0;
    } else if(critere >= this->epsilonF) {
        rho = 0.0;
    } else if(critere > this->epsilonR && critere < this->epsilonF) {
        double x = (critere - this->epsilonR) / (this->epsilonF - this->epsilonR);
        rho = -6*x*x*x*x*x + 15*x*x*x*x - 10*x*x*x + 1;
    }

    /* Calcul Drho */
    if(rho == 1.0 || rho == 0.0) {
        for (unsigned int i = 1; i <= Dim; ++i) {
            drho(i) = 0.0;
        }
    } else if(rho > 0.0 && rho < 1.0) {
        double x = (critere-this->epsilonR) / (this->epsilonF-this->epsilonR);
        double alpha = (-30*x*x*x*x + 60*x*x*x - 30*x*x);
        alpha /= (mat->getMasseParticules() * (this->epsilonF - this->epsilonR));
        for (unsigned int i = 1; i <= Dim; ++i) {
            drho(i) = alpha*moment(i);
        }
    }
    
}

template<unsigned int Dim>
void Fluide<Dim>::afficher_actives() {
    cout << "Particules actives :" << endl;
    typename list<Particule<Dim>*>::iterator act_it;
    cout << "   ";
    for (act_it = actives.begin(); act_it != actives.end(); ++act_it) {
        cout << (*act_it)->getIndice() << " ";
    }
    cout << endl;
}

template<unsigned int Dim>
void Fluide<Dim>::schemaIntegration() {

    /* Mise à jour des densité et pression des particules */
    majDensitePression();
    
    /* Mise à jour des forces */
    integrationForces();

    /* Pour itérer sur les particules */
    typename list<Particule<Dim> *>::iterator part_it;

    /* Mise à jour des vitesses */
    for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
        (*part_it)->setVitessePrec((*part_it)->getVitesse());
        cout << "Vitesse " << (*part_it)->getForces()*mat->getPasTemps()/(*part_it)->getMasseVolumique() << endl;
        (*part_it)->incrVitesse((*part_it)->getForces()*mat->getPasTemps()/(*part_it)->getMasseVolumique());
    }

    /* Réinitialisation de la liste des particules actives */
    actives.clear();
    for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
        /* Mise à jour de la liste des particules actives */
        double rho;
        Vecteur<Dim> drho;
        restriction((*part_it)->getVitesse(), rho, drho);
        cout << "Restriction : " << rho <<  " | " << drho << endl;
        if (rho < 1) {
            actives.push_back(*part_it);
        }
        /* Mise à jour des positions */
        Vecteur<Dim> incr = mat->getPasTemps() * 
            ((*part_it)->getVitesse() / mat->getMasseParticules() * (1 - rho)
             - 0.5 * pow((*part_it)->getVitesse().norme(), 2) / mat->getMasseParticules() * drho
             );
        cout << "Incr position " << incr << endl;
        (*part_it)->setPositionPrec((*part_it)->getPosition());
        (*part_it)->incrPosition(incr); // /mat->getMasseParticules());
        
        /* Détection des collisions */
        Vecteur<Dim> pos = (*part_it)->getPosition();
        Vecteur<Dim> contact = collision(pos);
        
        /* S'il y a collision, on met à jour la position et la vitesse */
        if (contact != pos) {
            pos = contact - pos;
            double dist = pos.norme();
            Vecteur<Dim> normale = pos / dist;
        
            /* Mise à jour de la position */
            (*part_it)->setPosition(contact);
            
            /* Mise à jour de la vitesse */
            (*part_it)->setVitesse((*part_it)->getVitesse()
                                   - (1 + mat->getCoeffRestitution() * dist
                                      / (mat->getPasTemps() * ((*part_it)->getVitesse()).norme()))
                                   * (((*part_it)->getVitesse()).scalaire(normale)) * normale);
        }
    }
    afficher_actives();

}
