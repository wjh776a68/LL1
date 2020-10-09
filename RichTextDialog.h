
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68	2020											*
* 																											*
*								File Name:			RichTextDialog.h				        				*
*								Author:				wjh776a68												*
*  								Function:			RichTextbox functions set header file.					*
*	 							CreateTime:			2020/10/02												*
* 								LastUpdateTime:		2020/10/04												*
* 																											*
*************************************************************************************************************/

#pragma once

#ifndef RICHTEXTDIALOGCLASS
#define RICHTEXTDIALOGCLASS

#include "DAcommon.h"

//#define CACHEMAXLEN 2048

//���ı�����
class RichTextDialogclass {
public:
	void RichTextDialog_BindHWND(HWND bindhWnd);			//��hwnd
	void RichTextDialog_SetText(TCHAR* content);			//����ı�
	void RichTextDialog_AppendText(TCHAR* content);			//׷���ı�
	void RichTextDialog_ClearText();						//����ı���

	//void RichTextDialog_Lock();							//�����ı�����
	//void RichTextDialog_UnLock();							//�����ı�����

	TCHAR* RichTextDialog_GetText();						//��ȡ�ı�
	CHAR* RichTextDialog_GetChar(long position);			//��ȡָ��λ�õ����ı�

	long RichTextDialog_GetLength();						//��ȡĿǰ���ı����ı�����

	CHAR tmpoutputCHAR[4];									//��ʱ��������ַ�
private:
	
	TCHAR blank[1] = TEXT("");
	HWND RichTextDialog_bindhWnd=NULL;						//�󶨵�hwnd
	//TCHAR lockCache[CACHEMAXLEN] = TEXT("");
};

#endif