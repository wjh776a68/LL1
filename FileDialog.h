
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68 2019-2020										*
* 																											*
*								File Name:			FileDialog.h											*
*								Author:				wjh776a68												*
*  								Function:			File Browser header code								*
*	 							CreateTime:			2020/05/02												*
* 								LastUpdateTime:		2020/10/02												*
* 																											*
*************************************************************************************************************/

#pragma once
#include "DAcommon.h"



#ifndef FILE_DIALOG_CLASS
#define FILE_DIALOG_CLASS

#define FILE_DIALOG_CMD_OPEN 1
#define FILE_DIALOG_CMD_CREATE 0



//文件对话框类
class FileDialogClass {
public:
	bool isfilepathvalid=false;							//filepath whether valid
	FileDialogClass() { clearLastfilepath(); };
	TCHAR* getfilepath(bool isopennotcreate);		//return the path your need
	TCHAR* getLastfilepath();						//return the last path your selected
	void	clearLastfilepath();					//clear the last path your selected
	//void saveLastfilepath(TCHAR* logfilepath);		//save the last path to file
	//TCHAR* loadLastfilepath(TCHAR* logfilepath);	//load the last path from file
private:
	TCHAR Lastfilepath[PATHMAXLEN + SUFFIXMAXLEN];
	bool OpenWindowsDlg(bool IsOpen, bool IsPickFolder, TCHAR* pFilePath);
	
};

#endif