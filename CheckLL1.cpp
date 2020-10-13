
/************************************************************************************************************
*								This Source File is part of LL(1) Project									*
* 								    Copyright (c) wjh776a68 2020								    		*
* 																											*
*								File Name:			CheckLL1.cpp						        			*
*								Author:				wjh776a68												*
*  								Function:			Functions of LL1 Analyse, source code					*
*	 							CreateTime:			2020/10/08												*
* 								LastUpdateTime:		2020/10/13												*
* 																											*
*************************************************************************************************************/

#include "CheckLL1.h"

#define NULLCHARACTER '$'

#define getStackTop *(AnalyseStack.rbegin())
#define getStringTop Input_Bind_RichTextDialogclass.tmpoutputCHAR[0]

#define outStack AnalyseStack.pop_back()
#define pushStack(i) AnalyseStack.push_back(i)

CheckLL1class::CheckLL1class() {
	//AnalyseSheet['E']['i'] = "TG";	//转换表，忽略FIRST，FOLLOW集可直接参与运算。
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



int CheckLL1class::DoCheck() {
	
	bool error = false;
	SendMessage(Output_Bind_RichTextDialogclass, LVM_DELETEALLITEMS, 0, 0);
	nIndex = -1;
	totalLength = Input_Bind_RichTextDialogclass.RichTextDialog_GetLength();
	iterator_pointer = 0;
	AnalyseStack.clear();
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
		auto getStackSecond = AnalyseStack.rbegin();
		getStackSecond++;
		if (getStackSecond == AnalyseStack.rend()) {
			;
		}
		if (getStackTop == '#') {
			return 0;
		}

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
		}
		else if (replaceStacktop(getStackTop, thechar) == true) {
			outputbystep(Grammaroutput, Grammarrightsentence);
		}
		else {
			MessageBoxW(NULL, TEXT("LL（1）文法分析失败"), TEXT("该句子不属于该文法！"), NULL);
			error = true;
			return -1;
		}
		nIndex++;
	}
	

	return 0;
}

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
*				函数名：		outputFirstSet
*				函数功能：	向绑定的First输出列表框输出结果
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::outputFirstSet() {
	LV_ITEM lv;
	lv.mask = LVIF_TEXT;
	lv.iItem = 0;
	lv.iImage = 0;
	std::string tmp;
	for (auto i = FIRSTset.begin(); i != FIRSTset.end(); i++) {
		lv.iSubItem = 0;

		tmp = "FIRST(";
		tmp += i->first;
		tmp += ")";

		lv.pszText = toTCHAR(tmp);
		ListView_InsertItem(FirstSet_Bind_RichTextDialogclass, &lv);

		tmp = "{";
		auto thelast = i->second.end();
		thelast--;
		for (auto ii = i->second.begin(); ii != thelast; ii++) {
			tmp += *ii;
			tmp += ",";
		}
		tmp += *thelast;
		tmp += "}";

		lv.iSubItem = 1;
		lv.pszText = toTCHAR(tmp);
		ListView_SetItem(FirstSet_Bind_RichTextDialogclass, &lv);

		lv.iItem++;
	}
}

/******************************************************************************
*				函数名：		outputFollowSet
*				函数功能：	向绑定的Follow输出列表框输出结果
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::outputFollowSet() {
	LV_ITEM lv;
	lv.mask = LVIF_TEXT;
	lv.iItem = 0;
	lv.iImage = 0;
	std::string tmp;
	for (auto i = FOLLOWset.begin(); i != FOLLOWset.end(); i++) {
		lv.iSubItem = 0;

		tmp = "FOLLOW(";
		tmp += i->first;
		tmp += ")";

		lv.pszText = toTCHAR(tmp);
		ListView_InsertItem(FollowSet_Bind_RichTextDialogclass, &lv);

		tmp = "{";
		auto thelast = i->second.end();
		thelast--;
		for (auto ii = i->second.begin(); ii != thelast; ii++) {
			tmp += *ii;
			tmp += ",";
		}
		tmp += *thelast;
		tmp += "}";

		lv.iSubItem = 1;
		lv.pszText = toTCHAR(tmp);
		ListView_SetItem(FollowSet_Bind_RichTextDialogclass, &lv);

		lv.iItem++;
	}
}


/******************************************************************************
*				函数名：		outputStatusSheet
*				函数功能：	向绑定的状态转换表输出列表框输出结果
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::outputStatusSheet() {
	LV_ITEM lv;
	lv.mask = LVIF_TEXT;
	lv.iItem = 0;
	lv.iImage = 0;

	for (auto i = AnalyseSheet.begin(); i != AnalyseSheet.end(); i++) {
		lv.iSubItem = 0;

		lv.pszText = toTCHAR(std::string{ i->first });
		ListView_InsertItem(StatusSheet_Bind_RichTextDialogclass, &lv);

		lv.iSubItem++;
		for (auto ii = SymbolSet.begin(); ii != SymbolSet.end(); ii++) {
			
			if (i->second.find(*ii) != i->second.end()) {
				lstrcpy(tmptchar, toTCHAR(std::string{ i->first }));
				lstrcat(tmptchar, equaldivision);
				
				if(i->second.find(*ii)->second!="")
					lstrcat(tmptchar, toTCHAR(std::string{ i->second.find(*ii)->second }));
				else
					lstrcat(tmptchar, nulldivision);
			}
			else {
				lstrcpy(tmptchar, toTCHAR(std::string{ ' ' }));
			}
			
			lv.pszText = tmptchar;
			ListView_SetItem(StatusSheet_Bind_RichTextDialogclass, &lv);

			lv.iSubItem++;
		}

		lv.iItem++;
	}
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
	memset(actionoutput, '\0', sizeof(actionoutput));

	stringoutput = "";

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
*				函数名：		BindoutputFirstSetHWND
*				函数功能：	绑定FIRST列表框的窗口句柄
*				传入参数：	Output_RichTextDialogclass HWND 要绑定的窗口句柄
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::BindoutputFirstSetHWND(HWND Output_RichTextDialogclass){
	// TODO: Add your implementation code here.
	HWND tmp = Output_RichTextDialogclass;
	FirstSet_Bind_RichTextDialogclass = tmp;
}

/******************************************************************************
*				函数名：		BindoutputFollowSetHWND
*				函数功能：	绑定FIRST列表框的窗口句柄
*				传入参数：	Output_RichTextDialogclass HWND 要绑定的窗口句柄
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::BindoutputFollowSetHWND(HWND Output_RichTextDialogclass) {
	// TODO: Add your implementation code here.
	HWND tmp = Output_RichTextDialogclass;
	FollowSet_Bind_RichTextDialogclass = tmp;
}

/******************************************************************************
*				函数名：		BindoutputStatusSheetHWND
*				函数功能：	绑定FIRST列表框的窗口句柄
*				传入参数：	Output_RichTextDialogclass HWND 要绑定的窗口句柄
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::BindoutputStatusSheetHWND(HWND Output_RichTextDialogclass) {
	// TODO: Add your implementation code here.
	HWND tmp = Output_RichTextDialogclass;
	StatusSheet_Bind_RichTextDialogclass = tmp;

	for (auto i = AnalyseSheet.begin(); i != AnalyseSheet.end(); i++)
		for (auto ii = i->second.begin(); ii != i->second.end(); ii++)
			SymbolSet.insert(ii->first);
}

/******************************************************************************
*				函数名：		getFIRSTsets
*				函数功能：	获取FIRST集
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
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

/******************************************************************************
*				函数名：		getFOLLOWsets
*				函数功能：	获取FOLLOW集
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::getFOLLOWsets() {

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

/******************************************************************************
*				函数名：		getStatusSheet
*				函数功能：	获取状态转换表
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::getStatusSheet() {
	for (auto i = FIRSTset.begin(); i != FIRSTset.end(); i++) {
		for (auto ii = i->second.begin(); ii != i->second.end(); ii++) {
			if (*ii != NULLCHARACTER) {
				int sum = 0;
				std::string possibleresult1 = "", possibleresult2 = "";
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
					MessageBoxW(NULL, TEXT("LL（1）文法分析失败"), TEXT("获取状态转换表时出现错误！"), NULL);
					return;
					//MessageBox(NULL, NULL, NULL, NULL);
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
}


/******************************************************************************
*				函数名：		ChecktoEraseRecursion
*				函数功能：	计算是否文法含有直间接左递归，并得出消去左递归后的文法
*				传入参数：	void
*				传出参数：	result	ChecktoEraseRecursion_result
*******************************************************************************/
ChecktoEraseRecursion_result CheckLL1class::ChecktoEraseRecursion() {
	ChecktoEraseRecursion_result result;
																//非终结符集合
	std::map<std::string, std::string> CheckGrammarFormula;
	int stepcounter = 4000;
	result.isNeedToTransfer = false;
	result.CheckGrammarFormula.clear();

	CheckGrammarFormula.insert(GrammarFormula.begin(), GrammarFormula.end());

	bool record = 1;
	for (auto i = CheckGrammarFormula.begin(); i != CheckGrammarFormula.end(); i++) {
		VnSet.insert(i->second.at(0));
	}
	//auto mosti = VnSet.rend();																//最高终结符
	//mosti--;
	for (auto i = VnSet.rbegin(); i != VnSet.rend()/*mosti*/; i++) {										//按顺序排列非终结符，并指定一非终结符，消去其余非终结符，从而观察是否含有左递归
		if (*i == mostcharacter)
			continue;

		for (auto ii = CheckGrammarFormula.begin(); ii != CheckGrammarFormula.end() && stepcounter>0; ii++, stepcounter--) {
			std::string tmp="";
			int catchpos=(int)ii->first.find(*i);
			if (catchpos >= 0) {
				for (auto formulaofi = CheckGrammarFormula.begin(); formulaofi != CheckGrammarFormula.end() && stepcounter>0; stepcounter--) {
					
					if (formulaofi->second.at(0) == *i) {
						tmp = ii->first.substr(0, catchpos);
						tmp += formulaofi->first;
						tmp += ii->first.substr((int)catchpos + 1, tmp.length());
						CheckGrammarFormula.insert(std::make_pair(tmp,ii->second));

						//auto oldformulaofi = formulaofi;			//临时变量，要消除的变量
						formulaofi++;
						//CheckGrammarFormula.erase(oldformulaofi);
					}
					else {
						formulaofi++;
					}
				}
			}
		}
	}

	if (stepcounter <= 0) {
		return result;
	}

	auto i = VnSet.rbegin();
	for (; i != VnSet.rend()/*mosti*/; i++) {
		if (*i == mostcharacter)
			continue;

		for (auto ii = CheckGrammarFormula.begin(); ii != CheckGrammarFormula.end();) {	//删除含其他符号的多余表达式
			int thepos =ii->first.find(*i);
			if (thepos >= 0 || ii->second.at(0)==*i) {
				auto oldii = ii;
				ii++;
				CheckGrammarFormula.erase(oldii);
			}
			else {
				ii++;
			}
		}
	}

	char newchar;																					//新增的非终结符
	for (newchar = 'A'; newchar <= 'Z'; newchar++) {
		if (newchar != CheckGrammarFormula.begin()->second.at(0)) {
			break;
		}
	}
	
	for (auto i = CheckGrammarFormula.begin(); i != CheckGrammarFormula.end();) {	//查看是否含有左递归
		if (i->first.at(0) == i->second.at(0)) {
			result.isNeedToTransfer = true;
			std::string tmpstring = i->first.substr(1, i->first.length());
			tmpstring += newchar;

			result.CheckGrammarFormula.insert(std::make_pair(tmpstring, std::string{ newchar }));
			result.CheckGrammarFormula.insert(std::make_pair(std::string{ NULLCHARACTER }, std::string{ newchar }));
			auto oldi = i;
			i++;
			CheckGrammarFormula.erase(oldi);
		}
		else {
			std::string tmpstring = i->first;
			tmpstring += newchar;
			result.CheckGrammarFormula.insert(std::make_pair(tmpstring, i->second));
			auto oldi = i;
			i++;
			CheckGrammarFormula.erase(oldi);
		}

	}

	return result;
}

/******************************************************************************
*				函数名：		buildAnalyseSheet
*				函数功能：	将输入文法转换为状态转换表
*				传入参数：	input	std::string		输入的文法内容
*				传出参数：	void
*******************************************************************************/
void CheckLL1class::buildAnalyseSheet(std::string input) {
	std::string tmp = input;

	FIRSTset.clear();
	FOLLOWset.clear();
	FOLLOWset[input.at(0)].insert('#');
	mostcharacter = input.at(0);

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

	auto returnvalue=ChecktoEraseRecursion();
	if (returnvalue.isNeedToTransfer == true) {
		GrammarFormula.clear();
		GrammarFormula.insert(returnvalue.CheckGrammarFormula.begin(), returnvalue.CheckGrammarFormula.end());

		Input_Bind_RichTextDialogclass.RichTextDialog_ClearText();

		std::string tmpoutput = "";
		for (auto tmpi = GrammarFormula.begin(); tmpi != GrammarFormula.end(); tmpi++) {
			tmpoutput += tmpi->second + "->" + tmpi->first + "\r\n";
		}
		Input_Bind_RichTextDialogclass.RichTextDialog_SetText(toTCHAR(tmpoutput));
	}

	getFIRSTsets();
	getFOLLOWsets();
	getStatusSheet();
	
	GrammarFormula.erase(std::string{ NULLCHARACTER});
}