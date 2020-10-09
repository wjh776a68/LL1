
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68 2019-2020										*
* 																											*
*								File Name:			DAcommon.h						        				*
*								Author:				wjh776a68												*
*  								Function:			Global Quotes, Varieties and functions					*
*	 							CreateTime:			2020/05/11												*
* 								LastUpdateTime:		2020/10/02												*
* 																											*
*************************************************************************************************************/

#define DEBUG 1
#define MAXLEN 255
#define SUFFIXMAXLEN 255
#define PATHMAXLEN 255



#pragma once

#ifndef DA_define_area
#define DA_define_area

#include <string>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <tchar.h>
#include <stdlib.h>
#include <ios>
#include <string.h>
#include <Richedit.h>
#include <Commctrl.h>
#include <malloc.h>						//calloc
#include <Commdlg.h>
#include <Shlobj.h>						//选择文件夹对话框


#include "resource.h"
#include "FileDialog.h"
#include "FileIOFunctions.h"
#include "RichTextDialog.h"
//#include "CheckDA.h"

#pragma comment(lib,"Shell32.lib")
#pragma comment(lib, "comctl32.lib")



#endif