#include "../core/particule.hpp"

template<unsigned int Dim>
Cascade<Dim>::Cascade(Fluide<Dim> *_f) {
    f = _f ;
    bassin_x = 3.0;
    bassin_y = 3.0;
    bassin_z = 1.0;
    obstacle_x = 0.1 * bassin_x ;
    obstacle_y = 0.15 * bassin_y ;
    obstacle_z = 1.1 * bassin_z ;
    pente_angle = 15;
    pente_x = 3.0;
    pente_y = 0.7*bassin_y;
    pente_z = 0.5;
}

template<unsigned int Dim>
Cascade<Dim>::Cascade(Fluide<Dim> *_f, double _bassin_x, double _bassin_y, double _bassin_z,
		      double _obstacle_x, double _obstacle_y, double _obstacle_z, 
		      double _pente_angle, double _pente_x, double _pente_y, double _pente_z) {
    f = _f;
    bassin_x = _bassin_x;
    bassin_y = _bassin_y;
    bassin_z = _bassin_z;
    obstacle_x = _obstacle_x;
    obstacle_y = _obstacle_y;
    obstacle_z = _obstacle_z;
    pente_angle = _pente_angle;
    pente_x = _pente_x;
    pente_y = _pente_y;
    pente_z = _pente_z;
}

template<unsigned int Dim>
Cascade<Dim>::~Cascade() {

}

template<unsigned int Dim>
void Cascade<Dim>::draw() {
    glPushMatrix();

    glColor3f(1, 1, 1);
    glTranslatef(0., 0., 0.1);

    /* Dessin du bassin */
    glEnable(GL_LIGHTING);
    glBegin (GL_QUADS);
    /* Fond */
    glNormal3f (0, 0, 1);
    glVertex3f (0, -bassin_y/2, 0);
    glVertex3f (0, bassin_y/2, 0);
    glVertex3f (bassin_x, bassin_y/2, 0);
    glVertex3f (bassin_x, -bassin_y/2, 0);

    glNormal3f (0, 0, -1);
    glVertex3f (0, -bassin_y/2, -0.001);
    glVertex3f (0, bassin_y/2, -0.001);
    glVertex3f (bassin_x, bassin_y/2, -0.001);
    glVertex3f (bassin_x, -bassin_y/2, -0.001);
    /* Faces internes */

    // Face arrière
    glNormal3f (1, 0, 0);
    glVertex3f (0, -bassin_y/2, 0);
    glVertex3f (0, bassin_y/2, 0);
    glVertex3f (0, bassin_y/2, bassin_z);
    glVertex3f (0, -bassin_y/2, bassin_z);

    glNormal3f (-1, 0, 0);
    glVertex3f (-0.001, -bassin_y/2, 0);
    glVertex3f (-0.001, bassin_y/2, 0);
    glVertex3f (-0.001, bassin_y/2, bassin_z);
    glVertex3f (-0.001, -bassin_y/2, bassin_z);

    // Face avant
    glNormal3f (1, 0, 0);
    glVertex3f (bassin_x, -bassin_y/2, 0);
    glVertex3f (bassin_x, bassin_y/2, 0);
    glVertex3f (bassin_x, bassin_y/2, bassin_z);
    glVertex3f (bassin_x, -bassin_y/2, bassin_z);  

    glNormal3f (-1, 0, 0);
    glVertex3f (bassin_x-0.001, -bassin_y/2, 0);
    glVertex3f (bassin_x-0.001, bassin_y/2, 0);
    glVertex3f (bassin_x-0.001, bassin_y/2, bassin_z);
    glVertex3f (bassin_x-0.001, -bassin_y/2, bassin_z);

    // Face gauche
    glNormal3f (0, -1, 0);
    glVertex3f (0, -bassin_y/2, 0);
    glVertex3f (bassin_x, -bassin_y/2, 0);
    glVertex3f (bassin_x, -bassin_y/2, bassin_z);
    glVertex3f (0, -bassin_y/2, bassin_z);

    glNormal3f (0, 1, 0);
    glVertex3f (0, -bassin_y/2+0.001, 0);
    glVertex3f (bassin_x, -bassin_y/2+0.001, 0);
    glVertex3f (bassin_x, -bassin_y/2+0.001, bassin_z);
    glVertex3f (0, -bassin_y/2+0.001, bassin_z);

    // Face droite
    glNormal3f (0, 1, 0);
    glVertex3f (0, bassin_y/2, 0);
    glVertex3f (bassin_x, bassin_y/2, 0);
    glVertex3f (bassin_x, bassin_y/2, bassin_z);
    glVertex3f (0, bassin_y/2, bassin_z);

    glNormal3f (0, -1, 0);
    glVertex3f (0, bassin_y/2-0.001, 0);
    glVertex3f (bassin_x, bassin_y/2-0.001, 0);
    glVertex3f (bassin_x, bassin_y/2-0.001, bassin_z);
    glVertex3f (0, bassin_y/2-0.001, bassin_z);

    // /* Dessin de l'obstacle */
    /* Haut */
    glNormal3f (0, 0, 1);
    glVertex3f (-obstacle_x/2, -obstacle_y/2, obstacle_z);
    glVertex3f (-obstacle_x/2, obstacle_y/2, obstacle_z);
    glVertex3f (obstacle_x/2, obstacle_y/2, obstacle_z);
    glVertex3f (obstacle_x/2, -obstacle_y/2, obstacle_z);

    glNormal3f (0, 0, -1);
    glVertex3f (-obstacle_x/2, -obstacle_y/2, obstacle_z-0.001);
    glVertex3f (-obstacle_x/2, obstacle_y/2, obstacle_z-0.001);
    glVertex3f (obstacle_x/2, obstacle_y/2, obstacle_z-0.001);
    glVertex3f (obstacle_x/2, -obstacle_y/2, obstacle_z-0.001);

    /* Faces latérales */
    glNormal3f (-1, 0, 0);
    glVertex3f (-obstacle_x/2, -obstacle_y/2, 0);
    glVertex3f (-obstacle_x/2, obstacle_y/2, 0);
    glVertex3f (-obstacle_x/2, obstacle_y/2, obstacle_z);
    glVertex3f (-obstacle_x/2, -obstacle_y/2, obstacle_z);  

    glNormal3f (1, 0, 0);
    glVertex3f (obstacle_x/2, -obstacle_y/2, 0);
    glVertex3f (obstacle_x/2, obstacle_y/2, 0);
    glVertex3f (obstacle_x/2, obstacle_y/2, obstacle_z);
    glVertex3f (obstacle_x/2, -obstacle_y/2, obstacle_z); 

    glNormal3f (0, -1, 0);
    glVertex3f (-obstacle_x/2, -obstacle_y/2, 0);
    glVertex3f (obstacle_x/2, -obstacle_y/2, 0);
    glVertex3f (obstacle_x/2, -obstacle_y/2, obstacle_z);
    glVertex3f (-obstacle_x/2, -obstacle_y/2, obstacle_z);

    glNormal3f (0, 1, 0);
    glVertex3f (-obstacle_x/2, obstacle_y/2, 0);
    glVertex3f (obstacle_x/2, obstacle_y/2, 0);
    glVertex3f (obstacle_x/2, obstacle_y/2, obstacle_z);
    glVertex3f (-obstacle_x/2, obstacle_y/2, obstacle_z);


    // /* Dessin de la pente */
    glNormal3f (sin(PI * pente_angle / 180), 0, cos(PI * pente_angle / 180));
    glVertex3f (0, -pente_y/2, bassin_z);
    glVertex3f (-pente_x * cos(PI * pente_angle/180), 
    		-pente_y/2, 
    		bassin_z + pente_x * sin(PI * pente_angle / 180));
    glVertex3f (-pente_x * cos(PI * pente_angle/180), 
    		pente_y/2, 
    		bassin_z + pente_x * sin(PI * pente_angle / 180));
    glVertex3f (0, pente_y/2, bassin_z);

    glNormal3f (sin(PI * pente_angle / 180), 0, -cos(PI * pente_angle / 180));
    glVertex3f (0, -pente_y/2, bassin_z-0.001);
    glVertex3f (-pente_x * cos(PI * pente_angle/180), 
    		-pente_y/2, 
    		bassin_z + pente_x * sin(PI * pente_angle / 180)-0.001);
    glVertex3f (-pente_x * cos(PI * pente_angle/180), 
    		pente_y/2, 
    		bassin_z + pente_x * sin(PI * pente_angle / 180)-0.001);
    glVertex3f (0, pente_y/2, bassin_z-0.001);

    

    /* Bords */
    // Bord gauche
    glNormal3f (0, 1, 0);
    glVertex3f (0, -pente_y/2, bassin_z);
    glVertex3f (pente_z * sin(PI * pente_angle / 180), 
    		-pente_y/2,
    		bassin_z + pente_z * cos(PI * pente_angle / 180));
    glVertex3f (pente_z * sin(PI * pente_angle / 180) - pente_x * cos (PI * pente_angle / 180),
    		-pente_y/2,
    		bassin_z + pente_z * cos(PI * pente_angle / 180) + pente_x * sin (PI * pente_angle / 180));
    glVertex3f (- pente_x * cos (PI * pente_angle / 180),
    		- pente_y/2,
    		bassin_z + pente_x * sin(PI * pente_angle / 180));

    glNormal3f (0, -1, 0);
    glVertex3f (0, -pente_y/2-0.001, bassin_z);
    glVertex3f (pente_z * sin(PI * pente_angle / 180), 
    		-pente_y/2-0.001,
    		bassin_z + pente_z * cos(PI * pente_angle / 180));
    glVertex3f (pente_z * sin(PI * pente_angle / 180) - pente_x * cos (PI * pente_angle / 180),
    		-pente_y/2-0.001,
    		bassin_z + pente_z * cos(PI * pente_angle / 180) + pente_x * sin (PI * pente_angle / 180));
    glVertex3f (- pente_x * cos (PI * pente_angle / 180),
    		- pente_y/2-0.001,
    		bassin_z + pente_x * sin(PI * pente_angle / 180));

    // Bord droit
    glNormal3f (0, -1, 0);
    glVertex3f (0, pente_y/2, bassin_z);
    glVertex3f (pente_z * sin(PI * pente_angle / 180), 
    		pente_y/2,
    		bassin_z + pente_z * cos(PI * pente_angle / 180));
    glVertex3f (pente_z * sin(PI * pente_angle / 180) - pente_x * cos (PI * pente_angle / 180),
    		pente_y/2,
    		bassin_z + pente_z * cos(PI * pente_angle / 180) + pente_x * sin (PI * pente_angle / 180));
    glVertex3f (- pente_x * cos (PI * pente_angle / 180),
    		pente_y/2,
    		bassin_z + pente_x * sin(PI * pente_angle / 180));

    glNormal3f (0, 1, 0);
    glVertex3f (0, pente_y/2+0.001, bassin_z);
    glVertex3f (pente_z * sin(PI * pente_angle / 180), 
    		pente_y/2+0.001,
    		bassin_z + pente_z * cos(PI * pente_angle / 180));
    glVertex3f (pente_z * sin(PI * pente_angle / 180) - pente_x * cos (PI * pente_angle / 180),
    		pente_y/2+0.001,
    		bassin_z + pente_z * cos(PI * pente_angle / 180) + pente_x * sin (PI * pente_angle / 180));
    glVertex3f (- pente_x * cos (PI * pente_angle / 180),
    		pente_y/2+0.001,
    		bassin_z + pente_x * sin(PI * pente_angle / 180));

    glEnd();

    /* On dessine les particules */
    typename list<Particule <Dim> *>::const_iterator it;
    list<Particule<Dim> *> partM = f->getParticulesMobiles();
    list<Particule<Dim> *> partI = f->getParticulesImmobiles();
    Materiau<Dim> * mat = f->getMateriau();
    for (it = partM.begin(); it != partM.end(); it++) {
	(*it)->draw(mat);
    }
    for (it = partI.begin(); it != partI.end(); it++) {
	(*it)->draw(mat);
    }
    glDisable (GL_LIGHTING);

    glPopMatrix();
}

template<unsigned int Dim>
void Cascade<Dim>::animate() {
    f->majDensitePression();
    f->majPositionVitesse();
}

template<unsigned int Dim>
const double & Cascade<Dim>::getBassinX() const
{
    return bassin_x;
}

template<unsigned int Dim>
const double & Cascade<Dim>::getBassinY() const
{
    return bassin_y;
}

template<unsigned int Dim>
const double & Cascade<Dim>::getBassinZ() const
{
    return bassin_z;
}

template<unsigned int Dim>
const double & Cascade<Dim>::getObstacleX() const
{
	return obstacle_x;
}

template<unsigned int Dim>
const double & Cascade<Dim>::getObstacleY() const
{
	return obstacle_y;
}

template<unsigned int Dim>
const double & Cascade<Dim>::getObstacleZ() const
{
	return obstacle_z;
}

template<unsigned int Dim>
const double & Cascade<Dim>::getPenteAngle() const
{
	return pente_angle;
}

template<unsigned int Dim>
const double & Cascade<Dim>::getPenteX() const
{
	return pente_x;
}

template<unsigned int Dim>
const double & Cascade<Dim>::getPenteY() const
{
	return pente_y;
}

template<unsigned int Dim>
const double & Cascade<Dim>::getPenteZ() const
{
	return pente_z;	
}


/*
 * Pente : a pour équation x*sin(alpha) + (z - bassin_z)*cos(alpha) = 0
 * -> en fonction de y, gérer le cas où on a x*sin() + (z - b_z)*cos() <= 0
 *
 * Les autres plans s'expriment simplement
 */
