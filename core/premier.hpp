#ifndef _PREMIER_HPP_
#define _PREMIER_HPP_

#include "particule.hpp"

/** 
 * \class Premier
 * @brief Classe contenant les méthodes relatives au calcul
 * du plus petit nombre premier supérieur
 */
template <unsigned int Dim>
class Premier {

public:
    /**
     * @brief Constructeur
     *
     * Constructeur
     */
    Premier(); 
    
    /**
     * @brief Destructeur
     *
     * Destructeur
     */
    ~Premier();

   
    /* ** Méthodes ** */
public:
    /**
     * @brief Accesseur
     * @param x Nombre entier
     * @return Le nombre premier supérieur ou égal à x
     */
    int getPremier(int x) const;

private:
    /* Retourne vrai ssi le nombre passé en paramètre est premier */
    bool estPremier(const int x) const;
    
};

#include "premier.tpp"

#endif
