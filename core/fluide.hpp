#ifndef _FLUIDE_HPP_
#define _FLUIDE_HPP_

#include <iostream>
#include <map>
#include <list>
#include "materiau.hpp"
#include "particule.hpp"
#include "vecteur.hpp"
#include "premier.hpp"
using std::multimap;
using std::list;

/** 
 * \class Fluide
 * @brief Gestion de l'ensemble des particules constituant le fluide
 * 
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class Fluide {
    
    /* ** Attributs ** */
private:
    Materiau<Dim> * mat;                 /*!< Materiau du fluide (avec toutes les constantes) */
    list<Particule<Dim> *> particules; /*!< Ensemble des particules mobiles */
    list<Particule<Dim> *> lignedEau;  /*!< Ensemble des particules immobiles sur le plan z = z_min */
public:
    double x_min;                        /*!< Définit le plan d'équation x = x_min (provisoire) */
    double x_max;                        /*!< Définit le plan d'équation x = x_max (provisoire) */
    double y_min;                        /*!< Définit le plan d'équation y = x_min (provisoire) */
    double y_max;                        /*!< Définit le plan d'équation y = x_max (provisoire) */
    double z_min;                        /*!< Définit le plan d'équation z = z_min (provisoire) */

private:
    int nbrParticules;                   /*!< Nombre de particules du fluide */
    bool debutAnim;                      /*!< Indique si on est au debut de l'animation */

    Premier<Dim> table;
    
    /* Table de hashage pour les voisins */
    multimap<int, Particule<Dim>*> hash_voisins;
    
    /* Longueur de la table de hashage */
    int lgrHash;


    /* ** Constructeurs ** */
public:
    /**
      * Constructeur par defaut
      * \param m matériau du fluide
      */
    Fluide(Materiau<Dim> * m);

    /**
      * Constructeur avec initialisation d'un parallèlépipède de particules
      * \param m Matériau du fluide
      * \param nb Tableau du nombre de particules sur chacune des dimensions
      * \param ecart Écart entre les particules
      * \param rho Masse volumique initiale des particules
      * \param p Pression initiale des particules
      */
    Fluide(Materiau<Dim> * m, int nb[Dim], double ecart, double rho, double p);
    
    /**
      * Destructeur
      */
    ~Fluide();


    /* ** Methodes ** */
public:
    /**
      * Ajoute une particule à l'ensemble des particules
      * \param part La particule à ajouter
      */
    void ajouteParticule(Particule<Dim> * part);

    /**
     * Détecte une collision avec les parois de la boîte
     */
    Vecteur<Dim> collision(const Vecteur<Dim> & v);

    /**
     * Retourne le vecteur des particules mobiles utilisées dans le fluide
     */
    list<Particule<Dim> *> getParticulesMobiles();

    /**
     * Retourne le vecteur des particules immobiles utilisées dans le fluide
     */
    list<Particule<Dim> *> getParticulesImmobiles();

    /**
     * Retourne un pointeur sur le type de matériau utilisé
     */
    Materiau<Dim>* getMateriau();
  
    /**
      * Met à jour la densité et la pression de toutes les particules
      */
    void majDensitePression();
    
    /**
      * Met à jour la densité et la pression de toutes les particules
      */
    void majPositionVitesse();
    
    /**
      * Fonction d'affichage du fluide
      */
    void draw() const;

    /**
      * Affichage des particules du fluide
      */
    void affiche();
    
    /**
      * Fonction de hashage
      */
    int fonction_hashage(Vecteur<Dim>);

    /**
      * Fonction d'accès au voisinage d'une particule
      */
    list<Particule<Dim>*> voisinage(Particule<Dim>&);

    /**
      * DEBUG : affichage de la table de hashage
      */
    void afficher_hash();

    /**
     * Fonction de tests basiques sur l'insertion dans la table de hashage,
     * qui a besoin de l'accès direct à celle-ci
     */
    friend void test_map();

    /**
     * Fonction de tests basiques sur le calcul du voisinage
     */
    friend void test_voisins();

};


#include "fluide.tpp"

#endif

