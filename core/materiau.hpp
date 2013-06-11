#ifndef __MATERIAU_
#define __MATERIAU_

/**
 * @file materiau.hpp
 * @author
 * @date 21/05/2013
 * @brief Classe pour définir l'ensemble des paramètres définissant le fluide, et le système
 */

#include "vecteur.hpp"

/**
 * @enum TypeFluide 
 * Permet de définir par défaut des types de fluides
 */
enum TypeFluide {
    EAU,
    MUCUS,
    VAPEUR
};

/**
 * @class Materiau
 * @brief Ensemble des paramètres définissant le fluide, et le système
 */

template <unsigned int Dim>
class Materiau {

private:
    /* Propriétés communes à tous les fluides */
    Vecteur<Dim> acc_gravitation;     // m.s-2
    double pas_temps;                 // s
    double temperature;               // K
    double pression_atm;              // Pa

    /* Propriétés physiques particulières des fluides */
    double densite_repos;             // kg.m-3
    double masse_particules;          // kg
    double coeff_flottabilite;        // n/a
    double viscosite;                 // Pa.s
    double tension_surface;           // N.m-1
    double seuil_surface;             // n/a
    double rigidite_gaz;              // J
    double coeff_restitution;         // n/a
    unsigned int nbr_noyau;           // n/a
    double rayon_noyau;               // m
    double celerite_son;              // m.s-1
    double alpha;                     // 1
public:

    /**
     * @brief Constructeur 
     *
     * Constructeur prenant en paramètre tous les attributs
     * @param g       Accélération de la gravitation
     * @param dt      Pas de temps pour le schéma intégrateur
     * @param t       Température du milieu
     * @param p       Pression atmosphérique
     * @param rho     Masse volumique au repos
     * @param mp      Masse des particules
     * @param b       Coefficient de flottabilité
     * @param mu      Viscosité
     * @param sigma   Tension de surface
     * @param l       Seuil pour le calcul des force de surface
     * @param k       Coefficient de rigidité pour les gaz
     * @param cr      Coefficient de restitution
     * @param x       Nombre de particules dans la sphère du noyau de lissage
     * @param h       Rayon du noyau de lissage
     * @param cs      Célérité du son dans le fluide
     * @param a       Constante de viscosité
     */
    Materiau(Vecteur<Dim> g, 
	     double dt,
	     double t,
	     double p,
	     double rho,
	     double mp,
	     double b,
	     double mu,
	     double sigma,
	     double l,
	     double k,
	     double cr,
	     unsigned int x,
	     double h,
	     double cs,
	     double a
	     );

    /**
     * @brief Constructeur
     *
     * Constructeur d'un certain type de fluide
     * @param type Type de fluide énuméré
     */
    Materiau(TypeFluide type);

    /* Accesseurs */
    /**
     * @brief Accesseur
     * @return L'accélération de la gravitation
     */
    Vecteur<Dim> getAccGrav();
    /**
     * @brief Accesseur
     * @return Le pas de temps pour le schéma intégrateur
     */
    double getPasTemps();
    /**
     * @brief Accesseur
     * @return La température du milieu
     */
    double getTemperature();
    /**
     * @brief Accesseur
     * @return La pression atmosphérique
     */
    double getPression();
    /**
     * @brief Accesseur
     * @return La masse volumique au repos
     */
    double getDensiteRepos();
    /**
     * @brief Accesseur
     * @return La masse des particules
     */
    double getMasseParticules();
    /**
     * @brief Accesseur
     * @return Le coefficient de flottabilité
     */
    double getCoeffFlott();
    /**
     * @brief Accesseur
     * @return La viscosité du fluide
     */
    double getViscosite();
    /**
     * @brief Accesseur
     * @return La tension de surface
     */
    double getTensionSurface();
    /**
     * @brief Accesseur
     * @return Seuil pour le calcul des force de surface
     */
    double getSeuilSurface();
    /**
     * @brief Accesseur
     * @return Le coefficient de rigidité pour les gaz
     */
    double getRigiditeGaz();
    /**
     * @brief Accesseur
     * @return Le coefficient de restitution pour les collisions
     */
    double getCoeffRestitution();
    /**
     * @brief Accesseur
     * @return Le nombre de particules dans la sphère du noyau de lissage
     */
    unsigned int getNbrPartNoyau();
    /**
     * @brief Accesseur
     * @return Le rayon du noyau de lissage
     */
    double getRayonNoyau();
    /**
     * @brief Accesseur
     * @return La célérité du son dans le fluide
     */
    double getCeleriteSon();
    /**
     * @brief Accesseur
     * @return La constante de viscosité alpha dans le calcul du facteur nu
     * intervenant dans le calcul de la force de viscosité
     */
    double getConstanteViscosite();

    /* ** Interaction utilisateur ** */

    /**
     * @brief Interaction utilisateur
     *
     * Méthode permettant de modifier les paramètres communs à tous les fluides
     * de manière interactive pendant la simulation
     */
    void changerSysteme();

    /**
     * @brief Interaction utilisateur
     *
     * Méthode permettant de modifier le type du fluide
     * de manière interactive pendant la simulation
     * @param type Nouveau type du fluide
     */
    void changerNature(TypeFluide type);

    /**
     * @brief Interaction utilisateur
     *
     * Méthode permettant de modifier les paramètres propres aux fluides
     * de manière interactive pendant la simulation
     */
    void changerParam();
    
};

#include "materiau.tpp"
#endif
