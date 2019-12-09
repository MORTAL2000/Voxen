#include "ray.h"

bool Ray::IntersectSphere(const QVector3D& pos, QVector3D r, QVector3D &isp1, QVector3D &isp2, double &t0, double &t1) {

    QVector3D o = m_origin-pos;
    QVector3D d = m_direction;


    r.setX(1.0/(r.x()*r.x()));
    r.setY(1.0/(r.y()*r.y()));
    r.setZ(1.0/(r.z()*r.z()));


    QVector3D rD = QVector3D(d.x()*r.x(), d.y()*r.y(), d.z()*r.z());
    QVector3D rO = QVector3D(o.x()*r.x(), o.y()*r.y(), o.z()*r.z());


    float A = QVector3D::dotProduct(d,rD);
    float B = 2.0*(QVector3D::dotProduct(d, rO));
    float C = QVector3D::dotProduct(o, rO) - 1.0;

    float S = (B*B - 4.0*A*C);

    if (S<=0) {
        isp1 = QVector3D(0,0,0);
        isp2 = QVector3D(0,0,0);
        t0 = 0;
        t1 = 0;
        return false;
    }

    t0 =  (-B - sqrt(S))/(2.0*A);
    t1 =  (-B + sqrt(S))/(2.0*A);

    isp1 = o+d*t0;
    isp2 = o+d*t1;

    return true;
}

bool Ray::IntersectBox(const QVector3D& pos, const QVector3D& bb, float& t0, float& t1)
{


        QVector3D min = pos-bb;
        QVector3D max = bb+pos;

        float tmin = (min.x() - m_origin.x()) / m_direction.x();
        float tmax = (max.x() - m_origin.x()) / m_direction.x();


        if (tmin > tmax) swap(tmin, tmax);

        float tymin = (min.y() - m_origin.y()) / m_direction.y();
        float tymax = (max.y() - m_origin.y()) / m_direction.y();

        if (tymin > tymax) swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax))
            return false;

        if (tymin > tmin)
            tmin = tymin;

        if (tymax < tmax)
            tmax = tymax;

        float tzmin = (min.z() - m_origin.z()) / m_direction.z();
        float tzmax = (max.z() - m_origin.z()) / m_direction.z();

        if (tzmin > tzmax) swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax))
            return false;

        if (tzmin > tmin)
            tmin = tzmin;

        if (tzmax < tmax)
            tmax = tzmax;

        t0=tmin;
        t1=tmax;




        m_hit = m_origin + m_direction*t0;


//        c = (b.aabb.vmin + b.aabb.vmax) * 0.5
          QVector3D p = m_hit - pos;
          QVector3D d = (min - max) * 0.5;
          double bias = 1.0001;

          m_N = QVector3D(
                      (int)(p.x() / abs(d.x()) * bias),
                      (int)(p.y() / abs(d.y()) * bias),
                      (int)(p.z() / abs(d.z()) * bias)).normalized();

        return true;
}
