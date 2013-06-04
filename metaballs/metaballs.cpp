#include "metaballs.hpp"

/* ** Constructeurs ** */

/*
 * Convention sur le cube utilisé
 * (Si) représente le sommet numéro i
 * Un simple chiffre représente le numéro de l'arête
 *
 * ......... z
 *
 * ......... ^
 * ......... |
 * ........(S4)------4------(S5)
 * .......  /|              / |
 * ....... / |             /  |
 * ...... 7  8            5   9
 * ..... /   |           /    |
 * .... /    |          /     |
 * ...(S7)------6-----(S6)    |
 * ... |    (S0)-----0--|---(S1)----> y
 * ... |    /           |    /
 * .. 11   /           10   /
 * ... |  3             |  1
 * ... | /              | /
 * ... |/               |/
 * ...(S3)------2-----(S2)
 * .. /
 * .. v
 * 
 * .. x
 */

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
    int config = 0 ;
    Vecteur<3> posCour;
    glBegin (GL_TRIANGLES);
    for (int i = 0 ; i < n - 1 ; i++) {
	for (int j = 0 ; j < p - 1 ; j++) {
	    for (int k = 0 ; k < q - 1 ; k++) {
		config = 0 ;
		for (int s = 0 ; s < 8 ; s++) {
		    /*
		     * C'est tordu, mais je n'ai rien trouvé de mieux pour éviter 8 "if"
		     * La boucle sur s va parcourir les 8 sommets du cube dont le sommet 0
		     * est (i, j, k)
		     * Peut-être est-il cependant plus pertinent d'écrire les huit instructions
		     * à la suite, d'autant plus qu'il n'y en a pas beaucoup (on évite ainsi un for)
		     * Si un point prend la valeur "vrai" il est considéré comme coloré
		     * c'est-à-dire à l'intérieur de la surface implicite
		     */
		    config |= points[i + ((s >> 1) % 2)][j + ((s + (s >> 1)) % 2)][k + (s >> 2)];
		    config <<= 1;
		}
		posCour = Vecteur<3> (origine(1) + cote*double(i)/(n - 1),
				      origine(2) + cote*double(j)/(p - 1),
				      origine(3) + cote*double(k)/(q - 1));
	        drawCube (posCour, cote, config);
	    }
	}
    }
    glEnd (GL_TRIANGLES);
    // To do : cas limites (bords de la boîte) (éventuellement)
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
    Vecteur<3> ptA = associerPoint (pos, cote, a);
    Vecteur<3> ptB = associerPoint (pos, cote, b);
    Vecteur<3> ptC = associerPoint (pos, cote, c);
    // Manque la normale !
    glVertex3d (ptA[0], ptA[1], ptA[2]);
    glVertex3d (ptB[0], ptB[1], ptB[2]);
    glVertex3d (ptC[0], ptC[1], ptC[2]);
}


Vecteur<3> Metaballs::associerPoint(Vecteur<3> pos, double cote, int a) {
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
