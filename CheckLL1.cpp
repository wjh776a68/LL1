
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

#define NULLCHARACTER '$'

#define getStackTop *(AnalyseStack.rbegin())
#define getStringTop Input_Bind_RichTextDialogclass.tmpoutputCHAR[0]

#define outStack AnalyseStack.pop_back()
#define pushStack(i) AnalyseStack.push_back(i)

CheckLL1class::CheckLL1class() {
	//AnalyseSheet['E']['i'] = "TG";	//转换表
	//AnalyseSheet['E']['('] = "TG";
	//AnalyseSheet['G']['+'] = "+TG";
	//AnalyseSheet['G']['-'] = "-TG";
	//AnalyseSheet['G'][')'] = "";
	//AnalyseSheet['G']['#'] = "";
	//AnalyseSheet['T']['i'] = "FS";
	//AnalyseSheet['T']['('] = "FS";
	//AnalyseSheet['S']['+'] = "";
	//AnalyseSheet['S']['-'] = "";
	//AnalyseSheet['S']['*'] = "*FS";
	//AnalyseSheet['S']['/'] = "/FS";
	//AnalyseSheet['S'][')'] = "";
	//AnalyseSheet['S']['#'] = "";
	//AnalyseSheet['F']['i'] = "i";
	//AnalyseSheet['F']['('] = "(E)";

	//GrammarFormula["TG"]	= "E";
	//GrammarFormula["+TG"]	= "G";
	//GrammarFormula["-TG"]	= "G";
	//GrammarFormula["FS"]	= "T";
	//GrammarFormula["*FS"]	= "S";
	//GrammarFormula["/FS"]	= "S";
	//GrammarFormula["(E)"]	= "F";
	//GrammarFormula["i"]		= "F";

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

void CheckLL1class::getFIRSTsets() {
	
	

	std::set<std::string> tmpunbuildsymbol,tmptotalbuildsymbol;
	
	for (auto i = GrammarFormula.begin(); i != GrammarFormula.end(); i++) {
		tmpunbuildsymbol.insert(i->second);
		tmptotalbuildsymbol.insert(i->second);
	}
	bool issolveable = false;
	std::set<std::string>::iterator i,li;
	while (tmpunbuildsymbol.empty() == false) {
		for ( i = tmpunbuildsymbol.begin(); i != tmpunbuildsymbol.end(); i++) {
			if (issolveable == true) {
				tmpunbuildsymbol.erase(std::string{ li->at(0) });
				if (tmpunbuildsymbol.empty() == true) {
					break;
				}
			}
			issolveable = true;
			for (auto ii = GrammarFormula.begin(); ii != GrammarFormula.end(); ii++) {
				if (ii->second.at(0) == i->at(0) && tmpunbuildsymbol.find(std::string{ ii->first.at(0) }) != tmpunbuildsymbol.end()) {
					//shangweikejie
					issolveable = false;
				}
				
			}
			if (issolveable == true) {
				for (auto ii = GrammarFormula.begin(); ii != GrammarFormula.end(); ii++) {
					if (ii->second.at(0) == i->at(0)) {
						//shangweikejie
						if (tmptotalbuildsymbol.find(std::string{ ii->first.at(0) }) != tmptotalbuildsymbol.end()) {
							FIRSTset[i->at(0)].insert(FIRSTset[ii->first.at(0)].begin(), FIRSTset[ii->first.at(0)].end());
						}
						else {
							FIRSTset[i->at(0)].insert(ii -> first.at(0));
						}
					}
				}			
			}
			li = i;
		}

		
	}
}

void CheckLL1class::getFOLLOWsets() {
	

	//FOLLOWset[GrammarFormula.begin()->second.at(0)].insert('#');

	std::set<std::string> tmptotalbuildsymbol;

	for (auto i = GrammarFormula.begin(); i != GrammarFormula.end(); i++) {
		tmptotalbuildsymbol.insert(i->second);
	}

	std::map<char, std::map<char, bool>> FirstLinear, FollowLinear;			//First集约束条件, Follow集约束条件

	for (auto i = GrammarFormula.begin(); i != GrammarFormula.end(); i++) {
		auto theend = i->first.rend();
		theend--;
		for (auto t = i->first.rbegin(); t != theend; t++) {
			if (tmptotalbuildsymbol.find(std::string{ *(t + 1) }) != tmptotalbuildsymbol.end()) {
				if(tmptotalbuildsymbol.find(std::string{ *(t) }) != tmptotalbuildsymbol.end())
					//FirstLinear[*t][*(t + 1)] = true;
					FOLLOWset[*(t + 1)].insert(FIRSTset[*t].begin(), FIRSTset[*t].end());
				else
					FOLLOWset[*(t+1)].insert(*t);
				FOLLOWset[*(t + 1)].erase(NULLCHARACTER);
			}
				
				
		}
	}

	for (auto i = GrammarFormula.begin(); i != GrammarFormula.end(); i++) {
		for (auto t = i->first.rbegin(); t != i->first.rend(); t++) {
			if (tmptotalbuildsymbol.find(std::string{ *t }) != tmptotalbuildsymbol.end() || *t ==NULLCHARACTER) {
				if(*t != NULLCHARACTER && i->second.at(0) != *t)
					FollowLinear[i->second.at(0)][*t] = true;
				if (*t != NULLCHARACTER && FIRSTset[*t].find(NULLCHARACTER) == FIRSTset[*t].end()) {	//不包含空集
					break;
				}
			}
			else {
				break;
			}
				
		}
	}

	while (FollowLinear.size() > 0) {
		for (auto i = tmptotalbuildsymbol.begin(); i != tmptotalbuildsymbol.end();) {
			bool isOK = true;
			for (auto ii = FollowLinear.begin(); ii != FollowLinear.end(); ii++) {
				if (ii->second.find(i->at(0)) != ii->second.end()) {
					isOK = false;
				}
			}

			if (isOK == true) {
				//for (auto ii = FirstLinear[i->at(0)].begin(); ii != FirstLinear[i->at(0)].end(); ii++) {
				//		FOLLOWset[i->at(0)].insert(FIRSTset[ii->first].begin(), FIRSTset[ii->first].end());
				//}

				for (auto ii = FollowLinear[i->at(0)].begin(); ii != FollowLinear[i->at(0)].end(); ii++) {
					FOLLOWset[ii->first].insert(FOLLOWset[i->at(0)].begin(), FOLLOWset[i->at(0)].end());
				}

				auto tmp = i;
				i++;
				FollowLinear.erase(tmp->at(0));

			}
			else {
				i++;
			}
		}
	}
	
}

void CheckLL1class::buildAnalyseSheet(std::string input) {
	std::string tmp = input;
	FIRSTset.clear();
	FOLLOWset.clear();
	FOLLOWset[input.at(0)].insert('#');
	std::string tmpheader, tmptail;
	int flag = 1;	//flag==1 for tmpheader flag==2 for tmptail
	for (auto i = tmp.begin(); i != tmp.end(); i++) {
		if (*i == '\r' || *i == '\n' && flag==2) {
			if(tmptail!="" && tmpheader!="")
				GrammarFormula.insert(std::make_pair(tmptail, tmpheader));
				//GrammarFormula[tmptail] = tmpheader;

			tmpheader = "";
			tmptail = "";
			flag = 1;
			i++;
		}
		else if(*i == '-' && *(i+1) == '>' && flag==1){
			i++;
			flag = 2;

		}
		else if (*i == '|' && flag == 2) {
			//GrammarFormula[tmptail] = tmpheader;
			GrammarFormula.insert(std::make_pair(tmptail, tmpheader));
			tmptail = "";
		}
		else if (flag == 1) {
			tmpheader += *i;
		}else if(flag == 2) {
			tmptail += *i;
		}
	}
	if (tmptail != "" && tmpheader != "")
		GrammarFormula.insert(std::make_pair(tmptail, tmpheader)); 
		//GrammarFormula[tmptail] = tmpheader;

	getFIRSTsets();
	getFOLLOWsets();


	for (auto i = FIRSTset.begin(); i != FIRSTset.end(); i++) {
		for (auto ii = i->second.begin(); ii != i->second.end(); ii++) {
			if (*ii != NULLCHARACTER) {
				int sum = 0;
				std::string possibleresult1="", possibleresult2="";
				for (auto i_tmp = GrammarFormula.begin(); i_tmp != GrammarFormula.end(); i_tmp++) {
					if (i_tmp->second.at(0) == i->first) {
						sum++;
						possibleresult1 = i_tmp->first;
					}
					if (i_tmp->second.at(0) == i->first && i_tmp->first.at(0) == *ii) {
						possibleresult2 = i_tmp->first;
					}
				}
				
				if (possibleresult2 != "")
					AnalyseSheet[i->first][*ii] = possibleresult2;
				else if (sum != 0 && possibleresult1 != "") {
					AnalyseSheet[i->first][*ii] = possibleresult1;
				}
				else {
					MessageBox(NULL, NULL, NULL, NULL);
				}
			}			
			else {
				for (auto tmper = FOLLOWset[i->first].begin(); tmper != FOLLOWset[i->first].end(); tmper++) {
					AnalyseSheet[i->first][*tmper] = "";
				}
				//int sum = 0;
				//std::string possibleresult1 = "", possibleresult2 = "";
				//for (auto i_tmp = GrammarFormula.begin(); i_tmp != GrammarFormula.end(); i_tmp++) {
				//	if (i_tmp->second.at(0) == i->first) {
				//		sum++;
				//		possibleresult1 = "";
				//	}
				//	if (*i_tmp->first.rbegin() == *ii) {
				//		possibleresult2 = "";
				//	}
				//}
				
				//AnalyseSheet[i->first][*ii] = "";

			}
				
		}
		
	}

	GrammarFormula.erase("$");
}