#include "FileManage.h"
#include <stdarg.h>
#include <io.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//获取所有的文件名
void GetAllFiles(string path, vector<string>& files)
{

	long   hFile = 0;
	//文件信息  
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

// 获取特定格式的文件名
// 该函数有不定个参数，第一个为路径字符串(string类型，最好为绝对路径)；
// 第二个参数为文件夹与文件名称存储变量(vector类型,引用传递)。
// 第三个参数为写入读取不同文件格式的数量
void GetMulFormatFiles(string path, vector<string>& files, int num, const char* format, ...)
{
	cout << path << endl;
	std::vector<string> FilesTypes;
	string filetype = format;
	FilesTypes.push_back(filetype);

	char* str;
	va_list arg_ptr;    //第1步,定义这个指向参数列表的变量
	va_start(arg_ptr, format);//第2步,把上面这个变量初始化.即让它指向参数列表
	int count = 0;
	while (count < num - 1)
	{
		//第3步,获取arg_ptr指向的当前参数.这个参数的类型由va_arg的第2个参数指定
		str = va_arg(arg_ptr, char*);
		filetype = str;
		FilesTypes.push_back(filetype);
		count++;
		
	} 
	va_end(arg_ptr);    //第4步,做一些清理工作
		/*for (int i = 0; i<FilesTypes.size(); i++)
			cout << FilesTypes[i].data() << endl;*/

	for (int i = 0; i < FilesTypes.size(); i++) 
	{
		GetAllSingleFormatFiles(path, files, FilesTypes[i]);
	}
}

// 该函数有两个参数，第一个为路径字符串(string类型，最好为绝对路径)；
// 第二个参数为文件夹与文件名称存储变量(vector类型,引用传递)。
void GetAllSingleFormatFiles(string path, vector<string>& files, string format)
{
	long long hFile = 0;
	//文件信息    
	struct _finddata_t fileinfo;//用来存储文件信息的结构体   
	int len = format.length();
	string p, temp;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)  //第一次查找  
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))  //如果查找到的是文件夹  
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)  //进入文件夹查找  
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
					GetAllSingleFormatFiles(p.assign(path).append("\\").append(fileinfo.name), files, format);
				}
			}
			else //如果查找到的不是是文件夹   
			{
				//files.push_back(p.assign(fileinfo.name) );  //将文件路径保存，也可以只保存文件名:    p.assign(path).append("\\").append(fileinfo.name)  
				temp = fileinfo.name;
				//判断字符串是否以format格式结尾
				if (temp.length()>len && temp.compare(temp.length() - len, len, format) == 0)
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile); //结束查找  
	}

}


