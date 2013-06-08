#ifndef _FLUIDE_HPP_
#define _FLUIDE_HPP_

#include <iostream>
#include <map>
#include <list>
#include <set>
#include "materiau.hpp"
#include "particule.hpp"
#include "vecteur.hpp"
#include "premier.hpp"
#include "metaballs.hpp"
using std::multimap;
using std::list;
using std::set;

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
    Materiau<Dim> * mat;               /*!< Materiau du fluide (avec toutes les constantes) */
    list<Particule<Dim> *> particules; /*!< Ensemble des particules mobiles */
    list<Particule<Dim> *> lignedEau;  /*!< Ensemble des particules immobiles sur le plan z = z_min */
    Metaballs ball;                     /*!< Metaball permettant de dessiner le fluide */
public:
    double x_min;                        /*!< Définit le plan d'équation x = x_min (provisoire) */
    double x_max;                        /*!< Définit le plan d'équation x = x_max (provisoire) */
    double y_min;                        /*!< Définit le plan d'équation y = x_min (provisoire) */
    double y_max;                        /*!< Définit le plan d'équation y = x_max (provisoire) */
    double z_min;                        /*!< Définit le plan d'équation z = z_min (provisoire) */

private:
    int nbrParticules;                   /*!< Nombre de particules du fluide */
    bool debutAnim;                      /*!< Indique si on est au debut de l'animation */

    /* Table de nombre premiers pour le calcul de la longueur de la table de hashage */
    Premier<Dim> table;
    /* Table de hashage pour les voisins */
    multimap<int, Particule<Dim>*> hash_voisins;
    /* Longueur de la table de hashage */
    int lgrHash;

    /* Seuils pour le critère d'activité des particules */
    double epsilonR;  // Seuil de dynamique restreinte (en-dessous duquel les particules restent immobiles)
    double epsilonF;  // Seuil de dynamique entière (au-dessus duquel les particules sont complètement libres)
    /* Liste des particules actives */
    list<Particule<Dim>*> actives;


    /* ** Constructeurs ** */
public:
    /**
     * Constructeur par défaut : le fluide ne contient aucune particule
     * \param m Matériau du fluide
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
     * @return Le vecteur des particules mobiles utilisées dans le fluide
     */
    list<Particule<Dim> *> getParticulesMobiles();

    /**
     * @return Le vecteur des particules immobiles utilisées dans le fluide
     */
    list<Particule<Dim> *> getParticulesImmobiles();

    /**
     * @return Un pointeur sur le type de matériau utilisé
     */
    Materiau<Dim>* getMateriau();
  
    /**
     * Met à jour la densité et la pression de toutes les particules
     */
    void majDensitePression();
    
    /**
     * Met à jour la position et la vitesse de toutes les particules
     */
    void majPositionVitesse();
    
    /**
     * Fonction d'affichage du fluide
     */
    void draw();

    /**
     * Affichage des particules du fluide
     */
    void affiche();
    
    /**
     * Mise à jour du système avec le schéma d'intégration de l'ARPS
     */
    void schemaIntegration();

    /**
     * Fonction de tests basiques sur l'insertion dans la table de hashage,
     * qui a besoin de l'accès direct à celle-ci
     */
    friend void test_map();

    /**
     * Fonction de tests basiques sur le calcul du voisinage
     */
    friend void test_voisins();

private:
    /*
     * Fonction interne appelée lors de la détection de collisions
     * Elle détecte une collision de la particule v avec la boîte
     * de plans X=x_min, X=x_max, Y=y_min, Y=y_max et Z=z_min
     * Elle renvoie le point de contact s'il y a collision, le Vecteur v sinon
     */
    Vecteur<Dim> collision(const Vecteur<Dim> & v);

  /**
   * Détecte une collision avec les parois de la cascade
   * @param v 
   * @return 
   */
  Vecteur<Dim> collisionCascade(const Vecteur<Dim> & v);

    /* 
     * Fonction de hashage 
     * ATTENTION : prend en argument le vecteur de position 
     * ** DANS LA GRILLE DE VOXELS ** (des entiers)
     */
    int fonction_hashage(Vecteur<Dim>);

    /* Fonction d'accès au voisinage d'une particule */
    set<Particule<Dim>*> voisinage(Particule<Dim>&);

    /*
     * Fonction d'accès au voisinage d'une particule,
     * en se basant sur les positions au pas de temps précédent
     */
    set<Particule<Dim>*> voisinagePrec(Particule<Dim>&);

    /* Mise à jour de la table : on la vide entièrement puis on réinsère les particules */
    void majTableHashage();
    
    /* DEBUG : affichage de la table de hashage */
    void afficher_hash();

    /* DEBUG : affichage de la liste des particules actives */
    void afficher_actives();

    /* Calcul des forces d'interaction entre 2 particules au temps courant */
    Vecteur<Dim> calculForcesInteraction(Particule<Dim>*, Particule<Dim>*);
    
    /* Calcul des forces d'interaction entre 2 particules au pas de temps précédent */
    Vecteur<Dim> calculForcesInteractionPrec(Particule<Dim>*, Particule<Dim>*);

    /*
     * Mise à jour des forces s'exerçant sur les particules du fluide,
     * par l'algorithme incrémental de l'ARPS
     */
    void integrationForces();

    /* Fonction de calcul d'un critère de restriction */
    double calculCritere(const Vecteur<Dim>&);
    
    /* Fonction de restriction concernant l'activité des particules */
    void restriction(const Vecteur<Dim>&, double&, Vecteur<Dim>&);

};


#include "fluide.tpp"

#endif

