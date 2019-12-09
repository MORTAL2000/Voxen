#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <omp.h>
#include <QImage>
#include "source/raytracer/camera.h"
#include "source/raytracer/raytracerglobals.h"
#include "octtree.h"
#include "source/misc/lcolorlist.h"


class Raytracer
{
public:
    Raytracer();

    LColorList m_colors;
    Camera m_camera;
    RayTracerGlobals m_globals;
    QVector<OctNode*> oData;
    QVector<OctNode*> oShadows;
    QVector<QVector3D> oNorm;

    void Render(Octtree& tree, QImage& img);
    void RayMarch(Octtree& tree, QImage &img);

};

#endif // RAYTRACER_H
