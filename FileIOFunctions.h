
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

//�ļ���д��
class FileIOFunctionsclass
{
public:
	FileIOFunctionsclass() {};										//���캯��
	void selectFile(TCHAR* FilePath);								//�ļ�ѡ��
	TCHAR* Reads();													//�ļ���ȡ
	int Saves(TCHAR* filepath, TCHAR* content);						//�ļ�����
	int Writes(TCHAR* content);										//�ļ�д��
	bool isEndofFile();												//�ļ��Ƿ��β
	TCHAR Read();													//�ļ���һ����
	int GetCurrentLocation();										//��ȡ��ǰ�ļ�ָ��λ��
	int SetCurrentLocation(int NewLocation);						//���õ�ǰ�ļ�ָ��λ��
	int MoveNextLocation();											//�ļ�ָ���ƶ�����һλ
	int MovePeriousLocation();										//�ļ�ָ���ƶ���ǰһλ
	void closeFile();												//�ļ��ر�
private:
	std::FILE* currentfilestruct;									//�ļ��ṹ
	TCHAR currentFilePath[PATHMAXLEN + SUFFIXMAXLEN];				//��ǰ�ļ�·��
	TCHAR tmpFilePath[SUFFIXMAXLEN + PATHMAXLEN];					//�ļ�·����ʱ����
};

#endif