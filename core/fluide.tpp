#include <GL/glut.h>
#include "fluide.hpp"
#include "noyauLissage.hpp"
using std::cout;
using std::endl;


/* ** Constructeurs ** */

template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m)
    : mat(m),
    debutAnim(true)
{
    // Initilisation du vector vide
    particules = vector<Particule<Dim> *> ();
}


template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m, int nb[Dim], double ecart, double rho, double p)
    : mat(m),
    debutAnim(true)
{
    // Initialisation du vector vide
    particules = vector<Particule<Dim> *> ();
    
    if (Dim == 2) {
    
        // Ici, on est en dimension 2
        // On va ajouter des particules regulierement disposees sur les deux dimensions
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j < nb[1]; j++) {
                Vecteur<Dim> vec = Vecteur<Dim>(i*ecart, j*ecart);
                Particule<Dim> * part = new Particule<Dim>(vec, Vecteur<Dim>(), rho, p);
                particules.push_back(part);
            }
        }
        
    } else if (Dim == 3) {
    
        // Ici, on est en dimension 3
        // On va ajouter des particules regulierement disposees sur les trois dimensions
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j < nb[1]; j++) {
                for (int k = 0; k < nb[2]; k++) {
                    Vecteur<Dim> vec = Vecteur<Dim>(i*ecart, j*ecart, k*ecart);
                    Particule<Dim> * part = new Particule<Dim>(vec, Vecteur<Dim>(), rho, p);
                    particules.push_back(part);
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
}



/* ** Methodes ** */

template<unsigned int Dim>
void Fluide<Dim>::ajouteParticule(Particule<Dim> * part) {
    particules.push_back(part);
}


template<unsigned int Dim>
void Fluide<Dim>::majDensitePression() {

    typename vector<Particule<Dim> *>::iterator it1;
    typename vector<Particule<Dim> *>::iterator it2;
    NoyauLissageDefaut<Dim> noyau = NoyauLissageDefaut<Dim>(mat->getRayonNoyau());
    
    // On boucles sur toutes les particules
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
    
        // On met leur masse volumique à jour
        double somme = 0;
        for (it2 = particules.begin(); it2 != particules.end(); it2++)
            somme += noyau.defaut((*it1)->getPosition() - (*it2)->getPosition());
        (*it1)->setMasseVolumique((mat->getMasseParticules())*somme);
        
        // On met leur pression à jour
        double diff = (*it1)->getPression() - mat->getDensiteRepos();
        (*it1)->setPression((mat->getRigiditeGaz())*diff);
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
    }
    
    return res;
}


template<unsigned int Dim>
void Fluide<Dim>::majPositionVitesse() {

    typename vector<Particule<Dim> *>::iterator it1;
    typename vector<Particule<Dim> *>::iterator it2;
    NoyauLissageDefaut<Dim> noyauDefaut = NoyauLissageDefaut<Dim>(mat->getRayonNoyau());
    NoyauLissagePression<Dim> noyauPression = NoyauLissagePression<Dim>(mat->getRayonNoyau());
    NoyauLissageViscosite<Dim> noyauViscosite = NoyauLissageViscosite<Dim>(mat->getRayonNoyau());
    
    // On boucles sur toutes les particules
    for (it1 = particules.begin(); it1 != particules.end(); it1++) {
        
        // Definition de toutes les forces
        Vecteur<Dim> fPression = Vecteur<Dim>();
        Vecteur<Dim> fViscosite = Vecteur<Dim>();
        Vecteur<Dim> fGravite = Vecteur<Dim>();
        Vecteur<Dim> fSurface = Vecteur<Dim>();
        double colorfield = 0;
        
        // Calcul des sommes utiles aux forces de pression, de viscosite et de surface
        for (it2 = particules.begin(); it2 != particules.end(); it2++) {
            if (it1 != it2) {
                fPression -= noyauPression.gradient((*it1)->getPosition() - (*it2)->getPosition())
                             * ((*it1)->getPression() + (*it2)->getPression())
                             / (*it2)->getMasseVolumique();
                
                fViscosite += ((*it2)->getVitesse() - (*it1)->getVitesse())
                              * noyauViscosite.laplacien((*it1)->getPosition() - (*it2)->getPosition())
                              / (*it2)->getMasseVolumique();
                              
                colorfield += noyauDefaut.laplacien((*it1)->getPosition() - (*it2)->getPosition())
                              / (*it2)->getMasseVolumique();
                              
                fSurface += noyauDefaut.gradient((*it1)->getPosition() - (*it2)->getPosition())
                            / (*it2)->getMasseVolumique();
            }
        }
        
        // Calcul des forces de gravité, de pression, de viscosite et de surface
        fGravite = (*it1)->getMasseVolumique() * mat->getAccGrav();
        fPression *= mat->getMasseParticules() / 2;
        fViscosite *= mat->getViscosite() * mat->getMasseParticules();
        fSurface *= mat->getMasseParticules();
        double norme = fSurface.norme();
        if (norme >= mat->getSeuilSurface()) {
            colorfield *= mat->getMasseParticules();
            fSurface *= -colorfield * mat->getTensionSurface() / norme;
        } else {
            fSurface = Vecteur<Dim>();
        }
        
        // Calcul de l'acceleration
        (*it1)->setAcceleration((fPression + fViscosite + fGravite + fSurface) / (*it1)->getMasseVolumique());
        
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


