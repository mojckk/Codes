#ifndef DECTFOB_H
#define DECTFOB_H

typedef int									INT;
typedef unsigned char						BYTE;

/*********************************************************************************
Function:       DectFob
Description:    检测FOB卡
Input:          char* fname              // 图片绝对路径
int top                  // FOB卡区域的上坐标y
Return:         正常： 1为阴性，2为弱阳，3为阳性
异常： 15  fob初始化配置文件失败(FOB卡)
71  FOB传入的图片读取失败(FOB卡)
72  FOB卡没有滴加样本
73  FOB算法检测失败
74	FOB卡背景被污染
Others:         无
***********************************************************************************/
int DectFob(const char* fname, int numText);

#endif
