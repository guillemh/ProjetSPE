#ifndef _PREMIER_HPP_
#define _PREMIER_HPP_

#include "particule.hpp"

/** 
 * \class Premier
 * @brief Classe contenant une lookup table des nombres premiers 
 */
template <unsigned int Dim>
class Premier {

public:
    /**
     * Constructeur
     */
    Premier(); 
    
    /**
     * Destructeur
     */
    ~Premier();

   
    /* ** Methodes ** */
public:
    /**
     * \return le nombre premier supérieur ou égal à x
     */
    int getPremier(int x) const;

private:
    /**
     * \return vrai si le nombre passé en paramètre est premier
     */
    bool estPremier(const int x) const;
    
};

#include "premier.tpp"

#endif
