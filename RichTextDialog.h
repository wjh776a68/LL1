
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

//富文本框类
class RichTextDialogclass {
public:
	void RichTextDialog_BindHWND(HWND bindhWnd);			//绑定hwnd
	void RichTextDialog_SetText(TCHAR* content);			//填充文本
	void RichTextDialog_AppendText(TCHAR* content);			//追加文本
	void RichTextDialog_ClearText();						//清空文本框

	//void RichTextDialog_Lock();							//开启文本缓存
	//void RichTextDialog_UnLock();							//结束文本缓存

	TCHAR* RichTextDialog_GetText();						//获取文本
	CHAR* RichTextDialog_GetChar(long position);			//获取指定位置单个文本

	long RichTextDialog_GetLength();						//获取目前富文本框文本长度

	CHAR tmpoutputCHAR[4];									//临时输出单个字符
private:
	
	TCHAR blank[1] = TEXT("");
	HWND RichTextDialog_bindhWnd=NULL;						//绑定的hwnd
	//TCHAR lockCache[CACHEMAXLEN] = TEXT("");
};

#endif