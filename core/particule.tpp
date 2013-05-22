#include <GL/glut.h>
#include "particule.hpp"


/* ** Constructeurs ** */

template<unsigned int Dim>
Particule<Dim>::Particule(Vecteur<Dim> pos, Vecteur<Dim> vit, double rho, double p)
    : position(pos),
    vitesse(vit),
    masse_volumique(rho),
    pression(p)
{
}


template<unsigned int Dim>
Particule<Dim>::~Particule() {
}



/* ** Methodes ** */

template<unsigned int Dim>
const Vecteur<Dim> & Particule<Dim>::getPosition() const {
    return position;
}


template<unsigned int Dim>
const Vecteur<Dim> & Particule<Dim>::getVitesse() const {
    return vitesse;
}


template<unsigned int Dim>
double Particule<Dim>::getMasseVolumique() const {
    return masse_volumique;
}


template<unsigned int Dim>
double Particule<Dim>::getPression() const {
    return pression;
}


template<unsigned int Dim>
void Particule<Dim>::setPosition(const Vecteur<Dim> &pos) {
    position = pos;
}


template<unsigned int Dim>
void Particule<Dim>::setVitesse(const Vecteur<Dim> &vit) {    
    vitesse = vit;
}


template<unsigned int Dim>
void Particule<Dim>::setMasseVolumique(double rho) {
    masse_volumique = rho;
}


template<unsigned int Dim>
void Particule<Dim>::setPression(double p) {    
    pression = p;
}


template<unsigned int Dim>
void Particule<Dim>::incrPosition(const Vecteur<Dim> &pos) {
    position += pos;
}


template<unsigned int Dim>
void Particule<Dim>::incrVitesse(const Vecteur<Dim> &vit) {
    vitesse += vit;
}


/*
template<unsigned int Dim>
void Particule<Dim>::draw() const {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glutSolidSphere(radius, 12, 12);
    glPopMatrix();

}
*/


template<unsigned int Dim>
std::ostream& operator<<(std::ostream& os, const Particule<Dim>& p) {
    os << "pos (" << p.getPosition() << "), vit (" << p.getVitesse() << ")" << std::endl
       << "m_v (" << p.getMasseVolumique() << "), pre (" << p.getPression() << ")";
    return os;
}

