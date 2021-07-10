/**
@file			JCGlobalValue.h
@brief			
@author			James
@version		1.0
@date			2018_5_30
*/

#ifndef __JCGlobalValue_H__
#define __JCGlobalValue_H__

#include <stdio.h>
#include <vector>

namespace laya
{
    enum VALUE_TYPE
    {
        VALUE_TYPE_NORMAL,
        VALUE_TYPE_MAT32,
        VALUE_TYPE_MAT2,
        VALUE_TYPE_MAT3,
        VALUE_TYPE_MAT4,
    };
    enum EXECUTE_TYPE
    {
        EXECUTE_JS_TRHEAD_BUFFER = 0,
        EXECUTE_RENDER_THREAD_BUFFER,
        EXECUTE_COPY_TO_RENDER,
        EXECUTE_COPY_TO_RENDER3D
    };
    enum VALUE_OPERATE_TYPE
    {
        VALUE_OPERATE_ADD = 0,
        VALUE_OPERATE_SUB,
        VALUE_OPERATE_MUL,
        VALUE_OPERATE_DIV,
        VALUE_OPERATE_M2_MUL,
        VALUE_OPERATE_M3_MUL,
        VALUE_OPERATE_M4_MUL,
        VALUE_OPERATE_M32_MUL,
        VALUE_OPERATE_SET,
        VALUE_OPERATE_M32_TRANSLATE,
        VALUE_OPERATE_M32_SCALE,
        VALUE_OPERATE_M32_ROTATE,
        VALUE_OPERATE_M32_SCALE_PIVOT,
        VALUE_OPERATE_M32_ROTATE_PIVOT,
        VALUE_OPERATE_M32_TRANSFORM_PIVOT,
        VALUE_OPERATE_BYTE4_COLOR_MUL,
    };

    enum VALUE_MODIFY_TYPE
    {
        VALUE_MODIFY_MESH,          //�޸�mesh��
        VALUE_MODIFY_SHADER,        //�޸�shader uniform��
        VALUE_MODIFY_DATA_LOCATION, //��������λ��
    };

    enum VALUE_INTERIOR_TYPE
    {
        VALUE_INTERIOR_TYPE_COUNT = 0,
    };

    struct ValueDesc
    {
        /*
         * VALUE_MODIFY_MESH,VALUE_MODIFY_SHADER
        */
        VALUE_MODIFY_TYPE m_nModifyType;

        /*
         * ֻ����4�ֽڶ���ģ���֧��short
         * GL_INT, GL_FLOAT
        */
        int m_nDataType;
        
        /*
         * size�����size
        */
        int m_nSize;

        /*
         * dataSize����λ��byte
        */
        int m_nDataSize;

        /*
         * offsetSize ƫ��ֵΪbyte
        */
        int m_nOffset;

        /*
         * offsetSize ƫ��ֵΪbyte
        */
        char* m_pDefaultValue;

        /*
         * ��������
        */
        VALUE_TYPE m_nValueType;

        ValueDesc()
        {
            m_nModifyType = VALUE_MODIFY_MESH;
            m_nDataType = 0;
            m_nSize = 0;
            m_nDataSize = 0;
            m_nOffset = 0;
            m_pDefaultValue = NULL;
            m_nValueType = VALUE_TYPE_NORMAL;
        }

        ~ValueDesc()
        {
            if (m_pDefaultValue)
            {
                delete[] m_pDefaultValue;
                m_pDefaultValue = NULL;
            }
        }
    };

    /** 
     * @brief 
    */
    class JCGlobalValue
    {
    public:

        struct Point
        {
            float x, y;
        };

    public:

        /** @brief���캯��
        */
        JCGlobalValue();

        /** @brief��������
        */
        ~JCGlobalValue();


        bool reset();


        /** @brief save����״̬
         *  @return ���سɹ�ʧ��
        */
        bool save();


        /** @brief �ָ����� 
         *  @return ���سɹ�ʧ��
        */
        bool restore();

    public:

        ValueDesc* getValueDesc(int nID);

        int addValueDefine(VALUE_MODIFY_TYPE nModifyType, int nDataType, int nSize,char* pDefaultValue,int nDefaultValueSize);

        void endValueDefine();

        void clone( JCGlobalValue* pValueData );

        ValueDesc* setValue(int nValueID, char* pData, VALUE_OPERATE_TYPE nOpreateType);
    
        void copyValue(int nValueID, char* pData,int nDataLenght);

    private:

        void createDefaultValue();

    public:

        char*                       m_pCurrentValue;            ///<��ǰ��ValueData

    public:
        
        char*			            m_pBuffer;                  ///<�����buffer
        int                         m_nCurrentBufferPos;        ///<��ǰ��bufferPos
        int                         m_nSaveDataSize;            ///<�洢��dataSize
        int                         m_nStrideSize;              ///<����save�����ݳ���
        std::vector<ValueDesc*>     m_vValueDesc;               ///<����������Ϣ
        char*                       m_pDefaultValue;            ///<����Ĭ��ֵ
    };
}
//------------------------------------------------------------------------------


#endif //__JCGlobalValue_H__

//-----------------------------END FILE--------------------------------