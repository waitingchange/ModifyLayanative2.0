/**
@file			JSTextMemoryCanvas.h
@brief			
@author			James
@version		1.0
@date			2016_5_17
*/

#ifndef __JSTextMemoryCanvas_H__
#define __JSTextMemoryCanvas_H__

#include <vector>
#include "../JSInterface/JSInterface.h"
#include <JSObjBase.h>
#include <fontMgr/JCFontInfo.h>
#include <fontMgr/JCFontManager.h>
#include <fontMgr/JCFreeTypeRender.h>

namespace laya
{
    class JSTextMemoryCanvas :public JsObjBase, public JSObjNode
	{
    public:

        static JSTextMemoryCanvas* getInstance();

		static JsObjClassInfo JSCLSINFO;

		void exportJS();	//ȫ�ֵĶ�����Ҫ����һ��ʵ�������Բ��þ�̬����

        JSTextMemoryCanvas();

		~JSTextMemoryCanvas();

        void clearAllData();

	public:

        /** @brief ��ʼ��freeTypeĬ������
        *  @param[in] �����·������������м��� \4 �ָ�
        *  @return �����Ƿ�ɹ�
        */
        bool initFreeTypeDefaultFontFromFile(const char* sDefaultTTFs);

        /** @brief ��ʼ��freeTypeĬ������
        *  @param[in] arrayBuffer
        *  @return �����Ƿ�ɹ�
        */
        bool initFreeTypeDefaultFontFromBuffer(JSValueAsParam pArrayBufferArgs);


        /** @brief ���������FileName�ж�ȡ
        *  @param[in] ��������
        *  @param[in] ttf��·��
        *  @return �Ƿ��ȡ�ɹ�
        */
        bool setFontFaceFromUrl(const char* sFontFamily, const char* sTTFFileName);

        /** @brief ���������buffer�ж�ȡ
        *  @param[in] ���������
        *  @param[in] buffer
        *  @param[in] bufferLength
        *  @return �Ƿ��ȡ�ɹ�
        */
        bool setFontFaceFromBuffer(const char* sFontFamily, JSValueAsParam pArrayBufferArgs);

        /** @brief �Ƴ�����
        *  @param[in] ���������
        *  @return
        */
        bool removeFont(const char* sFontFamily);

		void setFontInfo(const char* sFontInfo);

		const char* getFontInfo();

		//JsValue measureText(const char* sText);
		
        JsValue getTextBitmapData(const char* sText,int nColor, int nBorderSize, int nBorderColor);

        JsValue measureChar(int unicode);

        void scale(double x, double y);

    public:

        static JSTextMemoryCanvas*  ms_pTextMemoryCanvas;
        JCFontManager*              m_pFontManager;
        JCFreeTypeFontRender*       m_pFreeTypeRender;
        JCFontInfo*                 m_pCurrentFontInfo;
        std::string                 m_sFont;
        BitmapData                  m_kBitmapData;
#ifdef __APPLE__
        class JCIOSFreeType*              m_pIOSFreeType;                 ///<iosfreetype 
#endif
        double m_fScaleX;
        double m_fScaleY;
	};
}
//------------------------------------------------------------------------------


#endif //__JSTextMemoryCanvas_H__

//-----------------------------END FILE--------------------------------
