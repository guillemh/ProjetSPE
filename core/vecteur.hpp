#ifndef _VECTEUR_HPP_
#define _VECTEUR_HPP_

#include <cstdlib>
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;

/** 
 * \class Vecteur
 * @brief Classe représentant un noyau de lissage 
 * 
 * Dim : Dimension de l'espace
 */
template <unsigned int Dim>
class Vecteur {

    /* ** Attributs ** */
public:
    double t[Dim];      /*!< Tableau des coordonnées du vecteur */


    /* ** Constructeurs ** */
public :
    /**
     * Constructeur d'un vecteur nul bidimensionnel ou tridimensionnel
     */
    Vecteur();

    /**
     * Constructeur d'un vecteur comportant une valeur de remplissage par défaut
     *
     * \param def la valeur a entrer dans le vecteur
     */
    Vecteur(double def);

    /**
     * Constructeur par défaut du vecteur bidimensionnel
     *
     * \param x Première composante du vecteur
     * \param y Deuxième composante du vecteur
     */
    Vecteur(double x, double y);

    /**
     * Constructeur par défaut du point tridimensionnel
     *
     * \param x Première composante du vecteur
     * \param y Deuxième composante du vecteur
     * \param z Troisième composante du vecteur
     */
    Vecteur(double x, double y, double z);

    /**
     * Constructeur par recopie d'un autre vecteur
     *
     * \param v Référence sur le vecteur recopié */
    Vecteur(const Vecteur<Dim> &v);

    /**
     * Destructeur d'un objet de type vecteur
     */
    ~Vecteur();


    /* ** Methodes ** */
public:
    /**
     * Calcul de la norme d'un vecteur
     * \return norme du vecteur
     */
    inline double  norme() const {
        double somme = 0;
        for (unsigned int i = 0; i < Dim; i++) {
            somme += t[i] * t[i];
        }
        return sqrt(somme);
    }  

    /**
     * Calcul du produit scalaire de deux vecteurs
     * \param v le vecteur avec lequel faire le produit scalaire
     * \return le produit scalaire des deux vecteurs
     */
    inline double scalaire(Vecteur<Dim> & v) const {
        double somme = 0;
        for (unsigned int i = 0; i < Dim; i++) {
            somme += t[i] * v.t[i];
        }
        return somme;
    }


    //
    // Opérateurs d'accès
    // 

    /**
     *  \brief Operateur d'accès en écriture à un élément du vecteur
     * Fonction accédant a l'élément indexé par l'argument du vecteur.
     *
     * \param i Indice de l'élément
     * \return Référence sur l'élément situé dans la case numero i - 1 du vecteur
     *
     */
    inline double & operator()(unsigned int i) {
        return t[i - 1];
    }

    /**
     * \brief Operateur d'accès en lecture à un élément du vecteur
     * Fonction accédant a l'élément indexé par l'argument du vecteur.
     * La méthode n'a pas le droit de modifier les champs de l'objet manipulé.
     *
     * \param i Indice de l'élément
     * \return L'élément situe dans la case numero i - 1 du vecteur
     *
     */        
    inline double operator()(unsigned int i) const {
        return t[i - 1];
    }

    //
    // Opérations internes
    //

    /**
     * \brief Addition interne par un réel
     *
     * Fonction additionnant un réel à tous les elements de l'objet.
     *
     * \param valeur Réel
     * \return Référence sur le Vecteur créé par addition de l'argument et de l'existant
     *
     */
    inline Vecteur<Dim> & operator+=(const double &valeur) {
        Vecteur<Dim> &a = *this;
        for (unsigned int i = 1; i <= Dim; i++) {
            a(i) += valeur;
        }
        return a;
    }

    /*!
     * \brief Soustraction interne par un réel
     *
     * Fonction soustrayant un réel à tous les éléments de l'objet.
     *
     * \param valeur Réel
     * \return Référence sur le Vecteur créé par addition de l'argument et de l'existant
     *
     */
    inline Vecteur<Dim> & operator-=(const double &valeur) {
        Vecteur<Dim> &a = *this;
        for (unsigned int i = 1; i <= Dim; i++) {
            a(i) -= valeur;
        }
        return a;
    }
    /*!
     * \brief Multiplication interne par un réel
     *
     * Fonction multipliant un réel à tous les elements de l'objet.
     *
     * \param valeur Réel
     * \return Référence sur le Vecteur créé par addition de l'argument et de l'existant
     *
     */
    inline Vecteur<Dim> & operator*=(const double &valeur) {
        Vecteur<Dim> &a = *this;
        for (unsigned int i = 1; i <= Dim; i++) {
            a(i) *= valeur;
        }
        return a;
    }

    /*!
     * \brief Division interne par un réel
     *
     * Fonction divisant un réel à tous les éléments de l'objet.
     *
     * \param valeur Réel
     * \return Référence sur le Vecteur créé par addition de l'argument et de l'existant
     *
     */
    inline Vecteur<Dim> & operator/=(const double &valeur) {
        if (valeur != 0.0) {
            Vecteur<Dim> &a = *this;
            for (unsigned int i = 1; i <= Dim; i++) {
                a(i) /= valeur;
            }
            return a;
        } else {
            cout << "* 2 = 0 ! *" << endl ;
            cout << "Vecteur<Dim> & operator/=(const double &valeur) :" << endl;
            cout << "Erreur : division par zéro" << endl;
            exit(-1);
        }
    }

    /*!
     * \brief Addition interne par un vecteur
     *
     * Fonction additionnant terme à terme le vecteur à l'objet.
     *
     * \param v référence du vecteur à additionner 
     * \return Référence sur le Vecteur créé par addition ou un message d'erreur si vecteurs de tailles différentes
     *
     */
    inline Vecteur<Dim> & operator+=(const Vecteur<Dim> &v) {
        Vecteur<Dim> &a = *this;
        for (unsigned int i = 1; i <= Dim; i++) {
            a(i) += v(i);
        }
        return a;
    }

    /*!
     * \brief Soustraction interne par un vecteur
     *
     * Fonction soustrayant terme à terme le vecteur à l'objet.
     *
     * \param v référence du vecteur à soustraire
     * \return Référence sur le Vecteur créé par soustraction ou un message d'erreur si vecteurs de tailles différentes
     *
     */ 
    inline   Vecteur<Dim> & operator-=(const Vecteur<Dim> &v) {
        Vecteur<Dim> &a = *this;
        for (unsigned int i = 1; i <= Dim; i++) {
            a(i) -= v(i);
        }
        return a;
    }


    /*!
     * \brief Multiplication interne par un vecteur
     *
     * Fonction multipliant terme à terme le vecteur à l'objet.
     *
     * \param v référence du vecteur à multiplier
     * \return Référence sur le Vecteur créé par multiplication ou un message d'erreur si vecteurs de tailles différentes
     *
     */
    inline Vecteur<Dim> & operator*=(const Vecteur<Dim> &v) {
        Vecteur<Dim> &a = *this;
        for (unsigned int i = 1; i <= Dim; i++) {
            a(i) *= v(i);
        }
        return a;
    }

    /*!
     * \brief Division interne par un vecteur
     *
     * Fonction divisant terme à terme l'objet par le vecteur.
     *
     * \param v référence du vecteur à diviser
     * \return Référence sur le Vecteur créé par division ou un message d'erreur si division par zéro ou si vecteurs de tailles différentes
     *
     */
    inline Vecteur<Dim> & operator/=(const Vecteur<Dim> &v) {
        Vecteur <Dim> &a = *this;
        for (unsigned int i = 1; i <= Dim; i++) {
            if (v(i) != 0.0) {
                a(i) /= v(i);
            } else {
                cout << "Vecteur<Dim> & operator/=(const Vecteur<Dim> &v) :" << endl;
                cout << "Erreur : division par zéro" << endl;
                exit(-1);
            }
        }
        return a;
    }

    /*!
     * \brief Opérateur d'affectation
     *
     * \param v Référence à un Vecteur constant
     *
     * \return Référence sur le Vecteur obtenu
     *
     */
    inline Vecteur<Dim> & operator=(const Vecteur<Dim> &v) {
        for (unsigned int i = 1; i <= Dim; i++) {
            (*this)(i) = v(i);
        }
        return(*this);
    }

    /*!
     * \brief Operateur de comparaison a un autre Vecteur
     * 
     * \param v réference constante sur un Vecteur
     * \return Booleen contenant le résultat de la comparaison
     *
     */
    inline bool operator==(const Vecteur<Dim> &v) const {
        for (unsigned int i = 1; i <= Dim; i++) {
            // Etant donne que ce sont des double, on teste la difference plutot que l'egalite !
            if (std::abs((*this)(i) - v(i)) > 0.0000000001) {
                return false;
            }
        }
        return true;
    }

    /*!
     * \brief Operateur de difference a un autre Vecteur
     * 
     * \param v réference constante sur un Vecteur
     * \return Booleen valant true si les vecteurs ne sont pas égaux
     *
     */
    inline bool operator!=(const Vecteur<Dim> &v) const {
        return not ((*this) == v);
    }
};


//
// Opérations externes
//


/**
 * \brief Addition par un réel
 *
 * Fonction additionnant un réel à tous les elements d'un Vecteur.
 * Dans cette fonction, le premier argument est un double.
 *
 * \param r Réel
 * \param v Référence sur le Vecteur à qui on ajoute r 
 * \return Le Vecteur créé par addition de l'argument et de l'existant
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator+(double r, const Vecteur<Dim> &v) {
    Vecteur<Dim> a(v);
    a += r;
    return a;
}


/*!
 * \brief Addition par un réel
 *
 * Fonction additionnant un réel à tous les elements d'un Vecteur.
 * Dans cette fonction, le premier argument est un double.
 *
 * \param v Référence sur le Vecteur à qui on ajoute r 
 * \param r Réel
 * \return Le Vecteur créé par addition de l'argument et de l'existant
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator+(const Vecteur<Dim> &v, double r) {
    return (r + v);
}

/*!
 * \brief Soustraction par un réel
 *
 * Fonction soustrayant un réel à tous les elements d'un Vecteur.
 * Dans cette fonction, le premier argument est un double.
 *
 * \param r Réel
 * \param v Référence sur le Vecteur à qui on soustrait r 
 * \return Le Vecteur créé par soustraction de l'argument et de l'existant
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator-(double r, const Vecteur<Dim> &v)
{
    Vecteur<Dim> a(r);
    a -= v;
    return a;
}
/*!
 * \brief Soustraction par un réel
 *
 * Fonction soustrayant un réel à tous les elements d'un Vecteur.
 * Dans cette fonction, le premier argument est un vecteur.
 *
 * \param v Référence sur le Vecteur à qui on soustrait r 
 * \param r Réel
 * \return Le Vecteur créé par soustraction de l'argument et de l'existant
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator-(const Vecteur<Dim> &v, double r) {
    Vecteur<Dim> a(v);
    a -= r;
    return a;
}

/*!
 * \brief Multiplication par un réel
 *
 * Fonction multipliant tous les elements d'un Vecteur par un réel.
 * Dans cette fonction, le premier argument est un double.
 *
 * \param r Réel
 * \param v Référence sur le Vecteur que l'on multiplie par r 
 * \return Le Vecteur créé par multiplication de l'argument et de l'existant
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator*(double r, const Vecteur<Dim> &v) {
    Vecteur<Dim> a(v);
    a *= r;
    return a;
}

/*!
 * \brief Multiplication par un réel
 *
 * Fonction multipliant tous les elements d'un Vecteur par un réel.
 * Dans cette fonction, le premier argument est un vecteur.
 *
 * \param v Référence sur le Vecteur que l'on multiplie par r 
 * \param r Réel
 * \return Le Vecteur créé par multiplication de l'argument et de l'existant
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator*(const Vecteur<Dim> &v, double r) {
    return (r * v);
}

/*!
 * \brief Division par un réel
 *
 * Fonction divisant tous les éléments d'un Vecteur par un réel.
 *
 * \param v Référence sur le Vecteur divisé par r 
 * \param r Réel
 * \return Le Vecteur créé par division de l'argument et de l'existant
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator/(const Vecteur<Dim> &v, double r) {
    if (r != 0.0) {
        Vecteur<Dim> a = Vecteur<Dim>(v);
        a /= r;
        return a;
    } else {
        cout << "Vecteur<Dim> operator/(const Vecteur<Dim> &v, double r) :" << endl;
        cout << "Erreur : division par zero" << endl;
        exit(-1);
    }
}

/*!
 * \brief Division d'un réel
 *
 * Fonction retournant le résultat de la division terme à terme entre un Vecteur dont tous les élements sont égaux et un Vecteur.
 *
 * \param r Réel avec lequel on initialise le Vecteur à diviser
 * \param v Référence sur le Vecteur diviseur 
 * \return Le Vecteur créé par division de l'argument et de l'existant
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator/(double r, const Vecteur<Dim> &v) {
    Vecteur<Dim> b(r);
    return (b / v);
}

/*!
 * \brief Addition de deux objets de classe Vecteur
 *
 * Fonction additionnant deux objets de classe Vecteur.
 *
 * \param v1 Objet de type Vecteur, opérande gauche de l'addition
 * \param v2 Objet de type Vecteur, opérande droite de l'addition
 * \return Le Vecteur créé par addition des objets
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator+(const Vecteur<Dim> &v1, const Vecteur<Dim> &v2) {
    Vecteur<Dim> b(v1);
    b += v2;
    return b;
}


/*!
 * \brief Soustraction de deux objets de classe Vecteur
 *
 * Fonction soustrayant deux objets de classe Vecteur.
 *
 * \param v1 Objet de type Vecteur, opérande gauche de la soustraction
 * \param v2 Objet de type Vecteur, opérande droite de la soustracion
 * \return Le Vecteur créé par soustraction de v1 par v2
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator-(const Vecteur<Dim> &v1, const Vecteur<Dim> &v2) {
    Vecteur<Dim> b(v1);
    b -= v2;
    return b;
}

/*!
 * \brief Multiplication de deux objets de classe Vecteur
 *
 * Fonction multipliant deux objets de classe Vecteur.
 *
 * \param v1 Objet de type Vecteur, opérande gauche de la multiplication
 * \param v2 Objet de type Vecteur, opérande droite de la multiplication
 * \return Le Vecteur créé par multiplication de v1 par v2 terme à terme
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator*(const Vecteur<Dim> &v1, const Vecteur<Dim> &v2) {
    Vecteur<Dim> b(v1);
    b *= v2;
    return b;
}

/*!
 * \brief Division de deux objets de classe Vecteur
 *
 * Fonction divisant deux objets de classe Vecteur.
 *
 * \param v1 Objet de type Vecteur, numérateur de la division
 * \param v2 Objet de type Vecteur, dénominateur de la division
 * \return Le Vecteur créé par division de v1 par v2 terme à terme
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator/(const Vecteur<Dim> &v1, const Vecteur<Dim> &v2) {
    Vecteur<Dim> b(v1);
    b /= v2;
    return b;
}

/*!
 * \brief Moins unaire sur un objet de classe Vecteur
 *
 * Fonction effectuant un moins unaire sur un objet de classe Vecteur.
 *
 * \param v Objet de type Vecteur
 * \return L'opposé de v
 *
 */
template <unsigned int Dim>
inline Vecteur<Dim> operator-(const Vecteur<Dim> &v) {
    Vecteur<Dim> b;
    for (unsigned int i = 1; i <= Dim; i++) {
        b(i) = -v(i);
    }
    return b;
}

/*!
 * \brief Procedure de lecture des entrées d'un Vecteur
 *
 * Procedure affichant toutes les entrées d'un Vecteur
 * Attention, aucune ligne n'est passée entre deux coordonnées ou à la fin de
 * l'affichage des coordonnées
 * 
 * \param O Référence sur un flux sortie
 * \param v Référence sur un objet de type Vecteur
 * \return Un flux sortie comportant les éléments de v
 *
 */
template <unsigned int Dim>
std::ostream & operator<<(std::ostream &O, Vecteur<Dim> const &v);

#include "vecteur.tpp"

#endif
