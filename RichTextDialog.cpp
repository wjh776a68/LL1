
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68	2020											*
* 																											*
*								File Name:			RichTextDialog.cpp				        				*
*								Author:				wjh776a68												*
*  								Function:			RichTextbox functions set source file.					*
*	 							CreateTime:			2020/10/02												*
* 								LastUpdateTime:		2020/10/04												*
* 																											*
*************************************************************************************************************/

//#include "pch.h"
#include "RichTextDialog.h"

#define TCHARBUFFER_MAXLEN 4096						//富文本框内容备份区长度
TCHAR tchar_buffer[TCHARBUFFER_MAXLEN] = { 0 };		//富文本框内容备份区

/******************************************************************************
*				函数名：		RichTextDialog_Lock
*				函数功能：	将富文本框文本操作拷贝一份到备份区
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
//void RichTextDialogclass::RichTextDialog_Lock() {
//	//GetWindowText(RichTextDialog_bindhWnd, lockCache, TCHARBUFFER_MAXLEN);
//	
//
//}
//

/******************************************************************************
*				函数名：		RichTextDialog_Lock
*				函数功能：	停止拷贝并将备份区文本内容导入富文本框
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
//void RichTextDialogclass::RichTextDialog_UnLock() {
//	//SetWindowText(RichTextDialog_bindhWnd, lockCache);
//}

/******************************************************************************
*				函数名：		RichTextDialog_GetText
*				函数功能：	读取富文本框全部文本
*				传入参数：	void
*				传出参数：	tchar_buffer	TCHAR*	返回全部文本
*******************************************************************************/
TCHAR* RichTextDialogclass::RichTextDialog_GetText() {
	GetWindowText(RichTextDialog_bindhWnd, tchar_buffer, TCHARBUFFER_MAXLEN);
	
	return tchar_buffer;
}

/******************************************************************************
*				函数名：		RichTextDialog_AppendText
*				函数功能：	富文本框追加字符
*				传入参数：	content    TCHAR*      要追加的字符
*				传出参数：	void
*******************************************************************************/
void RichTextDialogclass::RichTextDialog_AppendText(TCHAR* content) {
	GetWindowText(RichTextDialog_bindhWnd, tchar_buffer, TCHARBUFFER_MAXLEN);
	lstrcat(tchar_buffer, content);
	//lstrcat(lockCache, content);
	SetWindowText(RichTextDialog_bindhWnd, tchar_buffer);
}

/******************************************************************************
*				函数名：		RichTextDialog_BindHWND
*				函数功能：	绑定富文本框
*				传入参数：	bindhWnd    HWND      要绑定的富文本框窗口句柄
*				传出参数：	void
*******************************************************************************/
void RichTextDialogclass::RichTextDialog_BindHWND(HWND bindhWnd) {
	RichTextDialog_bindhWnd = bindhWnd;
}

/******************************************************************************
*				函数名：		RichTextDialog_ClearText
*				函数功能：	清空富文本框
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
void RichTextDialogclass::RichTextDialog_ClearText() {
	SetWindowText(RichTextDialogclass::RichTextDialog_bindhWnd, blank);
	//lstrcpy(lockCache, TEXT(""));

}

/******************************************************************************
*				函数名：		RichTextDialog_SetText
*				函数功能：	设置富文本框文件内容
*				传入参数：	content    TCHAR*      富文本框文件内容
*				传出参数：	void
*******************************************************************************/
void RichTextDialogclass::RichTextDialog_SetText(TCHAR* content) {
	SetWindowText(RichTextDialog_bindhWnd, content);
	//lstrcpy(lockCache, content);
}

/******************************************************************************
*				函数名：		RichTextDialog_GetLength
*				函数功能：	读取富文本框文本长度
*				传入参数：	void
*				传出参数：					long		富文本框长度
*******************************************************************************/
long RichTextDialogclass::RichTextDialog_GetLength() {
	_gettextlengthex CurrentTextLength;
	CurrentTextLength.flags = GTL_DEFAULT;
	CurrentTextLength.codepage = CP_ACP;
	return (long)SendMessage(RichTextDialog_bindhWnd, EM_GETTEXTLENGTHEX, (WPARAM)&CurrentTextLength, 0);
}

/******************************************************************************
*				函数名：		RichTextDialog_GetChar
*				函数功能：	读取富文本框指定位置字符
*				传入参数：	position		long		获取指定位置字符
*				传出参数：	tmpoutputCHAR	CHAR*		字符值
*******************************************************************************/
CHAR* RichTextDialogclass::RichTextDialog_GetChar(long position) {
	
	_textrange CurrentSelectTextRange_iterator;
	CHARRANGE CurrentSelectTextCharRange_iterator;
	
	CurrentSelectTextRange_iterator.lpstrText = tmpoutputCHAR;
	long currentlength = RichTextDialog_GetLength();
	if(position<currentlength) {
		CurrentSelectTextCharRange_iterator.cpMin = position;
		CurrentSelectTextCharRange_iterator.cpMax = position + 1;
		CurrentSelectTextRange_iterator.chrg = CurrentSelectTextCharRange_iterator;
	
		SendMessage(RichTextDialog_bindhWnd, EM_GETTEXTRANGE, 0, (LPARAM)&CurrentSelectTextRange_iterator);
	}
	else {
		*tmpoutputCHAR = '\0';
	}
	

	
	return tmpoutputCHAR;
}