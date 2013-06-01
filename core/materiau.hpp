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
 * @enum TypeFluide permettant de définir par défaut des types de fluides
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
     * Constructeur d'un certain type de fluide
     * @param type Type de fluide énuméré
     */
    Materiau(TypeFluide type);

    /* Accesseurs */
    /**
     * @return L'accélération de la gravitation
     */
    Vecteur<Dim> getAccGrav();
    /**
     * @return Le pas de temps pour le schéma intégrateur
     */
    double getPasTemps();
    /**
     * @return La température du milieu
     */
    double getTemperature();
    /**
     * @return La pression atmosphérique
     */
    double getPression();
    /**
     * @return La masse volumique au repos
     */
    double getDensiteRepos();
    /**
     * @return La masse des particules
     */
    double getMasseParticules();
    /**
     * @return Le coefficient de flottabilité
     */
    double getCoeffFlott();
    /**
     * @return La viscosité du fluide
     */
    double getViscosite();
    /**
     * @return La tension de surface
     */
    double getTensionSurface();
    /**
     * @return Seuil pour le calcul des force de surface
     */
    double getSeuilSurface();
    /**
     * @return Le coefficient de rigidité pour les gaz
     */
    double getRigiditeGaz();
    /**
     * @return Le coefficient de restitution pour les collisions
     */
    double getCoeffRestitution();
    /**
     * @return Le nombre de particules dans la sphère du noyau de lissage
     */
    unsigned int getNbrPartNoyau();
    /**
     * @return Le rayon du noyau de lissage
     */
    double getRayonNoyau();
    /**
     * @return La célérité du son dans le fluide
     */
    double getCeleriteSon();
    /**
     * @return La constante de viscosité alpha dans le calcul du facteur nu
     * intervenant dans le calcul de la force de viscosité
     */
    double getConstanteViscosite();
};

#include "materiau.tpp"
#endif
