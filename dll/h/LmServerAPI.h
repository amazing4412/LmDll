#define byte unsigned char
#define UINT unsigned int
#pragma once

typedef void* HOBJECT;
//=====================================
//公共宏
//用户登录状态
#define LOGIN_STATE_FAILED        0x00  //登录失败，错误未知
#define LOGIN_STATE_SUCCESSFUL    0x01  //登陆成功
#define LOGIN_STATE_UNREG         0x02  //未注册
#define LOGIN_STATE_HAVELOGIN     0x03  //已经登陆
#define LOGIN_STATE_PASSWORDERROR 0x04  //密码错误
#define LOGIN_STATE_CANNOTCONN    0x05  //不能连接


//通信包状态
#define COMM_SEND_FAILED        0x00  //发送失败
#define COMM_SEND_SUCCESSFUL    0x01  //发送成功
#define COMM_CARD_NOTATLINE     0x02  //控制卡没上线
#define COMM_CARD_LOCKED        0x03  //控制卡已被锁定
#define COMM_USER_NORIGHT       0x04  //用户无权限通信
#define COMM_CARD_UNLOCKED      0x05  //控制卡没有锁定

#define COMM_RECV_FAILED        0x00  //接收失败
#define COMM_RECV_SUCCESSFUL    0x05  //接收数据成功，后面有返回数据包
#define COMM_RECV_LENERROR      -1    //接收缓冲区长度不足

//锁定、解锁控制卡返回码
#define LOCKCARD_STATE_SUCCESSFUL       0x01  //成功
#define LOCKCARD_STATE_FAILED           0x00  //失败

//通信类型
#define COMM_TYPE_NET           0x01   //网络通信
#define COMM_TYPE_GPRS          0x02   //GPRS通信


//控制卡状态
#define CARDSTATUS_OFFLINE       0x00  //离线
#define CARDSTATUS_NET_ONLINE    0x01  //网络在线
#define CARDSTATUS_GPRS_ONLINE   0x02  //GPRS在线


//=====================================

#ifdef LMSERVER_EXPORT_API
    #define LMSERVERAPI extern "C" __declspec(dllexport) 
#else
    #ifdef LMSERVER_IMPORT_API
        #ifdef __cplusplus
            #define LMSERVERAPI extern "C" __declspec(dllimport)
        #else
            #define LMSERVERAPI __declspec(dllimport)
        #endif         
    #else
        #define LMSERVERAPI      
    #endif
#endif

//说明：导出API需要添加预处理LMSERVER_EXPORT_API；
//      导入API需要添加预处理LMSERVER_IMPORT_API；

#define CALLING_CONV __stdcall


//==============================================================================================
//客户端使用接口
LMSERVERAPI int CALLING_CONV  LmServer_Login( const char* chIP , UINT nPort , const char* chUser , const char* chPassword ); //用户登陆
LMSERVERAPI int CALLING_CONV  LmServer_Logout(void);//退出登陆

LMSERVERAPI int CALLING_CONV  LmServer_LockCard( const char* chDeviceID ); //锁定控制卡，与控制卡通信之前调用
LMSERVERAPI int CALLING_CONV  LmServer_UnLockCard( const char* chDeviceID  ); //解锁控制卡，控制卡通信完成后调用
//通信数据包
LMSERVERAPI int CALLING_CONV  LmServer_SendCommPacket( const char* chDeviceID , byte byCommType , const byte* pDataBuf , long lDataLen );
LMSERVERAPI int CALLING_CONV  LmServer_RecvCommPacket( byte* pBuf , long lBufSize );

LMSERVERAPI int CALLING_CONV  LmServer_SendHeartbeatPacket(void);

LMSERVERAPI int CALLING_CONV  LmServer_SetReceiveTimeout(UINT nSecond ); //设置接收超时时间,单位毫秒，返回1成功，0失败

//查询控制卡的在线状态,当chDeviceID为Null时表示查询全部控制卡的状态，pBufStatus以字符串的格式保存查询到的控制卡，格式为：设备ID=0/1; ,0表示不在线，1表示网络在线，2表示GPRS在线，每组数据末尾都有分号
//返回值表示查询到的控制卡得数量，为0时表示没有控制卡，为-1是表示查询出错，其他负值表示缓冲区长度不足，其绝对值为缓冲区的最小要求大小
LMSERVERAPI int CALLING_CONV  LmServer_QueryCardStatus( const char* chDeviceID , char* pBufStatus , int nBufSize ); 

//==============================================================================================
//客户端使用接口,允许多用户
LMSERVERAPI HOBJECT CALLING_CONV  LmServer_Login2( const char* chIP , UINT nPort , const char* chUser , const char* chPassword , int* nResult ); //用户登陆,返回登录后的通信对象,作为后续接口的第一个参数，返回空表示登录失败，nResult存储登陆结果值
LMSERVERAPI int CALLING_CONV  LmServer_Logout2(HOBJECT hObj);//退出登陆

LMSERVERAPI int CALLING_CONV  LmServer_LockCard2(HOBJECT hObj, const char* chDeviceID ); //锁定控制卡，与控制卡通信之前调用
LMSERVERAPI int CALLING_CONV  LmServer_UnLockCard2(HOBJECT hObj, const char* chDeviceID  ); //解锁控制卡，控制卡通信完成后调用
//通信数据包
LMSERVERAPI int CALLING_CONV  LmServer_SendCommPacket2(HOBJECT hObj, const char* chDeviceID , byte byCommType , const byte* pDataBuf , long lDataLen );
LMSERVERAPI int CALLING_CONV  LmServer_RecvCommPacket2(HOBJECT hObj, byte* pBuf , long lBufSize );

LMSERVERAPI int CALLING_CONV  LmServer_SendHeartbeatPacket2(HOBJECT hObj);

LMSERVERAPI int CALLING_CONV  LmServer_SetReceiveTimeout2(HOBJECT hObj,UINT nSecond ); //设置接收超时时间,单位毫秒，返回1成功，0失败

//查询控制卡的在线状态,当chDeviceID为Null时表示查询全部控制卡的状态，pBufStatus以字符串的格式保存查询到的控制卡，格式为：设备ID=0/1; ,0表示不在线，1表示网络在线，2表示GPRS在线，每组数据末尾都有分号
//返回值表示查询到的控制卡得数量，为0时表示没有控制卡，为-1是表示查询出错，其他负值表示缓冲区长度不足，其绝对值为缓冲区的最小要求大小
LMSERVERAPI int CALLING_CONV  LmServer_QueryCardStatus2(HOBJECT hObj, const char* chDeviceID , char* pBufStatus , int nBufSize ); 













