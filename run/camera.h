#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>
#include <QVector2D>
#include <cmath>

//Arcball camera

class Camera
{
    public:
        Camera();
        Camera(QVector3D _target, double _distance, double _theta, double _phi, double angle, double aspect, double nearPlane, double farPlane, double _width, double _height);
        ~Camera();

    private:
        QMatrix4x4 m_projection;
        QMatrix4x4 m_view;  //camera view
        QMatrix4x4 m_model; //camera position

        double s_theta; // x-rotation of the camera
        double s_phi; // y-rotation of the camera
        double distance; // distance from the target

        QVector3D v_position; // camera position
        QVector3D v_target; // camera target

        double width; //screen width
        double height; //screen height

    public:
        const QMatrix4x4 & projection() const { return m_projection; }
        QMatrix4x4 & projection() { return m_projection; }
        const QMatrix4x4 & model() const { return m_model; }
        QMatrix4x4 & model() { return m_model; }
        const QMatrix4x4 & view() const { return m_view; }
        QMatrix4x4 & view() { return m_view; }
        const QVector3D & target() const { return v_target; }
        const QVector3D & position() const { return v_position; }

        void rotate( QPoint displacement );
};

#endif // CAMERA_H
