#ifndef RENDERER_H
#define RENDERER_H


#include <QDebug>
#include <QThread>
#include <QImage>
#include "source/raytracer/octtree.h"
#include "source/raytracer/raytracer.h"


class Renderer : public QThread
{
    Q_OBJECT



public:
    Renderer();
    int m_width = 320;
    int m_height = 200;

    Raytracer m_rt;
    QImage m_img;
    Octtree m_tree;

    void InitWorld();

    bool m_done = false;

    void run() override;

signals:
    void emitOutput();

};

#endif // RENDERER_H
