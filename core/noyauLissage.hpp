#ifndef _NOYAULISSAGE_HPP_
#define _NOYAULISSAGE_HPP_

#include <iostream>


/** \class NoyauLissage : classe représentant un noyau de lissage
 * Dim : Dimension de l'espace
 */
template<unsigned int Dim>
class NoyauLissage {

  /* ** Attributs ** */
private:
  double h; // Rayon de support du noyau de lissage


  /* ** Constructeurs ** */
public:
  /**
   * Constructeur
   * \param rayon rayon de support
   */
  NoyauLissage(double rayon);

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
   * \param type_noyau le type du noyau (0: par defaut, 1: pression, 
   *        2: viscosité)
   */
  double defaut(const Vecteur<Dim> r, const double h, const int type_noyau) const;

  /**
   *  Implémente la méthode de noyau de lissage avec le gradient
   * \param r position de la particule
   * \param h rayon de support
   * \param type_noyau le type du noyau (0: par defaut, 1: pression, 
   *        2: viscosité)
   */
  Vecteur<Dim> gradient(const Vecteur<Dim> r, const double h, const int type_noyau) const;

  /**
   *  Implémente la méthode de noyau de lissage avec le laplacien
   * \param r position de la particule
   * \param h rayon de support
   * \param type_noyau le type du noyau (0: par defaut, 1: pression, 
   *        2: viscosité)
   */
  double laplacien(const Vecteur<Dim> r, const double h, const int type_noyau) const;
  

};

#include "noyauLissage.tpp"

#endif
