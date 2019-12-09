#include "raytracer.h"

Raytracer::Raytracer()
{
    m_colors.InitC64();

}

void Raytracer::Render(Octtree& tree, QImage &img)
{
    m_camera.setupViewmatrix();


    if (oData.count()==0)
    {
        oData.resize(img.width()*img.height());
        for (int i=0;i<oData.count();i++)
            oData[i] = nullptr;
        oShadows.resize(img.width()*img.height());
        for (int i=0;i<oShadows.count();i++)
            oShadows[i] = nullptr;
        oNorm.resize(img.width()*img.height());
    }

#pragma omp parallel for
    for (int j=0;j<img.height();j++)
        for (int i=0;i<img.width();i++)
        {

            float x = i*m_globals.m_aspect;//*aspect;
            float y = j;//*aspect;

            QVector3D dir = m_camera.coord2ray(x,y,img.width(),img.height());
            Ray ray(m_camera.m_camera,dir);

            int val = 0;
            int idx = j*img.width() + i;
            OctData hn;
//            hn.hitNode = oData[idx];
            if (oData[idx]!=nullptr) {
                val = oData[idx]->RayIntersect(ray,100,hn);
                if ((oNorm[idx]-ray.m_N).lengthSquared()>0.5)
                    val=0; // CANCEL

//                oData[idx] = nullptr;

            }

            if (val == 0) {
                val = tree.RayIntersect(ray,100,hn);
                oData[idx] = hn.hitNode;
                oNorm[idx] = ray.m_N;


            }
            //            RayMarchSingle(ray, , nullptr,m_globals.m_steps,tid, QPoint(x,y));
            //          tmp[i+j*w] = ray.m_intensity;
           QColor c = Qt::black;
           m_globals.Sky(&ray,0.7);
           QVector3D sky = ray.m_intensity*255;

            if (val!=0) {
                float dist = Util::clamp(0.7*(ray.m_t0*0.01 - ray.m_hit.y()*0.02),0,1);
                c = m_colors.get(val).color;
                float l = Util::clamp(QVector3D::dotProduct(m_globals.m_lights[0]->m_direction, ray.m_N),0,1);
               // l = 1;


/*                Ray hit;
                hit.m_direction = m_globals.m_lights[0]->m_direction.normalized()*-1;
                hit.m_origin = ray.m_hit - hit.m_direction*0.001;
                OctData none;
                int treff = 0;
                if (oShadows[idx]!=nullptr) {
                    treff = oShadows[idx]->RayIntersect(hit,8, none);
                }
                if (treff==0) {
                   tree.RayIntersect(hit,8, none);
                }

                if (hit.m_t0<0) {
                    l=l*0.20;
                    oShadows[idx] = none.hitNode;
                }
*/


                c.setRed(c.red()*l);
                c.setGreen(c.green()*l);
                c.setBlue(c.blue()*l);

                c = Util::toColor(Util::fromColor(c)*(1-dist) +dist*sky);

            }
            else {
                c = Util::toColor(sky);
            }
            //Color c = Util::toColor(ray.m_intensity*256 + m_globals.m_ambient);
            img.setPixel(i,j,c.rgba());

        }
}

void Raytracer::RayMarch(Octtree& tree, QImage &img)
{
    m_camera.setupViewmatrix();


#pragma omp parallel for
    for (int j=0;j<img.height();j++)
        for (int i=0;i<img.width();i++)
        {

            float x = i*m_globals.m_aspect;//*aspect;
            float y = j;//*aspect;

            QVector3D dir = m_camera.coord2ray(x,y,img.width(),img.height());
            Ray ray(m_camera.m_camera,dir);

            OctData hn;
            //int val = tree.RayIntersect(ray,100,hn);
            int val = tree.RayMarchSingle(ray);

            //            RayMarchSingle(ray, , nullptr,m_globals.m_steps,tid, QPoint(x,y));
            //          tmp[i+j*w] = ray.m_intensity;
           QColor c = Qt::black;
            if (val!=0) {
                c = m_colors.get(val).color;
                float l = Util::clamp(QVector3D::dotProduct(m_globals.m_lights[0]->m_direction, ray.m_N),0,1);
                c.setRed(c.red()*l);
                c.setGreen(c.green()*l);
                c.setBlue(c.blue()*l);
            }
            else {
                m_globals.Sky(&ray,0.5);
                c = Util::toColor(ray.m_intensity*255);
            }
            //Color c = Util::toColor(ray.m_intensity*256 + m_globals.m_ambient);
            img.setPixel(i,j,c.rgba());

        }
}

