#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->FileButton->setEnabled(false);
    ui->SendButton->setEnabled(false);

    TcpServer = new QTcpServer(this);
    TcpServer->listen(QHostAddress::Any,8888);
    setWindowTitle("服务器端口为：8888");


    connect(TcpServer,&QTcpServer::newConnection,[=](){

    TcpSocket = TcpServer->nextPendingConnection();

    ui->FileButton->setEnabled(true);
    ui->SendButton->setEnabled(true);

    QString IP = TcpSocket->peerAddress().toString();
    quint16 PORT = TcpSocket->peerPort();

    QString str = QString("[%1:%2] 成功连接").arg(IP).arg(PORT);

    QMessageBox mess(QMessageBox::Warning,tr("通知"),str);
    mess.exec();
    }
);
    TcpSocket = new QTcpSocket(this);

    connect(&timer,&QTimer::timeout,[=]()
    {
        timer.stop();
        sendData();
    });

    ui->progressBar->setValue(0);

   hobject  = CP5200_Program_Create(100,100,0x77);
   if(hobject == NULL)
   {
       qDebug()<<tr("创建失败");
   }
   int id = CP5200_Program_AddPlayWindow(hobject, 0, 0, 100, 100);

   if(id >=0)
   {
       qDebug()<<tr("播放窗口正常");
   }
   QString pPictfile = QString("D:/Qt/app/LianXi/FileTcp/123.jpg");
  int flag= CP5200_Program_AddPicture(hobject, id,pPictfile.toStdString().data(), 0, 0, 0, 3, 0);
    if(flag >=0)
    {
        qDebug()<<tr("添加图片正常");
    }
    flag =CP5200_Program_SaveToFile(hobject,"00010000.lpb");
    if(0<=flag)
    {
        qDebug()<<flag;
    }
    flag=CP5200_Program_Destroy(hobject);
    if(flag ==0)
    {
        qDebug()<<tr("销毁正常");
    }



     HOBJECT hobj = CP5200_Playbill_Create(100, 100, 0x77);

     if(hobj == NULL)
     {
         qDebug()<<tr("创建节目单对象失败");

     }

     flag = CP5200_Playbill_AddFile(hobj,"00010000.lpb");
    if(flag >=0)
    {
        qDebug()<<tr("添加节目到节目单成功");
    }

   flag =CP5200_Playbill_SaveToFile(hobj, "playbill.lpp");
   if(flag ==0)
   {
       qDebug()<<tr("保存节目到节目单成功");
   }

 flag =CP5200_Playbill_Destroy( hobj);
 if(flag == 0)
 {
     qDebug()<<tr("销毁成功");

 }


 CP5200_Net_Init(0xc00a0064, 50000,0xffffffff,10);



flag = CP5200_Net_UploadFile(1,"00010000.lpb", "00010000.lpb");
if(flag ==0)
{
    qDebug()<<tr("发送成功");
}else
{
     qDebug()<<flag;
}

flag = CP5200_Net_UploadFile(1,"playbill.lpp","playbill.lpp");
if(flag ==0)
{
    qDebug()<<tr("发送成功");
}else
{
    qDebug()<<flag;
}

CP5200_Net_RestartApp(1);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_FileButton_clicked()
{

    QString filePath = QFileDialog::getOpenFileName(this,"open","../");

    if(filePath.isEmpty() == false)
    {
        fileName.clear();
        fileSize = 0;
        //获取文件信息
        //只读方式打开文件
        QFileInfo info(filePath);
        fileName = info.fileName(); //获取文件名字
        fileSize = info.size();     //获取文件大小
        ui->progressBar->setMaximum(fileSize/1024);
        ui->progressBar->setMinimum(0);
        ui->progressBar->setValue(0);


        sendSize =0;
         file.setFileName(filePath);
        bool isok =file.open(QIODevice::ReadOnly);
        if(false == isok)
        {
            qDebug()<<"打开文件有误";
        }
        ui->textEdit->append(filePath);

    }else
         {
        qDebug()<<"选择文件出错";
    }
}


//发送文件
void Widget::on_SendButton_clicked()
{
    //先发送文件头信息
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    //发送头部信息
    qint64 len = TcpSocket->write(head.toUtf8());
    if(len >0)
    {
        qDebug()<<"头部文件发送成功";
        timer.start(20);
    }else
    {
        qDebug()<<"头部信息发送失败";
    }
    //发送真正的文件信息
}

void Widget::sendData()
{
      qint64 len = 0;
    do
      {
     char buf[4*1024]={0};
     len = file.read(buf,sizeof(buf));
     len = TcpSocket->write(buf,len);
     sendSize +=len;
     ui->progressBar->setValue(sendSize/1024);
    }
    while(len >0);

        if(sendSize == fileSize)
        {
            ui->textEdit->append("文件发送完毕");
            file.close();

        }


}
