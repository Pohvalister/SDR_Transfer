#include "clientdialog.h"
#include "ui_clientdialog.h"
#include "connection_info.h"

ClientDialog::ClientDialog(QWidget *parent, ConnectionClient* client)
    : QDialog(parent)
    , ui(new Ui::ClientDialog)
    , connection_client(client)
{
    ui->setupUi(this);
}

ClientDialog::~ClientDialog()
{
    delete ui;
}

void ClientDialog::on_AcceptButton_accepted()
{
    server_info = connection_info("localhost",2290);//TODO виджеты для ввода параметров
}

void ClientDialog::on_AcceptButton_rejected()
{

}

void ClientDialog::on_pingButton_clicked()
{
    connection_client->establish_pingage();
}
