
/************************************************************************************************************
*								This Source File is part of LL(1) Project									*
* 								    Copyright (c) wjh776a68 2020								    		*
* 																											*
*								File Name:			CheckLL1.cpp						        			*
*								Author:				wjh776a68												*
*  								Function:			Functions of LL1 Analyse, source code					*
*	 							CreateTime:			2020/10/08												*
* 								LastUpdateTime:		2020/10/09												*
* 																											*
*************************************************************************************************************/

#include "CheckLL1.h"

#define getStackTop *(AnalyseStack.rbegin())
#define getStringTop Input_Bind_RichTextDialogclass.tmpoutputCHAR[0]

#define outStack AnalyseStack.pop_back()
#define pushStack(i) AnalyseStack.push_back(i)

CheckLL1class::CheckLL1class() {
	AnalyseSheet['E']['i'] = "TG";	//转换表
	AnalyseSheet['E']['('] = "TG";
	AnalyseSheet['G']['+'] = "+TG";
	AnalyseSheet['G']['-'] = "-TG";
	AnalyseSheet['G'][')'] = "";
	AnalyseSheet['G']['#'] = "";
	AnalyseSheet['T']['i'] = "FS";
	AnalyseSheet['T']['('] = "FS";
	AnalyseSheet['S']['+'] = "";
	AnalyseSheet['S']['-'] = "";
	AnalyseSheet['S']['*'] = "*FS";
	AnalyseSheet['S']['/'] = "/FS";
	AnalyseSheet['S'][')'] = "";
	AnalyseSheet['S']['#'] = "";
	AnalyseSheet['F']['i'] = "i";
	AnalyseSheet['F']['('] = "(E)";

	GrammarFormula["TG"]	= "E";
	GrammarFormula["+TG"]	= "G";
	GrammarFormula["-TG"]	= "G";
	GrammarFormula["FS"]	= "T";
	GrammarFormula["*FS"]	= "S";
	GrammarFormula["/FS"]	= "S";
	GrammarFormula["(E)"]	= "F";
	GrammarFormula["i"]		= "F";

	lstrcpy(equaldivision, TEXT(" → "));
	lstrcpy(nulldivision, TEXT("ε"));
}

bool::CheckLL1class::replaceStacktop(char arg1, char arg2) {
	bool found = false;
	
	//Grammaroutput = "";
	Grammarrightsentence = "";
	for (auto i_iter1 = AnalyseSheet.begin(); i_iter1 != AnalyseSheet.end(); i_iter1++) {
		if (i_iter1->first == arg1)
			for (auto i_iter2 = i_iter1->second.begin(); i_iter2 != i_iter1->second.end(); i_iter2++) {
				if (i_iter2->first == arg2) {
					lstrcpy(GrammarFormulaoutput, toTCHAR(std::string{ arg1 }));
					lstrcat(GrammarFormulaoutput, equaldivision);

					if (i_iter2->second == "") {
						//Grammaroutput = arg1;
						//Grammaroutput += "->NULL";
						
						lstrcat(GrammarFormulaoutput, nulldivision);

					}
					else {
						lstrcat(GrammarFormulaoutput, toTCHAR(i_iter2->second));
						//Grammaroutput = arg1;
						//Grammaroutput += "->";
						//Grammaroutput += i_iter2->second;
					}
					
					found = true;
					outStack;
					for (auto tmp_iter = i_iter2->second.rbegin(); tmp_iter != i_iter2->second.rend(); tmp_iter++) {
						Grammarrightsentence += *tmp_iter;
						pushStack(*tmp_iter);
					}

					if (i_iter2->second == "") {
						Grammarrightsentence = "POP";
					}
					else {
						Grammarrightsentence = "POP, PUSH(" + Grammarrightsentence + ")";
					}
					
					break;
				}
			}
	}
	return found;
}

std::string CheckLL1class::findWholeString(char input) {
	for (auto i_iter = GrammarFormula.begin(); i_iter != GrammarFormula.end(); i_iter++) {
		if (i_iter->first.at(0) == input) {
			return i_iter->second + i_iter->first;
		}
	}
}

int CheckLL1class::DoCheck() {
	
	bool error = false;
	SendMessage(Output_Bind_RichTextDialogclass, LVM_DELETEALLITEMS, 0, 0);
	nIndex = -1;
	totalLength = Input_Bind_RichTextDialogclass.RichTextDialog_GetLength();
	iterator_pointer = 0;

	Analysestep = -1;
	//outputbystep(" ", "初始化");

	pushStack('#');
	pushStack('E');	//前缀入栈
	Analysestep = 0;
	nIndex = 0;
	//outputbystep(" ", " ");
	outputbystep(" ", "inital");
	//return 0 ;
	
	nIndex++;

	char thechar;
	while (iterator_pointer <= totalLength && error==false) {
		if (iterator_pointer < totalLength) {
			Input_Bind_RichTextDialogclass.RichTextDialog_GetChar(iterator_pointer);
			thechar = getStringTop;
		}	
		else {
			thechar = '#';
		}
			
		
		if (getStackTop == thechar) {
			outStack;
			iterator_pointer++;
			
			outputbystep(" ","GETNEXT(I)");
			
			//mixoutput()
		}
		else if (replaceStacktop(getStackTop, thechar) == true) {
			outputbystep(Grammaroutput, Grammarrightsentence);
			/*error = true;
			break;*/
		}
		else {
			MessageBox(NULL, NULL, NULL, NULL);
			error = true;
		}
		nIndex++;
	}
	

	return 0;
}


void CheckLL1class::addVIWtoVIWWindows() {
	

}


#include <atlstr.h>
TCHAR* CheckLL1class::toTCHAR(std::string input) {
	if (input == "") {
		output[0] = '\0';
		output[1] = '\0';
		output[2] = '\0';
		output[3] = '\0';
	}
	else {
		_tcscpy_s(output, CA2T(input.c_str()));
	}
	
	return output;
}

TCHAR* CheckLL1class::toTCHAR(int input) {
	_itot_s(input, output, 10);
	return output;
}
/******************************************************************************
*				函数名：		mixoutput
*				函数功能：	向绑定的输出列表框输出一行结果
*				传入参数：	wc			TCHAR*		单词
*							attrib		TCHAR*		单词属性
*							wordtype	TCHAR*		单词类别
*							position	TCHAR*		单词所在行列
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::mixoutput() {
	
	LV_ITEM lv;
	lv.mask = LVIF_TEXT;
	lv.iSubItem = 0;
	lv.iItem = nIndex;
	lv.iImage = 0;
	lv.pszText = toTCHAR(Analysestep);
	if (lv.iItem >= 0) {
		ListView_InsertItem(Output_Bind_RichTextDialogclass, &lv);
	}
	
	lv.iSubItem = 1;
	lv.pszText = stackoutput;
	if (lv.iItem >= 0) {
		ListView_SetItem(Output_Bind_RichTextDialogclass, &lv);
	}
	lv.iSubItem = 2;
	
	lv.pszText = restoutput;
	if (lv.iItem >= 0) {
		ListView_SetItem(Output_Bind_RichTextDialogclass, &lv);
	}

	//lv.iItem = nIndex + 1;

	lv.iSubItem = 3;
	lv.pszText = GrammarFormulaoutput;
	if (lv.iItem >= 0) {
		ListView_SetItem(Output_Bind_RichTextDialogclass, &lv);
	}
	lv.iSubItem = 4;
	lv.pszText = actionoutput;
	if (lv.iItem >= 0) {
		ListView_SetItem(Output_Bind_RichTextDialogclass, &lv);
	}

	Analysestep++;
}

void CheckLL1class::outputbystep(std::string formformula, std::string action) {
	memset(stackoutput, '\0', sizeof(stackoutput));
	memset(restoutput, '\0', sizeof(restoutput));
	//memset(GrammarFormulaoutput, '\0', sizeof(Grammaroutput));
	memset(actionoutput, '\0', sizeof(actionoutput));

	stringoutput = "";

	//stackoutput = AnalyseStack.begin
	for (auto i_iter = AnalyseStack.begin(); i_iter != AnalyseStack.end(); i_iter++) {
		stringoutput += *i_iter;
	}

	lstrcpy(stackoutput, toTCHAR(stringoutput));
	stringoutput = "";

	for (long i = iterator_pointer; i <= totalLength; i++) {
		if (i == totalLength) {
			stringoutput += "#";
		}
		else {
			Input_Bind_RichTextDialogclass.RichTextDialog_GetChar(i);
			stringoutput += getStringTop;
		}
	}
	lstrcpy(restoutput, toTCHAR(stringoutput));

	//GrammarFormulaoutput;
	//lstrcpy(GrammarFormulaoutput, toTCHAR(formformula));
	

	if (action == "inital") {
		lstrcpy(actionoutput, TEXT("初始化"));
	}
	else {
		lstrcpy(actionoutput, toTCHAR(action));
		
		
	}

	mixoutput();
}


/******************************************************************************
*				函数名：		BindInputHWND
*				函数功能：	绑定输入文本框的窗口句柄
*				传入参数：	Input_RichTextDialogclass HWND 要绑定的窗口句柄
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::BindInputHWND(HWND Input_RichTextDialogclass)
{
	// TODO: Add your implementation code here.
	HWND tmp = Input_RichTextDialogclass;
	Input_Bind_RichTextDialogclass.RichTextDialog_BindHWND(tmp);
}

/******************************************************************************
*				函数名：		BindOutputHWND
*				函数功能：	绑定输出列表框的窗口句柄
*				传入参数：	Output_RichTextDialogclass HWND 要绑定的窗口句柄
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::BindOutputHWND(HWND Output_RichTextDialogclass)
{
	// TODO: Add your implementation code here.
	HWND tmp = Output_RichTextDialogclass;
	Output_Bind_RichTextDialogclass = tmp;
	//Output_Bind_RichTextDialogclass.RichTextDialog_BindHWND(tmp);
}

/******************************************************************************
*				函数名：		BindVIWHWND
*				函数功能：	绑定VIW列表框的窗口句柄
*				传入参数：	VIW_RichTextDialogclass HWND 要绑定的窗口句柄
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::BindVIWHWND(HWND viwhwnd) {
	HWND tmp = viwhwnd;
	VIW_Bind_RichTextDialogclass = tmp;
}