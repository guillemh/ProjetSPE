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
    double masse_volumique;      // Masse volumique de la particule (kg.m^-3)
    double pression;             // Pression de la particule (Pa)
    double masse;                // Masse de la particule (m)

    /* ** Constructeurs ** */
public:
    /**
     * Constructeur
     * \param pos Position initiale
     * \param vit Vitesse initiale
     * \param m Masse de la particule
     * \param rho Masse volumique initiale
     * \param p Pression initiale
     */
    Particule(Vecteur<Dim> pos, Vecteur<Dim> vit, double rho = 0, double p = 0, double m = 0);
    
    /**
     * Destructeur
     */
    ~Particule();


    /* ** Methodes ** */
public:
    /**
     * \return La position de la particule
     */
    const Vecteur<Dim> & getPosition() const;

    /**
     * \return La vitesse de la particule
     */
    const Vecteur<Dim> & getVitesse() const;

    /**
     * \return L'accélération de la particule
     */
    const Vecteur<Dim> & getAcceleration() const;

    /**
     * \return La masse de la particule
     */
    double getMasse() const;
   
    /**
     * \return La masse volumique de la particule
     */
    double getMasseVolumique() const;

    /**
     * \return La pression de la particule
     */
    double getPression() const;

    /**
     * Modifie la position de la particule
     * \param pos Nouvelle position de la particule
     */
    void setPosition(const Vecteur<Dim> &pos);

    /**
     * Modifie la vitesse de la particule
     * \param vit Nouvelle vitesse de la particule
     */
    void setVitesse(const Vecteur<Dim> &vit);

    /**
     * Modifie l'accélération de la particule
     * \param acc Nouvelle accélération de la particule
     */
    void setAcceleration(const Vecteur<Dim> &acc);

    /**
     * Modifie la masse volumique de la particule
     * \param rho Nouvelle masse volumique de la particule
     */
    void setMasseVolumique(double rho);

    /**
     * Modifie la pression de la particule
     * \param p Nouvelle pression de la particule
     */
    void setPression(double p);

    /**
     * Incrémente la position de la particule
     * \param pos Vecteur de déplacement de la particule (position += pos)
     */
    void incrPosition(const Vecteur<Dim> &pos);

    /**
     * Incrémente la vitesse de la particule
     * \param vit Facteur d'augmentation de la vitesse (vitesse += vit)
     */
    void incrVitesse(const Vecteur<Dim> &vit);

    /**
     * Met à jour la pression en fonction de la masse volumique de la particule
     * Prototype éventuellement à reprendre
     * \param son La vitesse du son
     * \param dens La densité au repos
     */
    void majPression(double son, double dens);

    /**
     * Calcule la valeur de l'isosurface de cette particule en un point de l'espace.
     * \param pos position à laquelle on veut calculer la valeur de l'isosurface
     */
    double isosurface(Vecteur<Dim> &pos);
    
    /**
     * Fonction d'affichage de la particule
     * \param mat Le matériau du fluide auquel appartient la particule
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

