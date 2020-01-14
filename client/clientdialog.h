#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>
#include <QTcpSocket>

#include "connectionclient.h"

namespace Ui {
class ClientDialog;
}

class ClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientDialog(QWidget *parent = nullptr,ConnectionClient * client = nullptr);
    ~ClientDialog();

private slots:
    void on_AcceptButton_accepted();
    void on_AcceptButton_rejected();
    void on_pingButton_clicked();

private:
    Ui::ClientDialog *ui;
    ConnectionClient* connection_client;
};

#endif // CLIENTDIALOG_H
