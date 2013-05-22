#include <GL/glut.h>
#include "noyauLissage.hpp"
#include <cmath>

/* ** Constructeurs ** */

template<unsigned int Dim>
NoyauLissage<Dim>::NoyauLissage(double rayon)
    : h(rayon)
{
}

template<unsigned int Dim>
NoyauLissage<Dim>::~NoyauLissage() {
}

/* ** Methodes ** */

template<unsigned int Dim>
double NoyauLissage<Dim>::getRayon() const {
      return h;
}

template<unsigned int Dim>
double NoyauLissage<Dim>::defaut(const Vecteur<Dim> r, const double h, const int type_noyau) const {
      switch(type_noyau)
      {
      case 0:
      {
	  if (r.norme() > h)
	      return 0;
	  return (315/(64*M_PI*pow(h,9)))*pow(pow(h,2)-pow(r.norme(),2),3);
      }
      case 1:
      {
	  if (r.norme() > h)
	      return 0;
	  return ((15/(M_PI*pow(h,6)))*pow(h-r.norme(),3));
      }
      case 2:
      {
	  if (r.norme() > h)
	      return 0;
	  return ((15/(2*M_PI*pow(h,3)))*(-(pow(r.norme(),3)/(2*pow(h,3)))+(pow(r.norme(),2)/pow(h,2))+(h/(2*r.norme()))-1));
      }
      } 
}

template<unsigned int Dim>
Vecteur<Dim> NoyauLissage<Dim>::gradient(const Vecteur<Dim> r, const double h, const int type_noyau) const {
       switch(type_noyau)
      {
      case 0:
      {
	  double coef = -(945/(32*M_PI*pow(h,9)))*pow((pow(h,2)-pow(r.norme(),2)),2);
	  return coef*r;

      }
      case 1:
      {
	  double coef = (-(45/(M_PI*pow(h,6)))*(1/(r.norme()))*pow((h-r.norme()),2));
	  return coef*r;
      }
      case 2:
      {
	  double coef = (15/(2*M_PI*pow(h,3)))*((-(3*r.norme())/(2*pow(h,3)))+(2/(pow(h,2)))-(h/(2*pow(r.norme(),3))));
	  return coef*r;
      }
      } 
}

template<unsigned int Dim>
double NoyauLissage<Dim>::laplacien(const Vecteur<Dim> r, const double h, const int type_noyau) const {
       switch(type_noyau)
      {
      case 0:
      {
	   double coef = -(945/(32*M_PI*pow(h,9)))*(pow(h,2)-pow(r.norme(),2));
	   return coef*(3*pow(h,2)-7*pow(r.norme(),2));
      }
      case 1:
      {
	  return (-(90/(M_PI*pow(h,6)))*(1/r.norme())*(h-r.norme())*(h-2*r.norme()));
      }
      case 2:
      {
	  return ((45/(M_PI*pow(h,6)))*(h-r.norme()));
      }
      }

}








