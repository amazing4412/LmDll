#include "clienwidget.h"
#include "ui_clienwidget.h"
#include <QMessageBox>
#include <QHostAddress>

ClienWidget::ClienWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClienWidget)
{
    ui->setupUi(this);
    TcpSocket = new QTcpSocket(this);

    isStart = true;
    connect(TcpSocket ,&QTcpSocket::readyRead,[=](){
        //取出接收内容
        QByteArray buf = TcpSocket->readAll();
        if(true == isStart)
        {
            isStart =false;
//            QString str ="hello##1024";
//            str.section("##",0,0);

            fileName = QString(buf).section("##",0,0);
            fileSize = QString(buf).section("##",1,1).toInt();

            ui->progressBar->setMinimum(0);
            ui->progressBar->setMaximum(fileSize/1024);
            recvSize =0;

            file.setFileName(fileName);
            bool isOk = file.open(QIODevice::WriteOnly);
            if(isOk == false)
            {
                qDebug()<<"打开出错";
            }

        }
        else

        {
            qint64 len =file.write(buf);
             recvSize +=len;
            ui->progressBar->setValue(recvSize/1024);
             if(recvSize == fileSize)
             {
                 file.close();
                 QMessageBox::information(this,"完成","文件传输完成");
                 isStart = true;
             }
        }


    });
}

ClienWidget::~ClienWidget()
{
    delete ui;
}

void ClienWidget::on_pushButton_clicked()
{
    QString IP = ui->IPEdit->text();
    quint16 Port = ui->PORTEdit->text().toInt();

    TcpSocket->connectToHost(QHostAddress(IP),Port);

    QMessageBox::information(this,"通知","服务器连接成功");

}
