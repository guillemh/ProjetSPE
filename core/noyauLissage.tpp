#include "noyauLissage.hpp"
#include <cmath>

using std::cout;
using std::endl;

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
    this->coefDefaut = 315/(64*M_PI*pow(this->h, 9));
    this->coefGradient = 945/(32*M_PI*pow(this->h, 9));
    this->coefLaplacien = this->coefGradient;
    hCarre = pow(this->h, 2);
}


template<unsigned int Dim>
NoyauLissageDefaut<Dim>::NoyauLissageDefaut(double rayon)
    : NoyauLissage<Dim>(rayon)
{
    this->coefDefaut = 315/(64*M_PI*pow(this->h, 9));
    this->coefGradient = 945/(32*M_PI*pow(this->h, 9));
    this->coefLaplacien = this->coefGradient;
    hCarre = pow(this->h, 2);
}


template<unsigned int Dim>
NoyauLissageDefaut<Dim>::~NoyauLissageDefaut() {
}



/* ** Methodes classe NoyauLissageDefaut ** */

template<unsigned int Dim>
double NoyauLissageDefaut<Dim>::defaut(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    return this->coefDefaut * pow(hCarre - pow(r.norme(), 2), 3);
}


template<unsigned int Dim>
Vecteur<Dim> NoyauLissageDefaut<Dim>::gradient(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return Vecteur<Dim>();
    return (-this->coefGradient * pow((hCarre - pow(r.norme(), 2)), 2) * r);
}


template<unsigned int Dim>
double NoyauLissageDefaut<Dim>::laplacien(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    return (-this->coefLaplacien * (hCarre - pow(r.norme(), 2)) * (3*hCarre - 7*pow(r.norme(), 2)));
}



/* ** Constructeurs classe NoyauLissagePression ** */

template<unsigned int Dim>
NoyauLissagePression<Dim>::NoyauLissagePression()
    : NoyauLissage<Dim>()
{
    this->coefDefaut = 15/(M_PI*pow(this->h, 6));
    this->coefGradient = 3*this->coefDefaut;
    this->coefLaplacien = 2*this->coefGradient;
}

template<unsigned int Dim>
NoyauLissagePression<Dim>::NoyauLissagePression(double rayon)
    : NoyauLissage<Dim>(rayon)
{
    this->coefDefaut = 15/(M_PI*pow(this->h, 6));
    this->coefGradient = 3*this->coefDefaut;
    this->coefLaplacien = 2*this->coefGradient;
}


template<unsigned int Dim>
NoyauLissagePression<Dim>::~NoyauLissagePression() {
}



/* ** Methodes classe NoyauLissagePression ** */

template<unsigned int Dim>
double NoyauLissagePression<Dim>::defaut(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    return (this->coefDefaut * pow(this->h - r.norme(), 3));
}


template<unsigned int Dim>
Vecteur<Dim> NoyauLissagePression<Dim>::gradient(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return Vecteur<Dim>();
    return (-this->coefGradient * (1/(r.norme())) * pow((this->h - r.norme()), 2)) * r;
}


template<unsigned int Dim>
double NoyauLissagePression<Dim>::laplacien(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    return (-this->coefLaplacien * (1/r.norme()) * (this->h - r.norme()) * (this->h - 2*r.norme()));
}



/* ** Constructeurs classe NoyauLissageViscosite ** */

template<unsigned int Dim>
NoyauLissageViscosite<Dim>::NoyauLissageViscosite()
    : NoyauLissage<Dim>()
{
    hCarre = pow(this->h, 2);
    hCube = pow(this->h, 3);
    this->coefDefaut = 15/(2*M_PI*hCube);
    this->coefGradient = this->coefDefaut;
    this->coefLaplacien = 45/(M_PI*pow(this->h, 6));
}


template<unsigned int Dim>
NoyauLissageViscosite<Dim>::NoyauLissageViscosite(double rayon)
    : NoyauLissage<Dim>(rayon)
{
    hCarre = pow(this->h, 2);
    hCube = pow(this->h, 3);
    this->coefDefaut = 15/(2*M_PI*hCube);
    this->coefGradient = this->coefDefaut;
    this->coefLaplacien = 45/(M_PI*pow(this->h, 6));
}


template<unsigned int Dim>
NoyauLissageViscosite<Dim>::~NoyauLissageViscosite() {
}



/* ** Methodes classe NoyauLissageViscosite ** */

template<unsigned int Dim>
double NoyauLissageViscosite<Dim>::defaut(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    return (this->coefDefaut * (-(pow(r.norme(), 3) / (2*hCube)) +
            (pow(r.norme(), 2) / hCarre) + (this->h / (2*r.norme())) - 1));
}


template<unsigned int Dim>
Vecteur<Dim> NoyauLissageViscosite<Dim>::gradient(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return Vecteur<Dim>();
    return (this->coefGradient * ((-(3*r.norme()) / (2*hCube))
           + (2 / (pow(this->h, 2))) - (this->h / (2*pow(r.norme(), 3)))) * r);
}

template<unsigned int Dim>
double NoyauLissageViscosite<Dim>::laplacien(const Vecteur<Dim> r) const {
    if (r.norme() > this->h)
        return 0;
    double res = (this->coefLaplacien * (this->h - r.norme()));
    if (res > 10000000) {
	cout << "!! Valeur de NoyauViscosite.laplacien : " << res << endl;
    }
    return res;
}


/*
 * Noyau de Monaghan
 * Implémentation
 *
 */
template<unsigned int Dim>
NoyauLissageMonaghan<Dim>::NoyauLissageMonaghan ()
    : NoyauLissage<Dim>()
{
    // Attributs inutilisés
    this->coefDefaut = 0;
    this->coefGradient = 0;
    this->coefLaplacien = 0;
}

template<unsigned int Dim>
NoyauLissageMonaghan<Dim>::NoyauLissageMonaghan (double rayon)
    : NoyauLissage<Dim>(rayon)
{
    // Attributs inutilisés
    this->coefDefaut = 0;
    this->coefGradient = 0;
    this->coefLaplacien = 0;
}

template<unsigned int Dim>
NoyauLissageMonaghan<Dim>::~NoyauLissageMonaghan () {
}

template<unsigned int Dim>
double NoyauLissageMonaghan<Dim>::defaut(const Vecteur<Dim> r) const {
    double q = r.norme()/(this->h);
    double res;
    if (q <= 1) {
	res = (pow(2 - q, 3) - 4.0 * pow(1 - q, 3)) / 6.0;
    } else if (q <= 2) {
	res = pow(2 - q, 3) / 6.0;
    } else {
	res = 0;
    }
    return res;
}

template<unsigned int Dim>
Vecteur<Dim> NoyauLissageMonaghan<Dim>::gradient(const Vecteur<Dim> r) const {
    double q = r.norme()/(this->h);
    Vecteur<Dim> res;
    if (q < 0.001) {
	res = Vecteur<Dim>();
    } else if (q <= 1) {
	res = (-3.0 * (r / r.norme()) * pow (2 - q, 2)
	       + 12.0 * (r / r.norme()) * pow (1 - q, 2)) / 6.0;
    } else if (q <= 2) {
	res = (-3.0 * (r / r.norme()) * pow (2 - q, 2));
    } else {
	res = Vecteur<Dim>();
    }
    return res;
}

template<unsigned int Dim>
double NoyauLissageMonaghan<Dim>::laplacien(const Vecteur<Dim> r) const {
    double q = r.norme()/(this->h);
    double res;
    if (q < 0.001) {
	res = 0;
    } else if (q <= 1) {
	res = (-6.0 * (2 - q) * (2 - 2*q) / r.norme()
	       + 24.0 * (1 - q) * (1 - 2*q) / r.norme()) / 6.0;
    } else if (q <= 2) {
	res = (-6.0 * (2 - q) * (2 - 2*q) / r.norme()) / 6.0;
    } else {
	res = 0;
    }
    return res;
}
