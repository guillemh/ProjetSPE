#include <cstdlib>
#include <cmath>
using std::cout;
using std::endl;

/* ** Constructeurs ** */

template <unsigned int Dim>
Vecteur<Dim>::Vecteur () {
    cout << "Appel constructeur par défaut" << endl ;
	t = new double [Dim] ;
	for (int i = 0 ; i < Dim ; i++) {
		t[i] = 0.0 ;
	}
}

template <unsigned int Dim>
Vecteur<Dim>::Vecteur(double x, double y) {
    if (Dim != 2) {
        cout << "Vecteur<Dim>::Vecteur<Dim>(double x, double y) :" << endl; 
        cout << "Erreur : Construction d'un vecteur non bidimensionnel avec spécification de 2 coordonnées" << endl;
        exit(-1);
    } else {
        t = new double[Dim];
        t[0] = x;
        t[1] = y;
    }
}


template <unsigned int Dim>
Vecteur<Dim>::Vecteur(double x, double y, double z) {
    if (Dim != 3) {
        cout << "Vecteur<Dim>::Vecteur<Dim>(double x, double y, double z) :" << endl; 
        cout << "Erreur : Construction d'un vecteur non tridimensionnel avec spécification de 3 coordonnées" << endl;
        exit(-1);
    } else {
        t = new double[Dim];
        t[0] = x;
        t[1] = y;
        t[2] = z;
    }
}


template <unsigned int Dim>
Vecteur<Dim>::Vecteur(const Vecteur<Dim> &v) {
    t = new double[Dim];
    for (unsigned int i = 0; i < Dim; i++) {
        t[i] = v.t[i];
    }
}


template <unsigned int Dim>
Vecteur<Dim>::~Vecteur<Dim>() {      
    delete [] t;
}



/* ** Methodes ** */

template <unsigned int Dim>
double  Vecteur<Dim>::norme() const {
    double somme = 0;
    for (unsigned int i = 1; i <= Dim; i++) {
        somme += pow((*this)(i),2);
    }
    return sqrt(somme);
}


template <unsigned int Dim>
double & Vecteur<Dim>::operator()(unsigned int i) {
	if (t != NULL) {
	    if (1 <= i && i <= Dim) {
	        return t[i - 1];
	    } else {
	        cout << "double & Vecteur<Dim>::operator()(unsigned int i) :" << endl;
	        cout << "Erreur : i n'est pas dans l'intervalle attendu" << endl;
	        exit(-1);
	    }
	}
}


template <unsigned int Dim>
double Vecteur<Dim>::operator()(unsigned int i) const {
	if (t != NULL) {
   		if (1 <= i && i <= Dim) {
    	    return t[i - 1];
    	} else {
    	    cout << "double Vecteur<Dim>::operator()(unsigned int i) const :" << endl;
    	    cout << "Erreur : i n'est pas dans l'intervalle attendu" << endl;
    	    exit(-1);
    	}
	}
}


template <unsigned int Dim>
Vecteur<Dim> & Vecteur<Dim>::operator+=(const double &valeur) {
    Vecteur<Dim> &a = *this;
    for (unsigned int i = 1; i <= Dim; i++) {
        a(i) += valeur;
    }
    return a;
}


template <unsigned int Dim>
Vecteur<Dim> & Vecteur<Dim>::operator-=(const double &valeur) {
    Vecteur<Dim> &a = *this;
    for (unsigned int i = 1; i <= Dim; i++) {
        a(i) -= valeur;
    }
    return a;
}


template <unsigned int Dim>
Vecteur<Dim> & Vecteur<Dim>::operator*=(const double &valeur) {
    Vecteur<Dim> &a = *this;
    for (unsigned int i = 1; i <= Dim; i++) {
        a(i) *= valeur;
    }
    return a;
}


template <unsigned int Dim>
Vecteur<Dim> & Vecteur<Dim>::operator/=(const double &valeur) {
    if (valeur == 0.0) {
    Vecteur<Dim> &a = *this;
    for (unsigned int i = 1; i <= Dim; i++) {
        a(i) /= valeur;
    }
    return a;
    } else {
        cout << "Vecteur<Dim> & Vecteur<Dim>::operator/=(const double &valeur) :" << endl;
        cout << "Erreur : division par zéro" << endl;
        exit(-1);
    }
}


template <unsigned int Dim>
Vecteur<Dim> & Vecteur<Dim>::operator+=(const Vecteur<Dim> &v) {
    Vecteur<Dim> &a = *this;
    for (unsigned int i = 1; i <= Dim; i++) {
        a(i) += v(i);
    }
    return a;
}


template <unsigned int Dim>
Vecteur<Dim> & Vecteur<Dim>::operator-=(const Vecteur<Dim> &v) {
    Vecteur<Dim> &a = *this;
    for (unsigned int i = 1; i <= Dim; i++) {
        a(i) -= v(i);
    }
    return a;
}


template <unsigned int Dim>
Vecteur<Dim> & Vecteur<Dim>::operator*=(const Vecteur<Dim> &v) {
    Vecteur<Dim> &a = *this;
    for (unsigned int i = 1; i <= Dim; i++) {
        a(i) *= v(i);
    }
    return a;
}


template <unsigned int Dim>
Vecteur<Dim> & Vecteur<Dim>::operator/=(const Vecteur<Dim> &v) {
    Vecteur <Dim> &a = *this;
    for (unsigned int i = 1; i <= Dim; i++) {
        if (v(i) != 0.0) {
            a(i) /= v(i);
        } else {
            cout << "Vecteur<Dim> & operator/=(const Vecteur<Dim> &v) :" << endl;
            cout << "Erreur : division par zéro" << endl;
            exit(-1);
        }
    }
    return a;
}


template <unsigned int Dim>
Vecteur<Dim> & Vecteur<Dim>::operator=(const Vecteur<Dim> &v) {
    if (t != NULL) {
        delete [] t;
    }
    t = new double[Dim];
    for (unsigned int i = 1; i <= Dim; i++) {
        (*this)(i) = v(i);
    }
    return(*this);
}

template <unsigned int Dim>
bool Vecteur<Dim>::operator==(Vecteur<Dim> &v) {
    for (unsigned int i = 1; i <= Dim; i++) {
        if ((*this)(i) != v(i)) {
            return false;
        }
    }
    return true;
}


template <unsigned int Dim>
Vecteur<Dim> operator+(double r, const Vecteur<Dim> &v) {
    Vecteur<Dim> a(v);
    a += r;
    return a;
}


template <unsigned int Dim>
Vecteur<Dim> operator+(const Vecteur<Dim> &v, double r) {
    return(r + v);
}


template <unsigned int Dim>
Vecteur<Dim> operator-(double r, const Vecteur<Dim> &v) {
    Vecteur <Dim> a(v);
    a -= r;
    return a;
}


template <unsigned int Dim>
Vecteur<Dim> operator-(const Vecteur<Dim> &v, double r) {
    return(r - v);
}


template <unsigned int Dim>
Vecteur<Dim> operator*(double r, const Vecteur<Dim> &v) {
    Vecteur <Dim> a(v);
    a *= r;
    return a;
}


template <unsigned int Dim>
Vecteur<Dim> operator*(const Vecteur<Dim> &v, double r) {
    return(r * v);
}


template <unsigned int Dim>
Vecteur<Dim> operator/(const Vecteur<Dim> &v, double r) {
    if (r != 0.0) {
        Vecteur<Dim> a = Vecteur<Dim>(v);
        a /= r;
        return a;
    } else {
        cout << "Vecteur<Dim> operator/(const Vecteur<Dim> &v, double r) :" << endl;
        cout << "Erreur : division par zero" << endl;
        exit(-1);
    }
}


template <unsigned int Dim>
Vecteur<Dim> operator/(double r, const Vecteur<Dim> &v) {
    Vecteur<Dim> b ;
    for (unsigned int i = 1; i <= Dim; i++) {
        b(i) = r;
    }
    return(b / v);
}


template <unsigned int Dim>
Vecteur<Dim> operator+(const Vecteur<Dim> &v1, const Vecteur<Dim> &v2) {
    Vecteur<Dim> b(v1);
    b += v2;
    return b;
}


template <unsigned int Dim>
Vecteur<Dim> operator-(const Vecteur<Dim> &v1, const Vecteur<Dim> &v2) {
    Vecteur<Dim> b(v1);
    b -= v2;
    return b;
}


template <unsigned int Dim>
Vecteur<Dim> operator*(const Vecteur<Dim> &v1, const Vecteur<Dim> &v2) {
    Vecteur<Dim> b(v1);
    b *= v2;
    return b;
}


template <unsigned int Dim>
Vecteur<Dim> operator/(const Vecteur<Dim> &v1, const Vecteur<Dim> &v2) {
    Vecteur<Dim> b(v1);
    b /= v2;
    return b;
}


template <unsigned int Dim>
Vecteur<Dim> operator-(const Vecteur<Dim> &v) {
    Vecteur<Dim> b(v);
    Vecteur<Dim> a ;
    a -= b;
    return a;
}


template <unsigned int Dim>
std::ostream & operator<<(std::ostream &O, Vecteur<Dim> const &v) {
    for (unsigned int i = 1; i <= Dim; i++) {
        O << v(i) << " ";
    }
    return O;
}

