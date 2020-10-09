
/************************************************************************************************************
*								This Source File is part of DA Project										*
* 								    Copyright (c) wjh776a68	2020											*
* 																											*
*								File Name:			FileIOFunctions.cpp				        				*
*								Author:				wjh776a68												*
*  								Function:			File IO Functions set source file.		    			*
*	 							CreateTime:			2020/10/02												*
* 								LastUpdateTime:		2020/10/02												*
* 																											*
*************************************************************************************************************/

//#include "pch.h"
#include "FileIOFunctions.h"

#include < io.h> 




/******************************************************************************
*				函数名：		Reads
*				函数功能：	文件读取全部内容
*				传入参数：	void
*				传出参数：	buffer  	TCHAR*	    得到的文件内容
*               //referrence link: https://my.oschina.net/u/4370928/blog/3410688
*******************************************************************************/
TCHAR* FileIOFunctionsclass::Reads(){   
    // TODO: Add your implementation code here.
    int size = _filelength(_fileno(currentfilestruct));
    TCHAR * buffer = (TCHAR*)malloc(size);
    for (int i = 0; i < size; i++) {
        *(buffer + i) = 0;
    }
    if (size <= 0) {
        MessageBox(NULL,NULL,NULL,NULL);
        return buffer;
    }
    else {
        fread(buffer, size, 1, currentfilestruct);
    }
   

    return buffer;
}

/******************************************************************************
*				函数名：		Saves
*				函数功能：	文件保存全部内容
*				传入参数：	filepath    TCHAR*      文件路径
*                           content     TCHAR*      要保存的内容
*				传出参数：	0           int  	    返回0
*******************************************************************************/
int FileIOFunctionsclass::Saves(TCHAR* filepath, TCHAR* content) {
    lstrcpy(tmpFilePath, filepath);
    if (lstrcmp(tmpFilePath, TEXT(""))) {
        closeFile();

        
       
        _tfopen_s(&currentfilestruct, tmpFilePath, TEXT("w+"));
        fwrite(content, sizeof(TCHAR), lstrlen(content), currentfilestruct);

        fclose(currentfilestruct);
        selectFile(currentFilePath);
    }
    return 0;
}

/******************************************************************************
*				函数名：		Writes
*				函数功能：	文件写入全部内容
*				传入参数：	content     TCHAR*      要保存的内容                    
*				传出参数：	0           int  	    返回0
*******************************************************************************/
int FileIOFunctionsclass::Writes(TCHAR* content){
    closeFile();
    _tfopen_s(&currentfilestruct, currentFilePath, TEXT("w+"));
    fwrite(content, sizeof(TCHAR), lstrlen(content),currentfilestruct);
    
    closeFile();

    selectFile(currentFilePath);

    return 0;
}

/******************************************************************************
*				函数名：		isEndofFile
*				函数功能：	文件判断是否结尾
*				传入参数：	void
*				传出参数：	            bool  	    是结尾返回true，否则返回false
*******************************************************************************/
bool FileIOFunctionsclass::isEndofFile(){
    
    return feof(currentfilestruct);
}

/******************************************************************************
*				函数名：		Read
*				函数功能：	文件读取一个字符
*				传入参数：	void
*				传出参数：	tmp         TCHAR  	    返回一个字符
*******************************************************************************/
TCHAR FileIOFunctionsclass::Read(){
    TCHAR tmp = { 0 };
    if (!isEndofFile())
        fread(&tmp, sizeof(TCHAR), 1, currentfilestruct);
    return tmp;
}

/******************************************************************************
*				函数名：		GetCurrentLocation
*				函数功能：	文件获取当前文件光标所在位置
*				传入参数：	void
*				传出参数：	tmp         int  	    返回光标位置
*******************************************************************************/
int FileIOFunctionsclass::GetCurrentLocation(){

    return 0;
}

/******************************************************************************
*				函数名：		SetCurrentLocation
*				函数功能：	文件设置当前文件光标所在位置
*				传入参数：	NewLocation int         新的光标位置
*				传出参数：	0           int  	    返回0
*******************************************************************************/
int FileIOFunctionsclass::SetCurrentLocation(int NewLocation){
    fseek(currentfilestruct, NewLocation, SEEK_SET);
    return 0;
}

/******************************************************************************
*				函数名：		MoveNextLocation
*				函数功能：	文件光标向后移动一格
*				传入参数：	void
*				传出参数：	0           int  	    返回0
*******************************************************************************/
int FileIOFunctionsclass::MoveNextLocation(){
    fseek(currentfilestruct, 1, SEEK_CUR);
    return 0;
}

/******************************************************************************
*				函数名：		MovePeriousLocation
*				函数功能：	文件光标向前移动一格
*				传入参数：	void
*				传出参数：	0           int  	    返回0
*******************************************************************************/
int FileIOFunctionsclass::MovePeriousLocation(){

    fseek(currentfilestruct, -1, SEEK_CUR);
    return 0;
}

/******************************************************************************
*				函数名：		closeFile
*				函数功能：	关闭文件
*				传入参数：	void
*				传出参数：	void
*******************************************************************************/
void FileIOFunctionsclass::closeFile() {
    if (lstrcmp(currentFilePath, TEXT(""))) {
        fclose(currentfilestruct);
        lstrcpy(currentFilePath, TEXT(""));
    }

}

/******************************************************************************
*				函数名：		selectFile
*				函数功能：	设置读取的文件路径
*				传入参数：	FilePath    TCHAR*      选择文件路径
*				传出参数：	void
*******************************************************************************/
void FileIOFunctionsclass::selectFile(TCHAR* FilePath) {
    lstrcpy(tmpFilePath, FilePath);
    if (lstrcmp(tmpFilePath, TEXT(""))) {
        lstrcpy(currentFilePath, tmpFilePath);
        _tfopen_s(&currentfilestruct, currentFilePath, TEXT("r+"));
    }
   
}