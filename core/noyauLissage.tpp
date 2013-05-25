#include "noyauLissage.hpp"
#include <cmath>

/* ** Constructeurs classe mère ** */

template<unsigned int Dim>
NoyauLissage<Dim>::NoyauLissage()
    : h(0)
{
}


template<unsigned int Dim>
NoyauLissage<Dim>::NoyauLissage(double rayon)
    : h(rayon)
{
}


template<unsigned int Dim>
NoyauLissage<Dim>::~NoyauLissage() {
}



/* ** Methodes generales ** */

template<unsigned int Dim>
double NoyauLissage<Dim>::getRayon() const {
    return h;
}



/* ** Constructeurs classe NoyauLissageDefaut ** */

template<unsigned int Dim>
NoyauLissageDefaut<Dim>::NoyauLissageDefaut()
    : NoyauLissage<Dim>()
{
}


template<unsigned int Dim>
NoyauLissageDefaut<Dim>::NoyauLissageDefaut(double rayon)
    : NoyauLissage<Dim>(rayon)
{
}


template<unsigned int Dim>
NoyauLissageDefaut<Dim>::~NoyauLissageDefaut() {
}



/* ** Methodes classe NoyauLissageDefaut ** */

template<unsigned int Dim>
double NoyauLissageDefaut<Dim>::defaut(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    return (315/(64*M_PI*pow(this->h, 9))) * pow(pow(this->h, 2)-pow(r.norme(), 2), 3);
}


template<unsigned int Dim>
Vecteur<Dim> NoyauLissageDefaut<Dim>::gradient(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return Vecteur<Dim>();
    double coef = -(945/(32*M_PI*pow(this->h, 9))) * pow((pow(this->h, 2)-pow(r.norme(), 2)), 2);
    return coef*r;
}


template<unsigned int Dim>
double NoyauLissageDefaut<Dim>::laplacien(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    double coef = -(945/(32*M_PI*pow(this->h, 9))) * (pow(this->h, 2)-pow(r.norme(), 2));
    return coef * (3*pow(this->h, 2) - 7*pow(r.norme(), 2));
}



/* ** Constructeurs classe NoyauLissagePression ** */

template<unsigned int Dim>
NoyauLissagePression<Dim>::NoyauLissagePression()
    : NoyauLissage<Dim>()
{
}


template<unsigned int Dim>
NoyauLissagePression<Dim>::NoyauLissagePression(double rayon)
    : NoyauLissage<Dim>(rayon)
{
}


template<unsigned int Dim>
NoyauLissagePression<Dim>::~NoyauLissagePression() {
}



/* ** Methodes classe NoyauLissagePression ** */

template<unsigned int Dim>
double NoyauLissagePression<Dim>::defaut(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    return ((15/(M_PI*pow(this->h, 6))) * pow(this->h-r.norme(), 3));
}


template<unsigned int Dim>
Vecteur<Dim> NoyauLissagePression<Dim>::gradient(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return Vecteur<Dim>();
    double coef = (-(45/(M_PI*pow(this->h, 6))) * (1/(r.norme())) * pow((this->h-r.norme()), 2));
    return coef*r;
}


template<unsigned int Dim>
double NoyauLissagePression<Dim>::laplacien(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    return (-(90/(M_PI*pow(this->h, 6))) * (1/r.norme()) * (this->h-r.norme()) * (this->h-2*r.norme()));
}



/* ** Constructeurs classe NoyauLissageViscosite ** */

template<unsigned int Dim>
NoyauLissageViscosite<Dim>::NoyauLissageViscosite()
    : NoyauLissage<Dim>()
{
}


template<unsigned int Dim>
NoyauLissageViscosite<Dim>::NoyauLissageViscosite(double rayon)
    : NoyauLissage<Dim>(rayon)
{
}


template<unsigned int Dim>
NoyauLissageViscosite<Dim>::~NoyauLissageViscosite() {
}



/* ** Methodes classe NoyauLissageViscosite ** */

template<unsigned int Dim>
double NoyauLissageViscosite<Dim>::defaut(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    return ((15/(2*M_PI*pow(this->h, 3))) * (-(pow(r.norme(), 3)/(2*pow(this->h, 3))) +
            (pow(r.norme(), 2)/pow(this->h, 2)) + (this->h/(2*r.norme())) - 1));
}


template<unsigned int Dim>
Vecteur<Dim> NoyauLissageViscosite<Dim>::gradient(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return Vecteur<Dim>();
    double coef = (15/(2*M_PI*pow(this->h, 3))) * ((-(3*r.norme())/(2*pow(this->h, 3)))
                  + (2/(pow(this->h, 2))) - (this->h/(2*pow(r.norme(), 3))));
    return coef*r;
}


template<unsigned int Dim>
double NoyauLissageViscosite<Dim>::laplacien(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    return ((45/(M_PI*pow(this->h, 6))) * (this->h-r.norme()));
}


