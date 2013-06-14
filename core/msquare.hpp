#ifndef _MSQUARE_
#define _MSQUARE_

class MarchingSquare {

private :
	int n ;
	int p ;
	double** points;            /*!< Tableau de booléens, chaque booléen étant associé à un point de l'espace :
		                             un booléen indique si le sommet doit être marqué ou non, pour avoir
		                             la configuration du carré qui sera défini à l'aide de quatre points */
    Vecteur<3> origine;         /*!< Origine spatiale de l'espace rectangulaire considéré dans le maillage */
	Vecteur<3> axe1;			/*!< Premier axe du repère plan dans lequel sont définis les carrés */
	Vecteur<3> axe2;			/*!< Deuxième axe du repère plan dans lequel sont définis les carrés */
	Vecteur<3> normale;         /*!< Normale au repère, obtenue par produit vectoriel des deux attributs précédents */
	double cote;			 	/*!< Côté du carré */
	int configurations[16][12]; /*!< Look-up table des 16 configurations possibles */

	/**
	 * \brief Constructeur 
	 *
	 * \param _origine Origine du repère, possédant les coordonnées minimales selon les axes axe1 et axe2
	 * \param _axe1 Premier axe du repère dans lequel est défini le marching square
	 * \param _axe2 Deuxième axe du repère dans lequel est défini le marching square
	 * \param _cote Côté des carrés
	 * \param x Dimension du rectangle selon le premier axe
	 * \param y Dimension du rectangle selon le deuxième axe
	 */
    MarchingSquare(Vecteur<3> origine, Vecteur<3> _axe1, Vecteur<3> _axe2, double _cote, double x = 1.0, double y = 1.0);

	/** 
	 * \brief Destructeur
	 * 
	 * Destructeur d'un objet de type Marching Square
	 */
	~MarchingSquare();

public :
    /**
     * \brief Coloration
     *
     * Calcule la valeur de la surface implicite définie par les particules du fluide pour tout point du maillage,
     * et attribue à chaque sommet sa couleur, ceci pour déterminer la configuration des cubes
     * @param particules Liste des particules considérées
     */
    void initColoration(list<Particule<3> *> &particules);
    
    /**
     * \brief Coloration
     *
     * Calcule la valeur de la surface implicite définie par les particules du fluide pour tout point du maillage,
     * et attribue à chaque sommet sa couleur, ceci pour déterminer la configuration des carrés
     * @param particules Liste des particules considérées
     */
    void coloration(list<Particule<3> *> &particules);

    /**
     * \brief Représentation
     *
     * Représente la surface implicite ainsi obtenue à l'aide de l'algorithme des Marching Squares
     */
    void draw();

    /**
     * \brief Représentation d'un carré
     *
     * Représente une configuration d'un Marching square, à la position et de taille voulue
     * \param pos Position du sommet 0 du carré, de coordonnées minimales selon les axes axe1 et axe2
     * \param cote Dimension du côté du carré
     * \param config Configuration du carré
	 * \param valeurCentrale Valeur de la fonction d'influence en le centre du carré, servant à trancher en cas d'ambiguïté
     */
    void drawSquare(Vecteur<3> pos, double cote, int config, bool valeurCentrale);

    /**
     * \brief Représentation d'un triangle
     *
     * Représente un triangle à l'intérieur d'un carré
     * \param pos Position du sommet 0 du carré, de coordonnées minimales selon axe1 et axe2
     * \param cote Dimension du côté du carré
     * \param a Numéro de la première arête à relier
     * \param b Numéro de la deuxième arête à relier
     * \param c Numéro de la troisième arête à relier
     */
    void drawTriangle(Vecteur<3> pos, double cote, int a, int b, int c);

    /**
     * \brief Association d'un point
     *
     * Retourne un point au milieu de l'arête a d'un carré, connaissant la position de son
     * sommet 0 et de son côté.
     * \param pos Position du sommet 0 du carré, de coordonnées minimales selon les axes axe1 et axe2
     * \param cote Dimension du côté du carré
     * \param a Numéro du point considéré
     * \return Le point de l'espace ainsi déterminé
     */
    Vecteur<3> associerPoint(Vecteur<3> pos, double cote, int a);
};

#endif
