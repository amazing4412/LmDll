#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QTimer>
#include <CP5200API.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_FileButton_clicked();

    void on_SendButton_clicked();

    void sendData();
    
private:
    Ui::Widget *ui;
    QTcpServer *TcpServer;
    QTcpSocket *TcpSocket;
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 sendSize;
    QTimer timer;

    HOBJECT hobject;
};

#endif // WIDGET_H
