#ifdef _TEST_
#include "../JCTestManager.h"
#include <util/JCCommonMethod.h>
#include <fileSystem/JCFileSystem.h>
#include <util/Log.h>

using namespace laya;

/*
 * �����namespace��û������Ҫ����Ϊ��ȫ�ֺ�����Ϊ�˷�ֹ��ͻ���ż���һ��namespace�������յĲ���û��Ӱ�졣
*/
namespace diskRWTest{
    std::string getAFile(const char*& pDt) {
        std::string ret;
        while ((*pDt == '\r' || *pDt == '\n') && *pDt != 0) {
            pDt++;
        }
        const char* pSt = pDt;
        while (*pDt != '\r' && *pDt != '\n' && *pDt != 0 ) { pDt++; }
        if (pDt - pSt >= 1) {
            ret.append(pSt, pDt - pSt);
            return ret;
        }
        return "";
    }

    void readSomeFile(const char* idx, const char* base,bool bRead) {
        std::string fb = readFileSync1(idx, NULL);
        const char* pDt = fb.c_str();
        std::string absfn = base;
        std::vector<std::string> allfiles;
        char* pReadBuff = nullptr;
        static const int bufsz =1024 * 1024;
        if (bRead) {
            pReadBuff = new char[bufsz];
        }
        while (*pDt != 0) {

            std::string fn = getAFile(pDt);
            if (fn.length() > 0) {
                absfn = base;
                allfiles.push_back(absfn + fn);
            }
        }
        long readsz = 0;
        int fc1 = 0;
        for (int n = 0; n < (bRead?1:4); n++){
            int num = 0, opennum = 0;
            auto sttm = tmGetCurms();
            for (auto i : allfiles) {
                FILE* fp = fopen(i.c_str(), "rb");
                if (fp) {
                    opennum++;
                    if (bRead) {
                        fseek(fp, 0, SEEK_END);
                        int len = ftell(fp);
                        readsz += len;
                        fseek(fp, 0, SEEK_SET);
                        while (len > 0) {
                            len -= fread(pReadBuff, 1, bufsz, fp);
                        }
                    }
                    fclose(fp);
                }
                else {
                    LOGE("Failed:%s", i.c_str());
                }
                num++;
            }
            if (bRead) {
                int dt = (int)(tmGetCurms() - sttm);
                LOGE("Read:%dK,TM:%d,%fM/s", (int)(readsz/1024),dt,(float)(readsz/1024/1.024f/dt));
            }
            else {
                LOGE("NUM:%d,OPENED:%d,TM:%d", num, opennum, (int)(tmGetCurms() - sttm));
            }
        }
        if (pReadBuff) {
            delete[] pReadBuff;
        }
    }
	void test1(){
        LOGE("��ͨ��");
        readSomeFile("/sdcard/temp/testdisk/1/allfiles.txt", "/sdcard/temp/testdisk/1",false);
        LOGE("��Ŀ¼��");
        readSomeFile("/sdcard/temp/testdisk/2/allfiles.txt", "/sdcard/temp/testdisk/2",false);
        LOGE("���ļ���");
        readSomeFile("/sdcard/temp/testdisk/3/allfiles.txt", "/sdcard/temp/testdisk/3", false);
        LOGE("�ֲ�Ŀ¼��");
        readSomeFile("/sdcard/temp/testdisk/4/allfiles.txt", "/sdcard/temp/testdisk/4", false);
        LOGE("��ͨ��ȡ��");
        //while(true)
        readSomeFile("/sdcard/temp/testdisk/1/allfiles.txt", "/sdcard/temp/testdisk/1", true);
        LOGE("���ļ���ȡ��");
        readSomeFile("/sdcard/temp/testdisk/3/allfiles.txt", "/sdcard/temp/testdisk/3", true);
    }

    //����������Ժ�����Ҫ������������еĲ��Ժ���
	void testMain(){
        test1();
	}
    //��Ӳ�����������һ�����������������ڶ����ǲ���������˵����Ҳ���Կ�������ִ�в��������Ĺ��ˡ�
	ADDTESTCASE(testMain,"diskrw");
}
#endif
