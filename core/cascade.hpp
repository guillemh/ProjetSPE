#ifndef _CASCADE_HPP_
#define _CASCADE_HPP_

#include "fluide.hpp"

template<unsigned int Dim>
class Cascade {

    /* ** Attributs ** */
private :
    Fluide<Dim> *f;
    double bassin_x;
    double bassin_y;
    double bassin_z;
    double obstacle_x;
    double obstacle_y;
    double obstacle_z;
    double pente_angle;
    double pente_x;
    double pente_y;
    double pente_z;

public :
    
    Cascade(Fluide<Dim> *_f);

    Cascade(Fluide<Dim> *_f, double _bassin_x, double _bassin_y, double _bassin_z,
	    double _obstacle_x, double _obstacle_y, double _obstacle_z, 
	    double _pente_angle, double _pente_x, double _pente_y, double _pente_z);

    ~Cascade();

    void draw();

    void animate();
};

#include "cascade.tpp"

#endif
