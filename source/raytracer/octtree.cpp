#include "octtree.h"

Octtree::Octtree()
{

}

void Octtree::Insert(QVector3D point, int val, int maxLevel)
{
    m_node.Insert(point,val,maxLevel);
}

int Octtree::RayIntersect(Ray& r)
{
    return m_node.RayIntersect(r);
}

void Octtree::InitRandomWorld(int N, float size, int val, int maxlevel)
{
    m_node = OctNode(QVector3D(0,0,0),size,0,0);
    for (int i=0;i<N;i++) {
        QVector3D p = (QVector3D(rand()%10000/10000.0,rand()%10000/10000.0,rand()%10000/10000.0)-QVector3D(0.5, 0.5, 0.5))*size;
            m_node.Insert(p,val,maxlevel);
    }
}

bool OctNode::PointWithin(QVector3D p)
{
    QVector3D c = p - center;
    if (abs(c.x())<size && abs(c.y())<size && abs(c.z())<size)
        return true;

    return false;
}

void OctNode::Insert(QVector3D point, int val, int maxLevel)
{
    if (!PointWithin(point))
        return;


    if (level == maxLevel) {
        value = val;
        m_isEmpty = false;
    }
    else {
        if (m_isLeaf) {
            Subdivide();
        }

        m_isEmpty = false;

        for (int i=0;i<8;i++) {
            m_children[i].Insert(point, val, maxLevel);
        }
    }
}

int OctNode::RayIntersect(Ray &r)
{
    if (m_isEmpty)
        return 0;

    if (r.IntersectBox(center,QVector3D(size,size,size),r.m_isp1, r.m_isp2, r.m_t0, r.m_t1)) {
       // if (value!=0)
         //   qDebug() << center << size << level << value << m_children.count();
        if (m_children.count()==0) {
//            if (value!=0)
  //              qDebug() << "FOUND one " << value;
            return value;
        }

        Ray keep = r;
        int kv = 0;
        keep.m_t0 = 1E40;
        for (int i=0;i<8;i++) {

            int v = m_children[i].RayIntersect(r);
            if (v!=0) {
//                qDebug() << v;
                if (r.m_t0<keep.m_t0) {
                    keep = r;
                    kv = v;
                }
            }
        }
       // if (level==0 && kv!=0) qDebug() << kv;

//        if (kv!=0)
  //          qDebug() << "Child winner: " <<kv << level;
        return kv;


    }
    return 0;
}

void OctNode::Subdivide()
{
    m_isLeaf = false;
    m_children.resize(8);
    float s2 = size/2.0f;
    for (int i=0;i<8;i++)
        m_children[i] = OctNode(center + (corners[i]-center)/2.0,s2, level+1, value);

}
