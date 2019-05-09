#ifndef DECTFOB_H
#define DECTFOB_H

typedef int									INT;
typedef unsigned char						BYTE;

/*********************************************************************************
Function:       DectFob
Description:    ���FOB��
Input:          char* fname              // ͼƬ����·��
int top                  // FOB�������������y
Return:         ������ 1Ϊ���ԣ�2Ϊ������3Ϊ����
�쳣�� 15  fob��ʼ�������ļ�ʧ��(FOB��)
71  FOB�����ͼƬ��ȡʧ��(FOB��)
72  FOB��û�еμ�����
73  FOB�㷨���ʧ��
74	FOB����������Ⱦ
Others:         ��
***********************************************************************************/
int DectFob(const char* fname, int numText);

#endif
