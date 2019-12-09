#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <omp.h>
#include <QImage>
#include "source/raytracer/camera.h"
#include "source/raytracer/raytracerglobals.h"
#include "octtree.h"

class Raytracer
{
public:
    Raytracer();

    Camera m_camera;
    RayTracerGlobals m_globals;


    void Render(Octtree& tree, QImage& img);

};

#endif // RAYTRACER_H
