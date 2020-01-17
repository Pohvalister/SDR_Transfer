#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>

#include "clientdialog.h"
#include "connection_info.h"
#include "connectionclient.h"

#include "signal_processing.h"

#include "vector"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void process_signal(char* buffer, int buffer_len);

    ~MainWindow();

private slots:
    void on_NetConfigureButton_clicked();
    void on_error_received(QString);
    void on_BroadcastButton_clicked();

    void on_NetDataReceived(QByteArray);

private:
    Ui::MainWindow *ui;
    //defaults
    const int DEFAULT_CENTER_FREQUENCY = 100;
    const int DEFAULT_SAMPLE_RATE = 10;
    const int DEFAULT_FREQUENCY_WIDTH = 50;

    ConnectionClient* connection_client;

    std::vector<double> display_data;

    //plot communication
    void refresh_MainPlot();


};
#endif // MAINWINDOW_H
