#ifndef _MATRICE_
#define _MATRICE_

#include <iostream>
#include "../core/vecteur.hpp"

/**
 * @class MatriceForces
 * @brief Matrice de vecteurs
 *
 * Matrice contenant les valeurs des forces d'interaction entre les particules d'un fluide <br/>
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class MatriceForces {

    /* Données */
    Vecteur<Dim>* data;
    /* Taille du tableau des forces */
    unsigned int taille;
    /* Nombre de particules */
    unsigned int nbr;
    
public:
    /**
     * @brief Constructeur
     *
     * Constructeur par défaut : aucun vecteur
     */
    MatriceForces();

    /**
     * @brief Constructeur
     *
     * Constructeur de vecteurs vides, prenant en argument
     * un nombre de particules
     * @param N Nombre de particules du fluide
     */
    MatriceForces(unsigned int N);

    /**
     * @brief Destructeur
     *
     * Destructeur
     */
    ~MatriceForces();

    /**
     * @brief Accès en écriture
     *
     * @return Dernière force d'interaction calculée entre la particule
     * d'indice i et celle d'indice j <br/>
     * Attention : ne tient pas compte de l'ordre demandé; il faut tester manuellement
     * pour connaître le bon signe à appliquer
     * @param i Numéro de la première particule
     * @param j Numéro de la seconde particule
     */
    Vecteur<Dim>& operator() (unsigned int i, unsigned int j);

    /**
     * @brief Accès en lecture
     *
     * @return Dernière force d'interaction calculée entre la particule
     * d'indice i et celle d'indice j. <br/>
     * Attention : ne tient pas compte de l'ordre demandé; il faut tester manuellement
     * pour connaître le bon signe à appliquer
     * @param i Numéro de la première particule
     * @param j Numéro de la seconde particule
     */
    Vecteur<Dim>& operator() (unsigned int i, unsigned int j) const;

    /**
     * @brief Opérateur d'affectation
     *
     * @param mF Matrice recopiée dans la matrice appelante
     * @return Matrice appelante, égale à celle en argument
     */
    MatriceForces<Dim>& operator = (const MatriceForces<Dim> &mF);

    /**
     * @brief Affichage
     *
     * Affiche les éléments de la matrice
     */
    void afficher();
    
};

#include "matriceForces.tpp"

#endif
