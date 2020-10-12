
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
	CheckLL1class();																//���캯��
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

	std::set<char> SymbolSet;		//�ս������
private:
	void outputbystep(std::string formformula,std::string action);


	std::string findWholeString(char input);
	void getFIRSTsets();
	void getFOLLOWsets();
	void getStatusSheet();

	bool replaceStacktop(char arg1, char arg2);
	void mixoutput();

	//RichTextDialogclass Output_Bind_RichTextDialogclass;
	HWND				Output_Bind_RichTextDialogclass;						//����б����
	HWND				FirstSet_Bind_RichTextDialogclass;						//First���б����
	HWND				FollowSet_Bind_RichTextDialogclass;						//Follow���б����
	HWND				StatusSheet_Bind_RichTextDialogclass;					//״̬ת��ͼ�б����
	RichTextDialogclass Input_Bind_RichTextDialogclass;							//�����ı����������
	int					nIndex;													//����б��Ԫ���� ��������

	int					Analysestep;
	TCHAR				output[MAXLEN] = { 0 };
	TCHAR				tmptchar[MAXLEN] = { 0 };

	std::string			stringoutput;
	TCHAR				newline[10] = TEXT("\r\n");								//����TCHAR*�ַ���

	TCHAR				stackoutput[MAXLEN] = { 0 };							//������ʱ����
	TCHAR				restoutput[MAXLEN] = { 0 };								//����������ʱ����
	TCHAR				GrammarFormulaoutput[MAXLEN] = { 0 };					//����������ʱ����
	TCHAR				actionoutput[MAXLEN] = { 0 };							//����������ʱ����

	TCHAR				tcharrow[3] = { 0 };									//����ʱ����
	TCHAR				tcharcol[3] = { 0 };									//����ʱ����

	TCHAR				nulldivision[6];
	TCHAR				equaldivision[6];

	char				str2[MAXLEN];

	long				totalLength;
	long				iterator_pointer;

	std::string			Grammaroutput;											//replaceStacktop ����﷨
	std::string			Grammarrightsentence;									//replaceStacktop ����Ҳ�	

	std::deque<char>	AnalyseStack;
	std::map<char, std::map<char, std::string>> AnalyseSheet;
	std::multimap<std::string, std::string> GrammarFormula;

	std::map<char, std::set<char>> FIRSTset;
	std::map<char, std::set<char>> FOLLOWset;
};