#ifndef OCTTREE_H
#define OCTTREE_H

#include <QVector>
#include <QVector3D>
#include "source/raytracer/ray.h"
#include <QDebug>
#include "source/misc/util.h"
#include "source/misc/SimplexNoise.h"

class OctNode;

class OctData {
public:
    OctNode* hitNode = nullptr;
};



class OctNode {
public:
    QVector3D center;
    float size;
    int level = 0;
    bool m_isEmpty = false;
    QVector<QVector3D> corners;
    int value = 0;
    OctNode* m_parent = nullptr;
    OctNode() {

    }
    OctNode(QVector3D c, float s, int lev, int val) {
        center = c;
        size = s;
        level = lev;
        value = val;
        corners.resize(8);
        corners[0] = c + QVector3D(-size, -size, -size);
        corners[1] = c + QVector3D(-size, -size, size);
        corners[2] = c + QVector3D(size, -size, size);
        corners[3] = c + QVector3D(size, -size, -size);

        corners[4] = c + QVector3D(-size, size, -size);
        corners[5] = c + QVector3D(-size, size, size);
        corners[6] = c + QVector3D(size, size, size);
        corners[7] = c + QVector3D(size, size, -size);
    }
    bool m_isLeaf = true;

    QVector<OctNode*> m_children;

    bool PointWithin(QVector3D p);
    void Insert(QVector3D point, int val, int maxLevel);

    int RayIntersect(Ray& r, int maxLen, OctData& hitNode);
    bool RayIntersectSingle(Ray& r);

    void Subdivide();

    void cleanUp();

    float intersect(Ray *ray)
    {
        QVector3D d = Util::abss(center+ ray->m_currentPos) - QVector3D(size,size,size);// +ray->m_currentPos;
        float r=0;//m_pNormal.x();
        return min(max(d.x()-r,max(d.y()-r,d.z()-r)),0.0f) + Util::maxx(d,QVector3D(0,0,0)).length();
    }


    OctNode* rayMarch(Ray& ray, int ml);
};


class Octtree
{
public:
    Octtree();
    OctNode m_node;
    void Insert(QVector3D point, int val, int maxLevel);
    int RayIntersect(Ray& r, int maxLen, OctData& hitNode);
    void InitRandomWorld(int N, float size, int val, int maxlevel);

    int RayMarchSingle(Ray& r);

};

#endif // OCTTREE_H
