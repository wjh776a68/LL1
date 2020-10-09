
/************************************************************************************************************
*								This Source File is part of LL(1) Project									*
* 								    Copyright (c) wjh776a68 2020								    		*
* 																											*
*								File Name:			CheckLL1.h							        			*
*								Author:				wjh776a68												*
*  								Function:			Functions of LL1 Analyse, header code					*
*	 							CreateTime:			2020/10/08												*
* 								LastUpdateTime:		2020/10/09												*
* 																											*
*************************************************************************************************************/

#pragma once

#include "RichTextDialog.h"

#include<deque>
#include<map>

class CheckLL1class {
public:
	CheckLL1class();																//构造函数
	~CheckLL1class() {};

	int DoCheck();
	void BindInputHWND(HWND Input_RichTextDialogclass);
	void BindVIWHWND(HWND VIW_RichTextDialogclass);
	void BindOutputHWND(HWND Output_RichTextDialogclass);

	void addVIWtoVIWWindows();

	
private:
	void outputbystep(std::string formformula,std::string action);

	TCHAR* toTCHAR(std::string input);
	TCHAR* toTCHAR(int input);
	std::string findWholeString(char input);

	void mixoutput();

	//RichTextDialogclass Output_Bind_RichTextDialogclass;
	HWND				Output_Bind_RichTextDialogclass;						//输出列表框句柄
	HWND				VIW_Bind_RichTextDialogclass;							//关键词列表框句柄
	RichTextDialogclass Input_Bind_RichTextDialogclass;							//输入文本框类的引用
	int					nIndex;													//输出列表框单元索引 迭代变量

	int Analysestep;
	TCHAR output[MAXLEN] = { 0 };
	std::string stringoutput;
	TCHAR newline[10] = TEXT("\r\n");											//换行TCHAR*字符串

	TCHAR stackoutput[MAXLEN] = { 0 };														//单词临时变量
	TCHAR restoutput[MAXLEN] = { 0 };													//单词属性临时变量
	TCHAR GrammarFormulaoutput[MAXLEN] = { 0 };													//单词类型临时变量
	TCHAR actionoutput[MAXLEN] = { 0 };													//单词行列临时变量


	TCHAR tcharrow[3] = { 0 };													//行临时变量
	TCHAR tcharcol[3] = { 0 };													//列临时变量

	TCHAR nulldivision[6];
	TCHAR equaldivision[6];

	std::string Grammaroutput;													//replaceStacktop 输出语法
	std::string Grammarrightsentence;											//replaceStacktop 输出右部	

	std::deque<char> AnalyseStack;
	bool replaceStacktop(char arg1, char arg2);

	std::map<char, std::map<char, std::string>> AnalyseSheet;

	std::map<std::string, std::string> GrammarFormula;

	char str2[MAXLEN];

	long totalLength;
	long iterator_pointer;
};