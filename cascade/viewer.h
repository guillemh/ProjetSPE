/*
 * Main GL viewer class, based on the QGLViewer library.
 * 
 * QGLViewer is a Qt-based viewer, which provides an OpenGL rendering
 * context and GUI event management.
 * The documentation of the QGLViewer library can be found at the following 
 * url: http://www.libqglviewer.com
 */

#ifndef _VIEWER_
#define _VIEWER_

#include <QGLViewer/qglviewer.h>
#include <list>
#include "sceneCascade.h"

using namespace std;

/**
 * \class Viewer 
 * @brief Classe interagissant avec OpenGL pour la représentation d'objets
 *
 * Classe du plus haut niveau permettant de représenter une scène et de l'animer,
 * en la créant dans un main
 */

class Viewer : public QGLViewer
{
 public :
    /**
     * \brief Constructeur
     * 
     * Constructeur par défaut d'un objet de classe Viewer
     */
    Viewer ();

    /**
     * \brief Destructeur
     */
    virtual ~Viewer ();

 protected :

    /**
     * \brief Initialisation
     *
     * Initialise la scène
     */
    virtual void init();
		
    /**
     * \brief Représentation
     *
     * Représentation de la scène à l'écran
     */
    virtual void draw();
    
    /**
     * @brief Animation
     *
     * Animation des objets
     */
    virtual void animate();

    bool toogleWireframe;   /*!< Booléen indiquant ou non si on dessine la scène sous une forme de maillage ou de faces pleines */
    bool toogleLight;       /*!< Booléen indiquant si le modèle d'illumination d'OpenGL (modèle de Phong) doit être respecté */
    bool toogleRecord;      /*!< Enregistrer ou non une vidéo */

    /**
     * \brief Interaction avec l'utilisateur
     *
     * Méthode interagissant avec l'utilisateur et appliquant un traitement aux touches pressées du clavier
     * @param e Événement clavier considéré
     */
    virtual void keyPressEvent(QKeyEvent *e);

    virtual QString helpString() const;
    
    void interact();

    SceneCascade *s;    /*!< Objet contenant tous les éléments de la scène */
};

#endif
