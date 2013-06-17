#include "metaballs.hpp"
#include <algorithm>
#include <cmath>

using std::min;
using std::max;

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

/*
 * Convention sur le carré utilisé
 * Ici, on ne fait pas la différence entre sommet et arête
 *
 * ... X
 * ... ^
 * ... |
 * ... 1--------5-------2
 * ... |                |
 * ... |                |
 * ... 4                6
 * ... |                |
 * ... |                |
 * ... |                |
 * ... 0--------7-------3 --> Y
 *
 */

Metaballs::Metaballs(Vecteur<3> _origine, double _cote, double _rayon, double x, double y, double z) :
    origine (_origine),
    cote (_cote),
    rayon (_rayon),
    configurations ({{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                     {7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                     {5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                     {5, 10, 7, 7, 10, 11, -1, -1, -1, -1, -1, -1},
                     {4, 9, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                     {6, 11, 7, 4, 9, 5, -1, -1, -1, -1, -1, -1},
                     {4, 9, 6, 6, 9, 10, -1, -1, -1, -1, -1, -1},
                     {9, 10, 11, 4, 9, 11, 4, 11, 7, -1, -1, -1},
                     {4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                     {4, 6, 8, 6, 11, 8, -1, -1, -1, -1, -1, -1},
                     {4, 7, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1},
                     {8, 10, 11, 4, 5, 8, 5, 10, 8, -1, -1, -1},
                     {7, 8, 5, 5, 8, 9, -1, -1, -1, -1, -1, -1},
                     {8, 9, 11, 5, 6, 9, 6, 11, 9, -1, -1, -1},
                     {8, 9, 10, 7, 8, 6, 6, 8, 10, -1, -1, -1},
                     {8, 9, 10, 8, 10, 11, -1, -1, -1, -1, -1, -1},
                     {2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                     {2, 3, 6, 3, 7, 6, -1, -1, -1, -1, -1, -1},
                     {2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1},
                     {3, 7, 5, 3, 5, 2, 2, 5, 10, -1, -1, -1},
                     {4, 9, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1},
                     {2, 3, 6, 3, 7, 6, 4, 9, 5, -1, -1, -1},
                     {2, 3, 11, 4, 9, 6, 6, 9, 10, -1, -1, -1},
                     {4, 9, 7, 9, 2, 7, 7, 2, 3, 9, 10, 2},
                     {2, 3, 11, 4, 7, 8, -1, -1, -1, -1, -1, -1},
                     {2, 4, 6, 2, 3, 4, 3, 8, 4, -1, -1, -1},
                     {2, 3, 11, 5, 10, 6, 4, 7, 8, -1, -1, -1},
                     {2, 3, 5, 3, 4, 5, 2, 5, 10, 3, 8, 4},
                     {2, 3, 11, 7, 8, 5, 5, 8, 9, -1, -1, -1},
                     {5, 6, 9, 9, 6, 3, 6, 2, 3, 9, 3, 8},
                     {2, 3, 11, 8, 9, 10, 7, 8, 6, 6, 8, 10},
                     {3, 8, 2, 2, 8, 10, 8, 9, 10, -1, -1, -1},
                     {1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                     {1, 2, 10, 6, 11, 7, -1, -1, -1, -1, -1, -1},
                     {1, 2, 5, 2, 6, 5, -1, -1, -1, -1, -1, -1},
                     {5, 1, 7, 1, 2, 11, 1, 11, 7, -1, -1, -1},
                     {1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1},
                     {1, 2, 10, 6, 11, 7, 4, 9, 5, -1, -1, -1},
                     {2, 6, 4, 1, 2, 4, 1, 4, 9, -1, -1, -1},
                     {4, 1, 7, 1, 2, 7, 1, 4, 9, 2, 11, 7},
                     {1, 2, 10, 4, 7, 8, -1, -1, -1, -1, -1, -1},
                     {1, 2, 10, 4, 6, 8, 6, 11, 8, -1, -1, -1},
                     {2, 6, 1, 1, 6, 5, 4, 7, 8, -1, -1, -1},
                     {8, 4, 5, 8, 5, 2, 5, 1, 2, 8, 2, 11},
                     {1, 2, 10, 7, 8, 5, 5, 8, 9, -1, -1, -1},
                     {1, 2, 10, 8, 9, 11, 5, 6, 9, 6, 11, 9},
                     {7, 8, 6, 8, 1, 6, 6, 1, 2, 8, 9, 1},
                     {8, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1},
                     {1, 3, 10, 3, 11, 10, -1, -1, -1, -1, -1, -1},
                     {1, 3, 7, 1, 7, 6, 1, 6, 10, -1, -1, -1},
                     {1, 3, 5, 11, 6, 3, 3, 6, 5, -1, -1, -1},
                     {1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1},
                     {1, 3, 10, 3, 11, 10, 4, 9, 5, -1, -1, -1},
                     {4, 9, 5, 1, 3, 7, 1, 7, 6, 1, 6, 10},
                     {4, 9, 1, 4, 1, 11, 1, 3, 11, 4, 11, 6},
                     {1, 3, 7, 1, 7, 4, 1, 4, 9, -1, -1, -1},
                     {4, 7, 8, 1, 3, 10, 3, 11, 10, -1, -1, -1},
                     {4, 3, 8, 4, 10, 3, 3, 10, 1, 4, 6, 10},
                     {4, 7, 8, 1, 3, 5, 3, 6, 5, 3, 11, 6},
                     {1, 3, 5, 3, 4, 5, 3, 8, 4, -1, -1, -1},
                     {1, 3, 10, 3, 11, 10, 7, 8, 5, 5, 8, 9},
                     {5, 6, 10, 3, 8, 1, 1, 8, 9, -1, -1, -1},
                     {6, 7, 11, 3, 8, 1, 1, 8, 9, -1, -1, -1},
                     {1, 3, 9, 3, 8, 9, -1, -1, -1, -1, -1, -1},
                     {1, 9, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                     {1, 9, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1},
                     {5, 10, 6, 1, 9, 0, -1, -1, -1, -1, -1, -1},
                     {7, 5, 11, 11, 5, 10, 1, 9, 0, -1, -1, -1 },
                     {4, 0, 5, 0, 1, 5, -1, -1, -1, -1, -1, -1 },
                     {4, 0, 5, 0, 1, 5, 7, 6, 11, -1, -1, -1 },
                     {6, 4, 0, 6, 0, 1, 6, 1, 10, -1, -1, -1 },
                     {7, 10, 11, 7, 0, 10, 10, 0, 1, 7, 4, 0 },
                     {9, 0, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1 },
                     {8, 4, 11, 4, 6, 11, 1, 9, 0, -1, -1, -1 },
                     {1, 9, 0, 6, 5, 10, 7, 8, 4, -1, -1, -1 },
                     {1, 9, 0, 11, 8, 10, 10, 8, 4, 10, 4, 5 },
                     {7, 1, 5, 7, 0, 1, 7, 8, 0, -1, -1, -1 },
                     {8, 0, 11, 0, 1, 5, 11, 5, 6, 11, 0, 5 },
                     {8, 0, 7, 0, 1, 7, 7, 1, 6, 1, 10, 6 },
                     {11, 8, 10, 8, 0, 10, 10, 0, 1, -1, -1, -1 },
                     {11, 2, 3, 1, 9, 0, -1, -1, -1, -1, -1, -1 },
                     {7, 6, 3, 6, 2, 3, 1, 9, 0, -1, -1, -1 },
                     {3, 11, 2, 10, 6, 5, 1, 9, 0, -1, -1, -1 },
                     {1, 9, 0, 3, 7, 5, 3, 5, 2, 5, 10, 2 },
                     {4, 0, 5, 0, 1, 5, 11, 2, 3, -1, -1, -1 },
                     {7, 6, 3, 6, 2, 3, 4, 0, 5, 5, 0, 1 },
                     {11, 2, 3, 6, 4, 0, 6, 0, 1, 6, 1, 10 },
                     {2, 1, 10, 7, 4, 3, 4, 0, 3, -1, -1, -1 },
                     {7, 8, 4, 11, 2, 3, 1, 9, 0, -1, -1, -1 },
                     {1, 9, 0, 4, 6, 2, 4, 2, 8, 2, 3, 8 },
                     {7, 8, 4, 6, 5, 10, 11, 2, 3, 1, 9, 0 },
                     {3, 8, 0, 4, 5, 9, 2, 1, 10, -1, -1, -1 },
                     {11, 2, 3, 7, 1, 5, 1, 7, 8, 1, 8, 0 },
                     {3, 8, 0, 2, 5, 6, 2, 1, 5, -1, -1, -1 },
                     {7, 11, 6, 3, 8, 0, 2, 1, 10, -1, -1, -1 },
                     {2, 1, 10, 3, 8, 0, -1, -1, -1, -1, -1, -1 },
                     {9, 0, 2, 9, 2, 10, -1, -1, -1, -1, -1, -1 },
                     {9, 0, 2, 9, 2, 10, 11, 7, 6, -1, -1, -1 },
                     {6, 0, 2, 6, 5, 0, 0, 5, 9, -1, -1, -1 },
                     {7, 2, 11, 7, 9, 2, 2, 9, 0, 7, 5, 9 },
                     {4, 0, 2, 2, 5, 4, 2, 10, 5, -1, -1, -1 },
                     {4, 2, 0, 2, 5, 4, 2, 10, 5, 11, 7, 6 },
                     {4, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1 },
                     {4, 0, 2, 4, 2, 7, 2, 11, 7, -1, -1, -1 },
                     {9, 0, 10, 0, 2, 10, 7, 8, 4, -1, -1, -1 },
                     {8, 4, 6, 8, 6, 11, 9, 0, 10, 0, 2, 10 },
                     {7, 8, 4, 6, 0, 2, 6, 9, 0, 6, 5, 9 },
                     {11, 8, 0, 11, 0, 2, 4, 5, 9, -1, -1, -1 },
                     {7, 8, 0, 7, 0, 10, 0, 2, 10, 7, 10, 5 },
                     {11, 8, 2, 2, 8, 0, 10, 5, 6, -1, -1, -1 },
                     {6, 0, 2, 6, 7, 0, 0, 7, 8, -1, -1, -1 },
                     {11, 8, 2, 8, 0, 2, -1, -1, -1, -1, -1, -1 },
                     {11, 10, 9, 11, 9, 0, 11, 0, 3, -1, -1, -1 },
                     {0, 3, 9, 3, 6, 9, 9, 6, 10, 3, 7, 6 },
                     {5, 9, 6, 6, 9, 0, 6, 0, 11, 11, 0, 3 },
                     {3, 7, 5, 5, 9, 3, 3, 9, 0, -1, -1, -1},
                     {4, 10, 5, 4, 3, 10, 10, 3, 11, 3, 4, 0 },
                     {7, 0, 3, 7, 4, 0, 6, 10, 5, -1, -1, -1 },
                     {6, 4, 0, 6, 0, 3, 6, 3, 11, -1, -1, -1 },
                     {7, 0, 3, 7, 4, 0, -1, -1, -1, -1, -1, -1 },
                     {9, 11, 10, 9, 3, 11, 9, 0, 3, 4, 7, 8},
                     {4, 6, 9, 6, 10, 9, 0, 3, 8, -1, -1, -1 },
                     {11, 6, 7, 4, 5, 9, 3, 8, 0, -1, -1, -1 },
                     {3, 8, 0, 4, 5, 9, -1, -1, -1, -1, -1, -1 },
                     {3, 8, 0, 5, 7, 11, 5, 11, 10, -1, -1, -1 },
                     {0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1},
                     {7, 11, 6, 8, 0, 3, -1, -1, -1, -1, -1, -1 },
                     {3, 8, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1}}),
    configurations2d({{-1, -1, -1, -1, -1, -1, -1, -1, -1},
                      {3, 6, 7, -1, -1, -1, -1, -1, -1},
                      {6, 2, 5, -1, -1, -1, -1, -1, -1},
                      {3, 2, 7, 7, 2, 5, -1, -1, -1},
                      {4, 5, 1, -1, -1, -1, -1, -1, -1},
                      {4, 5, 1, 3, 6, 7, -1, -1, -1},
                      {4, 6, 1, 1, 6, 2, -1, -1, -1},
                      {4, 7, 3, 4, 3, 2, 4, 2, 1},
                      {0, 7, 4, -1, -1, -1, -1, -1, -1},
                      {0, 3, 4, 4, 3, 6, -1, -1, -1},
                      {0, 7, 4, 5, 6, 2, -1, -1, -1},
                      {0, 3, 2, 0, 2, 5, 0, 5, 4},
                      {0, 7, 5, 0, 5, 1, -1, -1, -1},
                      {0, 3, 1, 1, 3, 6, 1, 6, 5},
                      {1, 0, 2, 2, 0, 7, 2, 7, 6},
                      {0, 3, 1, 1, 3, 2, -1, -1, -1}})
{

    /* Calcul des dimensions */
    n = 1 + x / cote;
    p = 1 + y / cote;
    q = 1 + z / cote;
    
    /* Allocation du tableau des points */
    points = (double***) calloc(n, sizeof(double **));
    for (int i = 0 ; i < n ; i++) {
        points[i] = (double**) calloc(p, sizeof(double *));
        for (int j = 0 ; j < p ; j++) {
            points[i][j] = (double*) calloc(q, sizeof(double));
        }
    }
}


Metaballs::~Metaballs() {
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < p ; j++) {
            free(points[i][j]);
        }
        free(points[i]);
    }
    free(points);
}


/* ** Méthodes ** */

void Metaballs::initColoration(list<Particule<3> *> &particules) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < q; k++) {
                points[i][j][k] = 0;
            }
        }
    }

    typename list<Particule<3> *>::iterator it;
    /* Rayon du support de la fonction d'influence */
    double d = 0.1; 

    for (it = particules.begin(); it != particules.end(); it++) {
            
        /* On sélectionne les points influencés par la particule */
        Vecteur<3> pos = (*it)->getPosition() - origine;
        pos(1) = fabs(pos(1));
        pos(2) = fabs(pos(2));
        pos(3) = fabs(pos(3));
        int i_min = max(0, (int) ceil((pos(1) - d)/cote));
        int i_max = min(n-1, (int) floor((pos(1) + d)/cote));
        int j_min = max(0, (int) ceil((pos(2) - d)/cote));
        int j_max = min(p-1, (int) floor((pos(2) + d)/cote));
        int k_min = max(0, (int) ceil((pos(3) - d)/cote));
        int k_max = min(q-1, (int) floor((pos(3) + d)/cote));

        double ic, jc;
        /* On boucle sur ces points pour ajouter son influence */
        for (int i = i_min; i <= i_max; i++) {
            ic = i*cote;
            for (int j = j_min; j <= j_max; j++) {
                jc = j*cote;
                for (int k = k_min; k <= k_max; k++) {
                    pos = origine + Vecteur<3>(ic, jc, k*cote);
                    points[i][j][k] += (*it)->isosurface(pos, false);
                }
            }
        }
    }
}


void Metaballs::coloration(list<Particule<3> *> &particules) {

    typename list<Particule<3> *>::iterator it;
    /* Rayon du support de la fonction d'influence */
    double d = 0.1; 

    for (it = particules.begin(); it != particules.end(); it++) {
        
        /* Si la particule a bougé */
        if ((*it)->getPosition() != (*it)->getPositionPrec()) {
    
            /* On sélectionne les points influencés par l'ancienne position de la particule */
            Vecteur<3> pos = (*it)->getPositionPrec() - origine;
            pos(1) = fabs(pos(1));
            pos(2) = fabs(pos(2));
            pos(3) = fabs(pos(3));
            int i_min = max(0, (int) ceil((pos(1) - d)/cote));
            int i_max = min(n-1, (int) floor((pos(1) + d)/cote));
            int j_min = max(0, (int) ceil((pos(2) - d)/cote));
            int j_max = min(p-1, (int) floor((pos(2) + d)/cote));
            int k_min = max(0, (int) ceil((pos(3) - d)/cote));
            int k_max = min(q-1, (int) floor((pos(3) + d)/cote));

            double ic, jc;
            /* On boucle sur ces points pour supprimer son influence */
            for (int i = i_min; i <= i_max; i++) {
                ic = i*cote;
                for (int j = j_min; j <= j_max; j++) {
                    jc = j*cote;
                    for (int k = k_min; k <= k_max; k++) {
                        pos = origine + Vecteur<3>(ic, jc, k*cote);
                        points[i][j][k] -= (*it)->isosurface(pos, true);
                    }
                }
            }

            /* On sélectionne les points influencés par la nouvelle position de la particule */
            pos = (*it)->getPosition() - origine;
            pos(1) = fabs(pos(1));
            pos(2) = fabs(pos(2));
            pos(3) = fabs(pos(3));
            i_min = max(0, (int) ceil((pos(1) - d)/cote));
            i_max = min(n-1, (int) floor((pos(1) + d)/cote));
            j_min = max(0, (int) ceil((pos(2) - d)/cote));
            j_max = min(p-1, (int) floor((pos(2) + d)/cote));
            k_min = max(0, (int) ceil((pos(3) - d)/cote));
            k_max = min(q-1, (int) floor((pos(3) + d)/cote));

            /* On boucle sur ces points pour ajouter son influence */
            for (int i = i_min; i <= i_max; i++) {
                ic = i*cote;
                for (int j = j_min; j <= j_max; j++) {
                    jc = j*cote;
                    for (int k = k_min; k <= k_max; k++) {
                        pos = origine + Vecteur<3>(ic, jc, k*cote);
                        points[i][j][k] += (*it)->isosurface(pos, false);
                    }
                }
            }
            
        }
    }
}


void Metaballs::draw() {
    int config;
    bool dedans;
    Vecteur<3> posCour;
    Vecteur<3> direction;
    
    /* On boucle sur l'ensemble des cubes pour appliquer les Marching Cubes */
    for (int i = 0 ; i < n - 1 ; i++) {
        for (int j = 0 ; j < p - 1 ; j++) {
            for (int k = 0 ; k < q - 1 ; k++) {
                config = 0 ;
                /*
                 * On parcourt les 8 sommets du cube dont le sommet 0 est (i, j, k)
                 * Si un point prend la valeur "vrai" il est considéré comme coloré
                 * c'est-à-dire à l'intérieur de la surface implicite
                 */
                for (int s = 0 ; s < 8 ; s++) {
                    /* Isovaleur de la fonction F(x) = 1/x² */
                    // dedans = points[i + ((s >> 1) & 1)][j + ((s + (s >> 1)) & 1)][k + (s >> 2)] > 1/(rayon*rayon);
                    
                    /* Isovaleur des fonctions F(x) = 0.1^10000x² et F(x) = exp(-x^4/0.000391) */
                    // dedans = points[i + ((s >> 1) & 1)][j + ((s + (s >> 1)) & 1)][k + (s >> 2)] > 0.9;

                    /* Isovaleur de la fonction F(x) affine ou de Hermite par morceaux */
                    // dedans = points[i + ((s >> 1) & 1)][j + ((s + (s >> 1)) & 1)][k + (s >> 2)] > 0.7;
                            
                    /* Isovaleur de la fonction F(x) = a/(1+b*x²) */
                    dedans = points[i + ((s >> 1) & 1)][j + ((s + (s >> 1)) & 1)][k + (s >> 2)] > 1.41/9.75;
                    
                    config <<= 1;
                    config |= dedans;
                }
                
                posCour = origine + Vecteur<3>(cote*i, cote*j, cote*k);
                drawCube(posCour, config);
            }
        }
    }
    
    
    /* On boucle sur l'ensemble des carrés du bord pour appliquer les Marching Squares */
    for (int i = 0 ; i < n - 1 ; i++) {
        for (int j = 0 ; j < p - 1 ; j++) {
            config = 0;
            for (int s = 0; s < 4; s++) {
                /* Isovaleur de la fonction F(x) = 1/x² */
                // bool dedans = points[i + ((s + (s >> 1)) & 1)][j + ((s >> 1) & 1)][0] > 1/(rayon*rayon);
                    
                /* Isovaleur des fonctions F(x) = 0.1^10000x² et F(x) = exp(-x^4/0.000391) */
                // bool dedans = points[i + ((s + (s >> 1)) & 1)][j + ((s >> 1) & 1)][0] > 0.9;

                /* Isovaleur de la fonction F(x) affine ou de Hermite par morceaux */
                // bool dedans = points[i + ((s + (s >> 1)) & 1)][j + ((s >> 1) & 1)][0] > 0.7;
                    
                /* Isovaleur de la fonction F(x) = a/(1+b*x²) */
                bool dedans = points[i + ((s + (s >> 1)) & 1)][j + ((s >> 1) & 1)][0] > 1.41/9.75;
                
                config <<= 1;
                config |= dedans;
            }
            posCour = origine + Vecteur<3>(cote*i, cote*j, 0);
            direction = Vecteur<3>(1, 1, 0);
            drawCarre(posCour, direction, config, -1);
        }
    }
    
    for (int j = 0 ; j < p - 1 ; j++) {
        for (int k = 0 ; k < q - 1 ; k++) {
            config = 0;
            for (int s = 0; s < 4; s++) {
                /* Isovaleur de la fonction F(x) = 1/x² */
                // bool dedans = points[0][j + ((s + (s >> 1)) & 1)][k + ((s >> 1) & 1)] > 1/(rayon*rayon);
                    
                /* Isovaleur des fonctions F(x) = 0.1^10000x² et F(x) = exp(-x^4/0.000391) */
                // bool dedans = points[0][j + ((s + (s >> 1)) & 1)][k + ((s >> 1) & 1)] > 0.9;

                /* Isovaleur de la fonction F(x) affine ou de Hermite par morceaux */
                // bool dedans = points[0][j + ((s + (s >> 1)) & 1)][k + ((s >> 1) & 1)] > 0.7;
                    
                /* Isovaleur de la fonction F(x) = a/(1+b*x²) */
                bool dedans = points[0][j + ((s + (s >> 1)) & 1)][k + ((s >> 1) & 1)] > 1.41/9.75;
                
                config <<= 1;
                config |= dedans;
            }
            posCour = origine + Vecteur<3>(0, cote*j, cote*k);
            direction = Vecteur<3>(0, 1, 1);
            drawCarre(posCour, direction, config, -1);

            config = 0;
            for (int s = 0; s < 4; s++) {
                /* Isovaleur de la fonction F(x) = 1/x² */
                // bool dedans = points[n-1][j + ((s + (s >> 1)) & 1)][k + ((s >> 1) & 1)] > 1/(rayon*rayon);
                    
                /* Isovaleur des fonctions F(x) = 0.1^10000x² et F(x) = exp(-x^4/0.000391) */
                // bool dedans = points[n-1][j + ((s + (s >> 1)) & 1)][k + ((s >> 1) & 1)] > 0.9;

                /* Isovaleur de la fonction F(x) affine ou de Hermite par morceaux */
                // bool dedans = points[n-1][j + ((s + (s >> 1)) & 1)][k + ((s >> 1) & 1)] > 0.7;
                    
                /* Isovaleur de la fonction F(x) = a/(1+b*x²) */
                bool dedans = points[n-1][j + ((s + (s >> 1)) & 1)][k + ((s >> 1) & 1)] > 1.41/9.75;
                
                config <<= 1;
                config |= dedans;
            }
            posCour = origine + Vecteur<3>(cote*(n-1), cote*j, cote*k);
            direction = Vecteur<3>(0, 1, 1);
            drawCarre(posCour, direction, config, 1);
        }
    }
    
    for (int i = 0 ; i < n - 1 ; i++) {
        for (int k = 0 ; k < q - 1 ; k++) {
            config = 0;
            for (int s = 0; s < 4; s++) {
                /* Isovaleur de la fonction F(x) = 1/x² */
                // bool dedans = points[i + ((s + (s >> 1)) & 1)][0][k + ((s >> 1) & 1)] > 1/(rayon*rayon);
                    
                /* Isovaleur des fonctions F(x) = 0.1^10000x² et F(x) = exp(-x^4/0.000391) */
                // bool dedans = points[i + ((s + (s >> 1)) & 1)][0][k + ((s >> 1) & 1)] > 0.9;

                /* Isovaleur de la fonction F(x) affine ou de Hermite par morceaux */
                // bool dedans = points[i + ((s + (s >> 1)) & 1)][0][k + ((s >> 1) & 1)] > 0.7;
                    
                /* Isovaleur de la fonction F(x) = a/(1+b*x²) */
                bool dedans = points[i + ((s + (s >> 1)) & 1)][0][k + ((s >> 1) & 1)] > 1.41/9.75;
                
                config <<= 1;
                config |= dedans;
            }
            posCour = origine + Vecteur<3>(cote*i, 0, cote*k);
            direction = Vecteur<3>(1, 0, 1);
            drawCarre(posCour, direction, config, 1);

            config = 0;
            for (int s = 0; s < 4; s++) {
                /* Isovaleur de la fonction F(x) = 1/x² */
                // bool dedans = points[i + ((s + (s >> 1)) & 1)][p-1][k + ((s >> 1) & 1)] > 1/(rayon*rayon);
                    
                /* Isovaleur des fonctions F(x) = 0.1^10000x² et F(x) = exp(-x^4/0.000391) */
                // bool dedans = points[i + ((s + (s >> 1)) & 1)][p-1][k + ((s >> 1) & 1)] > 0.9;

                /* Isovaleur de la fonction F(x) affine ou de Hermite par morceaux */
                // bool dedans = points[i + ((s + (s >> 1)) & 1)][p-1][k + ((s >> 1) & 1)] > 0.7;
                    
                /* Isovaleur de la fonction F(x) = a/(1+b*x²) */
                bool dedans = points[i + ((s + (s >> 1)) & 1)][p-1][k + ((s >> 1) & 1)] > 1.41/9.75;
                
                config <<= 1;
                config |= dedans;
            }
            posCour = origine + Vecteur<3>(cote*i, cote*(p-1), cote*k);
            direction = Vecteur<3>(1, 0, 1);
            drawCarre(posCour, direction, config, -1);
        }
    }
    
}


void Metaballs::drawCube(Vecteur<3> pos, int config) {
    int coef, numConfig;
    if (config < 128) {
        coef = 1;
        numConfig = config;
    } else {
        coef = -1;
        numConfig = 255 - config;
    } 
    int *listeAretes = configurations[numConfig];
    int i = 0;
    while (i < 4 && listeAretes[3 * i] != -1) {
        drawTriangle(pos, listeAretes[3*i], listeAretes[3*i + 1], listeAretes[3*i + 2], coef);
        i++;
    }
}


void Metaballs::drawTriangle(Vecteur<3> pos, int a, int b, int c, int coef) {
    Vecteur<3> ptA = associerPoint(pos, a);
    Vecteur<3> ptB = associerPoint(pos, b);
    Vecteur<3> ptC = associerPoint(pos, c);
    
    /* Calcul de la normale */
    Vecteur<3> normale = ptC - ptA;
    normale = coef*(ptB - ptA).vectoriel(normale);
    normale /= normale.norme();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.2, 0.8);
    glNormal3f(normale(1), normale(2), normale(3));
    glVertex3d(ptA(1), ptA(2), ptA(3));
    glVertex3d(ptB(1), ptB(2), ptB(3));
    glVertex3d(ptC(1), ptC(2), ptC(3));
    glEnd();
}


Vecteur<3> Metaballs::associerPoint(Vecteur<3> pos, int a) {
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


void Metaballs::drawCarre(Vecteur<3> pos, Vecteur<3> direction, int config, int coef) {
    int *listeAretes = configurations2d[config];
    int i = 0;
    while (i < 3 && listeAretes[3 * i] != -1) {
        drawTriangleBord(pos, direction, listeAretes[3*i], listeAretes[3*i + 1], listeAretes[3*i + 2], coef);
        i++;
    }
}


void Metaballs::drawTriangleBord(Vecteur<3> pos, Vecteur<3> direction, int a, int b, int c, int coef) {
    Vecteur<3> ptA = associerPointBord(pos, direction, a);
    Vecteur<3> ptB = associerPointBord(pos, direction, b);
    Vecteur<3> ptC = associerPointBord(pos, direction, c);
    
    /* Calcul de la normale */
    Vecteur<3> normale = ptB - ptA;
    normale = coef*(ptC - ptA).vectoriel(normale);
    normale /= normale.norme();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.2, 0.8);
    glNormal3f(normale(1), normale(2), normale(3));
    glVertex3d(ptA(1), ptA(2), ptA(3));
    glVertex3d(ptB(1), ptB(2), ptB(3));
    glVertex3d(ptC(1), ptC(2), ptC(3));
    glEnd();
}


Vecteur<3> Metaballs::associerPointBord(Vecteur<3> pos, Vecteur<3> direction, int a) {
    switch (a) {
    case 0 :
        return pos;
        break;
    case 1 :
        return Vecteur<3>(pos(1) + cote*direction(1), pos(2) + cote*(1-direction(1)), pos(3));
        break;
    case 2 :
        return Vecteur<3>(pos(1) + cote*direction(1), pos(2) + cote*direction(2), pos(3) + cote*direction(3));
        break;
    case 3 :
        return Vecteur<3>(pos(1), pos(2) + cote*(1-direction(3)), pos(3) + cote*direction(3));
        break;
    case 4 :
        return Vecteur<3>(pos(1) + cote*direction(1)/2.0, pos(2) + cote*(1-direction(1))/2.0, pos(3));
        break;
    case 5 :
        return Vecteur<3>(pos(1) + cote*direction(1), pos(2) + cote*(1-direction(1)) + cote*(1-direction(3))/2.0, pos(3) + cote*direction(3)/2.0);
        break;
    case 6 :
        return Vecteur<3>(pos(1) + cote*direction(1)/2.0, pos(2) + cote*(1-direction(1))/2.0 + cote*(1-direction(3)), pos(3) + cote*direction(3));
        break;
    case 7 :
        return Vecteur<3>(pos(1), pos(2) + cote*(1-direction(3))/2.0, pos(3) + cote*direction(3)/2.0);
        break;
    default :
        return Vecteur<3>();
        break;
    }
}
