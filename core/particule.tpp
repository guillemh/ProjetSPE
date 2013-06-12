#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "particule.hpp"

#define PI 3.1415926535
#define COLORATION 0 // Mettre a 1 pour obtenir une coloration des particules en fonction de leur activité

using std::endl;
using std::ostream;

/* ** Constructeurs ** */

template<unsigned int Dim>
Particule<Dim>::Particule(unsigned int ind, Vecteur<Dim> pos, Vecteur<Dim> vit, double rho, double p, double m, int a)
    : indice(ind),
      position(pos),
      positionPrec(pos),
      vitesse(vit),
      vitessePrec(vit),
      masse_volumique(rho),
      masse_volumique_prec(rho),
      pression(p),
      pressionPrec(p),
      masse(m),
      active(a)
{
}

template<unsigned int Dim>
Particule<Dim>::~Particule() {
}

/* ** Methodes ** */

template<unsigned int Dim>
unsigned int Particule<Dim>::getIndice() const {
    return indice;
}

template<unsigned int Dim>
const Vecteur<Dim> & Particule<Dim>::getPosition() const {
    return position;
}

template<unsigned int Dim>
const Vecteur<Dim> & Particule<Dim>::getPositionPrec() const {
    return positionPrec;
}


template<unsigned int Dim>
const Vecteur<Dim> & Particule<Dim>::getVitesse() const {
    return vitesse;
}

template<unsigned int Dim>
const Vecteur<Dim> & Particule<Dim>::getVitessePrec() const {
    return vitessePrec;
}


template<unsigned int Dim>
const Vecteur<Dim> & Particule<Dim>::getAcceleration() const {
    return acceleration;
}

template<unsigned int Dim>
const Vecteur<Dim> & Particule<Dim>::getForces() const {
    return forces;
}


template<unsigned int Dim>
double Particule<Dim>::getMasse() const {
    return masse;
}

template<unsigned int Dim>
double Particule<Dim>::getMasseVolumique() const {
    return masse_volumique;
}

template<unsigned int Dim>
double Particule<Dim>::getMasseVolumiquePrec() const {
    return masse_volumique_prec;
}


template<unsigned int Dim>
double Particule<Dim>::getPression() const {
    return pression;
}

template<unsigned int Dim>
double Particule<Dim>::getPressionPrec() const {
    return pressionPrec;
}

template<unsigned int Dim>
int Particule<Dim>::getActive() const {
    return active;
}


template<unsigned int Dim>
void Particule<Dim>::setPosition(const Vecteur<Dim> &pos) {
    position = pos;
}

template<unsigned int Dim>
void Particule<Dim>::setPositionPrec(const Vecteur<Dim> &pos) {
    positionPrec = pos;
}


template<unsigned int Dim>
void Particule<Dim>::setVitesse(const Vecteur<Dim> &vit) {    
    vitesse = vit;
}

template<unsigned int Dim>
void Particule<Dim>::setVitessePrec(const Vecteur<Dim> &vit) {    
    vitessePrec = vit;
}


template<unsigned int Dim>
void Particule<Dim>::setAcceleration(const Vecteur<Dim> &acc) {    
    acceleration = acc;
}


template<unsigned int Dim>
void Particule<Dim>::setMasseVolumique(double rho) {
    masse_volumique = rho;
}

template<unsigned int Dim>
void Particule<Dim>::setMasseVolumiquePrec(double rho) {
    masse_volumique_prec = rho;
}


template<unsigned int Dim>
void Particule<Dim>::setPression(double p) {    
    pression = p;
}

template<unsigned int Dim>
void Particule<Dim>::setPressionPrec(double p) {    
    pressionPrec = p;
}

template<unsigned int Dim>
void Particule<Dim>::incrPosition(const Vecteur<Dim> &pos) {
    position += pos;
}


template<unsigned int Dim>
void Particule<Dim>::incrVitesse(const Vecteur<Dim> &vit) {
    vitesse += vit;
}

template<unsigned int Dim>
void Particule<Dim>::incrForces(const Vecteur<Dim> &f) {
    forces += f;
}


template<unsigned int Dim>
void Particule<Dim>::decrForces(const Vecteur<Dim> &f) {
    forces -= f;
}

template<unsigned int Dim>
void Particule<Dim>::setActive(const int &b) {
    active = b;
}


template<unsigned int Dim>
void Particule<Dim>::majPression (double dens) {
    //void Particule<Dim>::majPression (double son, double dens) {
    /*
     * Calcul de la pression appliquée à une particule selon l'équation de Tait
     * (cf. Becker-Teschner, "Weakly compressible SPH for free surface flows")
     */
     
    double gamma = 7.0;
    double B = 100;
    pression = B * (pow(masse_volumique / dens, gamma) - 1);
    
    //    double B = dens * pow(son, 2.0) / gamma;
    //    pression = B * (pow(masse_volumique / dens, gamma));
    //    cout << "B = " << B << ", rho = " << masse_volumique << ", rho_0 = " << dens << ", rho/rho_0 = " << masse_volumique/dens << ", on obtient P = " << pression << endl;
}


template<unsigned int Dim>
double Particule<Dim>::isosurface(Vecteur<Dim> &pos, bool prec) {
    //    double d = (pos - position).norme();
    //    if (d <= 1/3)
    //        return 1 - 3*d*d;
    //    if (d <= 1)
    //        return 3*(1-d)*(1-d)/2;
    //    else
    //        return 0;

    Vecteur<Dim> diff = (prec) ? pos - positionPrec : pos - position;
    double r = diff.scalaire(diff);
    // if (r == 0.0)
    //     return 50000;
    // return 1 / (2*r);

    return pow(0.1, 10000*r*r);
    // return exp(-r*r/0.0003910);
}


template<unsigned int Dim>
void Particule<Dim>::draw(Materiau<Dim> *mat) const {
    // glPushMatrix();
    // glTranslatef(position(1), position(2), position(3));
    /* Calcul du rayon de la sphère :
     * r = racine cubique (3 * m / (4 * PI * rho)) 
     *     avec m masse de la particule
     *     et rho masse volumique du fluide
     * On a p * V = k constante de raideur du fluide, avec p pression
     * Or V = m / rho, donc m = rho * V = rho * k / p
     * ce qui simplifie le calcul
     */
    double rayon = pow((3 * mat->getRigiditeGaz())/(4 * PI * mat->getPression()), 1.0/3.0);

    glutSolidSphere(rayon, 12, 12);
    glVertex3f(position(1), position(2), position(3));
    // glPopMatrix();
}


template<unsigned int Dim>
void Particule<Dim>::draw(bool point) const {

    if (!COLORATION) {
       glColor3f(0.0, 1.0, 0.0);
    } else {
      if (active == 1) {
      	  glColor3f(1.0,0.0,0.0);       
      } else if (active == 2) {     
      	  glColor3f(0.0,0.0,1.0);    
      } else if (active == 3) {
	glColor3f(0.0, 1.0, 0.0);
      }
    }
    
    if (point) {
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        glVertex3f(position(1), position(2), position(3));
        glEnd();
    } else {
        glPushMatrix();
        glTranslatef(position(1), position(2), position(3));
        glutSolidSphere(0.025, 8, 8);
        glPopMatrix();
    }
}


template<unsigned int Dim>
ostream& operator<<(ostream& os, const Particule<Dim>& p) {
    os << "pos : " << p.getPosition() << endl
       << "    vit : " << p.getVitesse() <<  endl
       << "    m_v : " << p.getMasseVolumique() << endl
       << "    pre : " << p.getPression();
    return os;
}

