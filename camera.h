#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QMessageBox>

#include "mainwindow.h"

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

#include "qtipl.h"

class MainWindow;

class Camera : QObject
{
    Q_OBJECT

public:    
    Camera(MainWindow * p_mainWindow);
    ~Camera();
    bool connectCamera(int);
    void disconnect();

private:
    MainWindow * m_mainWindow;
    CvCapture * m_cameraCapture;
    QTimer m_timer;

private slots:
    void captureImage();


};

#endif // CAMERA_H
