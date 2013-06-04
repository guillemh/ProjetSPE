#ifndef _SKYBOX_
#define _SKYBOX_

#include <GL/glut.h>
#include "cascade.hpp"
#include <map>

/**
 * \class Skybox Classe respresentant la skybox associee a la scene
 */
class Skybox {
 public :
    enum TextureId {
	TEX_CRATE, 
    };


    /**
     * \brief Constructeur
     *
     * Constructeur par défaut d'un objet de classe Skybox
     */
    Skybox(const Cascade<3> *c);

    /**
     * \brief Destructeur
     */
    ~Skybox();

    /**
     * \brief Représentation 
     *
     * Représentation de la skybox
     */
    void init();
    void loadTexture(TextureId texId, const char *filename);
    void draw();
    void animate();

 private :
    Cascade<3> *c;
    double box_x;
    double box_y;
    double box_z;

 public:
    // activated by the 'f' key
    GLint filteringMode;
    void toogleFiltering();
    void setFiltering();
    void setFilteringMipmap();
 
 private:
    // association bewteen a TextureId and its OpenGL texture id
    // (generated with glGenTextures. cf the loadTexture method)
    std::map<TextureId, GLuint> textures;
    
};

#endif
