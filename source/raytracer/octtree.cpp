#include "octtree.h"

Octtree::Octtree()
{

}

void Octtree::Insert(QVector3D point, int val, int maxLevel)
{
    m_node.Insert(point,val,maxLevel);
}

int Octtree::RayIntersect(Ray& r,int maxLevel, OctData& hitNode)
{
    return m_node.RayIntersect(r,maxLevel, hitNode);
}

void Octtree::InitRandomWorld(int N, float size, int val, int maxlevel)
{
    if (N==0)
        m_node = OctNode(QVector3D(0,0,0),size,0,0);
/*    for (int i=0;i<N;i++) {
        QVector3D p = (QVector3D(rand()%10000/10000.0,rand()%10000/10000.0,rand()%10000/10000.0)-QVector3D(0.5, 0.5, 0.5))*size;
            m_node.Insert(p,(rand()%val)+1,maxlevel);
    }*/
    int S = pow(2,maxlevel);

    SimplexNoise n;
    float scale = 0.783;
//    qDebug() << S;
//#pragma omp parallel for
    //if (N<S)
    {
    for (int x=0;x<S;x++)
        for (int z=0;z<S;z++) {
            QVector3D p = QVector3D(((x/(float)S)-0.5),
                                    0,
                                    ((z/(float)S)-0.5));
            float v = n.fractal(5, p.x()*scale, p.z()*scale+0.5235);
            v=pow(v*2,2);

            for (int y=0;y<(v*0.12+0.15)*S;y++) {
//                if (p.y()<v*0.2-0.4)
                p.setY((y/(float)S)-0.5);
                    m_node.Insert(p*size,abs(p.y()+0.5)*24+4,maxlevel);
//                m_node.Insert(p*size,6,maxlevel);
            }

            }
//    m_node.cleanUp();
    }
}

int Octtree::RayMarchSingle(Ray &ray)
{
   QVector3D isp;
   float t = 1;
   OctNode *winner = nullptr;
     //   Ray rotated;
   ray.m_currentPos = ray.m_origin;
        // Generate list with bb
        int cur = 0;
        int cnt = 60;

        for (int i=0;i<cnt;i++) {
            float precis = 0.004*t;
            float keep=1000.0;
            ray.m_curStep =t; //(ray.m_origin-m_objects[j]->m_position).length();
            ray.setCurrent(t);

            OctNode* w= nullptr;
            for (int i=0;i<8;i++) {


/*                float keep2 = m_node.intersect(&ray);
        //            float keep2 = ro->intersect(&ray);
                if (keep2<keep) {
                    keep = keep2;
                    w = ro;

                }

                if (keep2<precis) {
                    winner = w;
                    i=cnt;
                    break;

                }
            }
  */

            t=t+keep;



            //rotated = ray;

        }

        if (winner!=nullptr) {
      //      m_objectsFlattened.removeAll(winner);
        //    m_objectsFlattened.insert(0,winner);

            return true;

        }
        }

        return false;
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

//     value = val;

//    m_isEmpty = false;
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
            m_children[i]->Insert(point, val, maxLevel);
        }
    }
}

int OctNode::RayIntersect(Ray &r, int maxLen, OctData& hitNode)
{
    if (m_isEmpty)
        return 0;


    if (r.IntersectBox(center,QVector3D(size,size,size), r.m_t0, r.m_t1)) {
        if (m_children.count()==0) {
            hitNode.hitNode = this;
            return value;
        }
/*        if (level>maxLen) {
            return m_children[0].value;
        }
*/
        Ray keep = r;
        int kv = 0;
//        float t = Util::clamp(maxLen*abs(9.0/(sqrt(r.m_t0))),4,7);
        keep.m_t0 = 1E40;
        for (int i=0;i<8;i++) {
            OctData hn;
            int v = m_children[i]->RayIntersect(r, maxLen, hn);
            if (v!=0) {
                if (r.m_t0<keep.m_t0) {
                    keep = r;
                    kv = v;
                    hitNode.hitNode = hn.hitNode;
                }
            }
        }



        r = keep;





//        r.m_t0 = keep.m_t0;
        return kv;


    }
    return 0;
}

bool OctNode::RayIntersectSingle(Ray &r)
{
    return r.IntersectBox(center,QVector3D(size,size,size), r.m_t0, r.m_t1);
}

void OctNode::Subdivide()
{
    m_isLeaf = false;
    m_children.resize(8);
    float s2 = size/2.0f;
    for (int i=0;i<8;i++) {
        m_children[i] = new OctNode(center + (corners[i]-center)/2.0,s2, level+1, value);
        m_children[i]->m_parent = this;
    }

}

void OctNode::cleanUp()
{
    if (m_isLeaf)
        return;

    for (int i=0;i<8;i++)
        m_children[i]->cleanUp();

    // test if all are leaves and equal
    for (int i=0;i<8;i++)
        if (!m_children[i]->m_isLeaf)
            return;

    int val = m_children[0]->value;
    for (int i=1;i<8;i++)
            if (m_children[i]->value!=val)
            return;


    value = val;
    m_children.clear();
    m_isLeaf = true;
    m_isEmpty = value==0;
//    qDebug() << "CLeanup at level " << level;

}

OctNode *OctNode::rayMarch(Ray &ray, int ml)
{

}
