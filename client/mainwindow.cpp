#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server_info = std::nullopt;
    out_request = sdr_request(DEFAULT_CENTER_FREQUENCY, DEFAULT_SAMPLE_RATE,DEFAULT_FREQUENCY_WIDTH);
    connection_client = new ConnectionClient();
    //connection_client ->setParent(this);

   //connect(connection_client,SIGNAL(ConnectErrorSignal(QString)),this, SLOT(on_error_received(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_NetConfigureButton_clicked()
{
    ClientDialog client(this,connection_client);
    client.setParent(this);
    client.exec();

}

/*void MainWindow::on_error_received(QString){

}*/

void MainWindow::on_BroadcastButton_clicked()
{
    server_info = connection_info("localhost", 2290);
    connection_client->establish_connection();
}
