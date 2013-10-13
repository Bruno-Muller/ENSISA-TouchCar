#include "camera.h"

Camera::Camera(MainWindow * p_mainWindow) :
    m_cameraCapture(0)
{
    qDebug("Camera::Camera(MainWindow * p_mainWindow)");
    this->m_mainWindow = p_mainWindow;

    connect(&(this->m_timer), SIGNAL(timeout()), this, SLOT(captureImage()));
}

Camera::~Camera()
{
    qDebug("Camera::~Camera()");
    if (this->m_cameraCapture)
        this->disconnect();;
}



bool Camera::connectCamera(int p_deviceNumber)
{
    qDebug("Camera::connectCamera(int %i)", p_deviceNumber);
    if (this->m_cameraCapture)
        this->disconnect();

    this->m_mainWindow->log("Starting webcam number <strong>" + QString::number(p_deviceNumber) + "</strong>");
    this->m_cameraCapture = cvCreateCameraCapture(p_deviceNumber);

    if (!this->m_cameraCapture)
    {
        this->m_mainWindow->logError("Webcam not connected !");
        QMessageBox::critical(this->m_mainWindow, "TouchCar - Webcam", "Webcam not connected !");
        return false;
    }


    this->m_timer.start(80);
    return true;
}

void Camera::disconnect()
{
    qDebug("Camera::disconnect()");
    if (this->m_timer.isActive())
        this->m_timer.stop();

    if (this->m_cameraCapture)
    {
        this->m_mainWindow->log("Shutdown webcam...");
        cvReleaseCapture(&(this->m_cameraCapture));
    }
}

void Camera::captureImage()
{
    qDebug("Camera::captureImage()");
    if (!this->m_cameraCapture)
        return;

    QTime timer;
    timer.start();
    IplImage *iplImage  = cvQueryFrame(this->m_cameraCapture);
    uchar *data;
    QImage *qImg = IplImageToQImage(iplImage, &data);
    this->m_mainWindow->setCameraFrame(*qImg);
    this->m_mainWindow->setCaptureTime(timer.elapsed());
    //qDebug("did in %i ms", timer.elapsed());
}


