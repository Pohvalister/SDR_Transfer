#include "connectionclient.h"

#include "connection_info.h"

ConnectionClient::ConnectionClient(){

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
    while(m_pTcpSocket->bytesAvailable()<sizeof(quint16)){
    }
    quint16 len;
    QByteArray receiveBuffer;

    QByteArray len_byted = m_pTcpSocket->read(sizeof(quint16));
    len = *((quint16*)len_byted.data());

    receiveBuffer= m_pTcpSocket->read(len);

    data_request check_request = *((data_request*)receiveBuffer.data());

    m_pTcpSocket->disconnectFromHost();
}

void ConnectionClient::slotSendToServer(){
    QByteArray sendBuffer;
    quint16 dataAmount = sizeof(sdr_request);
    sendBuffer.resize(sizeof(dataAmount) + dataAmount);
    memcpy(sendBuffer.data(), &dataAmount, sizeof(quint16));
    memcpy(sendBuffer.data()+sizeof(quint16), &sdr_request, sizeof(sdr_request));
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
void ConnectionClient::slotConnected   (){
    if (broadcast_flag){
        slotSendToServer();
    }
}
