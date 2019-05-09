#include "FileManage.h"
#include <stdarg.h>
#include <io.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//��ȡ���е��ļ���
void GetAllFiles(string path, vector<string>& files)
{

	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					GetAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}

}

// ��ȡ�ض���ʽ���ļ���
// �ú����в�������������һ��Ϊ·���ַ���(string���ͣ����Ϊ����·��)��
// �ڶ�������Ϊ�ļ������ļ����ƴ洢����(vector����,���ô���)��
// ����������Ϊд���ȡ��ͬ�ļ���ʽ������
void GetMulFormatFiles(string path, vector<string>& files, int num, const char* format, ...)
{
	cout << path << endl;
	std::vector<string> FilesTypes;
	string filetype = format;
	FilesTypes.push_back(filetype);

	char* str;
	va_list arg_ptr;    //��1��,�������ָ������б�ı���
	va_start(arg_ptr, format);//��2��,���������������ʼ��.������ָ������б�
	int count = 0;
	while (count < num - 1)
	{
		//��3��,��ȡarg_ptrָ��ĵ�ǰ����.���������������va_arg�ĵ�2������ָ��
		str = va_arg(arg_ptr, char*);
		filetype = str;
		FilesTypes.push_back(filetype);
		count++;
		
	} 
	va_end(arg_ptr);    //��4��,��һЩ������
		/*for (int i = 0; i<FilesTypes.size(); i++)
			cout << FilesTypes[i].data() << endl;*/

	for (int i = 0; i < FilesTypes.size(); i++) 
	{
		GetAllSingleFormatFiles(path, files, FilesTypes[i]);
	}
}

// �ú�����������������һ��Ϊ·���ַ���(string���ͣ����Ϊ����·��)��
// �ڶ�������Ϊ�ļ������ļ����ƴ洢����(vector����,���ô���)��
void GetAllSingleFormatFiles(string path, vector<string>& files, string format)
{
	long long hFile = 0;
	//�ļ���Ϣ    
	struct _finddata_t fileinfo;//�����洢�ļ���Ϣ�Ľṹ��   
	int len = format.length();
	string p, temp;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)  //��һ�β���  
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //������ҵ������ļ���  
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)  //�����ļ��в���  
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
					GetAllSingleFormatFiles(p.assign(path).append("\\").append(fileinfo.name), files, format);
				}
			}
			else //������ҵ��Ĳ������ļ���   
			{
				//files.push_back(p.assign(fileinfo.name) );  //���ļ�·�����棬Ҳ����ֻ�����ļ���:    p.assign(path).append("\\").append(fileinfo.name)  
				temp = fileinfo.name;
				//�ж��ַ����Ƿ���format��ʽ��β
				if (temp.length()>len && temp.compare(temp.length() - len, len, format) == 0)
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile); //��������  
	}

}


