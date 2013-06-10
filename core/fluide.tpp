#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

#include "fluide.hpp"
#include "noyauLissage.hpp"

using std::cout;
using std::endl;
using std::pair;

#define EPSR 4
#define DELTA 150
#define METABALLS 1 // Mettre a 1 pour dessiner les surface implicites, 0 sinon

/* ** Constructeurs ** */

template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m)
    : mat(m),
      ball (Metaballs(Vecteur<3>(-0.5, -0.5, 0.0), 0.05, mat->getRayonNoyau(), 1, 1, 0.5)),
      nbrParticules(0),
      debutAnim(true),
      hash_voisins(),
      lgrHash(0),
      epsilonR(EPSR),
      epsilonF(EPSR+DELTA)
{
    /* Initilisation de la liste vide */
    particules = list<Particule<Dim> *>();
    
    /* Définition des dimensions et de la metaball suivant la dimension */
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
    }
}


template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m, int nb[Dim], double ecart, double rho, double p, Vecteur<Dim> v0,
                    double xmin, double xmax, double ymin, double ymax, double zmin)
    : mat(m),
      ball (Metaballs(Vecteur<3>(xmin, ymin, zmin), 0.05, mat->getRayonNoyau(), xmax-xmin, ymax-ymin, 1)),
      x_min(xmin),
      x_max(xmax),
      y_min(ymin),
      y_max(ymax),
      z_min(zmin),
      debutAnim(true),
      hash_voisins(),
      epsilonR(EPSR),
      epsilonF(EPSR+DELTA)
{
    /* Initialisation de listes vides */
    particules = list<Particule<Dim> *>();

    // Création d'une table des nombres premiers 
    // pour calculer la dimension de la table de hashage
    //    Premier<Dim> table = Premier<Dim>();

    /* Pour la conversion des coordonnées de la particule dans la grille de voxels */
    Vecteur<Dim> noeud_grille;

    /* Compteur pour numéroter les particules */
    unsigned int cpt = 0;

    if (Dim == 2) {
    
        nbrParticules = nb[0]*nb[1];
        lgrHash = table.getPremier(2*nbrParticules);
        
        /* On définit la position des particules */
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j < nb[1]; j++) {
                ++cpt;
                Vecteur<Dim> vec = Vecteur<Dim>((i-nb[0]/2)*ecart, 0.01+ j*ecart);
                Particule<Dim> *part = new Particule<Dim>(cpt, vec, v0, mat->getMasseParticules(), rho, p);
                particules.push_back(part);
                noeud_grille(1) = int(floor(part->getPosition()(1)/mat->getRayonNoyau()));
                noeud_grille(2) = int(floor(part->getPosition()(2)/mat->getRayonNoyau()));
                hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(noeud_grille), part));
            }
        }
        
    } else if (Dim == 3) {
    
        nbrParticules = nb[0]*nb[1]*nb[2];
        lgrHash = table.getPremier(2*nbrParticules);
        
        /* On définit la position des particules */
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
                    /* On ajoute de l'aléa pour rendre le fluide plus réaliste */
                    double x = 0.02 * (rand() / double(RAND_MAX) - 0.5);
                    double y = 0.02 * (rand() / double(RAND_MAX) - 0.5);
                    double z = 0.02 * (rand() / double(RAND_MAX) - 0.5);
                    Vecteur<Dim> alea = Vecteur<Dim>(x,y,fabs(z));                    
                    vec = Vecteur<Dim>((i-nb[0]/2)*ecart, (j-nb[1]/2)*ecart, k*ecart) + alea;
                    // vec = Vecteur<Dim>((i-nb[0]/2)*ecart, (j-nb[1]/2)*ecart, 0.1 + k*ecart);
                    
                    part = new Particule<Dim>(cpt, vec, v0, mat->getMasseParticules(), rho, p);
                    particules.push_back(part);
                    noeud_grille(1) = int(floor(part->getPosition()(1)/mat->getRayonNoyau()));
                    noeud_grille(2) = int(floor(part->getPosition()(2)/mat->getRayonNoyau()));
                    noeud_grille(3) = int(floor(part->getPosition()(3)/mat->getRayonNoyau()));
                    hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(noeud_grille), part));               
                }
            }
        }

    } else {
        cout << "Erreur (Fluide) : la dimension de l'espace doit être 2 ou 3" << endl;
        exit(1);
    }
}


template<unsigned int Dim>
Fluide<Dim>::~Fluide() {
    typename list<Particule<Dim> *>::iterator it;
    /* On libère toutes les particules */
    for (it = particules.begin(); it != particules.end();it++) {
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
    /* On vide la table */
    hash_voisins.clear();

    typename list<Particule<Dim>*>::iterator part_it;
    int hash_key;
    /* Vecteur d'entiers représentants les indices dans la grille de voxels */
    Vecteur<Dim> noeud_grille;

    /* Puis on réinsère toutes les particules */
    for (part_it = particules.begin(); part_it != particules.end(); part_it++) {
        for (unsigned int i = 1; i <= Dim; i++) {
            noeud_grille(i) = int(floor((*part_it)->getPosition()(i)/mat->getRayonNoyau()));
        }
        hash_key = fonction_hashage(noeud_grille);
        hash_voisins.insert(pair<int, Particule<Dim>*>(hash_key, *part_it));
    }
    
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

template<>
inline set<Particule<2>*> Fluide<2>::voisinagePrec(Particule<2>& p) {
    set<Particule<2>*> res;
    double rnoyau = mat->getRayonNoyau();
    
    /* Noeuds correspondant à la bounding box de la particule */
    int bbmin[2] = {int(floor((p.getPositionPrec()(1)-2*rnoyau)/rnoyau)),
                    int(floor((p.getPositionPrec()(2)-2*rnoyau)/rnoyau))};
    int bbmax[2] = {int(floor((p.getPositionPrec()(1)+2*rnoyau)/rnoyau)),
                    int(floor((p.getPositionPrec()(2)+2*rnoyau)/rnoyau))};
                    
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
        if ((p.getPositionPrec() == (*set_it)->getPositionPrec())
            || (p.getPositionPrec() - (*set_it)->getPositionPrec()).norme() > 2*rnoyau) {
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
inline set<Particule<3>*> Fluide<3>::voisinagePrec(Particule<3>& p) {
    set<Particule<3>*> res;
    double rnoyau = mat->getRayonNoyau();
    
    /* Noeuds correspondant à la bounding box de la particule */
    int bbmin[3] = {int(floor((p.getPositionPrec()(1)-2*rnoyau)/rnoyau)),
                    int(floor((p.getPositionPrec()(2)-2*rnoyau)/rnoyau)),
                    int(floor((p.getPositionPrec()(3)-2*rnoyau)/rnoyau))};
    int bbmax[3] = {int(floor((p.getPositionPrec()(1)+2*rnoyau)/rnoyau)),
                    int(floor((p.getPositionPrec()(2)+2*rnoyau)/rnoyau)),
                    int(floor((p.getPositionPrec()(3)+2*rnoyau)/rnoyau))};
                    
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
        if ((p.getPositionPrec() == (*set_it)->getPositionPrec())
            || (p.getPositionPrec() - (*set_it)->getPositionPrec()).norme() > 2*rnoyau) {
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
Materiau<Dim>* Fluide<Dim>::getMateriau() {
    return mat;
}


template<unsigned int Dim>
void Fluide<Dim>::majDensitePression() {

    typename list<Particule<Dim> *>::iterator it1;
    NoyauLissageMonaghan<Dim> noyau = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());
    set<Particule<Dim>*> voisins;    
    typename set<Particule<Dim>*>::iterator it2;

    /* On boucle sur toutes les particules */
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
        /* On mémorise les valeurs précédentes */
        (*it1)->setMasseVolumiquePrec((*it1)->getMasseVolumique());
        (*it1)->setPressionPrec((*it1)->getPression());
    
        /* On met leur masse volumique à jour */
        double somme = noyau.defaut(Vecteur<Dim>());
        voisins = voisinage(*(*it1));
        
        for (it2 = voisins.begin(); it2 != voisins.end(); it2++) {
            // cout << (*it1)->getIndice() << ".voisin " << (*it2)->getIndice() << " " << ((*it1)->getPosition() - (*it2)->getPosition()).norme() << endl;
            somme += noyau.defaut((*it1)->getPosition() - (*it2)->getPosition());
        }
        
        (*it1)->setMasseVolumique((mat->getMasseParticules())*somme);
        
        /* On met leur pression à jour */
        (*it1)->majPression(mat->getDensiteRepos());
    }

}


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

/*
 * Fonction interne appelée lors de la détection de collisions
 * Elle détecte une collision avec les plans X=x_min, X=x_max, Y=y_min, Y=y_max et Z=z_min
 * Elle renvoie le point de contact s'il y a collision, le Vecteur v sinon
 */
template<unsigned int Dim>
//Vecteur<Dim> Fluide<Dim>::collisionCascade(const Vecteur<Dim> & v,  const Cascade<Dim> c) {

Vecteur<Dim> Fluide<Dim>::collisionCascade(const Vecteur<Dim> & v,
					   Materiau<Dim> *mat,
					   const double bassin_x,
					   const double bassin_y,
					   const double bassin_z) {

    Vecteur<Dim> res = Vecteur<Dim>(v);
    double rayon = pow((3 * mat->getRigiditeGaz())/(4 * PI * mat->getPression()), 1.0/3.0);
    rayon += 0.3*rayon;

    if (Dim == 2) {
        
    } else {
	if ((v(3)-rayon) < 0 && (v(1)+rayon) < bassin_x) // En dessous du fond du bassin
	    res(3) = 0+rayon;
        if ((v(1)-rayon) < 0 && (v(3)-rayon) < bassin_z) // Derrière la boite
	      res(1) = 0+rayon;
	if ((v(1)+rayon) >= bassin_x && (v(1)+rayon) <= (bassin_x+2*rayon) && (v(3)-rayon) < bassin_z/3) // Devant la boite
	    res(1) = bassin_x-rayon;
	if ((v(2)-rayon) < -bassin_y/2 && (v(3)-rayon) < bassin_z) // Coté gauche du bassin
	    res(2) = -bassin_y/2+rayon;
	if ((v(2)+rayon) > bassin_y/2 && (v(3)-rayon) < bassin_z) // Coté droit du bassin
	    res(2) = bassin_y/2-rayon;

    }
    return res;
}

template<unsigned int Dim>
void Fluide<Dim>::majPositionVitesse() {

    typename list<Particule<Dim> *>::iterator it1;
    NoyauLissageMonaghan<Dim> noyauMonaghan = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());

    /* On boucle sur toutes les particules */
    /* Ci-dessous, factorisation de calculs */
    double masse = mat->getMasseParticules();
    double nu_numerateur = 2*mat->getRayonNoyau()*mat->getConstanteViscosite()*mat->getCeleriteSon();

    set<Particule<Dim>*> voisins;

    typename set<Particule<Dim>*>::iterator it2;
    
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
 
        /* Définition de toutes les forces */
        Vecteur<Dim> fPression = Vecteur<Dim>();
        Vecteur<Dim> fViscosite = Vecteur<Dim>();
        Vecteur<Dim> fGravite = Vecteur<Dim>();
        Vecteur<Dim> fSurface = Vecteur<Dim>();
        double colorfield = 0;
        
        /*
         * Calcul des sommes utiles aux forces de pression, de viscosite et de surface,
         * selon l'article de Becker et Teschner (WCSPH)
         */
        double termePressionDensite_a = (*it1)->getPression() / pow((*it1)->getMasseVolumique(), 2);
        double masseVolumique_a = (*it1)->getMasseVolumique();

        voisins = voisinage(*(*it1));
        for (it2 = voisins.begin(); it2 != voisins.end(); it2++) {
        
            /* Quelques variables locales pour factoriser le calcul */
            Vecteur<Dim> x_ab = (*it1)->getPosition() - (*it2)->getPosition();
            Vecteur<Dim> v_ab = (*it1)->getVitesse() - (*it2)->getVitesse();
            double termePressionDensite_b = (*it2)->getPression() / pow((*it2)->getMasseVolumique(), 2);
            double masseVolumique_b = (*it2)->getMasseVolumique();

            /* Expression des forces */
            fPression -= noyauMonaghan.gradient(x_ab) * (termePressionDensite_a + termePressionDensite_b);

            double prodScal = (v_ab).scalaire(x_ab);
            if (prodScal < 0) {
                double nu = nu_numerateur / (masseVolumique_a + masseVolumique_b);
                double coeffTest = pow(mat->getRayonNoyau(), 2)/4;
                fViscosite += noyauMonaghan.gradient(x_ab) * nu * (prodScal / ( (0.01*coeffTest) + pow(x_ab.norme(), 2)));
            }

            colorfield += noyauMonaghan.laplacien(x_ab) / masseVolumique_b;
            fSurface += noyauMonaghan.gradient(x_ab) / masseVolumique_b;
        }
        
        /* Calcul des forces de gravité, de pression, de viscosité et de surface */
        fGravite = masseVolumique_a * mat->getAccGrav();
        fPression *= masse * masseVolumique_a /100;
        fViscosite *= masse * masseVolumique_a;
        
        fSurface *= masse;
        double norme = fSurface.norme();
        if (norme >= mat->getSeuilSurface()) {
            colorfield *= masse;
            fSurface *= -colorfield * mat->getTensionSurface() / norme;
        } else {
            fSurface = Vecteur<Dim>();
        }

        /* Calcul de l'acceleration */
        // cout << (*it1)->getIndice() << ". totalforces : " << (fPression + fViscosite + fGravite + fSurface) << endl;
        (*it1)->setAcceleration((fPression + fViscosite + fGravite + fSurface) / masseVolumique_a);

    }
    
    /*
     * On boucle une nouvelle fois sur toutes les particules pour mettre leur position
     * et leur vitesse à jour et tester les collisions
     */
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
    
        /* Calcul de la nouvelle vitesse (qu'on retient au temps t+Dt/2) */
        if (debutAnim) {
            (*it1)->incrVitesse(mat->getPasTemps() * (*it1)->getAcceleration() / 2);
        } else {
            (*it1)->incrVitesse(mat->getPasTemps() * (*it1)->getAcceleration());
        }
        
        /* Calcul de la nouvelle position (au temps t+Dt) */
        // cout << (*it1)->getIndice() << ". incrPos : " << mat->getPasTemps() * (*it1)->getVitesse() << endl;
        (*it1)->setPositionPrec((*it1)->getPosition());
        (*it1)->incrPosition(mat->getPasTemps() * (*it1)->getVitesse());
        
        /* Détection des collisions */
        Vecteur<Dim> pos = (*it1)->getPosition();
        Vecteur<Dim> contact = collision(pos);
	//Vecteur<Dim> contact = collisionCascade(pos, mat, 2.0, 1.0, 0.5);
        
        /* S'il y a collision, on met a jour la position et la vitesse */
        if (contact != pos) {
            pos = contact - pos;
            double dist = pos.norme();
            Vecteur<Dim> normale = pos / dist;
        
            /* Mise à jour de la position */
            (*it1)->setPosition(contact);
            
            /* Mise a jour de la vitesse */
            double vitesse = (*it1)->getVitesse().scalaire(normale);
            (*it1)->setVitesse(-mat->getCoeffRestitution() *vitesse*normale + (*it1)->getVitesse() - vitesse*normale);
        }
    }
    debutAnim = false;

    /* On met la table de hachage à jour */
    majTableHashage();
    
    /* On met à jour la coloration des sommets pour le calcul de la surface implicite */
    if (METABALLS)
        ball.coloration(particules);
}


template<unsigned int Dim>
void Fluide<Dim>::colorationMetaball() {
    if (METABALLS)
        ball.coloration(particules);
}


template<unsigned int Dim>
void Fluide<Dim>::draw() {

    if (METABALLS) {
        ball.draw();
    } else {
        typename list<Particule<Dim> *>::const_iterator it;
        for (it = particules.begin(); it != particules.end(); it++) {
            (*it)->draw();
        }
    }

    glPushMatrix();
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0, 1.0, 1.0, 0.1);
    glBegin(GL_QUADS);
    
    glNormal3f(-1, 0, 0);
    glVertex3f(x_min - 0.025, y_min - 0.025, z_min - 0.025);
    glVertex3f(x_min - 0.025, y_max + 0.025, z_min - 0.025);
    glVertex3f(x_min - 0.025, y_max + 0.025, 1);
    glVertex3f(x_min - 0.025, y_min - 0.025, 1);
    
    glNormal3f(0, -1, 0);
    glVertex3f(x_min - 0.025, y_min - 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_min - 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_min - 0.025, 1);
    glVertex3f(x_min - 0.025, y_min - 0.025, 1);
    
    glNormal3f(1, 0, 0);
    glVertex3f(x_max + 0.025, y_min - 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_max + 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_max + 0.025, 1);
    glVertex3f(x_max + 0.025, y_min - 0.025, 1);
    
    glNormal3f(0, 1, 0);
    glVertex3f(x_min - 0.025, y_max + 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_max + 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_max + 0.025, 1);
    glVertex3f(x_min - 0.025, y_max + 0.025, 1);
    
    glNormal3f(0, 0, -1);
    glVertex3f(x_min - 0.025, y_min - 0.025, z_min - 0.025);
    glVertex3f(x_min - 0.025, y_max + 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_max + 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_min - 0.025, z_min - 0.025);
    
    glEnd();
    glDisable (GL_BLEND);
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
    Vecteur<Dim> fSurface = Vecteur<Dim>();
    double colorfield = 0;  // pour seuiller les forces de surface

    /* Variables locales */
    Vecteur<Dim> x_1_2 = p1->getPosition() - p2->getPosition();
    /* On récupère la vitesse effective des particules, et non celle accumulée */
    double rho;
    Vecteur<Dim> drho;
    restriction(p2->getVitesse(), rho, drho);
    // Vecteur<Dim> v2 = p2->getVitesse() * (1 - rho) - 0.5 * pow(p2->getVitesse().norme(), 2)
    //     * p2->getMasseVolumique() * drho;
    Vecteur<Dim> v2 = p2->getVitesse() * (1 - rho) - 0.5 * pow(p2->getVitesse().norme(), 2)
        * mat->getMasseParticules() * drho;
    restriction(p1->getVitesse(), rho, drho);
    // Vecteur<Dim> v1 = p1->getVitesse() * (1 - rho) - 0.5 * pow(p1->getVitesse().norme(), 2)
    //     * p1->getMasseVolumique() * drho;
    Vecteur<Dim> v1 = p1->getVitesse() * (1 - rho) - 0.5 * pow(p1->getVitesse().norme(), 2)
        * mat->getMasseParticules() * drho;
    Vecteur<Dim> v_1_2 = v1 - v2;
    /* Renommages */
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
    colorfield += noyauMonaghan.laplacien(x_1_2) / masseVolumique_2;
    fSurface += noyauMonaghan.gradient(x_1_2) / masseVolumique_2;
    double norme = fSurface.norme();
    if (norme >= mat->getSeuilSurface()) {
        colorfield *= masse;
        fSurface *= -colorfield * mat->getTensionSurface() / norme;
    } else {
        fSurface = Vecteur<Dim>();
    }

    /* Multiplications par les facteurs constants */
    fPression *= masse * masseVolumique_1 / 100;
    fViscosite *= masse * masseVolumique_1;
    fSurface *= masse;
    
    return fPression + fViscosite + fSurface;
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
    Vecteur<Dim> fSurface = Vecteur<Dim>();
    double colorfield = 0;  // pour seuiller les forces de surface

    /* Variables locales */
    Vecteur<Dim> x_1_2 = p1->getPositionPrec() - p2->getPositionPrec();
    /* On récupère la vitesse effective des particules, et non celle accumulée */
    double rho;
    Vecteur<Dim> drho;
    restriction(p2->getVitessePrec(), rho, drho);
    // Vecteur<Dim> v2 = p2->getVitessePrec() * (1 - rho) - 0.5 * pow(p2->getVitessePrec().norme(), 2)
    //     * p2->getMasseVolumiquePrec() * drho;
    Vecteur<Dim> v2 = p2->getVitessePrec() * (1 - rho) - 0.5 * pow(p2->getVitessePrec().norme(), 2)
        * mat->getMasseParticules() * drho;
    restriction(p1->getVitessePrec(), rho, drho);
    // Vecteur<Dim> v1 = p1->getVitessePrec() * (1 - rho) - 0.5 * pow(p1->getVitessePrec().norme(), 2)
    //     * p1->getMasseVolumiquePrec() * drho;
    Vecteur<Dim> v1 = p1->getVitessePrec() * (1 - rho) - 0.5 * pow(p1->getVitessePrec().norme(), 2)
        * mat->getMasseParticules() * drho;
    Vecteur<Dim> v_1_2 = v1 - v2;
    /* Renommages */
    double termePressionDensite_1 = p1->getPressionPrec() / pow(p1->getMasseVolumiquePrec(), 2);
    double masseVolumique_1 = p1->getMasseVolumiquePrec();
    double termePressionDensite_2 = p2->getPressionPrec() / pow(p2->getMasseVolumiquePrec(), 2);
    double masseVolumique_2 = p2->getMasseVolumiquePrec();

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
    colorfield += noyauMonaghan.laplacien(x_1_2) / masseVolumique_2;
    fSurface += noyauMonaghan.gradient(x_1_2) / masseVolumique_2;
    double norme = fSurface.norme();
    if (norme >= mat->getSeuilSurface()) {
        colorfield *= masse;
        fSurface *= -colorfield * mat->getTensionSurface() / norme;
    } else {
        fSurface = Vecteur<Dim>();
    }

    /* Multiplications par les facteurs constants */
    fPression *= masse * masseVolumique_1 / 100;
    fViscosite *= masse * masseVolumique_1;
    fSurface *= masse;
    
    return fPression + fViscosite + fSurface;
}

template<unsigned int Dim>
void Fluide<Dim>::integrationForces() {
    set<Particule<Dim>*> vois;
    typename set<Particule<Dim>*>::iterator vois_it;
    typename list<Particule<Dim> *>::iterator part_it;
    
    if (debutAnim) {
        // affiche();
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
            // cout << (*part_it)->getIndice() << ". forces début : " << (*part_it)->getForces() << endl;
        }
        debutAnim = false;

    } else {
        /* Au milieu de l'algorithme incrémental */
        double rho;
        Vecteur<Dim> drho;
        
        /* On se base sur les anciennes positions pour enlever les anciennes forces */
        // cout << endl << "********************************************" << endl;
        // cout << "Forces enlevées :" << endl;
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On boucle sur les particules actives */
            vois = voisinagePrec(*(*part_it));
            // cout << (*part_it)->getIndice() << ". forces précédentes : " << (*part_it)->getForces() << endl;
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
                    // cout << " " << (*part_it)->getIndice() << " " << (*vois_it)->getIndice()
                    //      << " " << forcesPrec << endl;
                    // cout << " => force intermédiaire : " << (*part_it)->getForces() << endl;
                }
            }
            // cout << endl;
        }

        // cout << "BILAN des forces :" << endl;
        // for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
        //     cout << (*part_it)->getIndice() << " totalforces : " << (*part_it)->getForces() << endl;
        // }


        /*
         * On met à jour les positions dans la grille de voxels :
         * on met à jour la hashtable, uniquement pour les particules actives,
         * car les autres n'ont pas modifié leur position
         */
        // majTableHashage();
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
            //part_pit = hash_voisins.equal_range(hash_key);

            /* On récupère la particule courante */
            //hash_it = part_pit.first;
            hash_it = hash_voisins.find(hash_key);
            // while (hash_it != part_pit.second && (*hash_it).second != *part_it) {
            while (hash_it->second != *part_it && hash_it != hash_voisins.end()) {
                if (hash_it->first != hash_key) {
                    // cout << "**********************************oho" << endl;
                }
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
        // cout << endl << "********************************************" << endl;
        // cout << "Forces ajoutées :" << endl;
        for (part_it = actives.begin(); part_it != actives.end(); ++part_it) {
            /* On boucle sur les particules actives */
            vois = voisinage(*(*part_it));
            // cout << (*part_it)->getIndice() << ". forces précédentes : " << (*part_it)->getForces() << endl;
            for (vois_it = vois.begin(); vois_it != vois.end(); ++vois_it) {
                /* Boucle sur tous les voisins de la particule */
                restriction((*vois_it)->getVitesse(), rho, drho);
                if (rho == 1  // la particule voisine n'est pas active : il faut quand même
                              // mettre à jour les forces d'interaction entre elles,
                              // mais vois_it ne pourra pas le faire
                    || (*part_it)->getIndice() < (*vois_it)->getIndice()) {
                    /* Ajouter interactions */
                    Vecteur<Dim> forces = calculForcesInteraction(*part_it, *vois_it);
                    (*part_it)->incrForces(forces);
                    (*vois_it)->decrForces(forces);
                    // cout << " " << (*part_it)->getIndice() << " " << (*vois_it)->getIndice()
                    //      << " " << forces << endl;
                    // cout << " => force intermédiaire : " << (*part_it)->getForces() << endl;
                }
            }
            // cout << endl;
        }

        // cout << "BILAN des forces :" << endl;
        // for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
        //     cout << (*part_it)->getIndice() << " totalforces : " << (*part_it)->getForces() << endl;
        // }

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

    // cout << endl << "|||||||||||||||||||||||||| NOUVEAU PAS ||||||||||||||||||||||||||" << endl;
    
    /* Mise à jour des densité et pression des particules */
    majDensitePression();
    
    /* Mise à jour des forces */
    integrationForces();

    /* Pour itérer sur les particules */
    typename list<Particule<Dim> *>::iterator part_it;

    /* Mise à jour des vitesses */
    // cout << endl << "********************************************" << endl;
    for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
        (*part_it)->setVitessePrec((*part_it)->getVitesse());
        // cout << (*part_it)->getIndice() << ".Vitesse " << (*part_it)->getForces()*mat->getPasTemps()/(*part_it)->getMasseVolumique() << endl;
        (*part_it)->incrVitesse((*part_it)->getForces()*mat->getPasTemps()/(*part_it)->getMasseVolumique());
    }

    /* Réinitialisation de la liste des particules actives */
    actives.clear();
    cout << endl;
    // cout << endl << "********************************************" << endl;
    for (part_it = particules.begin(); part_it != particules.end(); ++part_it) {
        /* Mise à jour de la liste des particules actives */
        double rho;
        Vecteur<Dim> drho;
        restriction((*part_it)->getVitesse(), rho, drho);
        // cout << (*part_it)->getIndice() << ". Restriction : " << rho <<  " | " << drho << endl;
        if (rho < 1) {
            actives.push_back(*part_it);
        } else {
            cout << (*part_it)->getIndice() << " pas active" << endl;
        }
        /* Mise à jour des positions */
        Vecteur<Dim> incr = mat->getPasTemps() * 
            ((*part_it)->getVitesse() * (1 - rho)
             - 0.5 * pow((*part_it)->getVitesse().norme(), 2) * mat->getMasseParticules() * drho
             );
        // cout << (*part_it)->getIndice() << ". Incr position " << incr << endl;
        (*part_it)->setPositionPrec((*part_it)->getPosition());
        (*part_it)->incrPosition(incr); 
        
        /* Détection des collisions */
        Vecteur<Dim> pos = (*part_it)->getPosition();
        Vecteur<Dim> contact = collision(pos);
        
        /* S'il y a collision, on met a jour la position et la vitesse */
        if (contact != pos) {
            pos = contact - pos;
            double dist = pos.norme();
            Vecteur<Dim> normale = pos / dist;
        
            /* Mise à jour de la position */
            (*part_it)->setPosition(contact);
            
            /* Mise a jour de la vitesse */
            double vitesse = (*part_it)->getVitesse().scalaire(normale);
            (*part_it)->setVitesse(-mat->getCoeffRestitution() * vitesse*normale + (*part_it)->getVitesse() - vitesse*normale);
        }
    }
    
    // cout << endl << "********************************************" << endl;
    // afficher_actives();

}

template <unsigned int Dim>
void Fluide<Dim>::changerParam() {
    cout << "Quels paramètres voulez-vous modifier?" << endl;
}
