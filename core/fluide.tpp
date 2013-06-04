#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

#include "fluide.hpp"
#include "noyauLissage.hpp"
using std::cout;
using std::endl;
using std::pair;

/* ** Constructeurs ** */

template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m)
    : mat(m),
      nbrParticules(0),
      debutAnim(true),
      hash_voisins(),
      lgrHash(0)
{
    // Initilisation de la liste vide
    particules = list<Particule<Dim> *>();
    lignedEau = list<Particule<Dim> *>();
    if (Dim == 2) {
        x_min = -1.0;
        x_max = 1.0;
        y_min = 0;
        y_max = 2;
        z_min = 0;
    } else if (Dim == 3) {
        x_min = -1.0;
        x_max = 1.0;
        y_min = -1.0;
        y_max = 1.0;
        z_min = 0;
    }
}


template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m, int nb[Dim], double ecart, double rho, double p)
    : mat(m),
      debutAnim(true),
      hash_voisins()
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

    if (Dim == 2) {
    
        nbrParticules = nb[0]*nb[1];
        lgrHash = table.getPremier(2*nbrParticules);

        // Ici, on est en dimension 2
        // On va ajouter des particules regulierement disposees sur les deux dimensions
        // On définit la largeur de la boîte
        x_min = -1.0;
        x_max = 1.0;
        y_min = 0;
        y_max = 2;
        z_min = 0;
        
        // On définit ensuite la position des particules
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j < nb[1]; j++) {
                Vecteur<Dim> vec = Vecteur<Dim>((i-nb[0]/2)*ecart, 0.1 + j*ecart);
                Particule<Dim> *part = new Particule<Dim>(vec, Vecteur<Dim>(), mat->getMasseParticules(), rho, p);
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
        x_min = -1.0;
        x_max = 1.0;
        y_min = -1.0;
        y_max = 1.0;
        z_min = 0;
        
        // On définit ensuite la position des particules
        double largeur_x = x_max - x_min;
        double largeur_y = y_max - y_min;
        
        if (largeur_x < nb[0]*ecart || largeur_y < nb[1]*ecart) {
            cout << "Fluide<Dim>::Fluide(Materiau<Dim> * m, int nb[Dim], double ecart, double rho, double p)" << endl;
            cout << "Erreur : trop de particules pour les dimensions de la boîte" << endl;
            exit (1);
        }
        
        Vecteur<Dim> vec;
        Particule<Dim> *part;
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j < nb[1]; j++) {
                for (int k = 0; k < nb[2]; k++) {
                
                    // On ajoute de l'alea pour rendre le fluide plus realiste
                    double x = 0.02 * (rand() / double(RAND_MAX) - 0.5);
                    double y = 0.02 * (rand() / double(RAND_MAX) - 0.5);
                    double z = 0.02 * (rand() / double(RAND_MAX) - 0.5);
                    Vecteur<Dim> alea = Vecteur<Dim>(x,y,z);
                    
                    vec = Vecteur<Dim>((i-nb[0]/2)*ecart, (j-nb[1]/2)*ecart, 0.1 + k*ecart) + alea;
                    part = new Particule<Dim>(vec, Vecteur<Dim>(), mat->getMasseParticules(), rho, p);
                    particules.push_back(part);
                    noeud_grille(1) = int(floor(part->getPosition()(1)/mat->getRayonNoyau()));
                    noeud_grille(2) = int(floor(part->getPosition()(2)/mat->getRayonNoyau()));
                     noeud_grille(3) = int(floor(part->getPosition()(3)/mat->getRayonNoyau()));
                    hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(noeud_grille), part));               
                }
            }
        }
        
	//Ligne rigide de particules
	int nb_x = largeur_x/0.03;
	int nb_y = largeur_y/0.03;
	for (int i = 0; i <= nb_x; i++) {
	    for (int j = 0; j <= nb_y; j++) {
		vec = Vecteur<Dim>((x_min + largeur_x*(double(i)/double(nb_x))),
				   (y_min + largeur_y*(double(j)/double(nb_y))),
				   z_min);
		part = new Particule<Dim> (vec, Vecteur<Dim>(), 0.0, rho, p);
		lignedEau.push_back(part);
		hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(part->getPosition()), part));
	    }
	}
        cout << "On a construit " << particules.size() << " particules mobiles ";
        cout << "et " << lignedEau.size() << " particules fixes" << endl;
        
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


template<>
inline set<Particule<2>*> Fluide<2>::voisinage(Particule<2>& p) {
    set<Particule<2>*> res;
    double rnoyau = mat->getRayonNoyau();
    /* Noeuds correspondant à la bounding box de la particule */
    int bbmin[2] = {int(floor((p.getPosition()(1)-rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(2)-rnoyau)/rnoyau))};
    int bbmax[2] = {int(floor((p.getPosition()(1)+rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(2)+rnoyau)/rnoyau))};
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
            || (p.getPosition() - (*set_it)->getPosition()).norme() > rnoyau) {
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
    int bbmin[3] = {int(floor((p.getPosition()(1)-rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(2)-rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(3)-rnoyau)/rnoyau))};
    int bbmax[3] = {int(floor((p.getPosition()(1)+rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(2)+rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(3)+rnoyau)/rnoyau))};
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
            || (p.getPosition() - (*set_it)->getPosition()).norme() > rnoyau) {
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
    //typename set<Particule<Dim>*>::iterator it2;
    typename list<Particule<Dim>*>::iterator it2;

//    cout<<"appel MAJDP"<<endl;
//    int i = 0;
    // On boucles sur toutes les particules
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
        // On met leur masse volumique à jour
        double somme = noyau.defaut(Vecteur<Dim>());

        voisins = voisinage(*(*it1));
//        cout << "P" << i << " : " << voisins.size() << endl;
        for (it2 = particules.begin(); it2 != particules.end(); it2++) {  
//        for (it2 = voisins.begin(); it2 != voisins.end(); it2++) {
//            cout<<(**it2)<<endl;
            somme += noyau.defaut((*it1)->getPosition() - (*it2)->getPosition());
        }

        (*it1)->setMasseVolumique((mat->getMasseParticules())*somme);
        
        // On met leur pression à jour
        (*it1)->majPression(mat->getCeleriteSon(), mat->getDensiteRepos());
//        i++;
    }

//    for (it1 = lignedEau.begin(); it1 != lignedEau.end(); it1++) {
//        double somme = noyau.defaut(Vecteur<Dim>());
//        voisins = voisinage(*(*it1));
//        for (it2 = voisins.begin(); it2 != voisins.end(); it2++)
//            somme += noyau.defaut((*it1)->getPosition() - (*it2)->getPosition());
//            
//        (*it1)->setMasseVolumique((mat->getMasseParticules())*somme);
//        
//        // On met la pression a jour
//        (*it1)->majPression(mat->getCeleriteSon(), mat->getDensiteRepos());
//    }
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

    //typename set<Particule<Dim>*>::iterator it2;
    typename list<Particule<Dim>*>::iterator it2;
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
 
        // Definition de toutes les forces
        Vecteur<Dim> fPression = Vecteur<Dim>();
        Vecteur<Dim> fViscosite = Vecteur<Dim>();
        Vecteur<Dim> fGravite = Vecteur<Dim>();
        Vecteur<Dim> fSurface = Vecteur<Dim>();
        double colorfield = 0;
        
        // Calcul des sommes utiles aux forces de pression, de viscosite et de surface,
        // selon l'article de Becker et Teschner (WCSPH). Ci-dessous, quelques variables
        // ayant pour but la factorisation des calculs, même si le résultat peut sembler
        // moins clair qu'en écrivant des choses (*it1)->... dans les calculs 
        double termePressionDensite_a = (*it1)->getPression() / pow((*it1)->getMasseVolumique(), 2);
        double masseVolumique_a = (*it1)->getMasseVolumique();

        voisins = voisinage(*(*it1));
        // for (it2 = voisins.begin(); it2 != voisins.end(); it2++) {
        for (it2 = particules.begin(); it2 != particules.end(); it2++) {
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
                fViscosite += noyauMonaghan.gradient(x_ab) * nu * (prodScal / (0.0001 + pow(x_ab.norme(), 2)));
            }

            colorfield += noyauMonaghan.laplacien(x_ab) / masseVolumique_b;
          
            fSurface += noyauMonaghan.gradient(x_ab) / masseVolumique_b;
        }
        
        // Calcul des forces de gravité, de pression, de viscosite et de surface
        fGravite = masseVolumique_a * mat->getAccGrav();
        fPression *= masse * masseVolumique_a / 1000000;
        fViscosite *= masse * masseVolumique_a;
        fSurface *= masse;
        double norme = fSurface.norme();
        if (norme >= mat->getSeuilSurface()) {
            colorfield *= masse;
            fSurface *= -colorfield * mat->getTensionSurface() / norme;
        } else {
            fSurface = Vecteur<Dim>();
        }
                
        // Calcul de l'acceleration
        // cout << "fPression : " << fPression << endl;
        // cout << "fViscosite : "<< fViscosite << endl;
        // cout << "fGravite : " << fGravite << endl;
        // cout << "fSurface : " << fSurface << endl;
        (*it1)->setAcceleration((fPression + fViscosite + fGravite + fSurface) / masseVolumique_a);

    }
    
    // On boucle une nouvelle fois sur toutes les particules pour mettre leur position
    // et leur vitesse a jour et tester les collisions
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
        // Calcul de la nouvelle vitesse (qu'on retient au temps t+Dt/2)
        if (debutAnim) {
            (*it1)->incrVitesse(mat->getPasTemps() * (*it1)->getAcceleration() / 2);
            debutAnim = false;
        } else {
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
            (*it1)->setVitesse((*it1)->getVitesse()
                               - (1 + mat->getCoeffRestitution() * dist
                                  / (mat->getPasTemps() * ((*it1)->getVitesse()).norme()))
                               * (((*it1)->getVitesse()).scalaire(normale)) * normale);
        }
    }


    /* On met la table de hachage à jour */
    hash_voisins.clear();
    int hash_key;
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
        hash_key = fonction_hashage((*it1)->getPosition());
        hash_voisins.insert(pair<int, Particule<Dim>*>(hash_key, *it1));
    }
    for (it1 = lignedEau.begin(); it1 != lignedEau.end(); it1++) {
        hash_key = fonction_hashage((*it1)->getPosition());
        hash_voisins.insert(pair<int, Particule<Dim>*>(hash_key, *it1));
    }

}


template<unsigned int Dim>
void Fluide<Dim>::draw() const {
    typename list<Particule<Dim> *>::const_iterator it;
    for (it = particules.begin (); it != particules.end (); it++) {
        (*it)->draw (mat);
    }
    // for (it = lignedEau.begin (); it != lignedEau.end (); it++) {
    //    (*it)->draw (mat);
    // }
}


template<unsigned int Dim>
void Fluide<Dim>::affiche() {
    typename list<Particule<Dim> *>::iterator it;
    int i = 0;
    for (it = particules.begin(); it != particules.end(); it++) {
        cout << "P" << i << " : " << endl;
        cout << (**it) << endl;
        i++;
    }
}
