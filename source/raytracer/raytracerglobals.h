#ifndef RAYTRACERGLOBALS_H
#define RAYTRACERGLOBALS_H

#include <QVector3D>
#include <QVector>
#include <math.h>
#include <QMatrix3x3>
#include "source/misc/SimplexNoise.h"
#include "source/misc/util.h"

#include "camera.h"
#include "source/raytracer/ray.h"


class AbstractLight {
public:
    QVector3D m_color;
    QVector3D m_direction;
};

class DirectionalLight  : public AbstractLight{
public:

    DirectionalLight(QVector3D dir, QVector3D col) {
        m_color = col;
        m_direction = dir;
    }
};


class RayTracerGlobals
{
public:
    RayTracerGlobals();
    SimplexNoise m_noise;

    static const int output_type_c64 = 1;
    static const int output_type_pico8 = 2;
    static const int output_type_VGA = 3;

    double m_steps = 120;
    double m_shadowSteps = 60;
    float m_isPaused = 0;
    float m_skyScale = 1;
    float m_outputType = 0;
    float m_multicolor = 1;
    float m_dither = 0;
    float m_aspect = 1;
    float m_time = 0;
    QVector3D m_ditherStrength = QVector3D(0,0,0);
    float m_c64ImageType = 0;
    float m_shadowScale = 0.5;
    int m_width, m_height;
    QVector<int> m_c64Colors;
    QVector3D getPerlinNormal(QVector3D p, QVector3D n, QVector3D t, QVector3D bn, float s, float s2) {
        QVector3D p0 = n.normalized()+p;
        QVector3D p1 = (n+t*s).normalized()+p;
        QVector3D p2 = (n+bn*s).normalized()+p;
        p0 = p0*(1+s*m_noise.noise(s2*p0.x(), s2*p0.y(), s2*p0.z()));
        p1 = p1*(1+s*m_noise.noise(s2*p1.x(), s2*p1.y(), s2*p1.z()));
        p2 = p2*(1+s*m_noise.noise(s2*p2.x(), s2*p2.y(), s2*p2.z()));
        return QVector3D::crossProduct(p1-p0,p2-p0).normalized();
    }

    QVector3D m_ambient = QVector3D(0.3,0.3,0.3);

    QVector<AbstractLight*> m_lights;
    Camera* m_camera;


    void Sky(Ray* ray, float scale);


};

#endif // RAYTRACERGLOBALS_H
