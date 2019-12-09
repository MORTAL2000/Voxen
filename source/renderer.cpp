#include "renderer.h"

Renderer::Renderer()
{
    m_img = QImage(m_width,m_height, QImage::Format_RGB32);

}

void Renderer::InitWorld()
{
    m_tree.InitRandomWorld(5, 40,1,3);
    m_rt.m_camera.m_camera = QVector3D(50,50,50);
    m_rt.m_camera.m_target = QVector3D(0,0,0);
}

void Renderer::run()
{
    while (!m_done) {


 //       m_img.fill(QColor(255,rand()%255,0,255).rgb());
        float t = m_rt.m_globals.m_time*1.0;
        float r = 70;
        m_rt.m_camera.m_camera = QVector3D(r*cos(t),40,r*sin(t));
        m_rt.Render(m_tree,m_img);
        m_rt.m_globals.m_time+=0.1;
        msleep(100);
//        qDebug() << "tick " << rand()%1000;
        emit emitOutput();
    }
}
