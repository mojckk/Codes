#ifndef __FILEMANAGE
#define __FILEMANAGE
#include <string>
#include <vector>
#include <iostream>   
#include <fstream>  
#include <sstream>  
#include <io.h>
#include "windows.h"
using namespace std;
void GetMulFormatFiles(string path, vector<string>& files, int num, const char* format, ...);
void GetAllSingleFormatFiles(string path, vector<string>& files, string format);
void GetAllFiles(string path, vector<string>& files);
#endif // !__FILEMANAGE

