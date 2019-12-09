#include "raytracerglobals.h"

RayTracerGlobals::RayTracerGlobals()
{

}

void RayTracerGlobals::Sky(Ray* ray, float scale)
{

    DirectionalLight* light = static_cast<DirectionalLight*>(m_lights[0]);
        float sun = Util::minmax(QVector3D::dotProduct(light->m_direction.normalized(),ray->m_direction), 0.0f, 1.0 );
        QVector3D col = QVector3D(0.6,0.71,0.75) - ray->m_direction.y()*0.1*QVector3D(1.0,0.5,1.0) + 0.05*0.5*QVector3D(1,1,1);
        col += 1.0*QVector3D(1.0,.6,0.1)*pow( sun, 20.0 );


        // sun glare
//        col += 0.2*QVector3D(1.0,0.4,0.2)*pow( sun, 3.0 );
        ray->m_intensity = col*scale;
    return;
}

//bool Ray::::IntersectSphereFake(const QVector3D& pos, QVector3D r, QVector3D &isp1, QVector3D &isp2, double &t0, double &t1) {

