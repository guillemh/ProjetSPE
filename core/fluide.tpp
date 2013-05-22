#include <GL/glut.h>
#include "fluide.hpp"
#include "noyauLissage.hpp"
using std::cout;
using std::endl;


/* ** Constructeurs ** */

template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m)
    : mat(m)
{
    // Initilisation du vector vide
    particules = vector<Particule<Dim> *> ();
}


template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau<Dim> * m, int nb[Dim], double ecart, double rho, double p)
    : mat(m)
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
    NoyauLissage<Dim> noyau = NoyauLissage<Dim>(mat->getRayonNoyau(), DEFAUT);
    
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


/*
template<unsigned int Dim>
void Fluide<Dim>::draw() const {

}
*/


template<unsigned int Dim>
void Fluide<Dim>::affiche() {
    typename vector<Particule<Dim> *>::iterator it;
    for (it = particules.begin(); it != particules.end(); it++)
        cout << (**it) << endl;
}


