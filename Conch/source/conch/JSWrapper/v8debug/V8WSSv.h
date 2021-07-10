
#ifndef _V8_WEBSOCKET_SERVER_H__
#define _V8_WEBSOCKET_SERVER_H__

#include <libwebsockets.h>
#include "debug-agent.h"
#include <deque>

#define MAX_V8DBG_PAYLOAD 10240

namespace laya {

    //ÿ��session�ĸ�������
    class per_session_data__v8dbg {
    public:
        size_t rx, tx;
        unsigned char* pRecvBuff;   //�������̫�󣬾�������������Ҫ�ͷ�
        unsigned char RecvBuf[LWS_PRE + MAX_V8DBG_PAYLOAD];
        unsigned int nRecvLen;   //���յĳ���
        unsigned int index;
        unsigned char* pSendBuff;
        int final;
        int continuation;
        int binary;
        DebuggerAgent* pDbgAgent;   //����ж��session�Ļ���������Ա���session
        std::recursive_mutex     pTaskLock;
        std::deque<std::string> pSendTask;
        //std::vector<std::string>    pSendTask;
    };


    void startWSSV(int port, DebuggerAgent* pDbgAgent);
    void stopWSSV();
}

#endif