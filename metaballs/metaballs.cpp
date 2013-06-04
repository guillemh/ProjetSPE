#include "metaballs.hpp"

/* ** Constructeurs ** */

Metaballs::Metaballs(Vecteur<3> _origine, double _cote, double _rayon) {
    n = 20;
    p = 20;
    q = 10;
    points = new bool** [n];
    for (int i = 0 ; i < n ; i++) {
	points [i] = new bool* [p];
	for (int j = 0 ; j < p ; j++) {
	    points [i][j] = new bool [q];
	}
    }
    origine = _origine;
    cote = _cote;
    rayon = _rayon;
    /* Look-up table */
    // ...
    
}

Metaballs::~Metaballs() {
    for (int i = 0 ; i < n ; i++) {
	for (int j = 0 ; j < p ; j++) {
	    delete points [i][j][];
	}
	delete points [i][];
    }
    delete points [];
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

void Metaballs::drawCube(Vecteur<3> pos, double cote, int config) {
    int listeAretes [12] = configurations[config];
    int i = 0;
    while (i < 4 && listeAretes[3 * i] != -1) {
	drawTriangle(pos, cote, listeAretes[3*i], listeAretes[3*i + 1], listeAretes[3*i + 2]);
	i++;
    }
}

void Metaballs::drawTriangle(Vecteur<3> pos, double cote, int a, int b, int c) {
    double[3] ptA = associerPoint (pos, cote, a);
    double[3] ptB = associerPoint (pos, cote, b);
    double[3] ptC = associerPoint (pos, cote, c);
    // Manque la normale !
    glVertex3d (ptA[0], ptA[1], ptA[2]);
    glVertex3d (ptB[0], ptB[1], ptB[2]);
    glVertex3d (ptC[0], ptC[1], ptC[2]);
}

double[3] Metaballs::associerPoint(Vecteur<3> pos, double cote, int a) {
    switch (a) {
    case 0 : 
	return Vecteur<3>(pos(1), pos(2)+cote/2.0, pos(3));
	break;
    case 1 :
	return Vecteur<3>(pos(1)+cote/2.0, pos(2)+cote, pos(3));
	break;
    case 2 :
	return Vecteur<3>(pos(1)+cote, pos(2)+cote/2.0, pos(3));
	break;
    case 3 :
	return Vecteur<3>(pos(1)+cote/2.0, pos(2)+cote, pos(3));
	break;
    case 4 : 
	return Vecteur<3>(pos(1), pos(2)+cote/2.0, pos(3)+cote);
	break;
    case 5 :
	return Vecteur<3>(pos(1)+cote/2.0, pos(2)+cote, pos(3)+cote);
	break;
    case 6 :
	return Vecteur<3>(pos(1)+cote, pos(2)+cote/2.0, pos(3)+cote);
	break;
    case 7 :
	return Vecteur<3>(pos(1)+cote/2.0, pos(2)+cote, pos(3)+cote);
	break;
    case 8 :
	return Vecteur<3>(pos(1), pos(2), pos(3)+cote/2.0);
	break;
    case 9 :
	return Vecteur<3>(pos(1), pos(2)+cote, pos(3)+cote/2.0);
	break;
    case 10 :
	return Vecteur<3>(pos(1)+cote, pos(2)+cote, pos(3)+cote/2.0);
	break;
    case 11 :
	return Vecteur<3>(pos(1)+cote, pos(2), pos(3)+cote/2.0);
	break;
    default :
	return Vecteur<3>();
	break;
    }
}
