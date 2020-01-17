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
    connection_client ->setParent(this);

    //connect(connection_client,SIGNAL(ConnectErrorSignal(QString)),this, SLOT(on_error_received(QString)));

    //plot setting
    ui->MainPlot->setInteraction(QCP::iRangeDrag);

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

void MainWindow::on_error_received(QString){

}

void MainWindow::on_BroadcastButton_clicked()
{
    server_info = connection_info("localhost", 2290);
    connection_client->establish_connection();
}

void MainWindow::on_NetDataReceived(QByteArray data){
    sig_proc::convert_data(data.data(),data.size(), &display_data);
    refresh_MainPlot();
}

void MainWindow::refresh_MainPlot(){
    ui->MainPlot->addGraph();
    //ui->MainPlot->graph(0)->

    ui->MainPlot->xAxis->setLabel("x");
    ui->MainPlot->yAxis->setLabel("y");

    //ui->MainPlot->xAxis->setRange();
    //ui->MainPlot->yAxis->setRange();
    ui->MainPlot->replot();
}
