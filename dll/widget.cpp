#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    int argc = 7;

//    argv[1] = "58.61.157.155";    服务器IP
//    argv[2] = "5202";     端口
//    argv[3] = "user01";   用户名
//    argv[4] = "16888";    密码
//    argv[5] = "100005";  控制卡ID
//    argv[6] = "Hello,world!";

    int nResult = LOGIN_STATE_FAILED;
    if ( argc == 7)
    {
//        _tprintf(_T("参数：%s %d %s %s %s %s \n") ,argv[1] , atoi(argv[2]) , argv[3] , argv[4] ,argv[5] ,argv[6]  );

        HOBJECT hObj = LmServer_Login2( "58.61.157.155"  , 5202 , "user01" , "16888" ,&nResult);
        if ( hObj != NULL )
        {
            if ( LOCKCARD_STATE_SUCCESSFUL == LmServer_LockCard2( hObj, "100005" ))
            {
                int nIDLen = strlen("100005");
                //使用多窗口协议中的0x12指令发送纯文本数据到0号窗口
                byte byData[4096] ={0};
                int nLen = 2;
                memcpy( byData + nLen , "100005" , nIDLen );
                nLen += nIDLen;

                byData[nLen++] = 0x68;
                byData[nLen++] = 0x32;
                byData[nLen++] = 0xff;
                byData[nLen++] = 0x7b;
                byData[nLen++] = 0x01;
                byData[nLen++] = 0x00; //CC数据长度，先赋值为0
                byData[nLen++] = 0x00;
                byData[nLen++] = 0x00;
                byData[nLen++] = 0x00;

                byData[nLen++] = 0x12; //发送纯文本数据
                byData[nLen++] = 0x00;
                byData[nLen++] = 0x0B; //左滚
                byData[nLen++] = 0x00;
                byData[nLen++] = 0x01;
                byData[nLen++] = 0x00;
                byData[nLen++] = 0x03;
                byData[nLen++] = 0x02; //16点高字体
                byData[nLen++] = 0xff;
                byData[nLen++] = 0xff;
                byData[nLen++] = 0xff;
                strcpy( (char*)byData+nLen , "Hello,world!" ); //文本
                nLen += strlen("Hello,world!");
                byData[nLen++] = 0x00;

                byData[7+nIDLen] = (byte)(nLen-(11+nIDLen));     //重新给CC数据长度赋值
                byData[8+nIDLen] = (byte)((nLen-(11+nIDLen))>>8);


                unsigned short nCheckSum = 0x00;
                for ( int i = 2+nIDLen ; i < nLen ; i++ )
                    nCheckSum += byData[i];

                byData[nLen++] = (byte)nCheckSum;
                byData[nLen++] = (byte)(nCheckSum>>8);

                byData[0] = (byte)(nLen-2);     //给数据长度赋值
                byData[1] = (byte)((nLen-2)>>8);


                if ( COMM_SEND_SUCCESSFUL == LmServer_SendCommPacket2( hObj, "100005" , COMM_TYPE_NET , byData , nLen ) )
                {
                    nLen = LmServer_RecvCommPacket2( hObj, byData , sizeof(byData) );

                    if ( nLen >= 20  )
                    {
                        int nDataLen = byData[0] + ( byData[1]<<8 );
                        char chDeviceID[32] = { 0};
                        memcpy( chDeviceID , &byData[2] ,nIDLen );
                        chDeviceID[nIDLen] = 0;

                        if ( strcmp( chDeviceID , "100005") == 0 && nLen >= 2 + nDataLen && (byData[2+nIDLen] == 0x68 || byData[2+nIDLen] == 0xE8) &&  byData[6+nIDLen] == 0x00 && byData[11+nIDLen] == 0x12 )
                        {
//                            _tprintf(_T("Send plain text instruction 0x12 successfully:%s \n") , argv[6]);			//发送纯文本指令0x12成功：
                        }
                    }
                }

                LmServer_UnLockCard2( hObj,"Hello,world!" );
            }
            else
            {
//                _tprintf(_T("Lock card failed.\n"));//锁卡失败
            }
            LmServer_Logout2( hObj );
        }
        else
        {
//            _tprintf(_T("Login failed%d\n"),nResult );//登录失败
        }

    }
    else
    {
//        _tprintf(_T("Parameters are not right.\n"));//参数不对
    }
}

Widget::~Widget()
{
    delete ui;
}
