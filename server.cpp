#include "server.h"

Server::Server(MainWindow * p_view, Controller * p_controller)
{
    this->m_view = p_view;
    this->m_controller = p_controller;

    this->m_view->logInfo("Starting server...");

    // On cherche l'adresse ip de l'orindateur
    QString address;
    foreach(QHostAddress addr, QNetworkInterface::allAddresses())
    {
        // Filtre les adresses localhost ...
        if(addr != QHostAddress::LocalHostIPv6 && addr != QHostAddress::LocalHost &&
                !addr.isInSubnet(QHostAddress::parseSubnet("169.254.0.0/16")) && !addr.isInSubnet(QHostAddress::parseSubnet("FE80::/64")))
            address = addr.toString();
    }

    QSettings settings("../config.ini", QSettings::IniFormat);

    int port = settings.value("port", DEFAULT_PORT).toInt();

    // Gestion du serveur
    this->m_serveur = new QTcpServer(this->m_view);
    if (!this->m_serveur->listen(QHostAddress::Any, port)) // Démarrage du serveur sur toutes les IP disponibles et sur le port 50585
        this->m_view->logError("Server could not start on port <strong>" + QString::number(port) + "</strong>. Reason : <br />" + this->m_serveur->errorString());
    else
    {
        this->m_view->logInfo("Server has been started. IP:<strong>" + address + "</strong> Port:<strong>" + QString::number(port) + "</strong>");
        this->m_view->setIp(address);
        this->m_view->setPort(port);
        connect(this->m_serveur, SIGNAL(newConnection()), this, SLOT(newConnection()));
    }
}

Server::~Server()
{
    delete this->m_serveur;
}

void Server::sendToAll(CanMessage p_canMessage)
{
    this->m_view->logInfo("CanMessage: 0x" + QString::number(p_canMessage.getId(), 16) + " 0b" + QString::number(p_canMessage.getDataLow(), 2) + " 0b" + QString::number(p_canMessage.getDataHigh(), 2));
    this->m_controller->acceptCanMessage(p_canMessage);
    for (int i = 0; i < this->m_clients.size(); i++)
        this->m_clients[i]->write(p_canMessage.getBytes());
}

void Server::newConnection()
{
    QTcpSocket *nouveauClient = this->m_serveur->nextPendingConnection();
    this->m_clients << nouveauClient;

    this->m_view->logInfo("New client. IP:<strong>" + nouveauClient->peerAddress().toString() + "</strong>");

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(removedConnection()));
}

void Server::dataReceived()
{
    // On détermine quel client envoie le message (recherche du QTcpSocket du client)
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    while (socket->bytesAvailable() >= 6) {
        CanMessage canMessage(socket->read(6));
        this->sendToAll(canMessage);
    }
}

void Server::removedConnection()
{
    // On détermine quel client se déconnecte
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    this->m_view->log("Client removed. IP:<strong>" + socket->peerAddress().toString() + "</strong>");

    this->m_clients.removeOne(socket);

    socket->deleteLater();
}
