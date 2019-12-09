#ifndef RAY_H
#define RAY_H

#include <QVector>
#include <QVector3D>
#include <math.h>

class Ray {
public:
    QVector3D m_origin;
    QVector3D m_direction;
    QVector3D m_intensity = QVector3D(0,0,0);
    QVector3D m_isp1, m_isp2;
    QVector3D m_N;
    QVector3D m_hit;
    float m_t0, m_t1;
    bool m_intersects = false;
    float m_reflect = 3;
    double m_z = 1E20;


    float m_curStep = 0;
    QVector3D m_currentPos;
    QVector3D m_currentPosUnrotated;

    Ray() {}
    void swap(float& a, float& b) {
        float c=a;
        a=b;
        b=c;
    }

    void setCurrent(float t) {
        m_currentPos  = m_origin + m_direction*t;
    }

    Ray(QVector3D pos, QVector3D dir) {
        m_origin = pos;
        m_direction = dir;
    }
    Ray(QVector3D pos, QVector3D dir, QVector3D I) {
        m_origin = pos;
        m_direction = dir;
        m_intensity = I;
    }

    Ray Rotate(QMatrix4x4& rotmat, QVector3D pos) {
        Ray r(rotmat*(m_currentPos+pos)-pos,rotmat*m_direction);
        r.m_currentPos = r.m_origin;
        return r;
    }

    bool IntersectSphere(const QVector3D& pos, QVector3D r,QVector3D& isp1,QVector3D& isp2, double& t0, double& t1);
    bool IntersectBox(const QVector3D& pos, const QVector3D& bb, float& t0, float& t1);

};

#endif // RAY_H
