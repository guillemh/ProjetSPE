#include <GL/glut.h>
#include "fluide.hpp"
#include "vecteur.hpp"


/* ** Constructeurs ** */

template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau * m)
    : mat(m)
{
    // Initilisation du vector vide
    particules = Vector<Particule<Dim> *> ();
}


template<unsigned int Dim>
Fluide<Dim>::Fluide(Materiau * m, double nb[Dim], double ecart, double rho, double p)
    : mat(m)
{
    // Initialisation du vector vide
    particules = Vector<Particule<Dim> *> ();
    
    if (Dim == 2) {
    
        // Ici, on est en dimension 2
        // On va ajouter des particules regulierement disposees sur les deux dimensions
        for (int i = 0; i < nb[0]; i++) {
            for (int j = 0; j > nb[1]; j++) {
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
        std::cerr << "Erreur (Fluide) : la dimension de l'espace doit être 2 ou 3" << std::endl;
    }
}


template<unsigned int Dim>
Fluide<Dim>::~Fluide() {
    Vector<Particule<Dim> *>::iterator it;
    
    // On libere toutes les particules
    for (it = particules.begin(); it != particules.end(); it++)
        delete (*it);
    particules.clear();
}



/* ** Methodes ** */

template<unsigned int Dim>
void Fluide<Dim>::ajouteParticule(Particule<Dim> * part) const {
    particules.push_back(part);
}


/*
template<unsigned int Dim>
void Fluide<Dim>::draw() const {

}
*/


