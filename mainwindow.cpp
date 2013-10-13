#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug("MainWindow::MainWindow()");
    ui->setupUi(this);

    this->log("Starting program...");
    this->m_controller = new Controller(&m_car, this);

    this->m_camera = new Camera(this);
}


MainWindow::~MainWindow()
{
    qDebug("MainWindow::~MainWindow()");
    delete this->m_camera;
    delete ui;
}

void MainWindow::init()
{
    qDebug("MainWindow::init()");
    QSettings settings("../config.ini", QSettings::IniFormat);
    bool autoconnect = settings.value("autoconnect",false).toBool();
    ui->actionAutoconnect->setChecked(autoconnect);
    int deviceNumber = settings.value("webcam",CV_CAP_ANY).toInt();
    if (autoconnect)
        this->startCamera(deviceNumber);

}

void MainWindow::on_actionAutoconnect_triggered(bool p_checked)
{
    qDebug("MainWindow::on_actionAutoconnect_triggered(bool %i)", p_checked);
    QSettings settings("../config.ini", QSettings::IniFormat);
    settings.setValue("autoconnect", p_checked);
}

void MainWindow::on_actionTouchCar_triggered()
{
    qDebug("MainWindow::on_actionTouchCar_triggered()");
    Infos infos(this);
    infos.exec();
}

void MainWindow::on_actionPort_triggered()
{
    qDebug("MainWindow::on_actionPort_triggered()");
    QSettings settings("../config.ini", QSettings::IniFormat);
    int port = settings.value("port",Server::DEFAULT_PORT).toInt();
    int newPort = QInputDialog::getInteger(this, "TouchCar - Server", "Server port :", port, 1024, 65535);
    if (port != newPort )
    {
        settings.setValue("port", newPort);
        QMessageBox::information(this, "TouchCar - Server", "You need to restart the application to apply this setting.", QMessageBox::Ok);
    }
}

bool MainWindow::startCamera(int p_deviceNumber)
{
    qDebug("MainWindow::startCamera(int %i)", p_deviceNumber);
    if(!this->m_camera->connectCamera(p_deviceNumber)) {
        ui->camera->setText("No camera connected.");
        ui->lbl_framerate->setText("");
        ui->lbl_captureTime->setText("");
        return false;
    }
    this->m_timer.start();
    return true;
}

void MainWindow::on_actionDevice_Number_triggered()
{
    qDebug("MainWindow::on_actionDevice_Number_triggered()");
    QSettings settings("../config.ini", QSettings::IniFormat);
    int deviceNumber = settings.value("webcam",CV_CAP_ANY).toInt();
    deviceNumber = QInputDialog::getInteger(this, "TouchCar - Webcam", "Device Number :", deviceNumber, 0, 999);

    if(this->startCamera(deviceNumber))
        settings.setValue("webcam", deviceNumber);
}

void MainWindow::on_actionConnect_triggered()
{
    qDebug("MainWindow - on_actionConnect_triggered()");
    QSettings settings("../config.ini", QSettings::IniFormat);
    int deviceNumber = settings.value("webcam",CV_CAP_ANY).toInt();
    this->startCamera(deviceNumber);
}

void MainWindow::on_actionDisconnect_triggered()
{
    qDebug("MainWindow - on_actionDisconnect_triggered()");
    this->m_camera->disconnect();
    ui->camera->setText("No camera connected.");
    ui->lbl_framerate->setText("");
    ui->lbl_captureTime->setText("");
}

void MainWindow::log(QString p_string)
{
    ui->messages->appendHtml(p_string);
}

void MainWindow::logInfo(QString p_string)
{
    this->log(p_string);
}

void MainWindow::logError(QString p_string)
{
    this->log("<span style=\"color: #FF0000\">Error: " + p_string + "</span>");
}

void MainWindow::logWarning(QString p_string)
{
    this->log("<span style=\"color: #FF8C00\">Warning: " + p_string + "</span>");
}

void MainWindow::logDebug(QString p_string)
{
    this->log("<span style=\"color: #0000FF\">Debug: " + p_string + "</span>");
}

void MainWindow::setIp(QString p_ip)
{
    ui->lbl_ip->setText(p_ip);
}

void MainWindow::setPort(int p_port)
{
    ui->lbl_port->setText(QString::number(p_port));
}

void MainWindow::setCameraFrame(QImage p_image) {
    //qDebug("MainWindow::setCameraFrame(QImage p_image)");
    //QTime time;
    //time.start();
    ui->camera->setPixmap(QPixmap::fromImage(p_image));
    ui->lbl_framerate->setText(QString::number(this->m_timer.restart()) + " ms");
    //qDebug("did in %i ms", time.elapsed());
}

void MainWindow::setCaptureTime(int p_time)
{
    ui->lbl_captureTime->setText(QString::number(p_time) + " ms");
}

void MainWindow::updateIcons()
{
    qDebug("MainWindow::updateIcons()");
    QTime time;
    time.start();
    if (this->m_car.getLight(OpticalBlock::FRONT_LEFT, Light::BLINKER)->isOn() || this->m_car.getLight(OpticalBlock::REAR_LEFT, Light::BLINKER)->isOn())
        ui->button_blinker_left->setIcon(QIcon(":/buttons/blinker_left_on"));
    else
        ui->button_blinker_left->setIcon(QIcon(":/buttons/blinker_left_off"));

    if (this->m_car.getLight(OpticalBlock::FRONT_RIGHT, Light::BLINKER)->isOn() || this->m_car.getLight(OpticalBlock::REAR_RIGHT, Light::BLINKER)->isOn())
        ui->button_blinker_right->setIcon(QIcon(":/buttons/blinker_right_on"));
    else
        ui->button_blinker_right->setIcon(QIcon(":/buttons/blinker_right_off"));

    if (this->m_car.getLight(OpticalBlock::FRONT_LEFT, Light::MAINBEAM)->isOn() || this->m_car.getLight(OpticalBlock::FRONT_RIGHT, Light::MAINBEAM)->isOn())
        ui->button_mainbeam->setIcon(QIcon(":/buttons/mainbeam_on"));
    else
        ui->button_mainbeam->setIcon(QIcon(":/buttons/mainbeam_off"));

    if ((this->m_car.getLight(OpticalBlock::FRONT_LEFT, Light::POSITION_LIGHT)->isOn() ||
         this->m_car.getLight(OpticalBlock::FRONT_RIGHT, Light::POSITION_LIGHT)->isOn() ||
         this->m_car.getLight(OpticalBlock::REAR_LEFT, Light::POSITION_LIGHT)->isOn() ||
         this->m_car.getLight(OpticalBlock::REAR_RIGHT, Light::POSITION_LIGHT)->isOn()) &&
            (this->m_car.getLight(OpticalBlock::FRONT_LEFT, Light::LOWBEAM)->isOn() ||
             this->m_car.getLight(OpticalBlock::FRONT_RIGHT, Light::LOWBEAM)->isOn()))
        ui->button_position_lowbeam->setIcon(QIcon(":/buttons/position_on_lowbeam_on"));
    else if ((this->m_car.getLight(OpticalBlock::FRONT_LEFT, Light::POSITION_LIGHT)->isOn() ||
              this->m_car.getLight(OpticalBlock::FRONT_RIGHT, Light::POSITION_LIGHT)->isOn() ||
              this->m_car.getLight(OpticalBlock::REAR_LEFT, Light::POSITION_LIGHT)->isOn() ||
              this->m_car.getLight(OpticalBlock::REAR_RIGHT, Light::POSITION_LIGHT)->isOn()) &&
             this->m_car.getLight(OpticalBlock::FRONT_LEFT, Light::LOWBEAM)->isOff() &&
             this->m_car.getLight(OpticalBlock::FRONT_RIGHT, Light::LOWBEAM)->isOff())
        ui->button_position_lowbeam->setIcon(QIcon(":/buttons/position_on_lowbeam_off"));
    else
        ui->button_position_lowbeam->setIcon(QIcon(":/buttons/position_off_lowbeam_off"));

    if ((this->m_car.getLight(OpticalBlock::FRONT_LEFT, Light::BLINKER)->isOn() || this->m_car.getLight(OpticalBlock::REAR_LEFT, Light::BLINKER)->isOn()) &&
            (this->m_car.getLight(OpticalBlock::FRONT_RIGHT, Light::BLINKER)->isOn() || this->m_car.getLight(OpticalBlock::REAR_RIGHT, Light::BLINKER)->isOn()))
        ui->button_warning->setIcon(QIcon(":/buttons/warning_on"));
    else
        ui->button_warning->setIcon(QIcon(":/buttons/warning_off"));

    if (this->m_car.getLight(OpticalBlock::REAR_LEFT, Light::STOP_LIGHT)->isOn() || this->m_car.getLight(OpticalBlock::REAR_RIGHT, Light::STOP_LIGHT)->isOn())
        ui->button_stoplight->setIcon(QIcon(":/buttons/stoplight_on"));
    else
        ui->button_stoplight->setIcon(QIcon(":/buttons/stoplight_off"));

    if (this->m_car.getLight(OpticalBlock::REAR_LEFT, Light::BACK_LIGHT)->isOn() || this->m_car.getLight(OpticalBlock::REAR_RIGHT, Light::BACK_LIGHT)->isOn())
        ui->button_backlight->setIcon(QIcon(":/buttons/backlight_on"));
    else
        ui->button_backlight->setIcon(QIcon(":/buttons/backlight_off"));

    qDebug("did in %i ms", time.elapsed());
}

void MainWindow::on_button_backlight_pressed()
{
    this->m_controller->toggleBackLight();
}

void MainWindow::on_button_stoplight_pressed()
{
    this->m_controller->toggleStopLight();
}

void MainWindow::on_button_blinker_left_pressed()
{
    this->m_controller->toggleLeftBlinker();
}

void MainWindow::on_button_blinker_right_pressed()
{
    this->m_controller->toggleRightBlinker();
}

void MainWindow::on_button_mainbeam_pressed()
{
    this->m_controller->toggleMainBeam();
}

void MainWindow::on_button_mainbeam_released()
{
    if (this->m_car.getLight(OpticalBlock::FRONT_LEFT, Light::LOWBEAM)->isOff() && this->m_car.getLight(OpticalBlock::FRONT_RIGHT, Light::LOWBEAM)->isOff())
        this->m_controller->toggleMainBeam();
}

void MainWindow::on_button_position_lowbeam_pressed()
{
    this->m_controller->toggleLowBeamPositionLight();
}

void MainWindow::on_button_warning_pressed()
{
    this->m_controller->toggleWarning();
}

void MainWindow::on_button_clear_clicked()
{
    ui->messages->clear();
}
