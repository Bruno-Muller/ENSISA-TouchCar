#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QSettings>

#include "mainwindow.h"
#include "canmessage.h"
#include "controller.h"

class MainWindow;
class Controller;

class Server : public QObject
{
    Q_OBJECT
public:

    static int const DEFAULT_PORT = 50885;

    Server(MainWindow * p_view, Controller * p_controller);
    ~Server();

    void sendToAll(CanMessage);

private slots:
    void newConnection();
    void dataReceived();
    void removedConnection();

private:
    MainWindow * m_view;
    Controller * m_controller;
    QTcpServer *m_serveur;
    QList<QTcpSocket *> m_clients;
};

#endif // SERVER_H
