
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68	2020											*
* 																											*
*								File Name:			FileIOFunctions.h				        				*
*								Author:				wjh776a68												*
*  								Function:			File IO Functions set header file.		    			*
*	 							CreateTime:			2020/10/02												*
* 								LastUpdateTime:		2020/10/02												*
* 																											*
*************************************************************************************************************/

#pragma once

#include<fstream>
#include<ios>
#include "DAcommon.h"

#ifndef FILEIOFUNCTIONS_CLASS
#define FILEIOFUNCTIONS_CLASS

//文件读写类
class FileIOFunctionsclass
{
public:
	FileIOFunctionsclass() {};										//构造函数
	void selectFile(TCHAR* FilePath);								//文件选择
	TCHAR* Reads();													//文件读取
	int Saves(TCHAR* filepath, TCHAR* content);						//文件保存
	int Writes(TCHAR* content);										//文件写入
	bool isEndofFile();												//文件是否结尾
	TCHAR Read();													//文件读一个字
	int GetCurrentLocation();										//获取当前文件指针位置
	int SetCurrentLocation(int NewLocation);						//设置当前文件指针位置
	int MoveNextLocation();											//文件指针移动到下一位
	int MovePeriousLocation();										//文件指针移动到前一位
	void closeFile();												//文件关闭
private:
	std::FILE* currentfilestruct;									//文件结构
	TCHAR currentFilePath[PATHMAXLEN + SUFFIXMAXLEN];				//当前文件路径
	TCHAR tmpFilePath[SUFFIXMAXLEN + PATHMAXLEN];					//文件路径临时变量
};

#endif