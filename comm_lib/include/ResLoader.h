#ifndef __RESLOADER_H__
#define __RESLOADER_H__
/****************
 *�߻��������� bin ���ؽ���
 *@author:Georgehu
 *@since:2013-12-01
 *@example:
 int arrCount = MAX_NUM;
 ResMonster astcfg[MAX_NUM];

 int iRet = LoadTemplateCfg<ResMonster,MAX_NUM>(CCFileUtils::sharedFileUtils()->fullPathForFilename("cfg/bin/Monster.bin").c_str(),astcfg,&arrCount );
 if(iRet<0){
 CCLOG("load cfg failed:%d.\n",iRet);

 }
*******************/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "ResConv.h"

#define RL_MAX_PATH_LEN		256

#define RL_LOADMODE_XMLV1	1		/*��ȡǶ�׽ṹ������������ʶ��xml��Դ�ļ�*/
#define RL_LOADMODE_XMLV2	2		/*��ȡǶ�׽ṹ���Գ�Ա����ʶ��xml��Դ�ļ�*/
#define RL_LOADMODE_XMLV3	3		/*��ȡǶ�׽ṹ��������ֵ��ʶ��xml��Դ�ļ�*/
#define RL_LOADMODE_BIN		4		/*��ȡ���������ݸ�ʽ����Դ�ļ�*/

#ifndef RES_ID_ARRAY
#define RES_ID_ARRAY	1
#endif

/** @name TRC_LOADR����ID
*  @{
*/
#define RL_ERROR_OPEN_FILE_FAILED		-1		/*���ļ���ʧ��*/
#define RL_ERROR_READ_FILE_FAILED		-2		/*���ļ���ʧ��*/
#define RL_ERROR_CHECK_FAILE_FAILED		-3		/*������Դ�ļ�ʧ�ܣ�������Դ�ļ��İ汾��ħ���뱾�ӿڶ���Ĳ�һ��*/
#define RL_ERROR_NO_MEMORY				-4		/*�����ڴ�ʧ��*/
#define RL_ERROR_UNIT_SIZE_TOO_SMALE		-5		/*ָ���ĵ�����Դ�洢�ռ��Ԥ�ڵ�ҪС*/
#define RL_ERROR_BUFFER_SIZE_TO_SMALL	-6		/*������Դ���������ռ䲻��*/
#define RL_ERROR_DIFF_HASH 	-7		/*��Դ�ļ��м�¼��DRԪ���ݿ�hashֵ�뵱ǰָ����hashֵ��ͬ��˵����Դ�ṹ������Ѿ����*/
#define RL_ERROR_READ_XML_FILE_FAILED -8	/*��ȡxml�ļ�ʧ��*/
#define RL_ERROR_FAILED_TO_GET_HEAD_META -9	/*��ȡTResHeadԪ�����������ʧ��*/
#define RL_ERROR_FAILED_TO_READ_XRESHEAD -10	/*��xml�ж�ȡTResHeadʧ��*/
#define RL_ERROR_INVALID_PARAM -11	/*����ӿڵĲ�����Ч*/
/**   @}*/

/** @name TRC_LOADR��Դ���ر�ʶλ
*  @{
*/
#define RL_FLAG_INGORE_DIFF_HASH		0x00000001		/*������Դ�ļ���Ԫ�����������hashֵ�뵱ǰhashֵ�Ĳ�ͬ������������Դ*/
/**   @}*/




/*��ʾ�ò���ֻ���������*/
#ifndef IN
#define IN  
#endif


/*��ʾ�ò���ֻ���������*/
#ifndef OUT
#define OUT
#endif


/*��ʾ�ò���������������������������*/
#ifndef INOUT
#define INOUT
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/** @defgroup TRC_LOADR_VFILE �����ļ�ϵͳ֧�ֽӿ�
*  @{
*/
/** @defgroup TRC_LOADR_BIN �����Ƹ�ʽ����Դ�ļ����ؽӿ�
*  @{
*/

/*TRC_LOADR_BIN ��������Դ�ļ����ؽӿ�*/

/** ָ��������Դ���ݵĻ����С��ָ��������Դ���ݵ��ڴ��С,����Դ�ļ��н���Դ��С�������У��������Ŀռ��ں��������
*@param[in] pszBuff �������ݵĻ������׵�ַ
*@param[in] iBuff	�������Ŀ����ֽ���
*@param[in] iUnit	ָ��������Դ���ݽṹ������ڴ��еĴ洢�ռ䣬ͨ��������������߿���Ϊÿ����Դ�����ʵ����Ҫ�洢�ռ����Ŀռ䡣
����˲�����ֵΪ0���򵥸���Դ��Ϣ�ṹ��Ĵ洢�ռ�Ϊʵ������ռ�
*@param[in] pszFilePath	��Դ�ļ���
*@param[in] pszMetalibHash ����Դ�ļ�����Դ�ṹ��ӦDRԪ�����������hashֵ
*@param[in] iFlag	��Դ���ؿ��Ʊ�ʶλ���˲�������Ϊ0�����б�ʶλ��λ'��'ֵ:
*	-	RL_FLAG_INGORE_DIFF_HASH	����Ԫ����������hash�Ĳ�ͬ
*
*note	������Դ��Ϣ�Ļ������������trl_unload�����ͷ�
*note Ŀǰ��Դ�ļ���ͷ����¼��������Դ�ļ�ʱ����Դ�ṹ���ӦӦDR
*	Ԫ���ݿ��hashֵ��pszMetalibHash��������Ӧ�õ�ǰʹ�õ���Դ�ṹDR Ԫ���ݿ�
*	��hashֵ��ͨ�����hashֵ�Ƿ���ͬ�������ж���Դ�ļ�����Դ�ṹ�İ汾
*	�뵱ǰ�ṹ�İ汾�Ƿ���ͬ�������Դ�ṹ�汾��ͬ���������Դ
*	ʧ�ܣ������ܱ�������Դ�ṹ���������ش������Դ
*note	���pszMetalibHash������ΪNULL, �򲻼��Ԫ���ݿ��hashֵ����ʱ���ܼ��
*	��Դ�ļ��нṹ���뵱ǰʹ�õ���Դ�ṹ�Ƿ�һ��
*note 	��ǰ��Դ�ṹDR Ԫ��������hashֵ�Ļ�ȡ;����:
*	-	ͨ��ʹ��md5sum�������õ�ǰ������DRԪ���ݿ��ļ�����
*	-	����tdr���ߣ�����Դ�ṹ����ת����.hͷ�ļ�ʱ���Ὣ����Դ�ṹ
*		DRԪ���ݿ��hashֵд��ͷ�ļ��У�
*
*note ���ʹ�������ļ����洢�洢��Դ�ļ�������ñ��ӿ�֮ǰ�������trl_set_fileio_interface����
*	�����ļ�IO�����ӿ�
*@see trl_set_fileio_interface
*@retval ����  ��ȡ����Դ����
*@retval 0	�ļ���û����Դ
*@retval ������ ������Դʧ�ܣ����ܷ���ֵ�ʹ���ԭ��
*	�� RL_ERROR_OPEN_FILE_FAILED ���ļ���ʧ��
*	-  RL_ERROR_READ_FILE_FAILED	���ļ���ʧ��
*	- RL_ERROR_CHECK_FAILE_FAILED		������Դ�ļ�ʧ�ܣ�������Դ�ļ��İ汾��ħ���뱾�ӿڶ���Ĳ�һ��
*	- RL_ERROR_NO_MEMORY				�����ڴ�ʧ��
*	- RL_ERROR_DIFF_HASH	��Դ�ṹԪ����������hash��ͬ
*/
int trl_specail_load(IN char* pszBuff, IN int iBuff, IN int iUnit, IN const char* pszFilePath, 
					IN const char *pszMetalibHash, IN int iFlag);

/** �Ӷ�������Դ�ļ��ж�ȡ����Դ��Ϣͷ��
*@param[in] a_pszFilePath	��Դ�ļ���
*@param[in] a_pstResHead ������Դ��Ϣͷ����Ϣ�Ľṹ��ָ��
*
*note ���ʹ�������ļ����洢�洢��Դ�ļ�������ñ��ӿ�֮ǰ�������trl_set_fileio_interface����
*	�����ļ�IO�����ӿ�
*@see trl_set_fileio_interface
*retval 0	�ɹ�
*@retval ����  ʧ��,���ܷ���ֵ�ʹ���ԭ��
*	�� RL_ERROR_OPEN_FILE_FAILED ���ļ���ʧ��
*	-  RL_ERROR_READ_FILE_FAILED	���ļ���ʧ��
*	- RL_ERROR_CHECK_FAILE_FAILED		������Դ�ļ�ʧ�ܣ�������Դ�ļ��İ汾��ħ���뱾�ӿڶ���Ĳ�һ��
*/
int trl_read_reshead(IN const char* a_pszFilePath, IN LPTRESHEAD a_pstResHead);


/**  @}*/
#ifdef __cplusplus
}
#endif

//template <typename T, int N>
//int LoadTemplateCfg(const char * pCfgFilePath, T (&astTArrar)[N], int *piNum)
template <typename T>
int LoadTemplateCfg(const char * pCfgFilePath, T** astTArrar, int *piNum)
{
    TRESHEAD stHead;

    int iRet;
   
  
	/** �����ڴ��С **/
 //   memset(astTArrar, 0, sizeof(astTArrar));
	if (!astTArrar || !piNum)
		return -1;

	 *piNum = 0;

    /** ��ȡ�ļ�ͷ��Ϣ **/
    iRet = trl_read_reshead(pCfgFilePath, &stHead);
    if (iRet < 0)
    {        
        return iRet;
    }

	/*
    if (stHead.iCount > N)
    {
        return -5;
    }
	*/

	*astTArrar = new T [stHead.iCount];
	if (*astTArrar == NULL)
		return -2;

    iRet = trl_specail_load((char*)(*astTArrar), stHead.iCount * sizeof(T), sizeof(T),
        pCfgFilePath, 0, RL_FLAG_INGORE_DIFF_HASH);
    if (iRet < 0)
    {
        return -6;
    }

    *piNum = stHead.iCount;

    return 0;
}

#endif /* __RESLOADER_H__ */
