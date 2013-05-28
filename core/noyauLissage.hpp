#ifndef _NOYAULISSAGE_HPP_
#define _NOYAULISSAGE_HPP_

#include <iostream>


/** \class NoyauLissage : classe abstraite représentant un noyau de lissage
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class NoyauLissage {

    /* ** Attributs ** */
protected:
    double h; // Rayon de support du noyau de lissage
    double coefDefaut;
    double coefGradient;
    double coefLaplacien;


    /* ** Constructeurs ** */
public:
    /**
     * Constructeur par defaut, met h à 0
     */
    NoyauLissage();
    
    /**
     * Constructeur
     * \param rayon rayon de support
     */
    NoyauLissage(double rayon);

    /**
     * Destructeur
     */
    ~NoyauLissage();


    /* ** Methodes ** */
public:
    /**
     * \return le rayon du noyau de lissage
     */
    double getRayon() const;

    /**
     * Implémente la méthode par défaut de noyau de lissage
     * \param r position de la particule
     */
    virtual double defaut(const Vecteur<Dim> r) const = 0;

    /**
     * Implémente la méthode de noyau de lissage avec le gradient
     * \param r position de la particule
     */
    virtual Vecteur<Dim> gradient(const Vecteur<Dim> r) const = 0;

    /**
     * Implémente la méthode de noyau de lissage avec le laplacien
     * \param r position de la particule
     */
    virtual double laplacien(const Vecteur<Dim> r) const = 0;
    
};


/** \class NoyauLissageDefaut : classe représentant un noyau de lissage par défaut
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class NoyauLissageDefaut : public NoyauLissage<Dim> {

    /* ** Attributs ** */
private:
    double hCarre;


    /* ** Constructeurs ** */
public:
    /**
     * Constructeur par defaut, met h à 0
     */
    NoyauLissageDefaut();
    
    /**
     * Constructeur
     * \param rayon rayon de support
     */
    NoyauLissageDefaut(double rayon);

    /**
     * Destructeur
     */
    ~NoyauLissageDefaut();


    /* ** Methodes ** */
public:
    /**
     * Implémente la méthode par défaut de noyau de lissage
     * \param r position de la particule
     */
    virtual double defaut(const Vecteur<Dim> r) const;

    /**
     * Implémente la méthode de noyau de lissage avec le gradient
     * \param r position de la particule
     */
    virtual Vecteur<Dim> gradient(const Vecteur<Dim> r) const;

    /**
     * Implémente la méthode de noyau de lissage avec le laplacien
     * \param r position de la particule
     */
    virtual double laplacien(const Vecteur<Dim> r) const;

};


/** \class NoyauLissagePression : classe représentant un noyau de lissage de pression
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class NoyauLissagePression : public NoyauLissage<Dim> {

    /* ** Constructeurs ** */
public:
    /**
     * Constructeur par defaut, met h à 0
     */
    NoyauLissagePression();
    
    /**
     * Constructeur
     * \param rayon rayon de support
     */
    NoyauLissagePression(double rayon);

    /**
     * Destructeur
     */
    ~NoyauLissagePression();


    /* ** Methodes ** */
public:
    /**
     * Implémente la méthode par défaut de noyau de lissage
     * \param r position de la particule
     */
    virtual double defaut(const Vecteur<Dim> r) const;

    /**
     * Implémente la méthode de noyau de lissage avec le gradient
     * \param r position de la particule
     */
    virtual Vecteur<Dim> gradient(const Vecteur<Dim> r) const;

    /**
     * Implémente la méthode de noyau de lissage avec le laplacien
     * \param r position de la particule
     */
    virtual double laplacien(const Vecteur<Dim> r) const;

};


/** \class NoyauLissageViscosite : classe représentant un noyau de lissage de viscosité
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class NoyauLissageViscosite : public NoyauLissage<Dim> {

    /* ** Attributs ** */
private:
    double hCarre;
    double hCube;
    

    /* ** Constructeurs ** */
public:
    /**
     * Constructeur par defaut, met h à 0
     */
    NoyauLissageViscosite();
    
    /**
     * Constructeur
     * \param rayon rayon de support
     */
    NoyauLissageViscosite(double rayon);

    /**
     * Destructeur
     */
    ~NoyauLissageViscosite();


    /* ** Methodes ** */

public:
    /**
     * Implémente la méthode par défaut de noyau de lissage
     * \param r position de la particule
     */
    virtual double defaut(const Vecteur<Dim> r) const;

    /**
     * Implémente la méthode de noyau de lissage avec le gradient
     * \param r position de la particule
     */
    virtual Vecteur<Dim> gradient(const Vecteur<Dim> r) const;

    /**
     * Implémente la méthode de noyau de lissage avec le laplacien
     * \param r position de la particule
     */
    virtual double laplacien(const Vecteur<Dim> r) const;

};

#include "noyauLissage.tpp"

#endif
