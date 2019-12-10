#include "renderer.h"

Renderer::Renderer()
{
    m_img = QImage(m_width,m_height, QImage::Format_RGB32);

}

void Renderer::InitWorld()
{
    m_tree.InitRandomWorld(0, 100,15,8);
    m_rt.m_camera.m_camera = QVector3D(50,50,50);

    m_rt.m_camera.m_target = QVector3D(0,0,0);
    m_rt.m_camera.m_up = QVector3D(0,1,0);
    m_rt.m_camera.m_fov = 80;
}

void Renderer::run()
{
    while (!m_done) {


 //       m_img.fill(QColor(255,rand()%255,0,255).rgb());
        float t = m_rt.m_globals.m_time*0.2 + 1;
        m_rt.m_globals.m_lights[0]->m_direction = QVector3D(sin(t),0.7,cos(t)).normalized();

        float r = 50;
        m_rt.m_camera.m_camera = QVector3D(r*cos(t),-10,r*sin(t*0.7912));
        m_rt.m_camera.m_target = QVector3D(0.5*r*cos(t*0.6123),-20,0.5*r*sin(t*0.3212));
        QElapsedTimer tim;
        tim.start();

        m_rt.Render(m_tree,m_img);
//        m_rt.RayMarch(m_tree,m_img);
        qDebug() << tim.elapsed();
        m_rt.m_globals.m_time+=0.1;
  //      msleep(20);
//        qDebug() << "tick " << rand()%1000;
        emit emitOutput();
 //       m_tree.InitRandomWorld(cur++, 100,15,8);

    }
}
