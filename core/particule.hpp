#ifndef _PARTICULE_HPP_
#define _PARTICULE_HPP_

#include <iostream>
#include "vecteur.hpp"
#include "materiau.hpp"

/** 
 * \class Particule 
 * @brief Classe des particules constituant le fluide
 * 
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class Particule {

    /* ** Attributs ** */
private:
    Vecteur<Dim> position;       // Position de la particule (m)
    Vecteur<Dim> vitesse;        // Vitesse de la particule (m.s^-1)
    Vecteur<Dim> acceleration;   // Acceleration de la particule (m.s^-2)
    double masse;                // Masse de la particule (m)
    double masse_volumique;      // Masse volumique de la particule (kg.m^-3)
    double pression;             // Pression de la particule (Pa)

    /* ** Constructeurs ** */
public:
    /**
      * Constructeur
      * \param pos position initiale
      * \param vit vitesse initiale
      * \param m masse de la particule
      * \param rho masse volumique initiale
      * \param p pression initiale
      */
    Particule(Vecteur<Dim> pos, Vecteur<Dim> vit, double m, double rho = 0, double p = 0);
    
    /**
      * Destructeur
      */
    ~Particule();


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
      * \return l'accélération de la particule
      */
    const Vecteur<Dim> & getAcceleration() const;

    /**
      * \return la masse de la particule
      */
    double getMasse() const;
   
    /**
      * \return la masse volumique de la particule
      */
    double getMasseVolumique() const;

    /**
      * \return la pression de la particule
      */
    double getPression() const;

    /**
      * Modifie la position de la particule
      * \param pos nouvelle position de la particule
      */
    void setPosition(const Vecteur<Dim> &pos);

    /**
      * Modifie la vitesse de la particule
      * \param vit nouvelle vitesse de la particule
      */
    void setVitesse(const Vecteur<Dim> &vit);

    /**
      * Modifie l'accélération de la particule
      * \param acc nouvelle accélération de la particule
      */
    void setAcceleration(const Vecteur<Dim> &acc);

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
     * Met à jour la pression en fonction de la masse volumique de la particule
     * Prototype éventuellement à reprendre
     * \param son la vitesse du son
     * \param dens la densité au repos
     */
    void majPression(double son, double dens);

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
      * \param mat le matériau du fluide auquel appartient la particule
      */
    void draw(Materiau<Dim> *mat) const;
};

/**
  * Operateur d'affichage des composantes de la particule
  */
template<unsigned int Dim>
std::ostream& operator<<(std::ostream& os, const Particule<Dim>& p);


#include "particule.tpp"

#endif

