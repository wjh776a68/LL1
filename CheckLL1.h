
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
	CheckLL1class();																//���캯��
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
	HWND				Output_Bind_RichTextDialogclass;						//����б����
	HWND				VIW_Bind_RichTextDialogclass;							//�ؼ����б����
	RichTextDialogclass Input_Bind_RichTextDialogclass;							//�����ı����������
	int					nIndex;													//����б��Ԫ���� ��������

	int Analysestep;
	TCHAR output[MAXLEN] = { 0 };
	std::string stringoutput;
	TCHAR newline[10] = TEXT("\r\n");											//����TCHAR*�ַ���

	TCHAR stackoutput[MAXLEN] = { 0 };														//������ʱ����
	TCHAR restoutput[MAXLEN] = { 0 };													//����������ʱ����
	TCHAR GrammarFormulaoutput[MAXLEN] = { 0 };													//����������ʱ����
	TCHAR actionoutput[MAXLEN] = { 0 };													//����������ʱ����


	TCHAR tcharrow[3] = { 0 };													//����ʱ����
	TCHAR tcharcol[3] = { 0 };													//����ʱ����

	TCHAR nulldivision[6];
	TCHAR equaldivision[6];

	std::string Grammaroutput;													//replaceStacktop ����﷨
	std::string Grammarrightsentence;											//replaceStacktop ����Ҳ�	

	std::deque<char> AnalyseStack;
	bool replaceStacktop(char arg1, char arg2);

	std::map<char, std::map<char, std::string>> AnalyseSheet;

	std::map<std::string, std::string> GrammarFormula;

	char str2[MAXLEN];

	long totalLength;
	long iterator_pointer;
};