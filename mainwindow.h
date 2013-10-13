#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QtNetwork>
#include <QTime>
#include <QInputDialog>

#include "controller.h"
#include "camera.h"
#include "car.h"
#include "infos.h"
#include "server.h"

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

class Controller;
class Camera;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTimer * getTimer();
    void updateIcons();
    void log(QString);
    void logInfo(QString);
    void logError(QString);
    void logWarning(QString);
    void logDebug(QString);
    void setIp(QString);
    void setPort(int);
    bool startCamera(int);
    void init();
    void setCameraFrame(QImage);
    void setCaptureTime(int);

private:
    Ui::MainWindow *ui;

    Car m_car;
    Controller * m_controller;
    Camera * m_camera;
    QTime m_timer;

private slots:
    void on_button_backlight_pressed();
    void on_button_stoplight_pressed();
    void on_button_blinker_left_pressed();
    void on_button_blinker_right_pressed();
    void on_button_mainbeam_pressed();
    void on_button_mainbeam_released();
    void on_button_position_lowbeam_pressed();
    void on_button_warning_pressed();
    void on_button_clear_clicked();
    void on_actionTouchCar_triggered();
    void on_actionPort_triggered();
    void on_actionDevice_Number_triggered();
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void on_actionAutoconnect_triggered(bool);



};

#endif // MAINWINDOW_H
