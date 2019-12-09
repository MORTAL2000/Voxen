#ifndef OCTTREE_H
#define OCTTREE_H

#include <QVector>
#include <QVector3D>
#include "source/raytracer/ray.h"
#include <QDebug>


class OctNode {
public:
    QVector3D center;
    float size;
    int level = 0;
    bool m_isEmpty = false;
    QVector<QVector3D> corners;
    int value = 0;
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

    QVector<OctNode> m_children;

    bool PointWithin(QVector3D p);
    void Insert(QVector3D point, int val, int maxLevel);

    int RayIntersect(Ray& r);

    void Subdivide();



};


class Octtree
{
public:
    Octtree();
    OctNode m_node;
    void Insert(QVector3D point, int val, int maxLevel);
    int RayIntersect(Ray& r);
    void InitRandomWorld(int N, float size, int val, int maxlevel);
};

#endif // OCTTREE_H
