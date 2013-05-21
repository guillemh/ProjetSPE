#ifndef __MATERIAU_
#define __MATERIAU_

/**
 * @file materiau.hpp
 * @author 
 * @date 21/05/2013
 * @brief Ensemble des paramètres définissant le fluide, et le système
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
	     double h
	     );

    /**
     * Constructeur d'un certain type de fluide
     * @param type Type de fluide énuméré
     */
    Materiau(TypeFluide type);

    /* Accesseurs */
    Vecteur<Dim> getAccGrav();
    double getPasTemps();
    double getTemperature();
    double getPression();
    double getDensiteRepos();
    double getMasseParticules();
    double getCoeffFlott();
    double getViscosite();
    double getTensionSurface();
    double getSeuilSurface();
    double getRigiditeGaz();
    double getCoeffRestitution();
    unsigned int getNbrPartNoyau();
    double getRayonNoyau();


};

#include "materiau.tpp"
#endif
