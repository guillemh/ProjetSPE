#include "viewer.hpp"

Viewer::Viewer(QWidget *parent):
    QGLWidget(parent),
    m_vertexbuffer(QGLBuffer::VertexBuffer), //specifie ce que vont contenir les buffer
    m_colorbuffer(QGLBuffer::VertexBuffer),
    m_indicebuffer(QGLBuffer::IndexBuffer)
{

    //Definition des sommets du repere
    m_vertices.push_back( QVector3D(0.0,0.0,0.0) );
    m_vertices.push_back( QVector3D(1.0,0.0,0.0) );
    m_vertices.push_back( QVector3D(0.0,0.0,0.0) );
    m_vertices.push_back( QVector3D(0.0,1.0,0.0) );
    m_vertices.push_back( QVector3D(0.0,0.0,0.0) );
    m_vertices.push_back( QVector3D(0.0,0.0,1.0) );

    //Definition des couleurs du sommet du repere
    m_colors.push_back( QVector4D(1.0,0.0,0.0,0.0) );
    m_colors.push_back( QVector4D(1.0,0.0,0.0,0.0) );
    m_colors.push_back( QVector4D(0.0,1.0,0.0,0.0) );
    m_colors.push_back( QVector4D(0.0,1.0,0.0,0.0) );
    m_colors.push_back( QVector4D(0.0,0.0,1.0,0.0) );
    m_colors.push_back( QVector4D(0.0,0.0,1.0,0.0) );

    //Definition des indices du sommet du repere
    m_indices.push_back(0);
    m_indices.push_back(1);
    m_indices.push_back(2);
    m_indices.push_back(3);
    m_indices.push_back(4);
    m_indices.push_back(5);

    //Initialisation de la position de la souris et de la camera
    mousePosition = QPoint(0, 0);
    dist = 3.0;
    camera3D = Camera();

    //Initialisation des parametres de lanimation
    animationTimerId = 0;
    stopAnimation();
    animationPeriod=40; // frequence : 25Hz = 40 ms
    
    Materiau<3> *m = new Materiau<3>(EAU);
    d = Vecteur<3>(2, 2, 5);
    f = new Fluide<3>(m, d, 0.05, m->getDensiteRepos(), m->getPression(), Vecteur<3>());
}

Viewer::~Viewer(){}

void Viewer::resetView()
{
    //Initialize camera
    QVector3D target(0.0,0.0,0.0);
    camera3D = Camera(target, dist, 0.0, 0.0, 60.0, width() / (double) height(), 0.01, 1000.0, width(), height());

    //Initialize model matrix : object position
    model.setToIdentity();
}

void Viewer::initializeGL()
{
    //Initialize camera
    QVector3D target(0.0,0.0,0.0);
    camera3D = Camera(target, dist, 0.0, 0.0, 60.0, width() / (double) height(), 0.01, 1000.0, width(), height());

    //Initialize model matrix : object position
    model.setToIdentity();

    //Initialization Shader
    m_program.addShaderFromSourceFile(QGLShader::Vertex, "./../shaders/vertex_shader.gl");
    m_program.addShaderFromSourceFile(QGLShader::Fragment, "./../shaders/fragment_shader.gl");
    //Link between shader -> pipeline building
    if (!m_program.link())
    {
        QString error = m_program.log();
        std::cout << error.toStdString() << std::endl;
    }

    //Passage de parametre fixes au shader
    m_program.bind();

    //Recuperation de lidentifiant de la uniform/attribute variable utilise dans paintGL
    m_matrix_location = m_program.uniformLocation("matrixpmv");
    if(m_matrix_location == -1)
    {
        std::cerr << "Identifiant de la variable uniform matrix pmv : -1" << std::endl;
    }

    m_vertices_attribute = m_program.attributeLocation("vertex");
    if(m_vertices_attribute == -1)
    {
        std::cerr << "Identifiant de la variable attribute vertex: -1" << std::endl;
    }

    m_colors_attribute = m_program.attributeLocation("color");
    if(m_colors_attribute == -1)
    {
        std::cerr << "Identifiant de la variable attribute color : -1" << std::endl;
    }

    //    //Envoie des parametre constants
    //    m_program.setUniformValue("fixed_color", QColor(Qt::red)); //couleur

    m_program.release();

    /* Création des axes */

    // Vertex buffer init
    // m_vertexbuffer.create();
    // m_vertexbuffer.bind(); //precise que lon va travailler dessus avec la fonction bind
    // m_vertexbuffer.allocate(m_vertices.constData(), m_vertices.size() * sizeof(QVector3D)); //allocation de la memoire
    // m_vertexbuffer.release(); //fin d'utilisation

    // // Color buffer init
    // m_colorbuffer.create();
    // m_colorbuffer.bind(); //precise que lon va travailler dessus avec la fonction bind
    // m_colorbuffer.allocate(m_colors.constData(), m_colors.size() * sizeof(QVector4D)); //allocation de la memoire
    // m_colorbuffer.release(); //fin d'utilisation

    // // Indices buffer init
    // m_indicebuffer.create();
    // m_indicebuffer.bind();
    // m_indicebuffer.allocate(m_indices.constData(), m_indices.size() * sizeof(GLuint));
    // m_indicebuffer.release();

    /* Création des particules */

    f->draw (&m_pts_vertices, &m_pts_colors, &m_pts_indices);

    int nbParticules = d(1) * d(2) * d(3);
    cout << nbParticules << endl;
    // Vertex buffer init
    m_vertexbuffer.create();
    m_vertexbuffer.bind(); //precise que lon va travailler dessus avec la fonction bind
    m_vertexbuffer.allocate(m_pts_vertices.constData(), nbParticules * sizeof(QVector3D)); //allocation de la memoire
    m_vertexbuffer.release(); //fin d'utilisation

    // Color buffer init
    m_colorbuffer.create();
    m_colorbuffer.bind(); //precise que lon va travailler dessus avec la fonction bind
    m_colorbuffer.allocate(m_pts_colors.constData(), nbParticules * sizeof(QVector4D)); //allocation de la memoire
    m_colorbuffer.release(); //fin d'utilisation

    // Indices buffer init
    m_indicebuffer.create();
    m_indicebuffer.bind();
    m_indicebuffer.allocate(m_pts_indices.constData(), nbParticules * sizeof(GLuint));
    m_indicebuffer.release();

    // Set up the rendering context, define display lists etc.:
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void Viewer::resizeGL(int w, int h)
{
    // setup viewport, projection etc.:
    glViewport(0, 0, (GLint)w, (GLint)h);
}

void Viewer::render()
{
    //Clear Screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer

    //-------------------
    //  Shader Pipeline
    //-------------------

    //Activer QGLShaderProram
    m_program.bind();

    //Envoie au shader des variables via leur identifiant
    m_program.setUniformValue(m_matrix_location, camera3D.projection() * camera3D.view());

    //indique à la carte graphique que lon travaille avec des vertex array

    /* Représentation des axes */

    glEnableClientState(GL_VERTEX_ARRAY);

    //Vertex buffer
    m_vertexbuffer.bind(); //active le buffer
    m_program.enableAttributeArray(m_vertices_attribute); //indique a opengl que l'on utilise un buffer comme variable
    m_program.setAttributeBuffer(m_vertices_attribute,GL_FLOAT, 0, 3); //appel des fonctions opengl
    m_vertexbuffer.release(); //desactive le buffer

    //Color buffer
    m_colorbuffer.bind();
    m_program.enableAttributeArray(m_colors_attribute);
    m_program.setAttributeBuffer(m_colors_attribute,GL_FLOAT, 0, 4);
    m_colorbuffer.release();

    //Vertex And Color indice buffer
    m_indicebuffer.bind();
    glDrawElements(GL_POINTS, m_pts_indices.size(), GL_UNSIGNED_INT, NULL);
    m_indicebuffer.release();

    glDisableClientState(GL_VERTEX_ARRAY);

    /* Représentation des particules */

    // glEnableClientState(GL_VERTEX_ARRAY);

    // //Vertex buffer
    // m_vertexbuffer.bind(); //active le buffer
    // m_program.enableAttributeArray(m_vertices_attribute); //indique a opengl que l'on utilise un buffer comme variable
    // m_program.setAttributeBuffer(m_vertices_attribute,GL_FLOAT, 0, 3); //appel des fonctions opengl
    // m_vertexbuffer.release(); //desactive le buffer

    // //Color buffer
    // m_colorbuffer.bind();
    // m_program.enableAttributeArray(m_colors_attribute);
    // m_program.setAttributeBuffer(m_colors_attribute,GL_FLOAT, 0, 4);
    // m_colorbuffer.release();

    // //Vertex And Color indice buffer
    // m_indicebuffer.bind();
    // glDrawElements(GL_POINTS, m_pts_indices.size(), GL_UNSIGNED_INT, NULL);
    // m_indicebuffer.release();

    // glDisableClientState(GL_VERTEX_ARRAY);

    //libere les buffer utilises
    m_program.disableAttributeArray(m_colors_attribute);
    m_program.disableAttributeArray(m_vertices_attribute);

    //Desactive QGLShaderProgram
    //Restaurer le contexte de rendu par défaut
    m_program.release();

    //-----------------------------
    //  Utilisation du Pipeline Fix
    //-----------------------------
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(camera3D.projection().constData());
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(camera3D.view().constData());
}

void Viewer::paintGL()
{
    // Mise à jour des tableaux de données
    f->draw (&m_pts_vertices, &m_pts_colors, &m_pts_indices);
    // Scene rendering
    render();
}

void Viewer::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_R) {
        resetView(); updateGL();
    } else if (e->key() == Qt::Key_A) {
        if (animationStarted == false) {
            startAnimation();
            animationStarted = true;
        } else {
            stopAnimation();
            animationStarted = false;
        }
    } else if (e->key() == Qt::Key_Up) {
	dist -= 0.1;
	resetView();
	updateGL();
    } else if (e->key() == Qt::Key_Down) {
	dist += 0.1;
	resetView();
	updateGL();
    } else {
        std::cout << "Key Not Mapped" << std::endl;
    }
}

void Viewer::mousePressEvent(QMouseEvent *event)
{
    //Get the focus
    this->setFocus();

    //Remember mouse click position
    mousePosition.setX(event->x());
    mousePosition.setY(event->y());
}

void Viewer::mouseMoveEvent(QMouseEvent *event)
{
    //Rotate camera with respect to mouse displacement
    QPoint newMousePosition( event->x(), event->y());
    camera3D.rotate(mousePosition - newMousePosition);
    mousePosition = newMousePosition;
    updateGL();
}


void Viewer::timerEvent(QTimerEvent *) 
{  
    if(animationStarted)
    {  
        update();
        updateGL();
    }  
}  

void Viewer::startAnimation()
{  
    //Start a timer event : each animation period timerEvent() is called
    animationTimerId = startTimer(animationPeriod);
    animationStarted = true;
}  

void Viewer::stopAnimation()
{  
    animationStarted = false;
    if(animationTimerId != 0) 
    {  
        killTimer(animationTimerId);
    }  
}  
