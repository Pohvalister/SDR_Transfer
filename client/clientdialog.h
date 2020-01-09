#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class ClientDialog;
}

class ClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientDialog(QWidget *parent = nullptr);
    ~ClientDialog();

private slots:
    void on_AcceptButton_accepted();

    void on_AcceptButton_rejected();

private:
    Ui::ClientDialog *ui;
};

#endif // CLIENTDIALOG_H
