/*
 * Main GL viewer class, based on the QGLViewer library.
 * 
 * QGLViewer is a Qt-based viewer, which provides an OpenGL rendering
 * context and GUI event management.
 * The documentation of the QGLViewer library can be found at the following 
 * url: http://www.libqglviewer.com
 */

#ifndef _VIEWER_CASCADE_
#define _VIEWER_CASCADE_

#include <QGLViewer/qglviewer.h>
#include <list>
#include "sceneCascade.h"

using namespace std;

/**
 * \class ViewerCascade
 * @brief Classe interagissant avec OpenGL pour la représentation d'objets
 *
 * Classe du plus haut niveau permettant de représenter une scène et de l'animer,
 * en la créant dans un main
 */

class ViewerCascade : public QGLViewer
{
 public :
    /**
     * \brief Constructeur
     * 
     * Constructeur par défaut d'un objet de classe Viewer
     */
    ViewerCascade();

    /**
     * \brief Destructeur
     */
    virtual ~ViewerCascade();

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
	int select;

    /**
     * \brief Interaction avec l'utilisateur
     *
     * Méthode interagissant avec l'utilisateur et appliquant un traitement aux touches pressées du clavier
     * @param e Événement clavier considéré
     */
    virtual void keyPressEvent(QKeyEvent *e);

    /**
     * @brief Fenêtre d'aide
     *
     * Définit le texte présent dans la fenêtre d'aide de QglViewer,
     * affichée avec la touche 'H'
     * @return Le texte en question
     */
    virtual QString helpString() const;
    
    /**
     * @brief Interaction utilisateur
     *
     * Déclenche l'interaction utilisateur sur le terminal
     */
    void interact();

    SceneCascade *s;    /*!< Objet contenant tous les éléments de la scène */
};

#endif
