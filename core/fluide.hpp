#ifndef _FLUIDE_HPP_
#define _FLUIDE_HPP_

#include <QVector>
#include <QVector2D>
#include <QVector4D>

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
    Metaballs * ball;                  /*!< Metaball permettant de dessiner le fluide */
    
public:
    double x_min;                        /*!< Définit le plan d'équation x = x_min (provisoire) */
    double x_max;                        /*!< Définit le plan d'équation x = x_max (provisoire) */
    double y_min;                        /*!< Définit le plan d'équation y = x_min (provisoire) */
    double y_max;                        /*!< Définit le plan d'équation y = x_max (provisoire) */
    double z_min;                        /*!< Définit le plan d'équation z = z_min (provisoire) */

private:
    int nbrParticules;                   /*!< Nombre de particules du fluide */
    bool debutAnim;                      /*!< Indique si on est au debut de l'animation */
    bool afficheMetaballs;               /*!< Indique si l'on doit afficher les métaballs lors de l'animation */
    bool affichePoint;                    /*!< Indique si les particules sont affichées comme des points ou des spheres */

    /* Paramètres nécessaires à la réinitialisation du fluide */
    Vecteur<Dim> vitInit;
    double densiteInit;
    double pressionInit;

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

    /* Paramètres nécessaires à la réinitialisation du fluide */
    Vecteur<Dim> nbPart;
    double ecart;


    /* ** Constructeurs ** */
public:
    /**
     * @brief Constructeur
     *
     * Constructeur par défaut : le fluide ne contient aucune particule
     * \param m Matériau du fluide
     */
    Fluide(Materiau<Dim> * m);

    /**
     * @brief Constructeur
     *
     * Constructeur avec initialisation d'un parallélépipède de particules
     * \param m Matériau du fluide
     * \param nbP Tableau du nombre de particules sur chacune des dimensions
     * \param e Écart entre les particules
     * \param rho Masse volumique initiale des particules
     * \param p Pression initiale des particules
     * \param v0 Vitesse initiale des particules
     * \param xmin Bord de la boite
     * \param xmax Bord de la boite
     * \param ymin Bord de la boite
     * \param ymax Bord de la boite
     * \param zmin Dessous de la boite
     */
    Fluide(Materiau<Dim> * m, 
	   Vecteur<Dim> nbP, 
	   double e, 
	   double rho, 
	   double p, 
	   Vecteur<Dim> v0 = Vecteur<Dim>(),
            double xmin = -0.2, 
	   double xmax = 0.2, 
	   double ymin = -0.2, 
	   double ymax = 0.2, 
	   double zmin = 0.0);
    
    /**
     * @brief Destructeur
     *
     * Destructeur
     */
    ~Fluide();

    /**
     * @brief Initialisation
     *
     * Méthode appelée par le constructeur, qui (re)créé le fluide
     */
    void init();
    
    /* ** Méthodes ** */
    /**
     * @brief Ajout au fluide
     *
     * Ajoute une particule à l'ensemble des particules
     * \param part La particule à ajouter
     */
    void ajouteParticule(Particule<Dim> * part);

    /**
     * @brief Accesseur
     *
     * @return Le vecteur des particules mobiles utilisées dans le fluide
     */
    list<Particule<Dim> *> getParticulesMobiles();

    /**
     * @brief Accesseur
     *
     * @return Un pointeur sur le type de matériau utilisé
     */
    Materiau<Dim>* getMateriau();
  
    /**
     * @brief Mise à jour des particules pour un pas de temps
     *
     * Met à jour la densité et la pression de toutes les particules
     */
    void majDensitePression();
    
    /**
     * @brief Mise à jour des particules pour un pas de temps
     *
     * Met à jour la position et la vitesse de toutes les particules
     */
    void majPositionVitesse();
    
    /**
     * @brief Coloration des metaball
     *
     * A appeler apres la construction du fluide dans la scene
     */
    void colorationMetaball();
    
    /**
     * @brief Affichage graphique
     *
     * Fonction d'affichage du fluide
     */
    void draw();

    /**
     * @brief Affichage graphique
     *
     * Fonction d'affichage du fluide en utilisant les shaders
     * @param vertices Pointeur sur un tableau de type QGLBuffer où stocker la position des particules composant le fluide
     * @param colors Pointeur sur un tableau de type QGLBuffer où stocker la couleur des particules composant le fluide
     * @param indices Pointeurs sur un tableau contenant les indices de ces particules
     */
    void draw(struct QVector<QVector3D> *vertices, struct QVector<QVector4D> *colors, struct QVector<int> *indices);

    /**
     * @brief Trace de debug
     *
     * Affichage des particules du fluide
     */
    void affiche();
    
    /**
     * @brief Mise à jour des particules pour un pas de temps
     *
     * Mise à jour du système avec le schéma d'intégration de l'ARPS
     */
    void schemaIntegration();
    /* Avec des traces */
    void schemaIntegration_Traces();

    /* ** Interaction utilisateur ** */
    /**
     * @brief Interaction utilisateur
     *
     * Modification interactive des paramètres du fluide
     * @return True ssi il faut recommencer la simulation après modification
     */
    bool changerParam();

    /* ** Interaction utilisateur ** */
    /**
     * Modification interactive du mode d'affichage
     */
    void changerAffichage();

    /* ** Interaction utilisateur ** */
    /**
     * Modification interactive du mode d'affichage
     */
    void changerAffichageAuto();

    /**
     * @brief Interaction utilisateur
     *
     * Modification interactive des seuils de l'ARPS
     */
    void changerArps();

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
     * Supprime les éléments du fluide; appelée par le destructeur
     * et lors des réinitialisations
     */
    void clear();
    
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
    //Vecteur<Dim> collisionCascade(const Vecteur<Dim> & v, const Cascade<Dim> c);
    Vecteur<Dim> collisionCascade(const Vecteur<Dim> & v,
				  Materiau<Dim> *mat,
				  const double bassin_x,
				  const double bassin_y,
				  const double bassin_z);

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

    /* Mise à jour d'une particule dans la table de hashage */
    void reinsertionTable(Particule<Dim>*);
    
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
    /* Avec des traces de débug */
    void integrationForces_Traces();

    /* Fonction de calcul d'un critère de restriction */
    double calculCritere(const Vecteur<Dim>&);
    
    /* Fonction de restriction concernant l'activité des particules */
    void restriction(const Vecteur<Dim>&, double&, Vecteur<Dim>&);

};


#include "fluide.tpp"

#endif
