#include "metaballs.hpp"
#include <algorithm>

using std::min;

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



Metaballs::Metaballs(Vecteur<3> _origine, double _cote, double _rayon, double x, double y, double z) :
    origine (_origine),
    cote (_cote),
    rayon (_rayon),
    configurations ({{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                      {7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                      {5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                      {5, 7, 10, 7, 10, 11, -1, -1, -1, -1, -1, -1},
                      {4, 5, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                      {6, 7, 11, 4, 5, 9, -1, -1, -1, -1, -1, -1},
                      {4, 6, 9, 6, 9, 10, -1, -1, -1, -1, -1, -1},
                      {9, 10, 11, 4, 9, 11, 4, 7, 11, -1, -1, -1},
                      {4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                      {4, 6, 8, 6, 8, 11, -1, -1, -1, -1, -1, -1},
                      {4, 7, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1},
                      {8, 10, 11, 4, 5, 8, 5, 8, 10, -1, -1, -1},
                      {7, 5, 8, 5, 8, 9, -1, -1, -1, -1, -1, -1},
                      {8, 9, 11, 5, 6, 9, 6, 9, 11, -1, -1, -1},
                      {8, 9, 10, 7, 6, 8, 6, 8, 10, -1, -1, -1},
                      {8, 9, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1},
                      {2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                      {2, 3, 6, 3, 6, 7, -1, -1, -1, -1, -1, -1},
                      {2, 3, 11, 5, 6, 10, -1, -1, -1, -1, -1, -1},
                      {3, 5, 7, 3, 2, 5, 2, 5, 10, -1, -1, -1},
                      {4, 5, 9, 2, 3, 11, -1, -1, -1, -1, -1, -1},
                      {2, 3, 6, 3, 6, 7, 4, 5, 9, -1, -1, -1},
                      {2, 3, 11, 4, 6, 9, 6, 9, 10, -1, -1, -1},
                      {4, 9, 7, 9, 7, 2, 7, 2, 3, 9, 2, 10},
                      {2, 3, 11, 4, 7, 8, -1, -1, -1, -1, -1, -1},
                      {2, 6, 4, 2, 3, 4, 3, 4, 8, -1, -1, -1},
                      {2, 3, 11, 5, 6, 10, 4, 7, 8, -1, -1, -1},
                      {2, 3, 5, 3, 5, 4, 2, 5, 10, 3, 4, 8},
                      {2, 3, 11, 7, 5, 8, 5, 8, 9, -1, -1, -1},
                      {5, 9, 6, 9, 6, 3, 6, 3, 2, 9, 3, 8},
                      {2, 3, 11, 8, 9, 10, 7, 6, 8, 6, 8, 10},
                      {3, 2, 8, 2, 8, 10, 8, 9, 10, -1, -1, -1},
                      {1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                      {1, 2, 10, 6, 7, 11, -1, -1, -1, -1, -1, -1},
                      {1, 2, 5, 2, 5, 6, -1, -1, -1, -1, -1, -1},
                      {5, 1, 7, 1, 2, 11, 1, 7, 11, -1, -1, -1},
                      {1, 2, 10, 4, 5, 9, -1, -1, -1, -1, -1, -1},
                      {1, 2, 10, 6, 7, 11, 4, 5, 9, -1, -1, -1},
                      {2, 4, 6, 1, 2, 4, 1, 4, 9, -1, -1, -1},
                      {4, 1, 7, 1, 7, 2, 1, 4, 9, 2, 7, 11},
                      {1, 2, 10, 4, 7, 8, -1, -1, -1, -1, -1, -1},
                      {1, 2, 10, 4, 6, 8, 6, 8, 11, -1, -1, -1},
                      {2, 1, 6, 1, 6, 5, 4, 7, 8, -1, -1, -1},
                      {8, 4, 5, 8, 5, 2, 5, 2, 1, 8, 2, 11},
                      {1, 2, 10, 7, 5, 8, 5, 8, 9, -1, -1, -1},
                      {1, 2, 10, 8, 9, 11, 5, 6, 9, 6, 9, 11},
                      {7, 8, 6, 8, 6, 1, 6, 1, 2, 8, 1, 9},
                      {8, 9, 11, 1, 2, 9, 2, 9, 11, -1, -1, -1},
                      {1, 3, 10, 3, 10, 11, -1, -1, -1, -1, -1, -1},
                      {1, 3, 7, 1, 6, 7, 1, 6, 10, -1, -1, -1},
                      {1, 3, 5, 11, 3, 6, 3, 6, 5, -1, -1, -1},
                      {1, 3, 5, 3, 5, 7, -1, -1, -1, -1, -1, -1},
                      {1, 3, 10, 3, 10, 11, 4, 5, 9, -1, -1, -1},
                      {4, 5, 9, 1, 3, 7, 1, 6, 7, 1, 6, 10},
                      {4, 9, 1, 4, 1, 11, 1, 11, 3, 4, 11, 6},
                      {1, 3, 7, 1, 4, 7, 1, 4, 9, -1, -1, -1},
                      {4, 7, 8, 1, 3, 10, 3, 10, 11, -1, -1, -1},
                      {4, 8, 3, 4, 3, 10, 3, 10, 1, 4, 10, 6},
                      {4, 7, 8, 1, 3, 5, 3, 6, 5, 3, 6, 11},
                      {1, 3, 5, 3, 4, 5, 3, 4, 8, -1, -1, -1},
                      {1, 3, 10, 3, 10, 11, 7, 5, 8, 5, 8, 9},
                      {5, 6, 10, 3, 1, 8, 1, 8, 9, -1, -1, -1},
                      {6, 7, 11, 3, 1, 8, 1, 8, 9, -1, -1, -1},
                      {1, 3, 9, 3, 9, 8, -1, -1, -1, -1, -1, -1},
                      {1, 9, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                      {1, 9, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1},
                      {5, 10, 6, 1, 9, 0, -1, -1, -1, -1, -1, -1},
                      {7, 11, 5, 11, 5, 10, 1, 9, 0, -1, -1, -1 },
                      {4, 5, 0, 0, 5, 1, -1, -1, -1, -1, -1, -1 },
                      {4, 5, 0, 0, 5, 1, 7, 6, 11, -1, -1, -1 },
                      {6, 4, 0, 6, 0, 1, 6, 1, 10, -1, -1, -1 },
                      {7, 11, 10, 7, 10, 0, 10, 0, 1, 7, 0, 4 },
                      {9, 0, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1 },
                      {8, 4, 11, 4, 11, 6, 1, 9, 0, -1, -1, -1 },
                      {1, 9, 0, 6, 5, 10, 7, 8, 4, -1, -1, -1 },
                      {1, 9, 0, 11, 10, 8, 10, 8, 4, 10, 4, 5 },
                      {7, 5, 1, 7, 1, 0, 7, 0, 8, -1, -1, -1 },
                      {8, 11, 0, 0, 5, 1, 11, 6, 5, 11, 5, 0 },
                      {8, 0, 7, 0, 7, 1, 7, 1, 6, 1, 6, 10 },
                      {11, 8, 10, 8, 0, 10, 10, 0, 1, -1, -1, -1 },
                      {11, 2, 3, 1, 9, 0, -1, -1, -1, -1, -1, -1 },
                      {7, 6, 3, 6, 3, 2, 1, 9, 0, -1, -1, -1 },
                      {3, 2, 11, 10, 6, 5, 1, 9, 0, -1, -1, -1 },
                      {1, 9, 0, 3, 7, 5, 3, 5, 2, 5, 2, 10 },
                      {4, 5, 0, 0, 5, 1, 11, 3, 2, -1, -1, -1 },
                      {7, 6, 3, 6, 3, 2, 4, 5, 0, 5, 0, 1 },
                      {11, 3, 2, 6, 4, 0, 6, 0, 1, 6, 1, 10 },
                      {2, 10, 1, 7, 3, 4, 4, 3, 0, -1, -1, -1 },
                      {7, 8, 4, 11, 3, 2, 1, 9, 0, -1, -1, -1 },
                      {1, 9, 0, 4, 6, 2, 4, 2, 8, 2, 8, 3 },
                      {7, 8, 4, 6, 5, 10, 11, 3, 2, 1, 9, 0 },
                      {3, 8, 0, 4, 5, 9, 2, 10, 1, -1, -1, -1 },
                      {11, 3, 2, 7, 5, 1, 1, 7, 8, 1, 8, 0 },
                      {3, 8, 0, 2, 6, 5, 2, 5, 1, -1, -1, -1 },
                      {7, 6, 11, 3, 8, 0, 2, 10, 1, -1, -1, -1 },
                      {2, 10, 1, 3, 0, 8, -1, -1, -1, -1, -1, -1 },
                      {9, 0, 2, 9, 2, 10, -1, -1, -1, -1, -1, -1 },
                      {9, 0, 2, 9, 2, 10, 11, 7, 6, -1, -1, -1 },
                      {6, 2, 0, 6, 0, 5, 0, 5, 9, -1, -1, -1 },
                      {7, 11, 2, 7, 2, 9, 2, 9, 0, 7, 9, 5 },
                      {4, 0, 2, 2, 4, 5, 2, 5, 10, -1, -1, -1 },
                      {4, 0, 2, 2, 4, 5, 2, 5, 10, 11, 7, 6 },
                      {4, 6, 0, 6, 0, 2, -1, -1, -1, -1, -1, -1 },
                      {4, 0, 2, 4, 2, 7, 2, 7, 11, -1, -1, -1 },
                      {9, 0, 10, 0, 10, 2, 7, 8, 4, -1, -1, -1 },
                      {8, 4, 6, 8, 6, 11, 9, 0, 10, 0, 10, 2 },
                      {7, 8, 4, 6, 2, 0, 6, 0, 9, 6, 9, 5 },
                      {11, 8, 0, 11, 0, 2, 4, 5, 9, -1, -1, -1 },
                      {7, 8, 0, 7, 0, 10, 0, 10, 2, 7, 10, 5 },
                      {11, 8, 2, 2, 8, 0, 10, 6, 5, -1, -1, -1 },
                      {6, 2, 0, 6, 0, 7, 0, 7, 8, -1, -1, -1 },
                      {11, 8, 2, 8, 2, 0, -1, -1, -1, -1, -1, -1 },
                      {11, 10, 9, 11, 9, 0, 11, 0, 3, -1, -1, -1 },
                      {0, 9, 3, 3, 9, 6, 9, 6, 10, 3, 6, 7 },
                      {5, 6, 9, 6, 9, 0, 6, 0, 11, 11, 0, 3 },
		              {3, 7, 5, 5, 3, 9, 3, 9, 0, -1, -1, -1},
                      {4, 5, 10, 4, 10, 3, 10, 11, 3, 3, 4, 0 },
                      {7, 3, 0, 7, 0, 4, 6, 5, 10, -1, -1, -1 },
                      {6, 4, 0, 6, 0, 3, 6, 3, 11, -1, -1, -1 },
                      {7, 0, 3, 7, 0, 4, -1, -1, -1, -1, -1, -1 },
                      {9, 10, 11, 9, 11, 3, 9, 3, 0, 4, 7, 8},
                      {4, 6, 9, 6, 9, 10, 0, 8, 3, -1, -1, -1 },
                      {11, 7, 6, 4, 5, 9, 3, 8, 0, -1, -1, -1 },
                      {3, 8, 0, 4, 5, 9, -1, -1, -1, -1, -1, -1 },
                      {3, 8, 0, 5, 11, 7, 5, 11, 10, -1, -1, -1 },
                      {0, 8, 3, 5, 6, 10, -1, -1, -1, -1, -1, -1},
                      {7, 6, 11, 8, 3, 0, -1, -1, -1, -1, -1, -1 },
                      {3, 0, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1}})
{

    // Calcul des dimensions
    n = 1 + x / cote;
    p = 1 + y / cote;
    q = 1 + z / cote;
    
    // Allocation du tableau des points
    points = new bool** [n];
    for (int i = 0 ; i < n ; i++) {
        points [i] = new bool* [p];
        for (int j = 0 ; j < p ; j++) {
            points [i][j] = new bool [q];
        }
    }
}


Metaballs::~Metaballs() {
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < p ; j++) {
            delete points [i][j];
        }
        delete points [i];
    }
    delete [] points;
}


/* ** Methodes ** */

void Metaballs::coloration(list<Particule<3> *> &particules) {
    // void Metaballs::coloration() {
    typename list<Particule<3> *>::iterator it;
    // Pour chaque point, on regarde l'influence des particules du fluide
    // Si elle superieure a rayon, on "colorie" le point
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < q; k++) {
                Vecteur<3> position = origine + Vecteur<3>(i*cote, j*cote, k*cote);
                
                double influence = 0;
                for (it = particules.begin(); it != particules.end(); it++)
                    influence += (*it)->isosurface(position);
                    
//                cout << "i = " << i << ", j = " << j << ", k = " << k << endl;
//                cout << "influence : " << influence << endl;
                
	    // bool res = (min(0.95, influence) > 0.9)? true : false;
                bool res = (influence > 1/(rayon*rayon))? true : false;
                points[i][j][k] = res;
            }
        }
    }
}

void Metaballs::coloration(int config) {
    if (points == NULL) {
        cout << "NULL" << endl;
    }
    for (int s = 0 ; s < 8 ; s++) {
        // cout << "s = " << s << " : " << ((s >> 1) % 2) << " " << ((s + (s >> 1)) % 2) << " " << (s >> 2) << endl;
        points[((s >> 1) & 1)][((s + (s >> 1)) & 1)][(s >> 2)] = ((config >> (7 - s)) % 2);
    }
}

void Metaballs::draw() {
    int config = 0 ;
    Vecteur<3> posCour;
    // glBegin(GL_TRIANGLES);
    
    // On boucle sur l'ensemble des cubes
    for (int i = 0 ; i < n - 1 ; i++) {
        for (int j = 0 ; j < p - 1 ; j++) {
            for (int k = 0 ; k < q - 1 ; k++) {
                config = 0 ;
                for (int s = 0 ; s < 8 ; s++) {
                    /*
                     * La boucle sur s va parcourir les 8 sommets du cube dont le sommet 0
                     * est (i, j, k)
                     * Si un point prend la valeur "vrai" il est considéré comme coloré
                     * c'est-à-dire à l'intérieur de la surface implicite
                     */
                    config |= points[i + ((s >> 1) & 1)][j + ((s + (s >> 1)) & 1)][k + (s >> 2)];
                    config <<= 1;
                }
                config >>= 1;
		for (int s = 0 ; s < 8 ; s++) {
		    if (points[i + ((s >> 1) & 1)][j + ((s + (s >> 1)) & 1)][k + (s >> 2)]) {
			glColor3f (0.0, 1.0, 0.0);
		    } else {
			glColor3f (0.0, 0.0, 1.0);
		    }
		    // glPointSize(5.0f);
		    // glBegin(GL_POINTS);
		    // glVertex3f (origine(1) + cote*(i + ((s >> 1) & 1)),
		    //               origine(2) + cote*(j + ((s + (s >> 1)) & 1)),
		    //               origine(3) + cote*(k + (s >> 2)));
		    // glEnd();
		    glPushMatrix();
		    glTranslatef (origine(1) + cote*(i + ((s >> 1) & 1)),
				  origine(2) + cote*(j + ((s + (s >> 1)) & 1)),
				  origine(3) + cote*(k + (s >> 2)));
		    glutSolidSphere (0.05, 10, 10);
		    glPopMatrix();
		}
                posCour = origine + Vecteur<3>(cote*i, cote*j, cote*k);
                drawCube(posCour, cote, config);
            }
        }
    }
    // glEnd();
    
    // TODO : cas limites (bords de la boîte) (éventuellement)
}

void Metaballs::drawCube(Vecteur<3> pos, double cote, int config) {
    int numConfig = (config < 128)? config : 255 - config;
    int *listeAretes = configurations[numConfig];
    int i = 0;
    while (i < 4 && listeAretes[3 * i] != -1) {
        drawTriangle(pos, cote, listeAretes[3*i], listeAretes[3*i + 1], listeAretes[3*i + 2]);
        i++;
    }
}


void Metaballs::drawTriangle(Vecteur<3> pos, double cote, int a, int b, int c) {
    Vecteur<3> ptA = associerPoint(pos, cote, a);
    Vecteur<3> ptB = associerPoint(pos, cote, b);
    Vecteur<3> ptC = associerPoint(pos, cote, c);
    
    // Calcul de la normale
    Vecteur<3> normale = ptC - ptA;
    normale = (ptB - ptA).vectoriel(normale);
    normale /= normale.norme();
    
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glNormal3f(normale(1), normale(2), normale(3));
    glVertex3d(ptA(1), ptA(2), ptA(3));
    glVertex3d(ptB(1), ptB(2), ptB(3));
    glVertex3d(ptC(1), ptC(2), ptC(3));
    glEnd();
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
        return Vecteur<3>(pos(1)+cote/2.0, pos(2), pos(3));
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
        return Vecteur<3>(pos(1)+cote/2.0, pos(2), pos(3)+cote);
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
