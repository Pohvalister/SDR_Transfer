#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "clientdialog.h"
#include "connection_info.h"
#include "connectionclient.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_NetConfigureButton_clicked();
    //void on_error_received(QString);
    void on_BroadcastButton_clicked();

private:
    Ui::MainWindow *ui;
    //defaults
    const int DEFAULT_CENTER_FREQUENCY = 100;
    const int DEFAULT_SAMPLE_RATE = 10;
    const int DEFAULT_FREQUENCY_WIDTH = 50;

    ConnectionClient* connection_client;
};
#endif // MAINWINDOW_H
