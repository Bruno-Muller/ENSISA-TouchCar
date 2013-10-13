#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

#include "car.h"
#include "mainwindow.h"
#include "server.h"

class MainWindow;
class Server;

class Controller : public QObject
{
    Q_OBJECT

public:
    enum BlinkerState {OFF, LEFT, RIGHT, BOTH};

    Controller(Car * p_model, MainWindow * p_view);
    ~Controller();
    BlinkerState getBlinkerState();
    void acceptCanMessage(CanMessage p_canMessage);
    void toggleLeftBlinker();
    void toggleRightBlinker();
    void toggleWarning();
    void toggleStopLight();
    void toggleBackLight();
    void toggleMainBeam();
    void toggleLowBeamPositionLight();

private slots:
    void blinkerTask();

private:
    Car * m_model;
    MainWindow * m_view;
    Server * m_server;
    QTimer m_timer;

};

#endif // CONTROLLER_H
