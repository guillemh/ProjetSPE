#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

template <unsigned int Dim>
MatriceForces<Dim>::MatriceForces() {
    taille = 0;
    data = NULL;
    nbr = 0;
}

template <unsigned int Dim>
MatriceForces<Dim>::MatriceForces(unsigned int N) {
    taille = (N-1)*N/2;
    data = new Vecteur<Dim>[taille];
    for (unsigned int i = 0; i < taille; ++i) {
        data[i] = Vecteur<Dim>();
    }
    nbr = N;
}

template <unsigned int Dim>
MatriceForces<Dim>::~MatriceForces() {
    delete [] data;
}

template <unsigned int Dim>
Vecteur<Dim>& MatriceForces<Dim>::operator () (unsigned int i, unsigned int j) {
    unsigned int indice;
    if (i < j) {
        indice = (i-1)*(nbr-1) - (i-2)*(i-1)/2 + (j - i - 1);
    } else {
        indice = (j-1)*(nbr-1) - (j-2)*(j-1)/2 + (i - j - 1);
    }
    return data[indice];
}

template <unsigned int Dim>
Vecteur<Dim>& MatriceForces<Dim>::operator () (unsigned int i, unsigned int j) const {
    unsigned int indice;
    if (i < j) {
        indice = (i-1)*(nbr-1) - (i-2)*(i-1)/2 + (j - i - 1);
    } else {
        indice = (j-1)*(nbr-1) - (j-2)*(j-1)/2 + (i - j - 1);
    }
    return data[indice];
}

template <unsigned int Dim>
MatriceForces<Dim>& MatriceForces<Dim>::operator = (const MatriceForces<Dim> &mF) {
    taille = mF.taille;
    nbr = mF.nbr;
    if (data != NULL) {
        delete [] data;
    }
    data = new Vecteur<Dim>[taille];
    memcpy(data, &(mF(1,2)), taille * sizeof(Vecteur<Dim>));
    return *this;
}

template <unsigned int Dim>
void MatriceForces<Dim>::afficher() {
    cout << "Matrice des forces d'interaction :" << endl;
    for (unsigned int i = 0; i < taille; ++i) {
        cout << "  " << i+1 << " " << data[i] << endl;
    }
}
