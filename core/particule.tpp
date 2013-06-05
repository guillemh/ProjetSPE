#include <GL/glut.h>
#include "particule.hpp"
#include "materiau.hpp"

#define PI 3.1415926535

/* ** Constructeurs ** */

template<unsigned int Dim>
Particule<Dim>::Particule(unsigned int ind, Vecteur<Dim> pos, Vecteur<Dim> vit, double rho, double p, double m)
    : indice(ind),
      position(pos),
      positionPrec(pos),
      vitesse(vit),
      vitessePrec(vit),
      masse_volumique(rho),
      pression(p),
      masse(m)
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
double Particule<Dim>::getPression() const {
    return pression;
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

template<unsigned int Dim>
void Particule<Dim>::incrForces(const Vecteur<Dim> &f) {
    forces += f;
}


template<unsigned int Dim>
void Particule<Dim>::decrForces(const Vecteur<Dim> &f) {
    forces -= f;
}


template<unsigned int Dim>
void Particule<Dim>::majPression (double son, double dens) {
    /* Calcul de la pression appliquée à une particule selon l'équation de Tait
     * (cf. Becker-Teschner, "Weakly compressible SPH for free surface flows")
     */
    double gamma = 7.0;
//    double B = dens * pow(son, 2.0) / gamma;
    double B = 100;
//    pression = B * (pow(masse_volumique / dens, gamma));
    pression = B * (pow(masse_volumique / dens, gamma) - 1);
//    cout << "B = " << B << ", rho = " << masse_volumique << ", rho_0 = " << dens << ", rho/rho_0 = " << masse_volumique/dens << ", on obtient P = " << pression << endl;
}


template<unsigned int Dim>
double Particule<Dim>::isosurface(Vecteur<Dim> &pos) {
    Vecteur<Dim> diff = pos-position;
    return diff.scalaire(diff);
}


template<unsigned int Dim>
void Particule<Dim>::draw(Materiau<Dim> *mat) const {
//    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
//    glTranslatef(position(1), position(2), position(3));
    /* Calcul du rayon de la sphère :
     * r = racine cubique (3 * m / (4 * PI * rho)) 
     *     avec m masse de la particule
     *     et rho masse volumique du fluide
     * On a p * V = k constante de raideur du fluide, avec p pression
     * Or V = m / rho, donc m = rho * V = rho * k / p
     * ce qui simplifie le calcul
     */
//    double rayon = pow((3 * mat->getRigiditeGaz())/(4 * PI * mat->getPression()), 1.0/3.0);
//    glutSolidSphere(rayon, 12, 12);
    glVertex3f(position(1), position(2), position(3));
    glEnd();
//    glPopMatrix();
}


template<unsigned int Dim>
std::ostream& operator<<(std::ostream& os, const Particule<Dim>& p) {
    os << "pos (" << p.getPosition() << "), vit (" << p.getVitesse() << ")" << std::endl
       << "m (" << p.getMasse() << "), m_v (" << p.getMasseVolumique() << "), pre (" << p.getPression() << ")";
    return os;
}

