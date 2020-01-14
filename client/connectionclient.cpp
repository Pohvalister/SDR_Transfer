#include "connectionclient.h"

#include "connection_info.h"

ConnectionClient::ConnectionClient(){

}


void ConnectionClient::establish_pingage(){
    if (server_info.has_value()){
        m_pTcpSocket = new QTcpSocket(this);
        m_pTcpSocket -> connectToHost(server_info->hostName,server_info->port);
        connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnectedToPing()));
        connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyReceivePing()));
        connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)));
    }
}

void ConnectionClient::establish_connection(){
    if (server_info.has_value()){
        m_pTcpSocket = new QTcpSocket(this);
        m_pTcpSocket -> connectToHost(server_info->hostName,server_info->port);
        connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
        connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
        connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)));
    }
}
void ConnectionClient::slotReadyRead(){
    while(m_pTcpSocket->bytesAvailable()<sizeof(qint16)){
    }
    qint16 len;
    QByteArray receiveBuffer;

    QByteArray len_byted = m_pTcpSocket->read(sizeof(qint16));
    len = *((qint16*)len_byted.data());

    receiveBuffer= m_pTcpSocket->read(len);

    sdr_request check_request = *((sdr_request*)receiveBuffer.data());

    m_pTcpSocket->disconnectFromHost();
}

void ConnectionClient::slotSendToServer(){
    QByteArray sendBuffer;
    qint16 dataAmount = sizeof(sdr_request);
    sendBuffer.resize(sizeof(dataAmount) + dataAmount);
    memcpy(sendBuffer.data(), &dataAmount, sizeof(qint16));
    memcpy(sendBuffer.data()+sizeof(qint16), &out_request, sizeof(sdr_request));
    m_pTcpSocket->write(sendBuffer);
}

void ConnectionClient::slotError(QAbstractSocket::SocketError err){
    QString error_msg;
    switch (err) {
    case QAbstractSocket::HostNotFoundError :
            error_msg = "Host was not found";
            break;
    case QAbstractSocket::RemoteHostClosedError:
            error_msg = "Remote host is closed";
            break;
    case QAbstractSocket::ConnectionRefusedError:
            error_msg = "Connection was refused";
            break;
    default:
            error_msg = "Unknown error";
    }

    emit ConnectErrorSignal(error_msg);
}
void ConnectionClient::slotConnected(){
    if (broadcast_flag){
        slotSendToServer();
    }
}

void ConnectionClient::slotConnectedToPing(){
    QByteArray sendBuffer;
    qint16 pingVal = -1;
    sendBuffer.resize(sizeof(pingVal));
    memcpy(sendBuffer.data(), &pingVal, sizeof(qint16));
    m_pTcpSocket->write(sendBuffer);
}
void ConnectionClient::slotReadyReceivePing(){
    while(m_pTcpSocket->bytesAvailable()<sizeof(qint16)){
    }
    qint16 value;


    QByteArray value_byted = m_pTcpSocket->read(sizeof(qint16));
    value = *((qint16*)value_byted.data());
    if (value>0){
        return;
    }

    QByteArray receiveBuffer;
    receiveBuffer= m_pTcpSocket->read(((-1)*value));

    std::string error_message = *((std::string*)receiveBuffer.data());

    m_pTcpSocket->disconnectFromHost();
}
