#ifndef _PARTICULE_HPP_
#define _PARTICULE_HPP_

#include <iostream>
#include "materiau.hpp"
#include "vecteur.hpp"


/** \class Particule : classe des particules constituants le texte
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class Particule {

    /* ** Attributs ** */
private:
    Vecteur<Dim> position;  // Position de la particule (m)
    Vecteur<Dim> vitesse;   // Vitesse de la particule (m.s^-1)
    double masse_volumique; // Masse volumique de la particule (kg.m^-3)
    double pression;        // Pression de la particule (Pa)


    /* ** Constructeurs ** */
public:
    /**
      * Constructeur
      * \param pos position initiale
      * \param vit vitesse initiale
      * \param rho mase volumique initiale
      * \param p pression initiale
      */
    Particle(Vecteur<Dim> pos, Vecteur<Dim> vit, double rho, double p);
    
    /**
      * Destructeur
      */
    ~Particle();


    /* ** Methodes ** */
public:
    /**
      * \return la position de la particule
      */
    const Vecteur<Dim> & getPosition() const;

    /**
      * \return la vitesse de la particule
      */
    const Vecteur<Dim> & getVitesse() const;
    
    /**
      * \return la masse volumique de la particule
      */
    const Vecteur<Dim> & getMasseVolumique() const;

    /**
      * \return la pression de la particule
      */
    const Vecteur<Dim> & getPression() const;

    /**
      * Modifie la position de la particule
      * \param pos nouvelle position de la particule
      */
    void setPosition(const Vecteur<Dim> &pos);

    /**
      * Modifie la vitesse de la particule
      * \param pos nouvelle vitesse de la particule
      */
    void setVitesse(const Vecteur<Dim> &vit);

    /**
      * Modifie la masse volumique de la particule
      * \param rho nouvelle masse volumique de la particule
      */
    void setMasseVolumique(double rho);

    /**
      * Modifie la pression de la particule
      * \param p nouvelle pression de la particule
      */
    void setPression(double p);

    /**
      * Incrémente la position de la particule
      * \param pos vecteur de deplacement de la particule (position += pos)
      */
    void incrPosition(const Vecteur<Dim> &pos);

    /**
      * Incrémente la vitesse de la particule
      * \param vit facteur d'augmentation de la vitesse (vitesse += vit)
      */
    void incrVitesse(const Vecteur<Dim> &vit);
    
    /**
      * Fonction d'affichage de la particule
      */
    //void draw() const;
};

/**
  * Operateur d'affichage des composantes de la particule
  */
template<unsigned int Dim>
std::ostream& operator<<(std::ostream& os, const Particule<Dim>& p);


#include "particule.tpp"

#endif

