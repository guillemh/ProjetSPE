#include "../core/particule.hpp"

template<unsigned int Dim>
Cascade<Dim>::Cascade(Fluide<Dim> *_f) {
    f = _f ;
    bassin_x = 0.5;
    bassin_y = 0.5;
    bassin_z = 0.5;
    arps = false;
}

template<unsigned int Dim>
Cascade<Dim>::Cascade(Fluide<Dim> *_f, double _bassin_x, double _bassin_y, double _bassin_z) {
    f = _f;
    bassin_x = _bassin_x;
    bassin_y = _bassin_y;
    bassin_z = _bassin_z;
}

template<unsigned int Dim>
Cascade<Dim>::~Cascade() {

}

template<unsigned int Dim>
void Cascade<Dim>::draw() {
   
    glEnable(GL_LIGHTING);
    f->draw();

    glPushMatrix();
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0, 1.0, 1.0, 0.1);

    /* Cascade superieure */

    /* Dessin du bassin */
    glEnable(GL_LIGHTING);
    glBegin (GL_QUADS);
    /* Fond */
    glNormal3f (0, 0, 1);
    glVertex3f (-bassin_x/2, -bassin_y/2, -0.025);
    glVertex3f (-bassin_x/2, bassin_y/2, -0.025);
    glVertex3f (bassin_x/2, bassin_y/2, -0.025);
    glVertex3f (bassin_x/2, -bassin_y/2, -0.025);

    /*glNormal3f (0, 0, -1);
      glVertex3f (-bassin_x/2, -bassin_y/2, -0.001);
      glVertex3f (-bassin_x/2, bassin_y/2, -0.001);
      glVertex3f (bassin_x/2, bassin_y/2, -0.001);
      glVertex3f (bassin_x/2, -bassin_y/2, -0.001);*/

    /* Faces internes */

    // Face arrière
    glNormal3f (1, 0, 0);
    glVertex3f (-bassin_x/2, -bassin_y/2, -0.025);
    glVertex3f (-bassin_x/2, bassin_y/2,-0.025 );
    glVertex3f (-bassin_x/2, bassin_y/2, bassin_z-0.025);
    glVertex3f (-bassin_x/2, -bassin_y/2, bassin_z-0.025);

    /*glNormal3f (-1, 0, 0);
      glVertex3f (-bassin_x/2-0.001, -bassin_y/2, 0);
      glVertex3f (-bassin_x/2-0.001, bassin_y/2, 0);
      glVertex3f (-bassin_x/2-0.001, bassin_y/2, bassin_z);
      glVertex3f (-bassin_x/2-0.001, -bassin_y/2, bassin_z);*/

    // Face avant

    glNormal3f (1, 0, 0);
    glVertex3f (bassin_x/2, -bassin_y/2, -0.025);
    glVertex3f (bassin_x/2, 0-bassin_y/5, -0.025);
    glVertex3f (bassin_x/2, 0-bassin_y/5, bassin_z-0.025);
    glVertex3f (bassin_x/2, -bassin_y/2, bassin_z-0.025);  

    glNormal3f (1, 0, 0);
    glVertex3f (bassin_x/2, 0+bassin_y/5, 0-0.025);
    glVertex3f (bassin_x/2, bassin_y/2, 0-0.025);
    glVertex3f (bassin_x/2, bassin_y/2, bassin_z-0.025);
    glVertex3f (bassin_x/2, 0+bassin_y/5, bassin_z-0.025);  

    glNormal3f (1, 0, 0);
    glVertex3f (bassin_x/2, 0-bassin_y/5, bassin_z/5-0.025);
    glVertex3f (bassin_x/2, 0+bassin_y/5, bassin_z/5-0.025);
    glVertex3f (bassin_x/2, 0+bassin_y/5, bassin_z-0.025);
    glVertex3f (bassin_x/2, 0-bassin_y/5, bassin_z-0.025); 


    // Face gauche
    glNormal3f (0, -1, 0);
    glVertex3f (-bassin_x/2, -bassin_y/2, 0-0.025);
    glVertex3f (bassin_x/2, -bassin_y/2, 0-0.025);
    glVertex3f (bassin_x/2, -bassin_y/2, bassin_z-0.025);
    glVertex3f (-bassin_x/2, -bassin_y/2, bassin_z-0.025);

    /*glNormal3f (0, 1, 0);
      glVertex3f (-bassin_x/2, -bassin_y/2+0.001, 0);
      glVertex3f (bassin_x/2, -bassin_y/2+0.001, 0);
      glVertex3f (bassin_x/2, -bassin_y/2+0.001, bassin_z);
      glVertex3f (-bassin_x/2, -bassin_y/2+0.001, bassin_z);*/

    // Face droite
    glNormal3f (0, 1, 0);
    glVertex3f (-bassin_x/2, bassin_y/2, 0-0.025);
    glVertex3f (bassin_x/2, bassin_y/2, 0-0.025);
    glVertex3f (bassin_x/2, bassin_y/2, bassin_z-0.025);
    glVertex3f (-bassin_x/2, bassin_y/2, bassin_z-0.025);

    /* glNormal3f (0, -1, 0);
       glVertex3f (-bassin_x/2, bassin_y/2-0.001, 0);
       glVertex3f (bassin_x/2, bassin_y/2-0.001, 0);
       glVertex3f (bassin_x/2, bassin_y/2-0.001, bassin_z);
       glVertex3f (-bassin_x/2, bassin_y/2-0.001, bassin_z);*/

    glColor3f(1, 1, 1);

    /* Cascade intermédiaire */

    /* Dessin du bassin */
    glEnable(GL_LIGHTING);
    glBegin (GL_QUADS);
    /* Fond */
    glNormal3f (0, 0, 1);
    glVertex3f (bassin_x/2, -bassin_y/3, -1.0);
    glVertex3f (bassin_x/2, bassin_y/3, -1.0);
    glVertex3f (2*bassin_x, bassin_y/3, -1.0);
    glVertex3f (2*bassin_x, -bassin_y/3, -1.0);

    glNormal3f (0, 0, -1);
    glVertex3f (bassin_x/2, -bassin_y/3, -1.0-0.001);
    glVertex3f (bassin_x/2, bassin_y/3, -1.0-0.001);
    glVertex3f (2*bassin_x, bassin_y/3, -1.0-0.001);
    glVertex3f (2*bassin_x, -bassin_y/3, -1.0-0.001);
    /* Faces internes */

    // Face arrière
    glNormal3f (1, 0, 0);
    glVertex3f (bassin_x/2, -bassin_y/3, -1.0);
    glVertex3f (bassin_x/2, bassin_y/3, -1.0);
    glVertex3f (bassin_x/2, bassin_y/3, -1.0+bassin_z/3);
    glVertex3f (bassin_x/2, -bassin_y/3, -1.0+bassin_z/3);

    glNormal3f (-1, 0, 0);
    glVertex3f (bassin_x/2-0.001, -bassin_y/3, -1.0);
    glVertex3f (bassin_x/2-0.001, bassin_y/3, -1.0);
    glVertex3f (bassin_x/2-0.001, bassin_y/3, -1.0+bassin_z/3);
    glVertex3f (bassin_x/2-0.001, -bassin_y/3, -1.0+bassin_z/3);

    // Face avant
    glNormal3f (1, 0, 0);
    glVertex3f (2*bassin_x, -bassin_y/3, -1.0);
    glVertex3f (2*bassin_x, bassin_y/3, -1.0);
    glVertex3f (2*bassin_x, bassin_y/3, -1.0+bassin_z/7);
    glVertex3f (2*bassin_x, -bassin_y/3, -1.0+bassin_z/7);  

    glNormal3f (-1, 0, 0);
    glVertex3f (2*bassin_x-0.001, -bassin_y/3, -1.0);
    glVertex3f (2*bassin_x-0.001, bassin_y/3, -1.0);
    glVertex3f (2*bassin_x-0.001, bassin_y/3, -1.0+bassin_z/7);
    glVertex3f (2*bassin_x-0.001, -bassin_y/3, -1.0+bassin_z/7);  
    

    // Face gauche
    glNormal3f (0, -1, 0);
    glVertex3f (bassin_x/2, -bassin_y/3, -1.0);
    glVertex3f (2*bassin_x, -bassin_y/3, -1.0);
    glVertex3f (2*bassin_x, -bassin_y/3, -1.0+bassin_z/3);
    glVertex3f (bassin_x/2, -bassin_y/3, -1.0+bassin_z/3);

    glNormal3f (0, 1, 0);
    glVertex3f (bassin_x/2, -bassin_y/3+0.001, -1.0);
    glVertex3f (2*bassin_x, -bassin_y/3+0.001, -1.0);
    glVertex3f (2*bassin_x, -bassin_y/3+0.001, -1.0+bassin_z/3);
    glVertex3f (bassin_x/2, -bassin_y/3+0.001, -1.0+bassin_z/3);

    // Face droite
    glNormal3f (0, 1, 0);
    glVertex3f (bassin_x/2, bassin_y/3, -1.0);
    glVertex3f (2*bassin_x, bassin_y/3, -1.0);
    glVertex3f (2*bassin_x, bassin_y/3, -1.0+bassin_z/3);
    glVertex3f (bassin_x/2, bassin_y/3, -1.0+bassin_z/3);

    glNormal3f (0, -1, 0);
    glVertex3f (bassin_x/2, bassin_y/3-0.001, -1.0);
    glVertex3f (2*bassin_x, bassin_y/3-0.001, -1.0);
    glVertex3f (2*bassin_x, bassin_y/3-0.001, -1.0+bassin_z/3);
    glVertex3f (bassin_x/2, bassin_y/3-0.001, -1.0+bassin_z/3);


    /* Cascade inferieure 1 */

    /* Dessin du bassin */
    glEnable(GL_LIGHTING);
    glBegin (GL_QUADS);
    /* Fond */
    glNormal3f (0, 0, 1);
    glVertex3f (2*bassin_x, -bassin_y/2, -2.0);
    glVertex3f (2*bassin_x, bassin_y/2, -2.0);
    glVertex3f (4*bassin_x, bassin_y/2, -2.0);
    glVertex3f (4*bassin_x, -bassin_y/2, -2.0);

    glNormal3f (0, 0, -1);
    glVertex3f (2*bassin_x, -bassin_y/2, -0.001-2.0);
    glVertex3f (2*bassin_x, bassin_y/2, -0.001-2.0);
    glVertex3f (4*bassin_x, bassin_y/2, -0.001-2.0);
    glVertex3f (4*bassin_x, -bassin_y/2, -0.001-2.0);
    /* Faces internes */

    // Face arrière
    glNormal3f (1, 0, 0);
    glVertex3f (2*bassin_x, -bassin_y/2, 0-2.0);
    glVertex3f (2*bassin_x, bassin_y/2, 0-2.0);
    glVertex3f (2*bassin_x, bassin_y/2, bassin_z/5-2.0);
    glVertex3f (2*bassin_x, -bassin_y/2, bassin_z/5-2.0);

    glNormal3f (-1, 0, 0);
    glVertex3f (2*bassin_x-0.001, -bassin_y/2, 0-2.0);
    glVertex3f (2*bassin_x-0.001, bassin_y/2, 0-2.0);
    glVertex3f (2*bassin_x-0.001, bassin_y/2, bassin_z/5-2.0);
    glVertex3f (2*bassin_x-0.001, -bassin_y/2, bassin_z/5-2.0);

    // Face avant
    glNormal3f (1, 0, 0);
    glVertex3f (4*bassin_x, -bassin_y/2, 0-2.0);
    glVertex3f (4*bassin_x, bassin_y/2, 0-2.0);
    glVertex3f (4*bassin_x, bassin_y/2, bassin_z/5-2.0);
    glVertex3f (4*bassin_x, -bassin_y/2, bassin_z/5-2.0);  

    glNormal3f (-1, 0, 0);
    glVertex3f (4*bassin_x, -bassin_y/2, 0-2.0);
    glVertex3f (4*bassin_x, bassin_y/2, 0-2.0);
    glVertex3f (4*bassin_x, bassin_y/2, bassin_z/5-2.0);
    glVertex3f (4*bassin_x, -bassin_y/2, bassin_z/5-2.0);

    // Face gauche
    glNormal3f (0, -1, 0);
    glVertex3f (2*bassin_x, -bassin_y/2, 0-2.0);
    glVertex3f (4*bassin_x, -bassin_y/2, 0-2.0);
    glVertex3f (4*bassin_x, -bassin_y/2, bassin_z/5-2.0);
    glVertex3f (2*bassin_x, -bassin_y/2, bassin_z/5-2.0);

    glNormal3f (0, 1, 0);
    glVertex3f (2*bassin_x, -bassin_y/2+0.001, 0-2.0);
    glVertex3f (4*bassin_x, -bassin_y/2+0.001, 0-2.0);
    glVertex3f (4*bassin_x, -bassin_y/2+0.001, bassin_z/5-2.0);
    glVertex3f (2*bassin_x, -bassin_y/2+0.001, bassin_z/5-2.0);

    // Face droite
    glNormal3f (0, 1, 0);
    glVertex3f (2*bassin_x, bassin_y/2, 0-2.0);
    glVertex3f (4*bassin_x, bassin_y/2, 0-2.0);
    glVertex3f (4*bassin_x, bassin_y/2, bassin_z/5-2.0);
    glVertex3f (2*bassin_x, bassin_y/2, bassin_z/5-2.0);

    glNormal3f (0, -1, 0);
    glVertex3f (2*bassin_x, bassin_y/2-0.001, 0-2.0);
    glVertex3f (4*bassin_x, bassin_y/2-0.001, 0-2.0);
    glVertex3f (4*bassin_x, bassin_y/2-0.001, bassin_z/5-2.0);
    glVertex3f (2*bassin_x, bassin_y/2-0.001, bassin_z/5-2.0);


    /* Cascade inferieure 2 */

    /* Dessin du bassin */
    glEnable(GL_LIGHTING);
    glBegin (GL_QUADS);
    /* Fond */
    glNormal3f (0, 0, 1);
    glVertex3f (bassin_x, -bassin_y, -3.0+0.001);
    glVertex3f (bassin_x, bassin_y, -3.0+0.001);
    glVertex3f (6*bassin_x, bassin_y, -3.0+0.001);
    glVertex3f (6*bassin_x, -bassin_y, -3.0+0.001);

    glNormal3f (0, 0, -1);
    glVertex3f (bassin_x, -bassin_y, -3.0);
    glVertex3f (bassin_x, bassin_y, -3.0);
    glVertex3f (6*bassin_x, bassin_y, -3.0);
    glVertex3f (6*bassin_x, -bassin_y, -3.0);
    /* Faces internes */

    // Face arrière
    glNormal3f (1, 0, 0);
    glVertex3f (bassin_x, -bassin_y, 0-3.0);
    glVertex3f (bassin_x, bassin_y, 0-3.0);
    glVertex3f (bassin_x, bassin_y, bassin_z/5-3.0);
    glVertex3f (bassin_x, -bassin_y, bassin_z/5-3.0);

    glNormal3f (-1, 0, 0);
    glVertex3f (bassin_x-0.001, -bassin_y, 0-3.0);
    glVertex3f (bassin_x-0.001, bassin_y, 0-3.0);
    glVertex3f (bassin_x-0.001, bassin_y, bassin_z/5-3.0);
    glVertex3f (bassin_x-0.001, -bassin_y, bassin_z/5-3.0);

    // Face avant
    glNormal3f (1, 0, 0);
    glVertex3f (6*bassin_x, -bassin_y, 0-3.0);
    glVertex3f (6*bassin_x, bassin_y, 0-3.0);
    glVertex3f (6*bassin_x, bassin_y, bassin_z/5-3.0);
    glVertex3f (6*bassin_x, -bassin_y, bassin_z/5-3.0);  

    glNormal3f (-1, 0, 0);
    glVertex3f (6*bassin_x, -bassin_y, 0-3.0);
    glVertex3f (6*bassin_x, bassin_y, 0-3.0);
    glVertex3f (6*bassin_x, bassin_y, bassin_z/5-3.0);
    glVertex3f (6*bassin_x, -bassin_y, bassin_z/5-3.0);

    // Face gauche
    glNormal3f (0, -1, 0);
    glVertex3f (bassin_x, -bassin_y, 0-3.0);
    glVertex3f (6*bassin_x, -bassin_y, 0-3.0);
    glVertex3f (6*bassin_x, -bassin_y, bassin_z/5-3.0);
    glVertex3f (bassin_x, -bassin_y, bassin_z/5-3.0);

    glNormal3f (0, 1, 0);
    glVertex3f (bassin_x, -bassin_y+0.001, 0-3.0);
    glVertex3f (6*bassin_x, -bassin_y+0.001, 0-3.0);
    glVertex3f (6*bassin_x, -bassin_y+0.001, bassin_z/5-3.0);
    glVertex3f (bassin_x, -bassin_y+0.001, bassin_z/5-3.0);

    // Face droite
    glNormal3f (0, 1, 0);
    glVertex3f (bassin_x, bassin_y, 0-3.0);
    glVertex3f (6*bassin_x, bassin_y, 0-3.0);
    glVertex3f (6*bassin_x, bassin_y, bassin_z/5-3.0);
    glVertex3f (bassin_x, bassin_y, bassin_z/5-3.0);

    glNormal3f (0, -1, 0);
    glVertex3f (bassin_x, bassin_y-0.001, 0-3.0);
    glVertex3f (6*bassin_x, bassin_y-0.001, 0-3.0);
    glVertex3f (6*bassin_x, bassin_y-0.001, bassin_z/5-3.0);
    glVertex3f (bassin_x, bassin_y-0.001, bassin_z/5-3.0);

    glEnd();

    glDisable (GL_LIGHTING);

    glPopMatrix();
}

template<unsigned int Dim>
void Cascade<Dim>::animate(bool arps) {
    if (arps) {
        f->schemaIntegration();
    } else {
        f->majDensitePression();
        f->majPositionVitesse();
    }
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
