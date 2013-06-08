#ifndef _PARTICULE_HPP_
#define _PARTICULE_HPP_

#include <iostream>
#include "../core/vecteur.hpp"
#include "../core/materiau.hpp"

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
    unsigned int indice;         // Numéro identifiant la particule
    Vecteur<Dim> position;       // Position de la particule (m)
    Vecteur<Dim> positionPrec;   // Position de la particule 
                                 // au pas de temps précédent (m)
    Vecteur<Dim> vitesse;        // Vitesse de la particule (m.s^-1)
    Vecteur<Dim> vitessePrec;    // Vitesse de la particule 
                                 // au pas de temps précédent (m.s^-1)
    Vecteur<Dim> acceleration;   // Acceleration de la particule (m.s^-2)
    Vecteur<Dim> forces;         // Forces d'interaction s'exerçant sur la particule (kg.m.s -2)
    double masse_volumique;      // Masse volumique de la particule (kg.m^-3)
    double pression;             // Pression de la particule (Pa)
    double masse;                // Masse de la particule (m)

    /* ** Constructeurs ** */
public:
    /**
     * Constructeur
     * \param ind Numéro d'identification de la particule
     * \param pos Position initiale
     * \param vit Vitesse initiale
     * \param m Masse de la particule
     * \param rho Masse volumique initiale
     * \param p Pression initiale
     */
    Particule(unsigned int ind, Vecteur<Dim> pos, Vecteur<Dim> vit, double rho = 0, double p = 0, double m = 0);
    
    /**
     * Destructeur
     */
    ~Particule();


    /* ** Methodes ** */
public:
    /**
     * \return Le numéro de la particule
     */
    unsigned int getIndice() const;

    /**
     * \return La position de la particule
     */
    const Vecteur<Dim> & getPosition() const;

    /**
     * \return La position de la particule au pas de temps précédent
     */
    const Vecteur<Dim> & getPositionPrec() const;

    /**
     * \return La vitesse de la particule
     */
    const Vecteur<Dim> & getVitesse() const;

    /**
     * \return La vitesse de la particule au pas de temps précédent
     */
    const Vecteur<Dim> & getVitessePrec() const;

    /**
     * \return L'accélération de la particule
     */
    const Vecteur<Dim> & getAcceleration() const;

    /**
     * \return Le total des forces s'exerçant sur la particule
     */
    const Vecteur<Dim> & getForces() const;

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
     * Met à jour la position de la particule au pas de temps précédent
     * \param pos Nouvelle position précédente de la particule
     */
    void setPositionPrec(const Vecteur<Dim> &pos);

    /**
     * Modifie la vitesse de la particule
     * \param vit Nouvelle vitesse de la particule
     */
    void setVitesse(const Vecteur<Dim> &vit);

    /**
     * Met à jour la vitesse de la particule au pas de temps précédent
     * \param pos Nouvelle vitesse précédente de la particule
     */
    void setVitessePrec(const Vecteur<Dim> &pos);

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
     * Incrémente le total des forces
     * @param f Facteur d'incrémentation des forces (forces += f)
     */
    void incrForces(const Vecteur<Dim>& f);

    /**
     * Décrémente le total des forces
     * @param f Facteur de décrémentation des forces (forces -= f)
     */
    void decrForces(const Vecteur<Dim>& f);

    /**
     * Met à jour la pression en fonction de la masse volumique de la particule
     * Prototype éventuellement à reprendre
     * \param dens La densité au repos
     */
    void majPression(double dens);

    /**
     * Calcule la valeur de l'isosurface de cette particule en un point de l'espace.
     * \param pos position à laquelle on veut calculer la valeur de l'isosurface
     * \param prec booléen indiquant si on le fait pour la position actuelle ou précédente
     * @return Valeur de l'isosurface
     */
    double isosurface(Vecteur<Dim> &pos, bool prec);
    
    /**
     * Fonction d'affichage de la particule sous la forme d'une sphère
     * \param mat Le matériau du fluide auquel appartient la particule
     */
    void draw(Materiau<Dim> *mat) const;

    /**
     * Fonction d'affichage de la particule sous la forme d'un point
     */
    void draw() const;
};

/**
 * Operateur d'affichage des composantes de la particule
 */
template<unsigned int Dim>
std::ostream& operator<<(std::ostream& os, const Particule<Dim>& p);


#include "particule.tpp"

#endif

