
/************************************************************************************************************
*								This Source File is part of LL(1) Project									*
* 								    Copyright (c) wjh776a68 2020								    		*
* 																											*
*								File Name:			CheckLL1.h							        			*
*								Author:				wjh776a68												*
*  								Function:			Functions of LL1 Analyse, header code					*
*	 							CreateTime:			2020/10/08												*
* 								LastUpdateTime:		2020/10/13												*
* 																											*
*************************************************************************************************************/

#pragma once

#include "RichTextDialog.h"

#include <atlstr.h>	//tchar to string
#include<deque>
#include<map>
#include<set>

class CheckLL1class {
public:
	CheckLL1class();																//构造函数
	~CheckLL1class() {};

	void buildAnalyseSheet(std::string input);
	int DoCheck();
	void BindInputHWND(HWND Input_RichTextDialogclass);
	void BindoutputFirstSetHWND(HWND Output_RichTextDialogclass);
	void BindoutputFollowSetHWND(HWND Output_RichTextDialogclass);
	void BindoutputStatusSheetHWND(HWND Output_RichTextDialogclass);
	void BindOutputHWND(HWND Output_RichTextDialogclass);

	void outputFirstSet();
	void outputFollowSet();
	void outputStatusSheet();

	TCHAR* toTCHAR(std::string input);
	TCHAR* toTCHAR(int input);

	std::set<char> SymbolSet;		//终结符集合
private:
	void outputbystep(std::string formformula,std::string action);


	std::string findWholeString(char input);
	void getFIRSTsets();
	void getFOLLOWsets();
	void getStatusSheet();

	bool replaceStacktop(char arg1, char arg2);
	void mixoutput();

	//RichTextDialogclass Output_Bind_RichTextDialogclass;
	HWND				Output_Bind_RichTextDialogclass;						//输出列表框句柄
	HWND				FirstSet_Bind_RichTextDialogclass;						//First集列表框句柄
	HWND				FollowSet_Bind_RichTextDialogclass;						//Follow集列表框句柄
	HWND				StatusSheet_Bind_RichTextDialogclass;					//状态转换图列表框句柄
	RichTextDialogclass Input_Bind_RichTextDialogclass;							//输入文本框类的引用
	int					nIndex;													//输出列表框单元索引 迭代变量

	int					Analysestep;
	TCHAR				output[MAXLEN] = { 0 };
	TCHAR				tmptchar[MAXLEN] = { 0 };

	std::string			stringoutput;
	TCHAR				newline[10] = TEXT("\r\n");								//换行TCHAR*字符串

	TCHAR				stackoutput[MAXLEN] = { 0 };							//单词临时变量
	TCHAR				restoutput[MAXLEN] = { 0 };								//单词属性临时变量
	TCHAR				GrammarFormulaoutput[MAXLEN] = { 0 };					//单词类型临时变量
	TCHAR				actionoutput[MAXLEN] = { 0 };							//单词行列临时变量

	TCHAR				tcharrow[3] = { 0 };									//行临时变量
	TCHAR				tcharcol[3] = { 0 };									//列临时变量

	TCHAR				nulldivision[6];
	TCHAR				equaldivision[6];

	char				str2[MAXLEN];

	long				totalLength;
	long				iterator_pointer;

	std::string			Grammaroutput;											//replaceStacktop 输出语法
	std::string			Grammarrightsentence;									//replaceStacktop 输出右部	

	std::deque<char>	AnalyseStack;
	std::map<char, std::map<char, std::string>> AnalyseSheet;
	std::multimap<std::string, std::string> GrammarFormula;

	std::map<char, std::set<char>> FIRSTset;
	std::map<char, std::set<char>> FOLLOWset;
};