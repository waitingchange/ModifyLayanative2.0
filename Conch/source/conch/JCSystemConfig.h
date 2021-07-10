
#ifndef _LAYA_CONFIG_H__
#define _LAYA_CONFIG_H__

#include <string>
#include <JCWebGLPlus.h>

namespace laya
{
    enum FRAME_TYPE
    {
        FT_SLOW = 0,
        FT_FAST,
        FT_MOUSE,
    };
	class JCSystemConfig 
	{
	public:
		JCSystemConfig();
		void reset();
	public:
		std::string     m_strStartURL;
		bool	        m_bPerfStat;			        //����Ч��ͳ��
        FRAME_TYPE      m_nFrameType;
        double          m_nFrameThreshold;
        int             m_nSleepTime;
		int		        m_nPerf_UpdateNum;
		std::string	    m_strPerfOut;
		std::string     m_jsonparamExt;                 //�������
        bool            m_bShowInternalPerBar;          //�Ƿ���ʾjs ondraw���ֺ�gl����״����ͼ��
        bool            m_bUseChoreographer;            //��android������choreographer
        static bool     s_bIsPlug;                      //��Ϊ��ʼ��̫���ˣ�����static
        static bool     s_bLocalizable;                 //�����Ƿ��Ǳ��ذ�
        bool            m_bUseAndroidSystemFont;        //�Ƿ�ʹ��android���������
        THREAD_MODE     m_nThreadMODE;                  //�߳�ģʽ
	};
	extern JCSystemConfig g_kSystemConfig;
}

#endif