#include "camera.h"
#include <iostream>
Camera::Camera()
{
    m_projection.setToIdentity();
    m_view.setToIdentity();
    m_model.setToIdentity();
    v_target = QVector3D(0.0, 0.0, 0.0);
    distance = 0.0;
    s_theta = 0.0;
    s_phi = 0.0;
    v_position = QVector3D(0.0, 0.0, 0.0);
    width = 0.0;
    height = 0.0;
}

Camera::Camera(QVector3D _target, double _distance, double _theta, double _phi, double angle, double aspect, double nearPlane, double farPlane, double _width, double _height)
{
    //Initialization
    v_target = QVector3D(_target);
    distance = _distance;
    s_theta = _theta;
    s_phi = _phi;

    //Projection Matrix
    m_projection.setToIdentity();
    m_projection.perspective(angle, aspect, nearPlane, farPlane);

    //Model Matrix = placement
    m_model.setToIdentity();
    m_model.translate(_target);
    m_model.rotate(s_theta, 1.0, 0.0, 0.0);
    m_model.rotate(s_phi, 0.0, 1.0, 0.0);
    m_model.translate(0.0, 0.0, distance);

    //View Matrix = vue depuis model
    m_view.setToIdentity();
    m_view = m_model.inverted();

    //Camera Position
    v_position = QVector3D(0.0,0.0,0.0);
    v_position = m_model*v_position;

    //Screen Size
    width = _width;
    height = _height;

}

Camera::~Camera(){}

void Camera::rotate( QPoint displacement )
{
    //Scale mouse coordinate
    double mouseSensitivity = 1;
    QVector2D scaleDisplacement;
    scaleDisplacement.setX( mouseSensitivity*displacement.x()/width );
    scaleDisplacement.setY( mouseSensitivity*displacement.y()/height );

    //Compute Rotation Angle
    QVector3D axeX(1.0,0.0,0.0);
    double angleRotX = scaleDisplacement.y()*180.0/M_PI;
    QVector3D axeY(0.0,1.0,0.0);
    double angleRotY = scaleDisplacement.x()*180.0/M_PI;

    //Update Camera position
    s_theta += angleRotX;
    s_phi += angleRotY;

    m_model.setToIdentity();
    m_model.translate(v_target);
    m_model.rotate(s_theta, axeX);
    m_model.rotate(s_phi, axeY);
    m_model.translate(v_position);

    //Update Camera view
    m_view = m_model.inverted();
}
