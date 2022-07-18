#define byte unsigned char
#define UINT unsigned int
#pragma once

typedef void* HOBJECT;
//=====================================
//������
//�û���¼״̬
#define LOGIN_STATE_FAILED        0x00  //��¼ʧ�ܣ�����δ֪
#define LOGIN_STATE_SUCCESSFUL    0x01  //��½�ɹ�
#define LOGIN_STATE_UNREG         0x02  //δע��
#define LOGIN_STATE_HAVELOGIN     0x03  //�Ѿ���½
#define LOGIN_STATE_PASSWORDERROR 0x04  //�������
#define LOGIN_STATE_CANNOTCONN    0x05  //��������


//ͨ�Ű�״̬
#define COMM_SEND_FAILED        0x00  //����ʧ��
#define COMM_SEND_SUCCESSFUL    0x01  //���ͳɹ�
#define COMM_CARD_NOTATLINE     0x02  //���ƿ�û����
#define COMM_CARD_LOCKED        0x03  //���ƿ��ѱ�����
#define COMM_USER_NORIGHT       0x04  //�û���Ȩ��ͨ��
#define COMM_CARD_UNLOCKED      0x05  //���ƿ�û������

#define COMM_RECV_FAILED        0x00  //����ʧ��
#define COMM_RECV_SUCCESSFUL    0x05  //�������ݳɹ��������з������ݰ�
#define COMM_RECV_LENERROR      -1    //���ջ��������Ȳ���

//�������������ƿ�������
#define LOCKCARD_STATE_SUCCESSFUL       0x01  //�ɹ�
#define LOCKCARD_STATE_FAILED           0x00  //ʧ��

//ͨ������
#define COMM_TYPE_NET           0x01   //����ͨ��
#define COMM_TYPE_GPRS          0x02   //GPRSͨ��


//���ƿ�״̬
#define CARDSTATUS_OFFLINE       0x00  //����
#define CARDSTATUS_NET_ONLINE    0x01  //��������
#define CARDSTATUS_GPRS_ONLINE   0x02  //GPRS����


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

//˵��������API��Ҫ���Ԥ����LMSERVER_EXPORT_API��
//      ����API��Ҫ���Ԥ����LMSERVER_IMPORT_API��

#define CALLING_CONV __stdcall


//==============================================================================================
//�ͻ���ʹ�ýӿ�
LMSERVERAPI int CALLING_CONV  LmServer_Login( const char* chIP , UINT nPort , const char* chUser , const char* chPassword ); //�û���½
LMSERVERAPI int CALLING_CONV  LmServer_Logout(void);//�˳���½

LMSERVERAPI int CALLING_CONV  LmServer_LockCard( const char* chDeviceID ); //�������ƿ�������ƿ�ͨ��֮ǰ����
LMSERVERAPI int CALLING_CONV  LmServer_UnLockCard( const char* chDeviceID  ); //�������ƿ������ƿ�ͨ����ɺ����
//ͨ�����ݰ�
LMSERVERAPI int CALLING_CONV  LmServer_SendCommPacket( const char* chDeviceID , byte byCommType , const byte* pDataBuf , long lDataLen );
LMSERVERAPI int CALLING_CONV  LmServer_RecvCommPacket( byte* pBuf , long lBufSize );

LMSERVERAPI int CALLING_CONV  LmServer_SendHeartbeatPacket(void);

LMSERVERAPI int CALLING_CONV  LmServer_SetReceiveTimeout(UINT nSecond ); //���ý��ճ�ʱʱ��,��λ���룬����1�ɹ���0ʧ��

//��ѯ���ƿ�������״̬,��chDeviceIDΪNullʱ��ʾ��ѯȫ�����ƿ���״̬��pBufStatus���ַ����ĸ�ʽ�����ѯ���Ŀ��ƿ�����ʽΪ���豸ID=0/1; ,0��ʾ�����ߣ�1��ʾ�������ߣ�2��ʾGPRS���ߣ�ÿ������ĩβ���зֺ�
//����ֵ��ʾ��ѯ���Ŀ��ƿ���������Ϊ0ʱ��ʾû�п��ƿ���Ϊ-1�Ǳ�ʾ��ѯ����������ֵ��ʾ���������Ȳ��㣬�����ֵΪ����������СҪ���С
LMSERVERAPI int CALLING_CONV  LmServer_QueryCardStatus( const char* chDeviceID , char* pBufStatus , int nBufSize ); 

//==============================================================================================
//�ͻ���ʹ�ýӿ�,������û�
LMSERVERAPI HOBJECT CALLING_CONV  LmServer_Login2( const char* chIP , UINT nPort , const char* chUser , const char* chPassword , int* nResult ); //�û���½,���ص�¼���ͨ�Ŷ���,��Ϊ�����ӿڵĵ�һ�����������ؿձ�ʾ��¼ʧ�ܣ�nResult�洢��½���ֵ
LMSERVERAPI int CALLING_CONV  LmServer_Logout2(HOBJECT hObj);//�˳���½

LMSERVERAPI int CALLING_CONV  LmServer_LockCard2(HOBJECT hObj, const char* chDeviceID ); //�������ƿ�������ƿ�ͨ��֮ǰ����
LMSERVERAPI int CALLING_CONV  LmServer_UnLockCard2(HOBJECT hObj, const char* chDeviceID  ); //�������ƿ������ƿ�ͨ����ɺ����
//ͨ�����ݰ�
LMSERVERAPI int CALLING_CONV  LmServer_SendCommPacket2(HOBJECT hObj, const char* chDeviceID , byte byCommType , const byte* pDataBuf , long lDataLen );
LMSERVERAPI int CALLING_CONV  LmServer_RecvCommPacket2(HOBJECT hObj, byte* pBuf , long lBufSize );

LMSERVERAPI int CALLING_CONV  LmServer_SendHeartbeatPacket2(HOBJECT hObj);

LMSERVERAPI int CALLING_CONV  LmServer_SetReceiveTimeout2(HOBJECT hObj,UINT nSecond ); //���ý��ճ�ʱʱ��,��λ���룬����1�ɹ���0ʧ��

//��ѯ���ƿ�������״̬,��chDeviceIDΪNullʱ��ʾ��ѯȫ�����ƿ���״̬��pBufStatus���ַ����ĸ�ʽ�����ѯ���Ŀ��ƿ�����ʽΪ���豸ID=0/1; ,0��ʾ�����ߣ�1��ʾ�������ߣ�2��ʾGPRS���ߣ�ÿ������ĩβ���зֺ�
//����ֵ��ʾ��ѯ���Ŀ��ƿ���������Ϊ0ʱ��ʾû�п��ƿ���Ϊ-1�Ǳ�ʾ��ѯ����������ֵ��ʾ���������Ȳ��㣬�����ֵΪ����������СҪ���С
LMSERVERAPI int CALLING_CONV  LmServer_QueryCardStatus2(HOBJECT hObj, const char* chDeviceID , char* pBufStatus , int nBufSize ); 













