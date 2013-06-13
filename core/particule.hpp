#ifndef _PARTICULE_HPP_
#define _PARTICULE_HPP_

#include <iostream>
#include "../core/vecteur.hpp"
#include "../core/materiau.hpp"

/**
 * @enum TypeFluide 
 * Permet de définir par défaut des types de fluides
 */
enum EtatParticule {
    ACTIVE,
    INACTIVE,
    TRANSITION
};

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
    double masse_volumique_prec; // Masse volumique de la particule 
                                 // au pas de temps précédent (kg.m^-3)
    double pression;             // Pression de la particule (Pa)
    double pressionPrec;         // Pression de la particule 
                                 // au pas de temps précédent (Pa) 
    double masse;                // Masse de la particule (m)
    EtatParticule etat;          // Etat d'activité de la particule (ARPS)


    /* ** Constructeurs ** */
public:
    /**
     * @brief Constructeur
     *
     * Constructeur
     * \param ind Numéro d'identification de la particule
     * \param pos Position initiale
     * \param vit Vitesse initiale
     * \param m Masse de la particule
     * \param rho Masse volumique initiale
     * \param p Pression initiale
     * \param e Etat de la particule
     */
  Particule(unsigned int ind, Vecteur<Dim> pos, Vecteur<Dim> vit, double rho = 0, double p = 0, double m = 0, EtatParticule e = ACTIVE);
    
    /**
     * @brief Destructeur
     *
     * Destructeur
     */
    ~Particule();


    /* ** Methodes ** */
public:
    /* ** Accesseurs ** */
    /**
     * @brief Accesseur
     *
     * \return Le numéro de la particule
     */
    unsigned int getIndice() const;

    /**
     * @brief Accesseur
     *
     * \return La position de la particule
     */
    const Vecteur<Dim> & getPosition() const;

    /**
     * @brief Accesseur
     *
     * \return La position de la particule au pas de temps précédent
     */
    const Vecteur<Dim> & getPositionPrec() const;

    /**
     * @brief Accesseur
     *
     * \return La vitesse de la particule
     */
    const Vecteur<Dim> & getVitesse() const;

    /**
     * @brief Accesseur
     *
     * \return La vitesse de la particule au pas de temps précédent
     */
    const Vecteur<Dim> & getVitessePrec() const;

    /**
     * @brief Accesseur
     *
     * \return L'accélération de la particule
     */
    const Vecteur<Dim> & getAcceleration() const;

    /**
     * @brief Accesseur
     *
     * \return Le total des forces s'exerçant sur la particule
     */
    const Vecteur<Dim> & getForces() const;

    /**
     * @brief Accesseur
     *
     * \return La masse de la particule
     */
    double getMasse() const;
   
    /**
     * @brief Accesseur
     *
     * \return La masse volumique de la particule
     */
    double getMasseVolumique() const;

    /**
     * @brief Accesseur
     *
     * \return La masse volumique de la particule au pas de temps précédent
     */
    double getMasseVolumiquePrec() const;

    /**
     * @brief Accesseur
     *
     * \return La pression de la particule
     */
    double getPression() const;

    /**
     * @brief Accesseur
     *
     * \return La pression de la particule au pas de temps précédent
     */
    double getPressionPrec() const;

     /**
     * @brief Accesseur
     *
     * \return Etat d'acivité de la particule
     */
    EtatParticule getEtat() const;
    

    /* ** Mutateurs ** */
    /**
     * @brief Mutateur
     *
     * Modifie la position de la particule
     * \param pos Nouvelle position de la particule
     */
    void setPosition(const Vecteur<Dim> &pos);

    /**
     * @brief Mutateur
     *
     * Met à jour la position de la particule du pas de temps précédent
     * \param pos Nouvelle position précédente de la particule
     */
    void setPositionPrec(const Vecteur<Dim> &pos);

    /**
     * @brief Mutateur
     *
     * Modifie la vitesse de la particule
     * \param vit Nouvelle vitesse de la particule
     */
    void setVitesse(const Vecteur<Dim> &vit);

    /**
     * @brief Mutateur
     *
     * Met à jour la vitesse de la particule du pas de temps précédent
     * \param pos Nouvelle vitesse précédente de la particule
     */
    void setVitessePrec(const Vecteur<Dim> &pos);

    /**
     * @brief Mutateur
     *
     * Modifie l'accélération de la particule
     * \param acc Nouvelle accélération de la particule
     */
    void setAcceleration(const Vecteur<Dim> &acc);

    /**
     * @brief Mutateur
     *
     * Modifie la masse volumique de la particule
     * \param rho Nouvelle masse volumique de la particule
     */
    void setMasseVolumique(double rho);

    /**
     * @brief Mutateur
     *
     * Met à jour la masse volumique de la particule du pas de temps précédent
     * \param rho Nouvelle masse volumique précédente de la particule
     */
    void setMasseVolumiquePrec(double rho);

    /**
     * @brief Mutateur
     *
     * Modifie la pression de la particule
     * \param p Nouvelle pression de la particule
     */
    void setPression(double p);

    /**
     * @brief Mutateur
     *
     * Met à jour la pression de la particule du pas de temps précédent
     * \param p Nouvelle pression précédente de la particule
     */
    void setPressionPrec(double p);

    /**
     * @brief Mutateur
     *
     * Modifie l'état de la particule
     * @param e Etat associé à l'activité de la particule
     */
    void setEtat(const EtatParticule &e);

    
    /**
     * @brief Mutateur
     *
     * Incrémente la position de la particule
     * \param pos Vecteur de déplacement de la particule (position += pos)
     */
    void incrPosition(const Vecteur<Dim> &pos);

    /**
     * @brief Mutateur
     *
     * Incrémente la vitesse de la particule
     * \param vit Facteur d'augmentation de la vitesse (vitesse += vit)
     */
    void incrVitesse(const Vecteur<Dim> &vit);

    /**
     * @brief Mutateur
     *
     * Incrémente le total des forces
     * @param f Facteur d'incrémentation des forces (forces += f)
     */
    void incrForces(const Vecteur<Dim>& f);

    /**
     * @brief Mutateur
     *
     * Décrémente le total des forces
     * @param f Facteur de décrémentation des forces (forces -= f)
     */
    void decrForces(const Vecteur<Dim>& f);
  
    /**
     * @brief Mise à jour de la particule pour un pas de temps
     *
     * Met à jour la pression en fonction de la masse volumique de la particule
     * Prototype éventuellement à reprendre
     * \param dens La densité au repos
     */
    void majPression(double dens);

    /**
     * @brief Calcul d'une surface implicite pour le rendu
     *
     * Calcule la valeur de l'isosurface d'une particule en un point de l'espace.
     * \param pos Position à laquelle on veut calculer la valeur de l'isosurface
     * \param prec Booléen indiquant si on le fait pour la position actuelle ou précédente
     * @return Isovaleur au point pos
     */
    double isosurface(Vecteur<Dim> &pos, bool prec);
    
    /**
     * @brief Affichage graphique
     *
     * Fonction d'affichage de la particule sous la forme d'une sphère
     * \param mat Le matériau du fluide auquel appartient la particule
     */
    void draw(Materiau<Dim> *mat) const;

    /**
     * @brief Affichage graphique
     *
     * Fonction d'affichage de la particule sous la forme d'un point ou d'une sphere
     * \param point Indique si on doit afficher un point (true) ou une sphere (false)
     */
    void draw(bool point) const;
};

/**
 * Opérateur d'affichage des composantes de la particule
 */
template<unsigned int Dim>
std::ostream& operator<<(std::ostream& os, const Particule<Dim>& p);


#include "particule.tpp"

#endif

