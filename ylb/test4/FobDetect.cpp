#include "FobDetect.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h> 
#include <locale>
#include <string>
#include <cv.h>
#include "opencv.hpp"

using namespace std;
using namespace cv;
//����Ȥ����
int R, Step, mediate_w, low_w, right_add, top_add, num_count, sum_count, weight_up, weight_down, T_Region, labmax, labmin, threshtop, threshdown_w, threshdown_y, OTSUVal;
//ǿ�������ж�
int up_down, left_right, top_w, down_w, weight_max, weight_min, hsvweight, labamid;
double per_max, per_min, Percentage, Percentagetmp, labaper;

HMODULE GetSelfModuleHandle()
{
	MEMORY_BASIC_INFORMATION mbi;
	return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
}

std::string GetCurFolder()
{
	char exeFullPath[300];
	GetModuleFileNameA(GetSelfModuleHandle(), exeFullPath, 300);
	std::string path = exeFullPath;
	int lastnum = path.find_last_of("\\");
	std::string result(path.begin(), path.begin() + lastnum + 1);
	while (1)
	{
		int lastnum = result.find_first_of("\\");
		if (lastnum < 0)
		{
			break;
		}
		std::string tmp = "/";
		result.replace(lastnum, 1, tmp);
		int a = 1;
	}
	return result;
}


int strkv(char *src, char *key, char *value)
{
	char *p, *q;
	int len;
	p = strchr(src, '=');	// p�ҵ��Ⱥ�
	q = strchr(src, '\n');	// q�ҵ�����

							// ����еȺ��л���
	if (p != NULL && q != NULL)
	{
		*q = '\0'; // ����������Ϊ�ַ�����β
		strncpy(key, src, p - src); // ���Ⱥ�ǰ�����ݿ����� key ��
		strcpy(value, p + 1);	// ���Ⱥź�����ݿ����� value ��
		return 0;
	}
	else
	{
		printf("�����ļ���ʽ����\n");
		return 1;
	}
}

int GetConfiguration(char *profile, char *KeyName, char *KeyVal)
{
	int i;
	FILE *fd;
	char buf[50] = "";	// �����ַ���
	char key[50] = "";	// ���ñ�����
	char value[50] = "";	// ���ñ���ֵ	

							// �������ļ�
	fd = fopen(profile, "r");

	if (fd == NULL)
	{
		printf("�����ļ���ʧ�ܣ�\n");
		return 1;
	}

	// ���ζ�ȡ�ļ���ÿһ��
	while (fgets(buf, 50, fd))
	{
		//������ע���м��հ���
		if ((buf[0] == '/' && buf[1] == '/') || (buf[0] == '\n'))
		{
			continue;
		}
		// ��ȡ��ֵ��
		if (strkv(buf, key, value) == 0)
		{
			// ��������򿽱�
			if (strcmp(key, KeyName) == 0)
			{
				strcpy(KeyVal, value);
				fclose(fd);
				return 0;
			}
			// ��� ��ȡ������ key
			memset(key, 0, strlen(key));
		}
	}

	fclose(fd);
	printf("û���ҵ���Ӧ����%s\n��\n", KeyName);
	return 2;
}


int GetConfiguration_Write(char *profile, char *KeyName, char *KeyVal)
{
	int i;
	FILE *fd;
	char buf[50] = "";	// �����ַ���
	char key[50] = "";	// ���ñ�����
	char value[50] = "";	// ���ñ���ֵ	

							// �������ļ�
	fd = fopen(profile, "r");

	if (fd == NULL)
	{
		printf("�����ļ���ʧ�ܣ�\n");
		return 1;
	}

	// ���ζ�ȡ�ļ���ÿһ��
	while (fgets(buf, 50, fd))
	{
		//������ע���м��հ���
		if ((buf[0] == '/' && buf[1] == '/') || (buf[0] == '\n'))
		{
			continue;
		}
		// ��ȡ��ֵ��
		if (strkv(buf, key, value) == 0)
		{
			// ��������򿽱�
			if (strcmp(key, KeyName) == 0)
			{
				strcpy(KeyVal, value);
				fclose(fd);
				return 0;
			}
			// ��� ��ȡ������ key
			memset(key, 0, strlen(key));
		}
	}

	fclose(fd);
	return 2;
}

int WriteConfiguration(char *profile, char *KeyName, char *KeyVal)
{
	int i;
	FILE *fd;
	char buf[50] = "";	// �����ַ���
	char key[50] = "";	// ���ñ�����
	char value[50] = "";	// ���ñ���ֵ
	char writedata[150] = "";  //д������

	fd = fopen(profile, "a+");// �������ļ�

	if (fd == NULL)
	{
		printf("�����ļ���ʧ�ܣ�\n");
		return 1;
	}

	// ���ζ�ȡ�ļ���ÿһ��
	while (fgets(buf, 50, fd))
	{
		//������ע���м��հ���
		if ((buf[0] == '/' && buf[1] == '/') || (buf[0] == '\n'))
		{
			continue;
		}
		// ��ȡ��ֵ��
		if (strkv(buf, key, value) == 0)
		{
			// ��������򿽱�
			if (strcmp(key, KeyName) == 0)
			{
				fclose(fd);
				return 0;
			}
			// ��� ��ȡ������ key
			memset(key, 0, strlen(key));
		}
	}
	strcpy(writedata, KeyName);
	strcat(writedata, "=");
	strcat(writedata, KeyVal);
	fprintf(fd, "%s\n", writedata);
	fclose(fd);
	return 1;
}

bool FOBIni(int numText)
{
	string path = GetCurFolder();
	string configpath = path + "AlgorithmDependency/config_mmlab_Fob.ini";

	char RTmp[50];
	int srt = GetConfiguration((char*)(configpath.c_str()), "R", RTmp);
	if (srt > 0)
	{
		return false;
	}
	R = atof(RTmp);

	char right_addTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "right_add", right_addTmp);
	if (srt > 0)
	{
		return false;
	}
	right_add = atof(right_addTmp);

	char StepTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "Step", StepTmp);
	if (srt > 0)
	{
		return false;
	}
	Step = atof(StepTmp);

	char mediate_wTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "mediate_w", mediate_wTmp);
	if (srt > 0)
	{
		return false;
	}
	mediate_w = atof(mediate_wTmp);

	char low_wTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "low_w", low_wTmp);
	if (srt > 0)
	{
		return false;
	}
	low_w = atof(low_wTmp);

	char top_addTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "top_add", top_addTmp);
	if (srt > 0)
	{
		return false;
	}
	top_add = atof(top_addTmp);

	char sum_countTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "sum_count", sum_countTmp);
	if (srt > 0)
	{
		return false;
	}
	sum_count = atof(sum_countTmp);

	char num_countTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "num_count", num_countTmp);
	if (srt > 0)
	{
		return false;
	}
	num_count = atof(sum_countTmp);

	char weight_upTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "weight_up", weight_upTmp);
	if (srt > 0)
	{
		return false;
	}
	weight_up = atof(weight_upTmp);

	//char card_chooseTmp[50];
	//srt = GetConfiguration((char*)(configpath.c_str()), "card_choose", card_chooseTmp);
	//if (srt > 0)
	//{
	//	return false;
	//}
	//card_choose = atof(card_chooseTmp);


	string weightDown = "weight_down_" + to_string(numText);
	int len = weightDown.length();
	char* dataWeight = new char[len + 1];
	strcpy(dataWeight, weightDown.c_str());



	char weight_downkzTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), dataWeight, weight_downkzTmp);
	if (srt > 0)
	{
		return false;
	}
	weight_down = atof(weight_downkzTmp);

	string T_region = "T_Region_" + to_string(numText);
	int lenT = T_region.length();
	char* dataT = new char[lenT + 1];
	strcpy(dataT, T_region.c_str());

	char T_RegionkzTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), dataT, T_RegionkzTmp);
	if (srt > 0)
	{
		return false;
	}
	T_Region = atof(T_RegionkzTmp);

	char labmaxTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "labmax", labmaxTmp);
	if (srt > 0)
	{
		return false;
	}
	labmax = atof(labmaxTmp);

	char labminTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "labmin", labminTmp);
	if (srt > 0)
	{
		return false;
	}
	labmin = atof(labminTmp);

	char labamidTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "labamid", labamidTmp);
	if (srt > 0)
	{
		return false;
	}
	labamid = atof(labamidTmp);

	char labaperTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "labaper", labaperTmp);
	if (srt > 0)
	{
		return false;
	}
	labaper = atof(labaperTmp);

	char threshtopTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "threshtop", threshtopTmp);
	if (srt > 0)
	{
		return false;
	}
	threshtop = atof(threshtopTmp);

	char threshdownwTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "threshdown_w", threshdownwTmp);
	if (srt > 0)
	{
		return false;
	}
	threshdown_w = atof(threshdownwTmp);

	char threshdownyTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "threshdown_y", threshdownyTmp);
	if (srt > 0)
	{
		return false;
	}
	threshdown_y = atof(threshdownyTmp);

	char top_wTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "top_w", top_wTmp);
	if (srt > 0)
	{
		return false;
	}
	top_w = atof(top_wTmp);

	char hsvweightTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "hsvweight", hsvweightTmp);
	if (srt > 0)
	{
		return false;
	}
	hsvweight = atof(hsvweightTmp);

	char down_wTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "down_w", down_wTmp);
	if (srt > 0)
	{
		return false;
	}
	down_w = atof(down_wTmp);

	char up_downTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "up_down", up_downTmp);
	if (srt > 0)
	{
		return false;
	}
	up_down = atof(up_downTmp);

	char left_rightTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "left_right", left_rightTmp);
	if (srt > 0)
	{
		return false;
	}
	left_right = atof(left_rightTmp);

	char weight_maxTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "weight_max", weight_maxTmp);
	if (srt > 0)
	{
		return false;
	}
	weight_max = atof(weight_maxTmp);

	char weight_minTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "weight_min", weight_minTmp);
	if (srt > 0)
	{
		return false;
	}
	weight_min = atof(weight_minTmp);

	char per_maxTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "per_max", per_maxTmp);
	if (srt > 0)
	{
		return false;
	}
	per_max = atof(per_maxTmp);

	char per_minTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "per_min", per_minTmp);
	if (srt > 0)
	{
		return false;
	}
	per_min = atof(per_minTmp);

	char PercentageTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "Percentage", PercentageTmp);
	if (srt > 0)
	{
		return false;
	}
	Percentage = atof(PercentageTmp);

	char PercentagetmpTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "Percentagetmp", PercentagetmpTmp);
	if (srt > 0)
	{
		return false;
	}
	Percentagetmp = atof(PercentagetmpTmp);

	char OTSUValTmp[50];
	srt = GetConfiguration((char*)(configpath.c_str()), "OTSUVal", OTSUValTmp);
	if (srt > 0)
	{
		return false;
	}
	OTSUVal = atof(OTSUValTmp);

	return true;
}

bool whiteBalance(cv::Mat& I_RGB)
{
	vector<cv::Mat> chn;
	split(I_RGB, chn);
	cv::Mat L_R, L_G, L_B;
	double R1 = 0, G1 = 0, B1 = 0, KB = 0, KG = 0, KR = 0;
	L_B = chn[0];
	L_R = chn[2];
	L_G = chn[1];
	B1 = mean(L_B)[0];
	G1 = mean(L_G)[0];
	R1 = mean(L_R)[0];
	if (B1 > 0.1 && G1 > 0.1 && R1 > 0.1 && R1 < 250)
	{
		KB = (R1 + G1 + B1) / (3 * B1);
		KG = (R1 + G1 + B1) / (3 * G1);
		KR = (R1 + G1 + B1) / (3 * R1);
		L_B = L_B * KB;
		L_G = L_G * KG;
		L_R = L_R * KR;
		merge(chn, I_RGB);
		return true;
	}
	else
	{
		return false;
	}
}

void RGB2HSV_s(cv::Mat RGBMat, int width, int height, BYTE*s)
{
	// RGBתHSV
	//cv::Mat RGBMat(height, width, CV_8UC3, rgbData);
	cv::Mat dst;
	cvtColor(RGBMat, dst, CV_RGB2HSV);
	BYTE *hsvImg = new BYTE[width*height * 3];
	INT index = 0;
	for (INT nrow = 0; nrow < dst.rows; nrow++)
	{
		BYTE *line = dst.ptr<BYTE>(nrow);
		for (INT ncol = 0; ncol < dst.cols * 3; ncol++)
		{
			hsvImg[index] = line[ncol];
			index++;
		}
	}

	// ��ȡsͨ��
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			s[i*width + j] = hsvImg[i*width * 3 + j * 3 + 1];
			//cout << s[i*width + j] << '1';
		}
	}
	delete[] hsvImg;
	RGBMat.release();
	dst.release();
}

void RGB2LAB_a(cv::Mat RGBMat, int width, int height, BYTE*a)
{
	// RGBתHSV
	//cv::Mat RGBMat(height, width, CV_8UC3, rgbData);
	cv::Mat dst;
	cvtColor(RGBMat, dst, CV_BGR2Lab);
	BYTE *LabImg = new BYTE[width*height * 3];
	INT index = 0;
	for (INT nrow = 0; nrow < dst.rows; nrow++)
	{
		BYTE *line = dst.ptr<BYTE>(nrow);
		for (INT ncol = 0; ncol < dst.cols * 3; ncol++)
		{
			LabImg[index] = line[ncol];
			index++;
		}
	}

	// ��ȡaͨ��
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			a[i*width + j] = LabImg[i*width * 3 + j * 3 + 1];
		}
	}
	delete[] LabImg;
	RGBMat.release();
	dst.release();
}

void RGB2LAB_b(cv::Mat RGBMat, int width, int height, BYTE*b)
{
	// RGBתHSV
	//cv::Mat RGBMat(height, width, CV_8UC3, rgbData);
	cv::Mat dst;
	cvtColor(RGBMat, dst, CV_BGR2Lab);
	BYTE *LabImg = new BYTE[width*height * 3];
	INT index = 0;
	for (INT nrow = 0; nrow < dst.rows; nrow++)
	{
		BYTE *line = dst.ptr<BYTE>(nrow);
		for (INT ncol = 0; ncol < dst.cols * 3; ncol++)
		{
			LabImg[index] = line[ncol];
			index++;
		}
	}

	// ��ȡbͨ��
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			b[i*width + j] = LabImg[i*width * 3 + j * 3 + 2];
		}
	}
	delete[] LabImg;
	RGBMat.release();
	dst.release();
}

void fillHole(const Mat srcBw, Mat &dstBw)
{
	Size m_Size = srcBw.size();
	Mat Temp = Mat::zeros(m_Size.height + 2, m_Size.width + 2, srcBw.type());//��չͼ��
	srcBw.copyTo(Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)));
	cv::floodFill(Temp, cv::Point(0, 0), Scalar(255));
	Mat cutImg;//�ü���չ��ͼ��
	Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)).copyTo(cutImg);
	dstBw = srcBw | (~cutImg);
}

// CheckMode: 0����ȥ��������1����ȥ��������; NeihborMode��0����4����1����8����;
void RemoveSmallRegion(Mat &Src, Mat &Dst, int AreaLimit, int CheckMode, int NeihborMode)
{
	int RemoveCount = 0;
	//�½�һ����ǩͼ���ʼ��Ϊ0���ص㣬Ϊ�˼�¼ÿ�����ص����״̬�ı�ǩ��0����δ��飬1�������ڼ��,2�����鲻�ϸ���Ҫ��ת��ɫ����3������ϸ������   
	//��ʼ����ͼ��ȫ��Ϊ0��δ���  
	Mat PointLabel = Mat::zeros(Src.size(), CV_8UC1);
	if (CheckMode == 1)//ȥ��С��ͨ����İ�ɫ��  
	{
		//cout << "ȥ��С��ͨ��.";
		for (int i = 0; i < Src.rows; i++)
		{
			for (int j = 0; j < Src.cols; j++)
			{
				if (Src.at<uchar>(i, j) < 10)
				{
					PointLabel.at<uchar>(i, j) = 3;//��������ɫ����Ϊ�ϸ�����Ϊ3  
				}
			}
		}
	}
	else//ȥ���׶�����ɫ������  
	{
		//cout << "ȥ���׶�";
		for (int i = 0; i < Src.rows; i++)
		{
			for (int j = 0; j < Src.cols; j++)
			{
				if (Src.at<uchar>(i, j) > 10)
				{
					PointLabel.at<uchar>(i, j) = 3;//���ԭͼ�ǰ�ɫ���򣬱��Ϊ�ϸ�����Ϊ3  
				}
			}
		}
	}


	vector<Point2i>NeihborPos;//������ѹ������  
	NeihborPos.push_back(Point2i(-1, 0));
	NeihborPos.push_back(Point2i(1, 0));
	NeihborPos.push_back(Point2i(0, -1));
	NeihborPos.push_back(Point2i(0, 1));
	if (NeihborMode == 1)
	{
		//cout << "Neighbor mode: 8����." << endl;
		NeihborPos.push_back(Point2i(-1, -1));
		NeihborPos.push_back(Point2i(-1, 1));
		NeihborPos.push_back(Point2i(1, -1));
		NeihborPos.push_back(Point2i(1, 1));
	}
	else int a = 0;//cout << "Neighbor mode: 4����." << endl;
	int NeihborCount = 4 + 4 * NeihborMode;
	int CurrX = 0, CurrY = 0;
	//��ʼ���  
	for (int i = 0; i < Src.rows; i++)
	{
		for (int j = 0; j < Src.cols; j++)
		{
			if (PointLabel.at<uchar>(i, j) == 0)//��ǩͼ�����ص�Ϊ0����ʾ��δ���Ĳ��ϸ��  
			{   //��ʼ���  
				vector<Point2i>GrowBuffer;//��¼������ص�ĸ���  
				GrowBuffer.push_back(Point2i(j, i));
				PointLabel.at<uchar>(i, j) = 1;//���Ϊ���ڼ��  
				int CheckResult = 0;

				for (int z = 0; z < GrowBuffer.size(); z++)
				{
					for (int q = 0; q < NeihborCount; q++)
					{
						CurrX = GrowBuffer.at(z).x + NeihborPos.at(q).x;
						CurrY = GrowBuffer.at(z).y + NeihborPos.at(q).y;
						if (CurrX >= 0 && CurrX<Src.cols&&CurrY >= 0 && CurrY<Src.rows)  //��ֹԽ��    
						{
							if (PointLabel.at<uchar>(CurrY, CurrX) == 0)
							{
								GrowBuffer.push_back(Point2i(CurrX, CurrY));  //��������buffer    
								PointLabel.at<uchar>(CurrY, CurrX) = 1;           //���������ļ���ǩ�������ظ����    
							}
						}
					}
				}
				if (GrowBuffer.size()>AreaLimit) //�жϽ�����Ƿ񳬳��޶��Ĵ�С����1Ϊδ������2Ϊ����    
					CheckResult = 2;
				else
				{
					CheckResult = 1;
					RemoveCount++;//��¼�ж�������ȥ��  
				}

				for (int z = 0; z < GrowBuffer.size(); z++)
				{
					CurrX = GrowBuffer.at(z).x;
					CurrY = GrowBuffer.at(z).y;
					PointLabel.at<uchar>(CurrY, CurrX) += CheckResult;//��ǲ��ϸ�����ص㣬����ֵΪ2  
				}
				//********�����õ㴦�ļ��**********    
			}
		}
	}
	CheckMode = 255 * (1 - CheckMode);
	//��ʼ��ת�����С������    
	for (int i = 0; i < Src.rows; ++i)
	{
		for (int j = 0; j < Src.cols; ++j)
		{
			if (PointLabel.at<uchar>(i, j) == 2)
			{
				Dst.at<uchar>(i, j) = CheckMode;
			}
			else if (PointLabel.at<uchar>(i, j) == 3)
			{
				Dst.at<uchar>(i, j) = Src.at<uchar>(i, j);

			}
		}
	}
	//cout << RemoveCount << " objects removed." << endl;
}

int OtsuAlgThreshold(const cv::Mat image)
{
	if (image.channels() != 1)
	{
		cout << "Please input Gray-image!" << endl;
		return 0;
	}
	int T = 0; //Otsu�㷨��ֵ  
	double varValue = 0; //��䷽���м�ֵ����  
	double w0 = 0; //ǰ�����ص�����ռ����  
	double w1 = 0; //�������ص�����ռ����  
	double u0 = 0; //ǰ��ƽ���Ҷ�  
	double u1 = 0; //����ƽ���Ҷ�  
	double Histogram[256] = { 0 }; //�Ҷ�ֱ��ͼ���±��ǻҶ�ֵ�����������ǻҶ�ֵ��Ӧ�����ص�����  
	uchar *data = image.data;
	double totalNum = image.rows*image.cols; //��������  
											 //����Ҷ�ֱ��ͼ�ֲ���Histogram�����±��ǻҶ�ֵ�����������ǻҶ�ֵ��Ӧ���ص���  
	for (int i = 0; i<image.rows; i++)   //Ϊ������������û�а�rows��cols���������  
	{
		for (int j = 0; j<image.cols; j++)
		{
			Histogram[data[i*image.step + j]]++;
		}
	}
	for (int i = 0; i<255; i++)
	{
		//ÿ�α���֮ǰ��ʼ��������  
		w1 = 0;       u1 = 0;       w0 = 0;       u0 = 0;
		//***********����������ֵ����**************************  
		for (int j = 0; j <= i; j++) //�������ָ�ֵ����  
		{
			w1 += Histogram[j];  //�����������ص�����  
			u1 += j*Histogram[j]; //�������������ܻҶȺ�  
		}
		if (w1 == 0) //�����������ص���Ϊ0ʱ�˳�  
		{
			break;
		}
		u1 = u1 / w1; //��������ƽ���Ҷ�  
		w1 = w1 / totalNum; // �����������ص�����ռ����  
							//***********����������ֵ����**************************  

							//***********ǰ��������ֵ����**************************  
		for (int k = i + 1; k<255; k++)
		{
			w0 += Histogram[k];  //ǰ���������ص�����  
			u0 += k*Histogram[k]; //ǰ�����������ܻҶȺ�  
		}
		if (w0 == 0) //ǰ���������ص���Ϊ0ʱ�˳�  
		{
			break;
		}
		u0 = u0 / w0; //ǰ������ƽ���Ҷ�  
		w0 = w0 / totalNum; // ǰ���������ص�����ռ����  
							//***********ǰ��������ֵ����**************************  

							//***********��䷽�����******************************  
		double varValueI = w0*w1*(u1 - u0)*(u1 - u0); //��ǰ��䷽�����  
		if (varValue<varValueI)
		{
			varValue = varValueI;
			T = i;
		}
	}
	return T;
}

int DectFob(const char* fname, int numText)
{

	//�������ļ�
	bool tmp = FOBIni(numText);
	int result(0);
	if (!tmp)
	{
		printf("fob��ʼ�������ļ�ʧ��\n");
		return 15;
	}

	// ��ͼ
	string filename = fname;
	Mat Src_RGB = cv::imread(filename, 1);
	if (!Src_RGB.data)
	{
		printf("FOB�����ͼƬ��ȡʧ�� \n");
		return 71;
	}

	//��ƽ��
	bool ifBlack = whiteBalance(Src_RGB);
	if (!ifBlack)
	{
		printf("ȫ��ͼ�� \n");
		return 73;
	}

	Mat Src_median, Src_Gary;
	medianBlur(Src_RGB, Src_median, 3);
	cvtColor(Src_median, Src_Gary, CV_BGR2GRAY);//�ҶȻ�
	Mat Src_BW = Mat::zeros(Src_Gary.rows, Src_Gary.cols, CV_8UC1);
	threshold(Src_Gary, Src_BW, 152, 255, THRESH_BINARY);//��ֵ��
	Mat BW_ROI(360, 720, CV_8UC1);
	BW_ROI = Src_BW(cv::Range(310, 670), cv::Range(230, 950));
	RemoveSmallRegion(BW_ROI, BW_ROI, 200, 0, 0);
	double MaxValue_1 = 0, MinValue_1 = 0;
	Mat BW_ROI_Centre = BW_ROI(cv::Range(50, 300), cv::Range(60, 630));
	cv::minMaxLoc(BW_ROI_Centre, &MinValue_1, &MaxValue_1);
	if (MinValue_1 != 0)
	{
		printf("û�еμ����� \n");
		return 72;
	}

	bool isBlack = false;
	int RowsCount = 0;
	for (int i = 0; i < (BW_ROI.rows >> 1); i++)
	{
		uchar* dataout = BW_ROI.ptr<uchar>(i);
		int ColsCount = 0;
		for (int j = 0; j < BW_ROI.cols; j++)
		{
			if (dataout[j] == 0)
				ColsCount++;
		}
		if (ColsCount > 0.8 * BW_ROI.cols)
		{
			RowsCount++;
		}
		if (RowsCount > 30)
		{
			isBlack = true;
			break;
		}
	}

	int top = -1; int left0 = -1;
	Mat Fin_ROI;
	if (isBlack)  //�ڿ�
	{
		cout << "�ڿ�" << endl;
		Mat BW_ROI_Centre1;
		Mat Src_Gary1 = (Src_Gary(cv::Range(310, 670), cv::Range(230, 950)))(cv::Range(50, 300), cv::Range(60, 630));
		threshold(Src_Gary1, BW_ROI_Centre1, 200, 255, THRESH_BINARY);//��ֵ��
		int Count = 0;
		for (int i = 0; i < BW_ROI_Centre1.rows; i++)
		{
			uchar* dataout = BW_ROI_Centre1.ptr<uchar>(i);
			for (int j = 0; j < BW_ROI_Centre1.cols; j++)
			{
				if (dataout[j] == 0)
					Count++;
			}
		}
		if (Count > 0.8*BW_ROI_Centre1.cols*BW_ROI_Centre1.rows)
		{
			printf("FOB������Ⱦ \n");
			return 74;
		}
		for (int i = 0; i < BW_ROI.rows; i++)
		{
			uchar* dataout = BW_ROI.ptr<uchar>(i);
			int count1 = 0;
			for (int j = 0; j < BW_ROI.cols; j++)
			{
				if (dataout[j] != 0)
					count1++;
			}
			if (count1 > 0.4 * BW_ROI.cols && count1 < 0.8 * BW_ROI.cols)
			{
				top = i + 20;
				break;
			}
		}
		if (top != -1)
			cout << "top=" << top << endl;
		else
		{
			cout << "���topʧ��" << endl;
			return 73;
		}
		Mat Top_ROI = BW_ROI(cv::Range(top, top + top_add), cv::Range(0, BW_ROI.cols));
		RemoveSmallRegion(BW_ROI, BW_ROI, 200, 1, 0);
		uchar* dataout = Top_ROI.ptr<uchar>(55);
		for (int j = 0; j < Top_ROI.cols; j++)
		{
			if (dataout[j] == 255)
			{
				left0 = j;
				break;
			}
		}
		left0 += 30;
		if (left0 != -1)
			cout << "left=" << left0 << endl;
		else
		{
			cout << "���leftʧ��" << endl;
			return 73;
		}
		Fin_ROI = BW_ROI(cv::Range(top, top + top_add), cv::Range(left0, left0 + right_add));
	}
	else  //�׿�
	{
		Mat BW_ROI_Centre1;
		Mat Src_Gary1 = (Src_Gary(cv::Range(310, 670), cv::Range(230, 950)))(cv::Range(50, 300), cv::Range(60, 630));
		threshold(Src_Gary1, BW_ROI_Centre1, 160, 255, THRESH_BINARY);//��ֵ��
		int Count = 0;
		for (int i = 0; i < BW_ROI_Centre1.rows; i++)
		{
			uchar* dataout = BW_ROI_Centre1.ptr<uchar>(i);
			for (int j = 0; j < BW_ROI_Centre1.cols; j++)
			{
				if (dataout[j] == 0)
					Count++;
			}
		}
		if (Count > 0.35*BW_ROI_Centre1.cols*BW_ROI_Centre1.rows)
		{
			printf("FOB������Ⱦ \n");
			return 74;
		}
		cout << "�׿�" << endl;
		for (int i = 0; i < BW_ROI.rows; i++)
		{
			uchar* dataout = BW_ROI.ptr<uchar>(i);
			int count2 = 0;
			for (int j = 0; j < (BW_ROI.cols >> 1); j++)
			{
				if (dataout[j] == 0)
					count2++;
			}
			if (count2 >= 2)
			{
				top = i + 20;
				break;
			}
		}
		if (top != -1)
			cout << "top=" << top << endl;
		else
		{
			cout << "���topʧ��" << endl;
			return 73;
		}

		Mat Top_ROI = BW_ROI(cv::Range(top, top + top_add), cv::Range(0, BW_ROI.cols));
		uchar* dataout = Top_ROI.ptr<uchar>(55);
		for (int j = 0; j < Top_ROI.cols; j++)
		{
			if (dataout[j] == 0)
			{
				left0 = j;
				break;
			}
		}
		left0 += 30;
		if (left0 != -1)
			cout << "left=" << left0 << endl;
		else
		{
			cout << "���leftʧ��" << endl;
			return 73;
		}
		Fin_ROI = BW_ROI(cv::Range(top, top + 100), cv::Range(left0, left0 + right_add));
	}

	int count3 = 0;
	for (int i = 0; i < Fin_ROI.rows; i++)
	{
		uchar* dataout = Fin_ROI.ptr<uchar>(i);
		for (int j = 0; j < Fin_ROI.cols; j++)
		{
			if (dataout[j] == 0)
				count3++;
		}
	}
	if (count3 >= 0.5*Fin_ROI.cols*Fin_ROI.rows)
	{
		cout << "FOB����������Ⱦ" << endl;
		return 74;
	}

	//ͨ���Ҷȱ仯ֵ����
	cv::Mat I_Gray, I_Graytmp;
	int left_add = left0 + 230;
	int Top = 310 + top;
	//��һ����Χ�ڽ�ȡ�Ҷ�ͼ����c��(ֻҪ����C�߼��ɣ���Χ��Ҫ�����ֹ�����󽻼�������)
	I_Graytmp = Src_Gary(cv::Range(Top, Top + top_add), cv::Range(left_add, left_add + right_add));
	int r = R; int step = Step;
	cv::Mat gray1, gray2;
	cv::Mat gray = cv::Mat::zeros(I_Graytmp.rows, I_Graytmp.cols, CV_8UC1);
	for (int i = r; i < I_Graytmp.cols - r - step; i++)
	{
		for (int j = r; j < I_Graytmp.rows - r; j++)
		{
			int sum1 = 0, sum2 = 0;
			double avg1 = 0, avg2 = 0;
			gray1 = I_Graytmp(cv::Range(j - r, j + r + 1), cv::Range(i - r, i + r + 1));//Rect(i-r,j-r,2*r+1,2*r+1)
																						//g1.convertTo(g1, CV_8UC1);
			for (int k1 = 0; k1 < gray1.rows; ++k1)
			{
				uchar *p1 = gray1.ptr<uchar>(k1);
				for (int k2 = 0; k2 < gray1.cols; ++k2)
					sum1 = sum1 + p1[k2];
			}
			avg1 = sum1 / pow(2 * r + 1, 2);

			gray2 = I_Graytmp(cv::Range(j - r, j + r + 1), cv::Range(i - r + step, i + step + r + 1));//Rect(i-r, j-step-r, 2*r+1, 2*r+1)
																									  //g2.convertTo(g2, CV_8UC1);
			for (int k3 = 0; k3 < gray2.rows; ++k3)
			{
				uchar *p2 = gray2.ptr<uchar>(k3);
				for (int k4 = 0; k4 < gray2.cols; ++k4)
					sum2 = sum2 + p2[k4];
			}
			avg2 = sum2 / pow(2 * r + 1, 2);

			if (avg1 - avg2 < 0)
				gray.at<uchar>(j, i) = abs(avg1 - avg2);
			else
				gray.at<uchar>(j, i) = 0;
		}
	}

	gray.convertTo(gray, CV_8UC1);

	BYTE* graybw = new BYTE[gray.cols*gray.rows];
	memset(graybw, 0, sizeof(BYTE)*gray.cols*gray.rows);
	cv::Mat grayBW(gray.rows, gray.cols, CV_8UC1, graybw);
	threshold(gray, grayBW, 20, 255, cv::THRESH_BINARY);

	int *num_rows = new int[grayBW.cols];//һά����
	memset(num_rows, 0, sizeof(int)*grayBW.cols);

	for (int k = 0; k < grayBW.rows; k++)
	{
		uchar *garybw_rows = grayBW.ptr<uchar>(k);
		for (int i = 0; i < grayBW.cols; i++)
			num_rows[i] = num_rows[i] + garybw_rows[i] / 255;
	}

	for (int i = 0; i < grayBW.cols; i++)
	{
		if (num_rows[i] > sum_count)
		{
			for (int j = 0; j < grayBW.rows; j++)
				graybw[j*grayBW.cols + i] = 255;
		}
		else
		{
			for (int j = 0; j < grayBW.rows; j++)
				graybw[j*grayBW.cols + i] = 0;
		}
	}



	//ͨ���ж���ɫ����
	vector<cv::Mat> chn;//��ȡͨ��
	Mat L_R, L_G;
	split(Src_RGB, chn);
	L_R = chn[2];
	L_G = chn[1];
	Mat L_Rtmp = L_R(cv::Range(Top, Top + top_add), cv::Range(left_add, left_add + right_add));
	Mat L_Gtmp = L_G(cv::Range(Top, Top + top_add), cv::Range(left_add, left_add + right_add));

	BYTE *tmpL_RG = new BYTE[L_Rtmp.rows*L_Rtmp.cols];
	memset(tmpL_RG, 0, sizeof(BYTE)*L_Rtmp.rows*L_Rtmp.cols);
	INT index = 0;
	for (INT nrow = 0; nrow < L_Rtmp.rows; nrow++)
	{
		BYTE *linex = L_R.ptr<BYTE>(nrow + Top);
		BYTE *liney = L_G.ptr<BYTE>(nrow + Top);
		for (INT ncol = 0; ncol < L_Rtmp.cols; ncol++)
		{
			tmpL_RG[index] = abs((int)linex[ncol + left_add] - (int)liney[ncol + left_add]);
			index++;
		}
	}

	cv::Mat L_RG(L_Rtmp.rows, L_Rtmp.cols, CV_8UC1, tmpL_RG);
	BYTE *threshdst = new BYTE[L_Rtmp.cols*L_Rtmp.rows];
	memset(threshdst, 0, sizeof(BYTE)*L_Rtmp.cols*L_Rtmp.rows);
	cv::Mat threshDst(L_Rtmp.rows, L_Rtmp.cols, CV_8UC1, threshdst);
	//imshow("1", L_RG);
	//waitKey();
	int thresholdValue = OtsuAlgThreshold(L_RG);
	thresholdValue = thresholdValue * 1.4;
	if (thresholdValue < 15)
	{
		thresholdValue = 15;
	}
	threshold(L_RG, threshDst, thresholdValue, 255, cv::THRESH_BINARY);//��ͼ���ֵ��
	int *num = new int[right_add];
	memset(num, 0, sizeof(int)*right_add);
	INT ind = 0, count = 0, flag = 0, cntAll = 0, cmt = 0;
	for (int row = 0; row < top_add; row++)//����Ȥ���������±߽�
	{
		uchar *dstx = threshDst.ptr<uchar>(row);
		for (count = 0; count < right_add; count++)
		{
			num[count] = num[count] + dstx[count] / 255;
		}
	}


	for (int i = 0; i < L_RG.cols; i++)
	{
		if (num[i] > num_count)
		{
			for (int j = 0; j < L_RG.rows; j++)
				threshdst[j*L_RG.cols + i] = 255;//
		}
		else
		{
			for (int j = 0; j < L_RG.rows; j++)
				threshdst[j*L_RG.cols + i] = 0;//
		}
	}
	//cv::imwrite("E:\\˶ʿ\\ʵ����\\FOB_test\\fob��\\r-g.bmp", threshDst);



	//BYTE* rgbAndGrayTmp = new BYTE[L_RG.cols];
	//
	int **saveCnt = new int*[10]; //��һά
	for (int i = 0; i < 10; i++)
	{
		saveCnt[i] = new int[2];  //����ڶ�ά����¼������Ⱥ���ʼλ��
		memset(saveCnt[i], 0, sizeof(int) * 2);
	}
	for (int cnt_1 = 0; cnt_1 < L_RG.cols; cnt_1++)
	{
		//ȡ��ɫ�ռ�ͻҶȿռ�İ�ɫ������ΪC�ߵ�λ��
		if (threshdst[cnt_1] == 255 && graybw[cnt_1] == 255)
			//if (threshDst.at<uchar>(0,cnt_1) == 255 && grayBW.at<uchar>(0,cnt_1) == 255)
		{
			//rgbAndGrayTmp[cnt] = 1;
			cntAll = cntAll + 1;//����ÿһ�������Ŀ��
		}
		else
		{
			if (cntAll > 5)
			{
				saveCnt[cmt][0] = cntAll;//���
				saveCnt[cmt][1] = cnt_1 - cntAll;//��ǰλ��-���=��ʼλ��
				cmt++;
			}
			cntAll = 0;
		}
	}

	int maxCnt = 0, Cline_left = 0, Cline_right = 0;
	if (cmt > 0)
	{
		flag = 1;//�ж�����C�ߣ��ǲ��ǿհ׿�
		maxCnt = saveCnt[0][0];
		ind = saveCnt[0][1];
		Cline_left = left_add - weight_up;//C�����
		Cline_right = saveCnt[0][0] + left_add - weight_up;//C���Ҷ�
		if (cmt > 1)
		{
			for (int i = 1; i < cmt; i++)
			{
				if (maxCnt > 15)
				{
					break;
				}
				if (saveCnt[i][0] > maxCnt)
				{
					maxCnt = saveCnt[i][0];
					ind = saveCnt[i][1];//ind = left_add + savecnt;
					Cline_left = left_add - weight_up;//C�����
					Cline_right = saveCnt[i][0] + left_add - weight_up;//C���Ҷ�
				}
			}
		}

	}

#ifdef logFOB
	logFileFOB << "Ostu�Զ���ֵ*1.4 = " << thresholdValue << endl;
	logFileFOB << "��λ����������" << endl;
#endif


	if (flag == 1)
	{
#ifdef logFOB
		logFileFOB << "C��T�߼�⿪ʼ" << endl;
#endif

		INT left = ind + weight_up;
		INT right = 0;
		right = left + weight_down;
		cv::Mat I_TranRGB;
		cv::Mat ROI = Src_RGB(cv::Range(Top, Top + top_add), cv::Range(left_add - 200, left_add + right_add));// cv::Range(left, right)
#ifdef logFOB
		logFileFOB << "��ȡROI�ɹ�" << endl;
#endif
		transpose(ROI, I_TranRGB);
		//0: ��X�ᷭת�� >0: ��Y�ᷭת�� <0: ��X���Y�ᷭת
		flip(I_TranRGB, I_TranRGB, 1);
#ifdef showImg
		imshow("1", I_TranRGB);
		waitKey();
#endif

		int h = I_TranRGB.rows;
		int w = I_TranRGB.cols;


		cv::Mat channel[3];
		split(I_TranRGB, channel);

		cv::Mat R_ROI = channel[2];
		cv::Mat G_ROI = channel[1];
		BYTE* tpL_RG = new BYTE[R_ROI.rows*R_ROI.cols];
		memset(tpL_RG, 0, sizeof(BYTE)*R_ROI.rows*R_ROI.cols);
		INT index = 0;
		for (INT nrow = 0; nrow < R_ROI.rows; nrow++)
		{
			BYTE *linex = R_ROI.ptr<BYTE>(nrow);
			BYTE *liney = G_ROI.ptr<BYTE>(nrow);
			for (INT ncol = 0; ncol < R_ROI.cols; ncol++)
			{
				tpL_RG[index] = abs((int)linex[ncol] - (int)liney[ncol]);
				index++;
			}
		}
		cv::Mat RG_ROI(R_ROI.rows, R_ROI.cols, CV_8UC1, tpL_RG);
		BYTE *threshROI = new BYTE[R_ROI.rows*R_ROI.cols];
		memset(threshROI, 0, sizeof(BYTE)*R_ROI.rows*R_ROI.cols);
		cv::Mat threshROIDst(R_ROI.rows, R_ROI.cols, CV_8UC1, threshROI);

		threshold(RG_ROI, threshROIDst, 12, 255, cv::THRESH_BINARY);//��ͼ���ֵ��

		int *numROI = new int[R_ROI.rows];
		memset(numROI, 0, sizeof(int)*R_ROI.rows);
		for (int row = 0; row < R_ROI.rows; row++)//����Ȥ���������±߽�
		{
			uchar *dstx = threshROIDst.ptr<uchar>(row);
			for (int countROI = 0; countROI < R_ROI.cols; countROI++)
			{
				numROI[row] += dstx[countROI] / 255;
			}
		}
		for (int i = 0; i < R_ROI.rows; i++)
		{
			if (numROI[i] > num_count)
			{
				for (int j = 0; j < R_ROI.cols; j++)
					threshROI[i*R_ROI.cols + j] = 255;
			}
			else
			{
				for (int j = 0; j < R_ROI.cols; j++)
					threshROI[i*R_ROI.cols + j] = 0;
			}
		}
#ifdef saveImg
		cv::imwrite("E:\\˶ʿ\\ʵ����\\FOB_test\\fob��\\r-g.bmp", threshROIDst);
#endif


		cv::Mat L_space;
		INT Red_Region = 0;
		cv::Mat tmprgbg2 = I_TranRGB(cv::Range(h / 2, h), cv::Range(0, w));
		BYTE *b_1 = new BYTE[w*h];
		memset(b_1, 0, sizeof(BYTE)*w*h);
		cv::Mat B_1(h, w, CV_8UC1, b_1);
		RGB2LAB_b(I_TranRGB, w, h, b_1);
		double MaxValueb_1 = 0, MinValueb_1 = 0;
		cv::minMaxLoc(B_1, &MinValueb_1, &MaxValueb_1);
#ifdef logFOB
		logFileFOB << "ͨ���������ɫ����ѡ��Rͨ������Bͨ��" << endl;
#endif

		if (MaxValueb_1 > labmax && MinValueb_1 > labmin &&MaxValueb_1 < 197)
		{
#ifdef logFOB
			logFileFOB << "ʹ��Rͨ��" << endl;//�Ƶ׵���Rͨ��
#endif		
			L_space = channel[2];
			Red_Region = 1;
		}
		else
		{
#ifdef logFOB
			logFileFOB << "ʹ��Bͨ��" << endl;//�׵׵Ŀ�����ͨ��
#endif
			L_space = channel[0];
		}

		cv::Mat I_ROI = L_space;
		cv::Mat ROIgray1, ROIgray2;
		cv::Mat ROIgray = cv::Mat::zeros(I_ROI.rows, I_ROI.cols, CV_8UC1);
		for (int i = r + step; i < I_ROI.rows - r; i++)
		{
			for (int j = r; j < I_ROI.cols - r; j++)
			{
				int sum1 = 0, sum2 = 0;
				double avg1 = 0, avg2 = 0;
				ROIgray1 = I_ROI(cv::Range(i - r, i + r + 1), cv::Range(j - r, j + r + 1));//

				for (int k1 = 0; k1 < ROIgray1.rows; ++k1)
				{
					uchar *p1 = ROIgray1.ptr<uchar>(k1);
					for (int k2 = 0; k2 < ROIgray1.cols; ++k2)
						sum1 = sum1 + p1[k2];
				}
				avg1 = sum1 / pow(2 * r + 1, 2);

				ROIgray2 = I_ROI(cv::Range(i - r - step, i - step + r + 1), cv::Range(j - r, j + r + 1));//Rect(i-r, j-step-r, 2*r+1, 2*r+1)
																										 //g2.convertTo(g2, CV_8UC1);
				for (int k3 = 0; k3 < ROIgray2.rows; ++k3)
				{
					uchar *p2 = ROIgray2.ptr<uchar>(k3);
					for (int k4 = 0; k4 < ROIgray2.cols; ++k4)
						sum2 = sum2 + p2[k4];
				}
				avg2 = sum2 / pow(2 * r + 1, 2);

				if (avg1 - avg2 < 0)
					ROIgray.at<uchar>(i, j) = abs(avg1 - avg2);
				else
					ROIgray.at<uchar>(i, j) = 0;
			}
		}
		ROIgray.convertTo(ROIgray, CV_8UC1);
		BYTE* grayROIbw = new BYTE[I_ROI.rows*I_ROI.cols];
		memset(grayROIbw, 0, sizeof(BYTE)*I_ROI.rows*I_ROI.cols);
		cv::Mat grayROIBW(I_ROI.rows, I_ROI.cols, CV_8UC1, grayROIbw);
		//threshdown_w = 0;
		if (MaxValueb_1 > labmax && MinValueb_1 > labmin)
		{
			threshold(ROIgray, grayROIBW, threshdown_y, 255, cv::THRESH_BINARY); //threshdown_y
			labamid = 122;
		}
		else
		{
			threshold(ROIgray, grayROIBW, threshdown_w, 255, cv::THRESH_BINARY);// threshdown_w																	
		}

		int *num_ROIrows = new int[I_ROI.rows];
		memset(num_ROIrows, 0, sizeof(int)*I_ROI.rows);

		for (int k = 0; k < I_ROI.rows; k++)
		{
			uchar *garybw_ROIrows = grayROIBW.ptr<uchar>(k);
			for (int i = 0; i < I_ROI.cols; i++)
			{
				num_ROIrows[k] += garybw_ROIrows[i] / 255;
			}
			if (num_ROIrows[k] > sum_count)
			{
				for (int j = 0; j < I_ROI.cols; j++)
				{
					grayROIbw[k*I_ROI.cols + j] = 255;
				}
			}
			else
			{
				for (int j = 0; j < I_ROI.cols; j++)
					grayROIbw[k*I_ROI.cols + j] = 0;
			}
		}
#ifdef saveImg
		cv::imwrite("E:\\˶ʿ\\ʵ����\\FOB_test\\fob��\\rgb.bmp", grayROIBW);
#endif

		INT cntAllROI = 0, cmtROI = 0;
		BYTE* rgbAndGrayROITmp = new BYTE[R_ROI.rows];
		int **saveROICnt = new int*[10]; //��һά��
		for (int i = 0; i < 10; i++)
		{
			saveROICnt[i] = new int[3];  //����ڶ�ά��ÿһ�еĿռ䡣
			memset(saveROICnt[i], 0, sizeof(int) * 3);
		}
		//if (!whitecard)
		//{
		//	T_Region = T_Region - 40;		//ȷ������ȤС�������ұ߽�
		//}

		for (int cnt_region = T_Region - 70; cnt_region < grayROIBW.rows; cnt_region++)                        //zj 11.30 cnt = 345  cnt < 390
		{
			if (grayROIbw[cnt_region*R_ROI.cols] == 255 && threshROI[cnt_region*R_ROI.cols] == 255)  //zj 11.30 cnt<389 T_Region - 1
			{
				cntAllROI = cntAllROI + 1;
			}
			else
			{
				if (cntAllROI > 1)
				{
					saveROICnt[cmtROI][0] = cntAllROI;
					saveROICnt[cmtROI][1] = cnt_region - cntAllROI;//Tline_left
					saveROICnt[cmtROI][2] = cnt_region;//Tline_right
					cmtROI++;
				}
				cntAllROI = 0;
			}
		}

		cv::Mat C_ROI, T_ROI, T_DownROI;
		T_DownROI = I_TranRGB(cv::Range(T_Region - 70, T_Region), cv::Range(left_right, I_ROI.cols - left_right));
		int maxROICnt = 0, Tline_left = 0, Tline_right = 0, T_line = 0;
		if (cmtROI > 0)
		{
			maxROICnt = saveROICnt[0][0];
			Tline_left = saveROICnt[0][1];
			Tline_right = saveROICnt[0][2];
			T_line = 1;
			if (cmtROI > 1)
			{
				for (int i = 1; i < cmtROI; i++)
				{
					if (saveROICnt[i][0] > maxROICnt)
					{
						maxROICnt = saveROICnt[i][0];
						Tline_left = saveROICnt[i][1];
						Tline_right = saveROICnt[i][2];
					}
				}
			}
			C_ROI = I_TranRGB(cv::Range(Cline_left, Cline_right), cv::Range(left_right, I_ROI.cols - left_right));
			T_ROI = I_TranRGB(cv::Range(Tline_left, Tline_right), cv::Range(left_right, I_ROI.cols - left_right));
#ifdef showImg
			imshow("2", T_ROI);
			//cv::imwrite("E:\\˶ʿ\\ʵ����\\FOB_test\\fob��\\T_ROIGary.bmp", T_ROIGary);
			waitKey();
#endif
		}

		//������ж�
#ifdef logFOB
		logFileFOB << "������ж���ʼ" << endl;
#endif

		if (T_line == 1)
		{
			int T_line_Width = Tline_right - Tline_left;
			cv::Mat I_GrayBw;
			double MinValue_Tgary = 0, MaxValue_Tgary = 0, per_Tval = 0;
			INT cntT_Gary = 0, flag_gary = 0, count_Tval = 0;
			BYTE *T_ROIgaryrows = new BYTE[T_DownROI.rows];
			memset(T_ROIgaryrows, 0, sizeof(BYTE)*T_DownROI.rows);
			BYTE *T_ROIGaryrows = new BYTE[T_DownROI.rows * T_DownROI.cols];
			memset(T_ROIGaryrows, 0, sizeof(BYTE)*T_DownROI.rows * T_DownROI.cols);
			cv::Mat T_ROIGary(T_DownROI.rows, T_DownROI.cols, CV_8UC1, T_ROIGaryrows);
			cv::cvtColor(T_DownROI, I_GrayBw, CV_BGR2GRAY);
			cv::minMaxLoc(I_GrayBw, &MinValue_Tgary, &MaxValue_Tgary);
			int **HistCnt = new int*[255]; //��һά��
			for (int i = 0; i < 255; i++)
			{
				HistCnt[i] = new int[2];  //����ڶ�ά��ÿһ�еĿռ䡣
				memset(HistCnt[i], 0, sizeof(int) * 2);
			}

			for (int flg = 0; flg < MaxValue_Tgary - MinValue_Tgary; flg++)
			{
				for (int row = 0; row < T_DownROI.rows; ++row)
				{
					uchar *p2 = I_GrayBw.ptr<uchar>(row);
					for (int col = 0; col < T_DownROI.cols; ++col)
					{
						if (p2[col] == MinValue_Tgary + flg)
						{
							HistCnt[flg][0] = HistCnt[flg][0] + 1;
						}
					}
				}
				HistCnt[flg][1] = MinValue_Tgary + flg;
			}

			INT Max_Hist = 0, Max_Pos = 0;
			Max_Hist = HistCnt[0][0];
			Max_Pos = HistCnt[0][1];
			for (int flg = 0; flg < MaxValue_Tgary - MinValue_Tgary; flg++)
			{
				if (HistCnt[flg][0] > Max_Hist)
				{
					Max_Hist = HistCnt[flg][0];
					Max_Pos = HistCnt[flg][1];
				}
			}

			for (int flg = 0; flg < MaxValue_Tgary - MinValue_Tgary; flg++)
			{
				if (per_Tval < 0.01)
				{
					count_Tval = 0;
					for (int row = 0; row < T_DownROI.rows; ++row)
					{
						uchar *p2 = I_GrayBw.ptr<uchar>(row);
						for (int col = 0; col < T_DownROI.cols; ++col)
						{
							if (p2[col] >= MaxValue_Tgary - flg)
							{
								count_Tval = count_Tval + 1;
							}
						}
					}
					per_Tval = (double)count_Tval / ((double)(T_DownROI.rows*T_DownROI.cols));
				}
				else
				{
					MaxValue_Tgary = MaxValue_Tgary - flg + 1;
					break;
				}
			}

			per_Tval = 0;
			for (int flg = 0; flg < MaxValue_Tgary - MinValue_Tgary; flg++)
			{

				if (per_Tval < 0.01)
				{
					count_Tval = 0;
					for (int row = 0; row < T_DownROI.rows; ++row)
					{
						uchar *p2 = I_GrayBw.ptr<uchar>(row);
						for (int col = 0; col < T_DownROI.cols; ++col)
						{
							if (p2[col] <= MinValue_Tgary + flg)
							{
								count_Tval = count_Tval + 1;
							}
						}
					}
					per_Tval = (double)count_Tval / ((double)(T_DownROI.rows*T_DownROI.cols));
				}
				else
				{
					MinValue_Tgary = MinValue_Tgary + flg + 1;
					break;
				}
			}
			INT threshold_garyVal = 0;
			if (MaxValue_Tgary - MinValue_Tgary < 8)
			{
				threshold_garyVal = MinValue_Tgary;
			}
			else if (MaxValue_Tgary - MinValue_Tgary < 11)
			{
				threshold_garyVal = (int)((MaxValue_Tgary + MinValue_Tgary) / 2) - 2;// -2
			}
			else
			{
				threshold_garyVal = Max_Pos + 1;
			}
			if (threshold_garyVal > 174 && Red_Region == 0)
			{
				threshold_garyVal = threshold_garyVal + 2;//
			}
			if (threshold_garyVal > 183 && Red_Region == 0)
			{
				threshold_garyVal = threshold_garyVal + 2;//
			}
			if (threshold_garyVal > 194 && Red_Region == 0)
			{
				threshold_garyVal = threshold_garyVal + 8;//
			}
			//if (threshold_garyVal > 178)
			//{
			//	flag_toolager = 1;
			//}
			if (threshold_garyVal < OTSUVal)
			{
				threshold(I_GrayBw, T_ROIGary, 0, 255, CV_THRESH_OTSU);//�����ֵ��ͼ���ֵ��
			}
			else
			{
				threshold(I_GrayBw, T_ROIGary, threshold_garyVal, 255, cv::THRESH_BINARY);//��ͼ���ֵ��
			}
#ifdef showImg
			imshow("3", T_DownROI);
			//cv::imwrite("E:\\˶ʿ\\ʵ����\\FOB_test\\fob��\\T_ROIGary.bmp", T_ROIGary);
			waitKey();
#endif
			RemoveSmallRegion(T_ROIGary, T_ROIGary, 2, 1, 0);
#ifdef showImg
			imshow("3", T_ROIGary);
			//cv::imwrite("E:\\˶ʿ\\ʵ����\\FOB_test\\fob��\\T_ROIGary.bmp", T_ROIGary);
			waitKey();
#endif
			for (int k = 0; k < T_ROIGary.rows; k++)
			{
				uchar *T_Garyrows = T_ROIGary.ptr<uchar>(k);
				for (int i = 0; i < T_ROIGary.cols; i++)
				{
					T_ROIgaryrows[k] += T_Garyrows[i] / 255;
				}
				if (T_ROIgaryrows[k] < 8)//10
				{
					for (int j = 0; j < T_ROIGary.cols; j++)
					{
						T_ROIGaryrows[k*T_ROIGary.cols + j] = 255;
					}
				}
				else
				{
					for (int j = 0; j < T_ROIGary.cols; j++)
						T_ROIGaryrows[k*T_ROIGary.cols + j] = 0;
				}
			}
#ifdef showImg
			imshow("4", T_ROIGary);
			waitKey();
#endif
			for (int cnt = 0; cnt < T_ROIGary.rows; cnt++)
			{
				if (T_ROIGaryrows[cnt*T_ROIGary.cols] == 255 && cnt < T_ROIGary.rows - 1)
				{
					cntT_Gary = cntT_Gary + 1;
				}
				else
				{
					if (cntT_Gary > 1)
					{
						flag_gary = 1;
						break;
					}
					cntT_Gary = 0;
				}
			}
			delete[] T_ROIgaryrows;
			delete[] T_ROIGaryrows;
			for (int i = 0; i < 10; i++)
			{
				delete[] HistCnt[i];
			}
			delete[] HistCnt;

			BYTE *a_T = new BYTE[T_ROI.rows*T_ROI.cols];
			memset(a_T, 0, sizeof(BYTE)*T_ROI.rows*T_ROI.cols);
			cv::Mat A_T(T_ROI.rows, T_ROI.cols, CV_8UC1, a_T);
			RGB2LAB_a(T_ROI, T_ROI.cols, T_ROI.rows, a_T);

			double MaxValuea_T = 0, MinValuea_T = 0;
			cv::minMaxLoc(A_T, &MinValuea_T, &MaxValuea_T);
			double pr = 0;
			int	countpr = 0;
			for (int row = 0; row < T_ROI.rows; ++row)
			{
				uchar *p_T = A_T.ptr<uchar>(row);
				for (int col = 0; col < T_ROI.cols; ++col)
				{
					if (p_T[col] >= labamid - 3)
					{
						countpr = countpr + 1;
					}
				}
			}
			pr = (double)countpr / ((double)(T_ROI.rows*T_ROI.cols));
			delete[] a_T;
#ifdef logFOB
			logFileFOB << "lab��aͨ������135ռ��" << pr << endl;
#endif

			if (MaxValuea_T < labamid || pr < labaper)//ɾ��||flag_gary == 0
			{
				result = 1;
			}
			else
			{
				BYTE *s_C = new BYTE[C_ROI.rows*C_ROI.cols];
				memset(s_C, 0, sizeof(BYTE)*C_ROI.rows*C_ROI.cols);
				cv::Mat S_C(C_ROI.rows, C_ROI.cols, CV_8UC1, s_C);
				RGB2HSV_s(C_ROI, C_ROI.cols, C_ROI.rows, s_C);

				BYTE *s_T = new BYTE[T_ROI.rows*T_ROI.cols];
				memset(s_T, 0, sizeof(BYTE)*T_ROI.rows*T_ROI.cols);
				cv::Mat S_T(T_ROI.rows, T_ROI.cols, CV_8UC1, s_T);
				RGB2HSV_s(T_ROI, T_ROI.cols, T_ROI.rows, s_T);

				double MaxValue_1 = 0, MinValue_1 = 0, MaxValue_2 = 0, MinValue_2 = 0;
				cv::minMaxLoc(S_C, &MinValue_1, &MaxValue_1);
				cv::minMaxLoc(S_T, &MinValue_2, &MaxValue_2);

				int count3 = 0;
				int sum = 0;
				long S_T_Size = S_T.rows*S_T.cols;
				for (int i = 0; i < S_T.rows; i++)
				{
					uchar* p = S_T.ptr<uchar>(i);
					for (int j = 0; j < S_T.cols; j++)
					{
						if (p[j]> 60)
							count3++;
						sum += p[j];
					}
				}
				int average = sum / S_T_Size;

				int count4 = 0; int count5 = 0;
				for (int i = 0; i < S_T.rows; i++)
				{
					uchar* p = S_T.ptr<uchar>(i);
					for (int j = 0; j < S_T.cols; j++)
					{
						if (abs(p[j] - average) > 5)
							count4++;
						if (p[j] >= 35)
							count5++;
					}
				}

				//cout << MaxValue_1 << endl << MinValue_1 << endl << MaxValue_2 << endl << MinValue_2 << endl;

				int count = 0;
				double per = 0;
				for (int flg = 0; flg < MaxValue_2 - MinValue_2; flg++)
				{
					if (per < 0.01)
					{
						for (int row = 0; row < S_T.rows; ++row)
						{
							uchar *p2 = S_T.ptr<uchar>(row);
							for (int col = 0; col < S_T.cols; ++col)
							{
								if (p2[col] == MaxValue_2 - flg)
								{
									count = count + 1;
								}
							}
						}
						per = (double)count / ((double)(T_ROI.rows*T_ROI.cols));
					}
					else
					{
						MaxValue_2 = MaxValue_2 - flg + 1;
						break;
					}
				}
				delete[] s_C;
				delete[] s_T;

				if (count3 > 30 && MaxValue_2 - MinValue_2 >= 20 && T_line_Width < 60)
				{
					result = 3;
				}
				else
				{
					if (T_line_Width < 50)
					{
						if (count4 > 0.05*S_T_Size || count5 > 0.1*S_T_Size)
							result = 2;
						else
							result = 1;
					}
					else
						if (count4 > 0.05*S_T_Size)
							result = 74;
						else
							result = 1;
				}
			}
		}
		else
		{
			result = 1;
		}
#ifdef cutImg
		string FolderPath_1;
		char name[100] = {};
		if (result == 1)
		{
			FolderPath_1 = "E:\\˶ʿ\\ʵ����\\FOB_test\\Photosort\\yin";
			sprintf(name, "%s\\FOB_%d.bmp", FolderPath_1.c_str(), numFOB);
		}
		else if (result == 2)
		{
			FolderPath_1 = "E:\\˶ʿ\\ʵ����\\FOB_test\\Photosort\\ruoyang";
			sprintf(name, "%s\\FOB_%d.bmp", FolderPath_1.c_str(), numFOB);
		}
		else
		{
			FolderPath_1 = "E:\\˶ʿ\\ʵ����\\FOB_test\\Photosort\\yang";
			sprintf(name, "%s\\FOB_%d.bmp", FolderPath_1.c_str(), numFOB);
		}

		cv::imwrite(name, T_DownROI);
#endif



		for (int i = 0; i < 10; i++)
		{
			delete[] saveROICnt[i];
		}
		delete[] saveROICnt;
		delete[] tpL_RG;
		delete[] threshROI;
		delete[] numROI;
		delete[] b_1;
		delete[] grayROIbw;
		delete[] num_ROIrows;
		delete[] rgbAndGrayROITmp;
	}
	else
	{
		result = 72;
	}
#ifdef logFOB
	if (result == 1)
	{
		logFileFOB << "�б���������" << endl;
	}
	else if (result == 2)
	{
		logFileFOB << "�б���������" << endl;
	}
	else if (result == 3)
	{
		logFileFOB << "�б���������" << endl;
	}
	else if (result == 72)
	{
		logFileFOB << "�б�����δ�ο�" << endl;
	}
	else if (result == 73)
	{
		logFileFOB << "�б������쳣" << endl;
	}
	logFileFOB << "######FOB######" << endl;
	logFileFOB.close();
#endif

	delete[] graybw;
	delete[] num_rows;
	delete[] tmpL_RG;
	delete[] num;
	//delete[] rgbAndGrayTmp;
	for (int i = 0; i < 10; i++)
	{
		delete[] saveCnt[i];
	}
	delete[] saveCnt;
	delete[] threshdst;
	return result;
}