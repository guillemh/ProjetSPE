#ifndef VIEWER_H
#define VIEWER_H

#include <QKeyEvent>
#include <QGLWidget>
#include <QGLShaderProgram>
#include <QGLBuffer>
#include <QMatrix4x4>
#include <iostream>
#include <QTime>
#include <QMouseEvent>
#include <QVector2D>
#include <QVector4D>
#include "camera.h"

#include "../core/vecteur.hpp"
#include "../core/materiau.hpp"
#include "../core/fluide.hpp"

class Viewer : public QGLWidget
{
    Q_OBJECT        // must include this if you use Qt signals/slots

    public:
        Viewer(QWidget *parent);
        ~Viewer();

    private:
        //-----------------------------------------------
        //              SHADER DATA
        //-----------------------------------------------
        QGLShaderProgram m_program; //manipule les shaders

        QVector< QVector3D > m_vertices; //sommets des axes
        QVector< QVector4D > m_colors;  //couleurs des axes
        QVector< int > m_indices;   //indices des axes

        QVector< QVector3D > m_pts_vertices; //sommets des particules
        QVector< QVector4D > m_pts_colors;  //couleurs des particules
        QVector< int > m_pts_indices;   //indices des particules

        QGLBuffer m_vertexbuffer;   //buffer des sommets 
        QGLBuffer m_colorbuffer;    //buffer des couleurs 
        QGLBuffer m_indicebuffer;   //buffer des indices

        int m_matrix_location; //id of projection-view-model matrice sent to graphic card
        int m_vertices_attribute; //data id
        int m_colors_attribute; //color id


        //-----------------------------------------------
        //              CAMERA
        //-----------------------------------------------
	double dist;
        Camera camera3D;
        QMatrix4x4 model; //Position des points
        QPoint mousePosition;


        //-----------------------------------------------
        //             ANIMATION 
        //-----------------------------------------------
        bool animationStarted;
        int animationTimerId;
        int animationPeriod;

	Vecteur<3> d;
	Fluide<3> *f;

    protected:
        void resetView();
        void initializeGL();
        void resizeGL(int w, int h);
        void animate();
        void render();
        void keyPressEvent(QKeyEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        virtual void paintGL();
        void timerEvent(QTimerEvent *);
        void startAnimation();
        void stopAnimation();
};

#endif
