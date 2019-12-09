#include "raytracer.h"

Raytracer::Raytracer()
{

}

void Raytracer::Render(Octtree& tree, QImage &img)
{
#pragma omp parallel for
    for (int j=0;j<img.height();j++)
        for (int i=0;i<img.width();i++)
        {

            float x = i*m_globals.m_aspect;//*aspect;
            float y = j;//*aspect;

            QVector3D dir = m_camera.coord2ray(x,y,img.width(),img.height());;
            Ray ray(m_camera.m_camera,dir);
            ray.m_reflect=3;
            int tid = omp_get_thread_num();

            //            float m_z = 1E20;
            //int tid = 0;
           int val = tree.RayIntersect(ray);
            //            RayMarchSingle(ray, , nullptr,m_globals.m_steps,tid, QPoint(x,y));
            //          tmp[i+j*w] = ray.m_intensity;
            if (val==1)// && ray.m_intersects)
                ray.m_intensity = QVector3D(0.5,1,0.2);
            QColor c = Util::toColor(ray.m_intensity*256 + m_globals.m_ambient);
            img.setPixel(i,j,c.rgba());

        }
}

