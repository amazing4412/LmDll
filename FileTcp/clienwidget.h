#ifndef CLIENWIDGET_H
#define CLIENWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class ClienWidget;
}

class ClienWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClienWidget(QWidget *parent = 0);
    ~ClienWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ClienWidget *ui;
    QTcpSocket *TcpSocket;

    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 recvSize;
    bool isStart;
};

#endif // CLIENWIDGET_H
