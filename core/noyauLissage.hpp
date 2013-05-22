#ifndef _NOYAULISSAGE_HPP_
#define _NOYAULISSAGE_HPP_

#include <iostream>

/**
 * @enum TypeNoyau permettant de définir des types de noyau de lissage
 */
enum TypeNoyau {
  DEFAUT,
  PRESSION,
  VISCOSITE
};


/** \class NoyauLissage : classe représentant un noyau de lissage
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class NoyauLissage {

  /* ** Attributs ** */
private:
  double h; // Rayon de support du noyau de lissage
  TypeNoyau type;

  /* ** Constructeurs ** */
public:
  /**
   * Constructeur
   * \param rayon rayon de support
   */
  NoyauLissage(double rayon, TypeNoyau t);

  /**
   * Destructeur
   */
  ~NoyauLissage();


  /* ** Methodes ** */
public:
  /**
   * \return le rayon du noyau de lissage
   */
    double getRayon() const;

  /**
   *  Implémente la méthode par défaut de noyau de lissage
   * \param r position de la particule
   * \param h rayon de support
   */
  double defaut(const Vecteur<Dim> r) const;

  /**
   *  Implémente la méthode de noyau de lissage avec le gradient
   * \param r position de la particule
   */
  Vecteur<Dim> gradient(const Vecteur<Dim> r) const;

  /**
   *  Implémente la méthode de noyau de lissage avec le laplacien
   * \param r position de la particule
   */
  double laplacien(const Vecteur<Dim> r) const;
  

};

#include "noyauLissage.tpp"

#endif
