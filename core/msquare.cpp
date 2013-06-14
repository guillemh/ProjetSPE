#include "metaballs.hpp"

MarchingSquares::MarchingSquares(Vecteur<3> _origine, Vecteur<3> _axe1, Vecteur<3> _axe2, double _cote, double x, double y) :
    origine (_origine),
    axe1 (_axe1),
    axe2 (_axe2),
    cote (_cote),
	configurations({-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                   {0, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                   {0, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                   {0, 5, 1, 0, 5, 7, -1, -1, -1, -1, -1, -1},
                   {2, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                   {0, 4, 7, 2, 5, 6, 4, 6, 7, 4, 6, 5}, // 5 : Configuration ambiguë
                   {4, 2, 1, 4, 2, 6, -1, -1, -1, -1, -1, -1},
                   {1, 0, 7, 1, 6, 7, 1, 6, 2, -1, -1, -1},
                   {3, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                   {0, 6, 4, 0, 6, 3, -1, -1, -1, -1, -1, -1},
                   {3, 6, 7, 1, 4, 5, 4, 6, 7, 4, 6, 5}, // 10 : Configuration ambiguë
                   {0, 1, 5, 0, 5, 6, 0, 6, 3, -1, -1, -1},
                   {3, 7, 2, 7, 2, 5, -1, -1, -1, -1, -1, -1},
                   {3, 0, 4, 3, 4, 5, 3, 5, 2, -1, -1, -1},
                   {2, 3, 7, 2, 7, 4, 2, 4, 1, -1, -1, -1},
                   {0, 1, 2, 0, 2, 3, -1, -1, -1, -1, -1, -1}}) {
    n = 1 + 2*x/cote;
    p = 1 + 2*y/cote;
    normale = axe1 ^ axe2;
    points = (double**) calloc(n, sizeof(double *));
    for (int i = 0 ; i < n ; i++) {
        points[i] = (double**) calloc(p, sizeof(double));
    }
}

MarchingSquares::~MarchingSquares() {
    for (int i = 0 ; i < n ; i++) {
        free(points[i]);
    }
    free(points);
}

void Metaballs::initColoration(list<Particule<3> *> &particules) {
    for (int i = 0; i < n; i++) {
         for (int j = 0; j < p; j++) {
         }
    }

    typename list<Particule<3> *>::iterator it;
    double d = 0.1; // Rayon du support de la fonction d'influence

    for (it = particules.begin(); it != particules.end(); it++) {
        // ...
    }
}

void MarchingSquares::drawSquare(Vecteur<3> pos, double cote, int config, bool valeurCentrale) {
    int *listeAretes = configurations[numConfig];
    int i = 0;
    if (config != 5 && config != 10) {
        while (i < 4 && listeAretes[3 * i] != -1) {
            drawTriangle(pos, cote, listeAretes[3*i], listeAretes[3*i + 1], listeAretes[3*i + 2]);
            i++;
        }
    } else {
        /* Ambiguïté dans la configuration */
        drawTriangle(pos, cote, listeAretes[0], listeAretes[1], listeAretes[2]);
        drawTriangle(pos, cote, listeAretes[3], listeAretes[4], listeAretes[5]);
        /* Considérer le point central du carré.
         * En fonction de sa coloration, déterminer s'il faut dessiner les deux derniers triangles ou pas */
        if (valeurCentrale) {
            drawTriangle(pos, cote, listeAretes[6], listeAretes[7], listeAretes[8]);
            drawTriangle(pos, cote, listeAretes[9], listeAretes[10], listeAretes[11]);
        }
    }
}

void MarchingSquares::drawTriangle(Vecteur<3> pos, double cote, int config, int a, int b, int c) {
    Vecteur<3> ptA = associerPoint(pos, cote, a);
    Vecteur<3> ptB = associerPoint(pos, cote, b);
    Vecteur<3> ptC = associerPoint(pos, cote, c);

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.2, 0.8);
    glNormal3f(normale(1), normale(2), normale(3));
    glVertex3d(ptA(1), ptA(2), ptA(3));
    glVertex3d(ptB(1), ptB(2), ptB(3));
    glVertex3d(ptC(1), ptC(2), ptC(3));
    glEnd();
}

Vecteur<3> MarchingSquares::associerPoint(Vecteur<3> pos, double cote, int a) {
    switch (a) {
    case 0 : 
        return pos;
        break;
    case 1 :
        return pos + cote*axe1;
        break;
    case 2 :
        return pos + cote*(axe1 + axe2);
        break;
    case 3 :
        return pos + cote*axe2;
        break;
    case 4 :
        return pos + (cote/2)*axe1;
        break;
    case 5 :
        return pos + cote*axe1 + (cote/2)*axe2;
        break;
    case 6 :
        return pos + (cote/2)*axe1 + cote*axe2;
        break;
    case 7 :
        return pos + (cote/2)*axe2;
        break;
    default :
        return pos;
        break;
    }
}

}
