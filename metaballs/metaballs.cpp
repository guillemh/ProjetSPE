#include "metaballs.hpp"


/* ** Constructeurs ** */

Metaballs::Metaballs() {

}

Metaballs::~Metaballs() {
}


/* ** Methodes ** */

void Metaballs::coloration(const list<Particule<3> *> &particules) {
    typename list<Particule<Dim> *>::iterator it;

    // Pour chaque point, on regarde l'influence des particules du fluide
    // Si elle superieure a rayon, on colorie le point
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < q; k++) {
                Vecteur<3> position = origine + Vecteur<3>(i*cote, j*cote, k*cote);
                
                double influence = 0;
                for (it = particules.begin(); it != particules.end(); it++)
                    influence += (*it)->isosurface(position);
                    
                points[i][j][k] = (influence >= rayon)? true : false;
            }
        }
    }
}


void Metaballs::draw() {

}


void Metaballs::drawCube(Vecteur<Dim> pos, double cote, int config) {

}


void Metaballs::drawTriangle(Vecteur<Dim> pos, double cote, int a, int b, int c) {

}
