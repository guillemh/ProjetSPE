#include <GL/glut.h>
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
    // Initialisation du vector vide
    particules = vector<Particule<Dim> *> ();
}


template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m, int nb[Dim], double ecart, double rho, double p)
    : mat(m),
      debutAnim(true),
      hash_voisins()
{
    // Initialisation du vector vide
    particules = vector<Particule<Dim> *>();
    
    /* 
     * Création d'une table des nombres premiers 
     * pour calculer la dimension de la table de hashage 
     */
    //    Premier<Dim> table = Premier<Dim>();

    if (Dim == 2) {
    
	nbrParticules = nb[0]*nb[1];
	lgrHash = table.getPremier(2*nbrParticules);
        // Ici, on est en dimension 2
        // On va ajouter des particules régulierement disposees sur les deux dimensions
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j < nb[1]; j++) {
                Vecteur<Dim> vec = Vecteur<Dim>(i*ecart, j*ecart);
                Particule<Dim> *part = new Particule<Dim>(vec, Vecteur<Dim>(), rho, p);
                particules.push_back(part);
                hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(part->getPosition()), part));
            }
        }
        
    } else if (Dim == 3) {
    
	nbrParticules = nb[0]*nb[1]*nb[2];
	lgrHash = table.getPremier(2*nbrParticules);
        // Ici, on est en dimension 3
        // On va ajouter des particules regulierement disposees sur les trois dimensions
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j < nb[1]; j++) {
                for (int k = 0; k < nb[2]; k++) {
                    Vecteur<Dim> vec = Vecteur<Dim>(i*ecart, j*ecart, k*ecart + 0.1);
                    Particule<Dim> *part = new Particule<Dim>(vec, Vecteur<Dim>(), rho, p);
                    particules.push_back(part);
                    hash_voisins.insert(pair<int, Particule<Dim>*>(fonction_hashage(part->getPosition()), part));               
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
    typename vector<Particule<Dim> *>::iterator it;
    // On libere toutes les particules
    for (it = particules.begin(); it != particules.end();) {
        delete (*it);
        particules.erase(it);
    }
    hash_voisins.clear();
}


/* Fonction de hashage */

template<>
inline int Fluide<2>::fonction_hashage(Vecteur<2> pos) {
    int noeud_grille[2] = {int(floor(pos(1)/mat->getRayonNoyau())),
                           int(floor(pos(2)/mat->getRayonNoyau()))};
    int p1 = 73856093;
    int p2 = 19349663;
    return (noeud_grille[0]*p1 
	    ^ noeud_grille[1]*p2) 
	% lgrHash;
}


template<>
inline int Fluide<3>::fonction_hashage(Vecteur<3> pos) {
    int noeud_grille[3] = {int(floor(pos(1)/mat->getRayonNoyau())),
                           int(floor(pos(2)/mat->getRayonNoyau())),
                           int(floor(pos(3)/mat->getRayonNoyau()))};
    int p1 = 73856093;
    int p2 = 19349663;
    int p3 = 83492791;
    return (noeud_grille[0]*p1 
	    ^ noeud_grille[1]*p2
	    ^ noeud_grille[2]*p3) 
	% lgrHash;
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
inline list<Particule<2>*> Fluide<2>::voisinage(Particule<2>& p) {
    list<Particule<2>*> res;
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
                res.push_back(part_it->second);
            }
        }
    }

    /* Dans ces voisins, on ne garde que ceux qui sont dans la sphère */
    list<Particule<2>*>::iterator liste_it;
    for (liste_it = res.begin(); liste_it != res.end(); ) {
	if ((p.getPosition() == (*liste_it)->getPosition())
	    || (p.getPosition() - (*liste_it)->getPosition()).norme() > rnoyau) {
	    liste_it = res.erase(liste_it);
	} else {
	    ++liste_it;
	}
    }
    return res;
}

template<>
inline list<Particule<3>*> Fluide<3>::voisinage(Particule<3>& p) {
    list<Particule<3>*> res;
    double rnoyau = mat->getRayonNoyau();
    /* Noeuds correspondant à la bounding box de la particule */
    int bbmin[3] = {int(floor((p.getPosition()(1)-rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(2)-rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(3)-rnoyau)/rnoyau))};
    int bbmax[3] = {int(floor((p.getPosition()(1)+rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(2)+rnoyau)/rnoyau)),
                    int(floor((p.getPosition()(3)-rnoyau)/rnoyau))};
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
		    cout << "ajoute qqn" << endl;
		    res.push_back(part_it->second);
		}
	    }
	}
    }

    /* Dans ces voisins, on ne garde que ceux qui sont dans la sphère */
    list<Particule<3>*>::iterator liste_it;
    for (liste_it = res.begin(); liste_it != res.end(); ) {
	if ((p.getPosition() == (*liste_it)->getPosition())
	    || (p.getPosition() - (*liste_it)->getPosition()).norme() > rnoyau) {
	    if (p.getPosition() == (*liste_it)->getPosition()) {
		cout << " enleve moi-mm" << endl;
	    } else {
		cout << " enleve qqn" << endl;
	    }
	    liste_it = res.erase(liste_it);
	} else {
	    ++liste_it;
	}
    }
    return res;
}


template<unsigned int Dim>
void Fluide<Dim>::majDensitePression() {

    typename vector<Particule<Dim> *>::iterator it1;
    NoyauLissageDefaut<Dim> noyau = NoyauLissageDefaut<Dim>(mat->getRayonNoyau());
    list<Particule<Dim>*> voisins;    
    // typename list<Particule<Dim>*>::iterator it2;
    typename vector<Particule<Dim> *>::iterator it2;

    int i = 0;
    // On boucles sur toutes les particules
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
//        cout << "P" << i << " : ";
        // On met leur masse volumique à jour
        double somme = 0;
//        voisins = voisinage(*(*it1));
//        cout << voisins.size() << " voisins trouvés" << endl;
//        for (it2 = voisins.begin(); it2 != voisins.end(); it2++)
        for (it2 = particules.begin(); it2 != particules.end(); it2++) {
            if (it1 != it2) {
//                cout << "r.norme () : " << ((*it1)->getPosition() - (*it2)->getPosition()).norme() << endl;
//                cout << "h : " << noyau.getRayon() << endl;
                somme += noyau.defaut((*it1)->getPosition() - (*it2)->getPosition());
            }
        }
//        cout << somme << endl;
        if (somme != 0)
            (*it1)->setMasseVolumique((mat->getMasseParticules())*somme);
        
        // On met leur pression à jour
        (*it1)->majPression(mat->getCeleriteSon(), mat->getDensiteRepos());
        i++;
    }
}


// Fonction interne appelee lors de la detection de collisions
// Elle detecte une collision avec les plans X=-5, X=5, Y=-5, Y=5 et Z=0
// Elle renvoie le point de contact s'il y a collision, le Vecteur v sinon
template<unsigned int Dim>
Vecteur<Dim> collision(const Vecteur<Dim> & v) {
    Vecteur<Dim> res = Vecteur<Dim>(v);

    if (Dim == 2) {
        if (v(1) < -5)
            res(1) = -5;
        if (v(1) > 5)
            res(1) = 5;
        if (v(2) < 0)
            res(2) = 0;
        if (v(2) > 5)
            res(2) = 5;
    } else {
        if (v(1) < -5)
            res(1) = -5;
        if (v(1) > 5)
            res(1) = 5;
        if (v(2) < -5)
            res(2) = -5;
        if (v(2) > 5)
            res(2) = 5;
        if (v(3) < 0)
            res(3) = 0;
        if (v(3) > 5)
            res(3) = 5;
    }
    
    return res;
}


template<unsigned int Dim>
void Fluide<Dim>::majPositionVitesse() {

    typename vector<Particule<Dim> *>::iterator it1;
    NoyauLissageMonaghan<Dim> noyauMonaghan = NoyauLissageMonaghan<Dim>(mat->getRayonNoyau());

    // On boucles sur toutes les particules
    // Ci-dessous, factorisation de calculs
    double masse = mat->getMasseParticules();
    double nu_numerateur = 2*mat->getRayonNoyau()*mat->getConstanteViscosite()*mat->getCeleriteSon();

    list<Particule<Dim>*> voisins;    
    // typename list<Particule<Dim>*>::iterator it2;
    typename vector<Particule<Dim> *>::iterator it2;
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

        // voisins = voisinage(*(*it1));
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
        fPression *= masse * masseVolumique_a;
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
//        cout << "fPression : " << fPression << endl;
//        cout << "fGravite : " << fGravite << endl;
        (*it1)->setAcceleration((fPression + fGravite) / masseVolumique_a);
        // (*it1)->setAcceleration((fPression + fViscosite + fGravite + fSurface) / masseVolumique_a);
        
    }
    
    
    // On boucles une nouvelle fois sur toutes les particules pour mettre leur position
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

}


template<unsigned int Dim>
void Fluide<Dim>::draw() const {
    typename vector<Particule<Dim> *>::const_iterator it;
    for (it = particules.begin () ; it != particules.end () ; it++) {
        (*it)->draw (mat);
    }
}


template<unsigned int Dim>
void Fluide<Dim>::affiche() {
    typename vector<Particule<Dim> *>::iterator it;
    for (it = particules.begin(); it != particules.end(); it++)
        cout << (**it) << endl;
}


