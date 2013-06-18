#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

#include "fluide.hpp"
#include "noyauLissage.hpp"

using std::cout;
using std::endl;
using std::pair;

/* Macros pour initialiser les seuils de l'ARPS */
#define EPSR 1
#define DELTA 2

#define METABALLS 0 // Mettre a 1 pour dessiner des surfaces, 0 pour des particules
#define POINT 0     // Mettre a 1 pour dessiner des points, 0 pour des spheres
#define CASCADE 1   // Mettre a 1 pour les collisions avec la cascade

/* ** Constructeurs ** */

template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m)
    : mat(m),
      nbrParticules(0),
      debutAnim(true),
      afficheMetaballs(METABALLS),
      affichePoint(POINT),
      hash_voisins(),
      lgrHash(0),
      epsilonR(EPSR),
      epsilonF(EPSR+DELTA),
      ecart(0)
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
Fluide<Dim>::Fluide(Materiau<Dim> * m, Vecteur<Dim> nbP, double e, double rho, double p, Vecteur<Dim> v0,
                    double xmin, double xmax, double ymin, double ymax, double zmin)
    : mat(m),
      x_min(xmin),
      x_max(xmax),
      y_min(ymin),
      y_max(ymax),
      z_min(zmin),
      debutAnim(true),
      afficheMetaballs(METABALLS),
      affichePoint(POINT),
      vitInit(v0),
      densiteInit(rho),
      pressionInit(p),
      hash_voisins(),
      epsilonR(EPSR),
      epsilonF(EPSR+DELTA),
      nbPart(nbP),
      ecart(e)
{
    particules = list<Particule<Dim> *>();

    init();
}


template<unsigned int Dim>
Fluide<Dim>::~Fluide() {
    clear();
}

template<unsigned int Dim>
void Fluide<Dim>::clear() {
    typename list<Particule<Dim> *>::iterator it;
    /* On libère toutes les particules */
    for (it = particules.begin(); it != particules.end();it++) {
        delete (*it);
    }
    hash_voisins.clear();
    actives.clear();
}

template <unsigned int Dim>
void Fluide<Dim>::init() {

    /* On supprime les anciennes particules etc */
    clear();

    /* On commence l'animation */
    debutAnim = true;
    
    /* Initialisation de liste vide */
    particules = list<Particule<Dim> *>();

    /* Pour la conversion des coordonnées de la particule dans la grille de voxels */
    Vecteur<Dim> noeud_grille;

    /* Compteur pour numéroter les particules */
    unsigned int cpt = 0;

    if (Dim == 2) {

        /* Initialisation de nb */
        int nb[2] = {int(nbPart(1)),
                     int(nbPart(2))};
        
        nbrParticules = nb[0]*nb[1];
        lgrHash = table.getPremier(2*nbrParticules);
        matF = MatriceForces<Dim>(nbrParticules);
        
        /* On définit la position des particules */
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j < nb[1]; j++) {
                ++cpt;
                Vecteur<Dim> vec = Vecteur<Dim>((i-nb[0]/2)*ecart, 0.01+ j*ecart);
                Particule<Dim> *part = new Particule<Dim>(cpt, vec, vitInit, mat->getMasseParticules(), densiteInit, pressionInit);
                particules.push_back(part);
                noeud_grille(1) = int(floor(part->getPosition()(1)/mat->getRayonNoyau()));
                noeud_grille(2) = int(floor(part->getPosition()(2)/mat->getRayonNoyau()));
                hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(noeud_grille), part));
            }
        }
        
    } else if (Dim == 3) {
    
        /* Initialisation de nb */
        int nb[3] = {int(nbPart(1)),
                     int(nbPart(2)),
                     int(nbPart(3))};
        
        nbrParticules = nb[0]*nb[1]*nb[2];
        lgrHash = table.getPremier(2*nbrParticules);
        matF = MatriceForces<Dim>(nbrParticules);
        
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
                    
                    part = new Particule<Dim>(cpt, vec, vitInit, mat->getMasseParticules(), densiteInit, pressionInit);
                    particules.push_back(part);
                    noeud_grille(1) = int(floor(part->getPosition()(1)/mat->getRayonNoyau()));
                    noeud_grille(2) = int(floor(part->getPosition()(2)/mat->getRayonNoyau()));
                    noeud_grille(3) = int(floor(part->getPosition()(3)/mat->getRayonNoyau()));
                    hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(noeud_grille), part));               
                }
            }
        }
    
        /* Initialisation de la metaball */

#if CASCADE
        ball = new Metaballs(Vecteur<3>(-0.6, -0.6, -3.0), 0.01, mat->getRayonNoyau(), 3.7, 1.2, 3.6);
#else 
        ball = new Metaballs(Vecteur<3>(x_min, y_min, z_min), 0.01, mat->getRayonNoyau(), x_max-x_min, y_max-y_min, 1.2);
#endif
	
        if (afficheMetaballs) {
            ball->initColoration(particules);
        }
    } else {
        cout << "Erreur (Fluide) : la dimension de l'espace doit être 2 ou 3" << endl;
        exit(1);
    }
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
        cout << " " << (*mmap_it).first << " => " << ((*mmap_it).second)->getIndice() << endl;
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
            somme += noyau.defaut((*it1)->getPosition() - (*it2)->getPosition());
        }
        
        (*it1)->setMasseVolumique((mat->getMasseParticules())*somme);
        
        /* On met leur pression à jour */
        (*it1)->majPression(mat->getDensiteRepos());
    }

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
        if (voisins.size() >= 10 || ((*it1)->getVitesse().norme() < 0.1)) {
            (*it1)->setCouleur(0.0);
        } else {
            (*it1)->setCouleur(1 - voisins.size()/10.0);
        }

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
        (*it1)->setPositionPrec((*it1)->getPosition());
        (*it1)->incrPosition(mat->getPasTemps() * (*it1)->getVitesse());
        
        /* Détection des collisions */
        Vecteur<Dim> pos = (*it1)->getPosition();
        Vecteur<Dim> contact;
#if (!CASCADE)
        contact = collision(pos);
#else
        contact = collisionCascade(pos, mat, 0.5, 0.5, 0.5);
#endif
        
        /* S'il y a collision, on met a jour la position et la vitesse */
        if (contact != pos) {
            pos = contact - pos;
            double dist = pos.norme();
            Vecteur<Dim> normale = pos / dist;
        
            /* Mise à jour de la position */
            (*it1)->setPosition(contact);
            
            /* Mise a jour de la vitesse */
            double vitesse = (*it1)->getVitesse().scalaire(normale);
            
            // (*it1)->incrVitesse(-(1+mat->getCoeffRestitution()) * vitesse*normale);
            /* Technique plus adaptee dans le cas de la vague, qui consiste a empecher 
             * Les particules de s'empiler sur un bord */
             if (normale(3) < 0.001 && (*it1)->getVitesse()(3) < 0.0) {
                 (*it1)->incrVitesse(-3 * vitesse * normale);
             } else {
                 (*it1)->incrVitesse(-(1+mat->getCoeffRestitution()) * vitesse * normale);
             }
        }
    }
    debutAnim = false;

    /* On met la table de hachage à jour */
    majTableHashage();
    
    /* On met à jour la coloration des sommets pour le calcul de la surface implicite */
    if (afficheMetaballs) {
        ball->coloration(particules);
    }
}


template<unsigned int Dim>
void Fluide<Dim>::colorationMetaball() {
    if (afficheMetaballs) {
        if (debutAnim) {
            ball->initColoration(particules);
        } else {
            ball->coloration(particules);
        }
    }
}


template<unsigned int Dim>
void Fluide<Dim>::draw() {

    if (afficheMetaballs) {
        ball->draw();
    } else {
        typename list<Particule<Dim> *>::const_iterator it;
        for (it = particules.begin(); it != particules.end(); it++) {
            (*it)->draw(affichePoint);
        }
    }
    
    glNormal3f(-1, 0, 0);
    glVertex3f(x_min - 0.025, y_min - 0.025, z_min - 0.025);
    glVertex3f(x_min - 0.025, y_max + 0.025, z_min - 0.025);
    glVertex3f(x_min - 0.025, y_max + 0.025, 1.1);
    glVertex3f(x_min - 0.025, y_min - 0.025, 1.1);
    
    glNormal3f(0, -1, 0);
    glVertex3f(x_min - 0.025, y_min - 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_min - 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_min - 0.025, 1.1);
    glVertex3f(x_min - 0.025, y_min - 0.025, 1.1);
    
    glNormal3f(1, 0, 0);
    glVertex3f(x_max + 0.025, y_min - 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_max + 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_max + 0.025, 1.1);
    glVertex3f(x_max + 0.025, y_min - 0.025, 1.1);
    
    glNormal3f(0, 1, 0);
    glVertex3f(x_min - 0.025, y_max + 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_max + 0.025, z_min - 0.025);
    glVertex3f(x_max + 0.025, y_max + 0.025, 1.1);
    glVertex3f(x_min - 0.025, y_max + 0.025, 1.1);

#if (!CASCADE)

    double decalage;
    if (afficheMetaballs)
        decalage = 0.005;
    else
        decalage = 0.025;

    glPushMatrix();
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0, 1.0, 1.0, 0.1);
    glBegin(GL_QUADS);
    
    glNormal3f(-1, 0, 0);
    glVertex3f(x_min - decalage, y_min - decalage, z_min - decalage);
    glVertex3f(x_min - decalage, y_max + decalage, z_min - decalage);
    glVertex3f(x_min - decalage, y_max + decalage, 1.2);
    glVertex3f(x_min - decalage, y_min - decalage, 1.2);
    
    glNormal3f(0, -1, 0);
    glVertex3f(x_min - decalage, y_min - decalage, z_min - decalage);
    glVertex3f(x_max + decalage, y_min - decalage, z_min - decalage);
    glVertex3f(x_max + decalage, y_min - decalage, 1.2);
    glVertex3f(x_min - decalage, y_min - decalage, 1.2);
    
    glNormal3f(1, 0, 0);
    glVertex3f(x_max + decalage, y_min - decalage, z_min - decalage);
    glVertex3f(x_max + decalage, y_max + decalage, z_min - decalage);
    glVertex3f(x_max + decalage, y_max + decalage, 1.2);
    glVertex3f(x_max + decalage, y_min - decalage, 1.2);
    
    glNormal3f(0, 1, 0);
    glVertex3f(x_min - decalage, y_max + decalage, z_min - decalage);
    glVertex3f(x_max + decalage, y_max + decalage, z_min - decalage);
    glVertex3f(x_max + decalage, y_max + decalage, 1.2);
    glVertex3f(x_min - decalage, y_max + decalage, 1.2);
    
    glNormal3f(0, 0, -1);
    glVertex3f(x_min - decalage, y_min - decalage, z_min - decalage);
    glVertex3f(x_min - decalage, y_max + decalage, z_min - decalage);
    glVertex3f(x_max + decalage, y_max + decalage, z_min - decalage);
    glVertex3f(x_max + decalage, y_min - decalage, z_min - decalage);
    
    glEnd();
    glDisable (GL_BLEND);
#endif
}

template<unsigned int Dim>
void Fluide<Dim>::draw(struct QVector<QVector3D> *vertices, struct QVector<QVector4D> *colors, struct QVector<int> *indices) {
    vertices->clear();
    colors->clear();
    indices->clear();
    typename list<Particule<Dim> *>::const_iterator it;
    int i = 0;
    for (it = particules.begin(); it != particules.end(); it++) {
        Vecteur<Dim> posIt = (*it)->getPosition();
        vertices->push_back(QVector3D(posIt(1), posIt(2), posIt(3)));
        colors->push_back(QVector4D(0.0, 1.0, 0.0, 0.0));
        indices->push_back(i);
        i++;
    }
}

template<unsigned int Dim>
void Fluide<Dim>::affiche() {
    typename list<Particule<Dim> *>::iterator it;
    int i = 0;
    for (it = particules.begin(); it != particules.end(); it++) {
        cout << "P" << i+1 << " : " << endl;
        cout << "    " << (**it) << endl;
        i++;
    }
}

template <unsigned int Dim>
void Fluide<Dim>::afficheHauteur(double hauteur) {
    typename list<Particule<Dim> *>::iterator it;
    for (it = particules.begin(); it != particules.end(); it++) {
        if ((*it)->getPosition()(3) >= hauteur) {
            cout << (*it)->getIndice() << " " << (**it) << endl;
            cout << "     " << (*it)->getForces() << endl;
        }
    }
}

#include "fluide_collisions.tpp"
#include "fluide_arps.tpp"
#include "fluide_interactions.tpp"
