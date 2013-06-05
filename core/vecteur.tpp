#include <cstdlib>
#include <cmath>
using std::cout;
using std::endl;

/* ** Constructeurs ** */

template <unsigned int Dim>
Vecteur<Dim>::Vecteur() {
    for (unsigned int i = 0; i < Dim; i++) {
	t[i] = 0.0;
    }
}

template <unsigned int Dim>
Vecteur<Dim>::Vecteur(double def) {
    for (unsigned int i = 0; i < Dim; i++) {
	t[i] = def;
    }
}

template <unsigned int Dim>
Vecteur<Dim>::Vecteur(double x, double y) {
    t[0] = x;
    t[1] = y;
}


template <unsigned int Dim>
Vecteur<Dim>::Vecteur(double x, double y, double z) {
    t[0] = x;
    t[1] = y;
    t[2] = z;
}


template <unsigned int Dim>
Vecteur<Dim>::Vecteur(const Vecteur<Dim> &v) {
    for (unsigned int i = 0; i < Dim; i++) {
        t[i] = v.t[i];
    }
}


template <unsigned int Dim>
Vecteur<Dim>::~Vecteur<Dim>() {
}

// Methodes

template <unsigned int Dim>
std::ostream & operator<<(std::ostream &O, Vecteur<Dim> const &v) {
    for (unsigned int i = 1; i < Dim; i++) {
        O << v(i) << " ";
    }
    O << v(Dim);
    return O;
}
