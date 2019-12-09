#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(&m_renderer, SIGNAL(emitOutput()), this, SLOT(OnImage()));
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(OnQuit()));


    m_renderer.InitWorld();
    m_renderer.start();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::SetDarkPalette() {
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    QApplication::setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffE0C0; background-color: #000000; border: 0px; }");

}

void MainWindow::OnImage()
{
//    qDebug() << "UPdating texture";
    ui->widget->setTexture(m_renderer.m_img);
    ui->widget->chromatic = 0;
    ui->widget->CD = QVector3D(0,0,0);
    ui->widget->lsca = 0;
}

void MainWindow::OnQuit()
{
    m_renderer.m_done = true;
    m_renderer.msleep(250);
    QThread::msleep(250);

}

