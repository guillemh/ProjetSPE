#ifndef _NOYAULISSAGE_HPP_
#define _NOYAULISSAGE_HPP_

#include <iostream>


/** 
 * \class NoyauLissage
 * @brief Classe abstraite représentant un noyau de lissage
 * 
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class NoyauLissage {

    /* ** Attributs ** */
protected:
    double h;                  /*!< Rayon de support du noyau de lissage */
    double coefDefaut;         /*!< Coefficient constant pour le calcul de la valeur par défaut */
    double coefGradient;       /*!< Coefficient constant pour le calcul du gradient */
    double coefLaplacien;      /*!< Coefficient constant pour le calcul du laplacien */


    /* ** Constructeurs ** */
public:
    /**
     * @brief Constructeur
     *
     * Constructeur par défaut, met h à 0
     */
    NoyauLissage();
    
    /**
     * @brief Constructeur
     *
     * Constructeur prenant en argument le rayon du noyau
     * \param rayon Rayon de support
     */
    NoyauLissage(double rayon);

    /**
     * @brief Destructeur
     *
     * Destructeur
     */
    ~NoyauLissage();


    /* ** Methodes ** */
public:
    /**
     * @brief Accesseur
     * \return Le rayon du noyau de lissage
     */
    inline double getRayon() const {
        return h;
    }

    /**
     * @brief Calcul de valeur
     *
     * Implémente la méthode par défaut de noyau de lissage
     * @param r Position de la particule
     * @return La valeur du noyau évalué en r
     */
    virtual double defaut(const Vecteur<Dim> r) const = 0; 

    /**
     * @brief Calcul de valeur
     *
     * Implémente la méthode de noyau de lissage avec le gradient
     * @param r Position de la particule
     * @return La valeur du gradient du noyau évalué en r
     */
    virtual Vecteur<Dim> gradient(const Vecteur<Dim> r) const = 0;

    /**
     * @brief Calcul de valeur
     *
     * Implémente la méthode de noyau de lissage avec le laplacien
     * @param r Position de la particule
     * @return La valeur du laplacien du noyau évalué en r
     */
    virtual double laplacien(const Vecteur<Dim> r) const = 0;
    
};


/** 
 * \class NoyauLissageDefaut
 * @brief Classe représentant un noyau de lissage par défaut
 * 
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
     * @brief Constructeur
     *
     * Constructeur par defaut, met h à 0
     */
    NoyauLissageDefaut();
    
    /**
     * @brief Constructeur
     *
     * Constructeur
     * \param rayon Rayon de support
     */
    NoyauLissageDefaut(double rayon);

    /**
     * @brief Destructeur
     *
     * Destructeur
     */
    ~NoyauLissageDefaut();


    /* ** Methodes ** */
public:

    virtual double defaut(const Vecteur<Dim> r) const;

    virtual Vecteur<Dim> gradient(const Vecteur<Dim> r) const;

    virtual double laplacien(const Vecteur<Dim> r) const;

};


/** 
 * \class NoyauLissagePression 
 * @brief Classe représentant un noyau de lissage de pression
 * 
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class NoyauLissagePression : public NoyauLissage<Dim> {

    /* ** Constructeurs ** */
public:
    /**
     * @brief Constructeur
     *
     * Constructeur par defaut, met h à 0
     */
    NoyauLissagePression();
    
    /**
     * @brief Constructeur
     *
     * Constructeur
     * \param rayon Rayon de support
     */
    NoyauLissagePression(double rayon);

    /**
     * @brief Destructeur
     *
     * Destructeur
     */
    ~NoyauLissagePression();


    /* ** Methodes ** */
public:

    virtual double defaut(const Vecteur<Dim> r) const;

    virtual Vecteur<Dim> gradient(const Vecteur<Dim> r) const;

    virtual double laplacien(const Vecteur<Dim> r) const;

};


/** 
 * \class NoyauLissageViscosite
 * @brief Classe représentant un noyau de lissage de viscosité
 * 
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
     * @brief Constructeur
     *
     * Constructeur par defaut, met h à 0
     */
    NoyauLissageViscosite();
    
    /**
     * @brief Constructeur
     *
     * Constructeur
     * \param rayon Rayon de support
     */
    NoyauLissageViscosite(double rayon);

    /**
     * @brief Destructeur
     *
     * Destructeur
     */
    ~NoyauLissageViscosite();


    /* ** Methodes ** */

public:

    virtual double defaut(const Vecteur<Dim> r) const;

    virtual Vecteur<Dim> gradient(const Vecteur<Dim> r) const;

    virtual double laplacien(const Vecteur<Dim> r) const;

};


/** 
 * \class NoyauLissageMonaghan
 * @brief Classe représentant le noyau de lissage utilisé par Monaghan
 * dans l'article "Smooth Particle Hydrodynamics" (2005)
 * 
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class NoyauLissageMonaghan : public NoyauLissage<Dim> {

    /* ** Constructeurs ** */
public:
    /**
     * @brief Constructeur
     *
     * Constructeur par defaut, met h à 0
     */
    NoyauLissageMonaghan();
    
    /**
     * @brief Constructeur
     *
     * Constructeur
     * \param rayon Rayon de support
     */
    NoyauLissageMonaghan(double rayon);

    /**
     * @brief Destructeur
     *
     * Destructeur
     */
    ~NoyauLissageMonaghan();


    /* ** Methodes ** */
public:

    inline virtual double defaut(const Vecteur<Dim> r) const {
        double q = r.norme()/(this->h);
        double res;
        if (q <= 1) {
            res = (pow(2 - q, 3) - 4.0 * pow(1 - q, 3));
        } else if (q <= 2) {
            res = pow(2 - q, 3);
        } else {
            res = 0;
        }
        if (Dim == 3) {
            res *= 1.0/(4.0 * PI * pow(this->h, 3));
        } else if (Dim == 2) {
            res *= 15.0/(14.0 * PI * pow (this->h, 2));
        } else if (Dim == 1) {
            res *= 1.0/(6.0 * this->h);
        }
        return res;
    }

    inline virtual Vecteur<Dim> gradient(const Vecteur<Dim> r) const {
        double q = r.norme()/(this->h);
        Vecteur<Dim> res;
        //if (q < 0.001) {
        //    res = Vecteur<Dim>();
        //} else if (q <= 1) {
        if (q <= 1) {
            //res = r/(2.0 * this->h * r.norme()) * (-pow(2 - q, 2) + 4.0 * pow(1 - q, 2));
            res = (-r/(2.0*this->h*this->h))*(4-3*q);
        } else if (q <= 2) {
            res = -(r * pow(2 - q, 2)) / (2.0 * this->h * r.norme());
        } else {
            res = Vecteur<Dim>();
        }
        if (Dim == 3) {
            res *= 3.0/(2.0 * PI * pow(this->h, 3));
        } else if (Dim == 2) {
            res *= 45.0/(7.0 * PI * pow (this->h, 2));
        } else if (Dim == 1) {
            res /= this->h;
        }
        return res;
    }

    inline virtual double laplacien(const Vecteur<Dim> r) const {
        double q = r.norme()/(this->h);
        double res;
        if (q < 0.001) {
            res = 0;
        } else if (q <= 1) {
            double prod = r.norme() * this->h;
            double h_carre = pow(this->h, 2);
            res = -(1.0 / prod) * pow(2 - q, 2) + (1.0 / h_carre) * (2 - q)
                + (4.0 / prod) * pow(1 - q, 2) - (4.0 / h_carre) * (1 - q);
        } else if (q <= 2) {
            res = -(1.0 / (r.norme() * this->h)) * pow(2 - q, 2) + (1.0 / pow(this->h, 2)) * (2 - q);
        } else {
            res = 0;
        }
        if (Dim == 3) {
            res *= 3.0/(2.0 * PI * pow(this->h, 3));
        } else if (Dim == 2) {
            res *= 45.0/(7.0 * PI * pow (this->h, 2));
        } else if (Dim == 1) {
            res /= this->h;
        }
        return res;
    }

};

#include "noyauLissage.tpp"

#endif
