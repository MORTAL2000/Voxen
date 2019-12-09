#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <source/renderer.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Renderer m_renderer;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static void SetDarkPalette();



private slots:
    void OnImage();
private slots:
    void OnQuit();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
