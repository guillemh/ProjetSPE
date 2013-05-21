#include <GL/glut.h>
#include "particule.hpp"


/* ** Constructeurs ** */

Particule::Particule(Vecteur<Dim> pos, Vecteur<Dim> vit, double rho, double p)
    : mat(ma),
    position(pos),
    masse_volumique(rho),
    pression(p)
{
}



/* ** Methodes ** */

Particule::~Particule()
{
}


const Vecteur<Dim> & Particule::getPosition() const
{
    return position;
}


const Vecteur<Dim> & Particule::getVitesse() const
{
    return vitesse;
}


double Particule::getMasseVolumique() const
{
    return masse_volumique;
}


double Particule::getPression() const
{
    return pression;
}


void Particule::setPosition(const Vecteur<Dim> &pos)
{
    position = pos;
}


void Particule::setVelocity(const Vecteur<Dim> &vit)
{    
    velocity = vit;
}


void Particule::setMasseVolumique(double rho)
{
    masse_volumique = rho;
}


void Particule::setPression(double p)
{    
    pression = p;
}


void Particule::incrPosition(const Vecteur<Dim> &pos)
{
    position += pos;
}


void Particule::incrVelocity(const Vecteur<Dim> &vit)
{
    vitesse += vit;
}


/*
void Particule::draw() const
{
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glutSolidSphere(radius, 12, 12);
    glPopMatrix();

}
*/


std::ostream& operator<<(std::ostream& os, const Particule& p)
{
    os << "pos (" << p.getPosition() << "), vit (" << p.getVitesse() << ")" << std::endl
       << "m_v (" << p.getMasseVolumique() << "), pre (" << p.getPression() << ")" << std::endl;
    return os;
}
