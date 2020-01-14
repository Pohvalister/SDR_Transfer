#ifndef CONNECTIONCLIENT_H
#define CONNECTIONCLIENT_H

#include <QObject>
#include <QWidget>
#include <QTcpSocket>

class ConnectionClient : public QWidget
{
    Q_OBJECT

private:
    QTcpSocket* m_pTcpSocket;
    quint16 m_nNextBlockSize;

    bool broadcast_flag = true;


public:
    ConnectionClient();

    void establish_connection();

    void establish_pingage();

    void keep_broadcasting(bool);

signals:
    void ConnectErrorSignal(QString);

private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotSendToServer();
    void slotConnected();

    void slotReadyReceivePing();
    void slotConnectedToPing();
};

#endif // CONNECTIONCLIENT_H
