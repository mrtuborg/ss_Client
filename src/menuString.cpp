#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <deque>
#include <string.h>

#include "myTypes.h"
#include "buffer/ssBuffer.h"
#include "udp/udp_port.h"
#include "ssCmd/cmd.h"
#include "udpAction.h"
#include "menuParam.h"
#include "menuString.h"
#include "global.h"



menuString::menuString(BYTE ID, const char* itemString, BYTE paramQnty, BYTE resultQnty, udpAction *sndAct, udpAction *rcvAct)
{
    itemId=ID;
    
    itemName=new char[strlen(itemString)+1];
    strcpy(itemName,itemString);
    paramsQnty=paramQnty;
    resultsQnty=resultQnty;
    SendAction=sndAct;
     RecvEvent=rcvAct;
    
    if (paramsQnty>0)
    {
	paramStrings=new menuParam*[paramsQnty];
	//printf("--- paramStrings=%p\n",paramStrings);
	for (BYTE i=0; i<paramsQnty; i++)
	{
	    paramStrings[i]=new menuParam();
	    //printf("%d: ",i);
	    //printf("paramStrints_ptr=%p\n",paramStrings[i]);
	}
    } else paramStrings=0;
    
    if (resultsQnty>0)
    {
	resultStrings=new menuParam*[resultsQnty];
	//printf("--- paramStrings=%p\n",paramStrings);
	for (BYTE i=0; i<resultsQnty; i++)
	{
	    resultStrings[i]=new menuParam();
	    //printf("%d: ",i);
	    //printf("paramStrints_ptr=%p\n",paramStrings[i]);
	}
    } else resultStrings=0;
    
    
    //action=new udpAction(0, 5003); //Sending to 5003/udp socket
}

menuString::~menuString()
{
    delete itemName;
    //for (BYTE i=0; i<paramsQnty; i++) delete paramStrings[i];
    delete paramStrings;
    delete resultStrings;
    delete SendAction;
    delete RecvEvent;
}

errType menuString::printParams()
{
    if (paramsQnty>0) {
	for (BYTE i=0; i<paramsQnty; i++) {
	 printf("\t\t");
	 if (paramStrings[i]) paramStrings[i]->printString();
	 printf("\n");
	}
    }
    return err_not_init;
}

errType menuString::printResults()
{
    if (resultsQnty>0) {
	for (BYTE i=0; i<resultsQnty; i++) {
	 printf("\t\t");
	 if (resultStrings[i]) resultStrings[i]->printString();
	 printf("\n");
	}
    }
    return err_not_init;
}



errType menuString::printString()
{
    errType result=err_not_init;
    printf("%s\n",itemName);
    printParams();
    return result;
}

errType menuString::paramsConstruct(BYTE parNo, const char* parName, MyType parType, BYTE* defaultValue)
{
    errType result=err_not_init;
    if (parNo<paramsQnty) paramStrings[parNo]->paramConstruct(parName, parType, defaultValue);
    return result;
}

errType menuString::resultsConstruct(BYTE resNo, const char* resName, MyType resType, BYTE* defaultValue)
{
    errType result=err_not_init;
    if (resNo<resultsQnty) resultStrings[resNo]->paramConstruct(resName, resType, defaultValue);
    return result;
}

errType menuString::setParamValue(BYTE parNo, BYTE* value)
{
    errType result=err_not_init;
    if (parNo<paramsQnty) paramStrings[parNo]->setParamValue(value);
    return result;
}

errType menuString::getParamValue(BYTE parNo, BYTE** value)
{
    errType result=err_not_init;
    if (parNo<paramsQnty) paramStrings[parNo]->getParamValue(value);
    return result;
}


errType menuString::setResultValue(BYTE resNo, BYTE* value)
{
    errType result=err_not_init;
    if (resNo<resultsQnty) paramStrings[resNo]->setParamValue(value);
    return result;
}

errType menuString::getResultValue(BYTE resNo, BYTE** value)
{
    errType result=err_not_init;
    if (resNo<resultsQnty) resultStrings[resNo]->getParamValue(value);
    return result;
}

errType menuString::execMenu()
{
    errType result=err_not_init;
    char choose[15];
    int choosen=0;
    char strVal[255];
    int intVal=0;
    DWORD dwdVal=0;
    DWORD qwdVal=0;
    float fltVal=0;
    double dblVal=0;
    
    BYTE* value=0;

    printf("\tx. Запуск на исполнение \"%s\"\n",itemName );
    printf("\ta. Отказ запуска на исполнение\n",itemName );
    
    for (BYTE i=0; i<paramsQnty; i++) {
	if (paramStrings[i]) 
	{
	    printf("\t%d. Установлен ",i+1);
	    paramStrings[i]->printString();
	    printf("\n");
	}
    }
    
    printf("\n");
    
    do {
	printf("\t---> ");
	scanf("%s",choose);
	    
	if (choose[0]!='x')
	{
	    choosen=atoi(choose);
		
	    if (choose[0]=='a') result=err_abort;
	    if ((choosen!=0) && (choosen<=paramsQnty) && (paramStrings[choosen-1]))
	    {
		printf("\tНовое значение: ");
		switch (paramStrings[choosen-1]->getParamType()){
		    case type_CHAR: scanf("%c", (char*) &strVal[0]);
			    value=(BYTE*)strVal;
			    break;
		    case type_DWORD: scanf("%lu", (long unsigned int*) &dwdVal);
			    value=(BYTE*)&dwdVal;
			    break;
		    case type_QWORD: scanf("%lu", (long unsigned int*) &qwdVal);
			    value=(BYTE*)&qwdVal;
			    break;
		    case type_FLOAT: scanf("%f", &fltVal);
			    value=(BYTE*)&fltVal;
			    break;
		    case type_DOUBLE: scanf("%e", (float*) &dblVal);
			    value=(BYTE*)&dblVal;
			    break;
		    case type_BYTE: scanf("%d", &intVal);
			    value=(BYTE*)&intVal;
			    break;
		    case type_WORD: scanf("%d", &intVal);
			    value=(BYTE*)&intVal;
			    break;
		    case type_CHARVECTOR:
			    scanf("%s", strVal);
			    value=(BYTE*)strVal;
			    break;
			     
		    default:
			printf("unrecognized type\n");
			break;
		} // switch
		    
		result=paramStrings[choosen-1]->setParamValue(value);
		printf("\tУстановленное значение ");
		paramStrings[choosen-1]->printString();
		printf("\n\n");
		
	    } else { // choosen > paramsQnty
		if (choose[0]!='a') {
		    printf ("\t\tКомманда не поддерживается, либо введена неверно\n");
		}
	    }
	} //if !x
	else result=err_result_ok;
	
	}while ((choose[0]!='x') && (choose[0]!='a'));
	
	return result;
}

errType menuString::execFunc()
{
	errType result=err_not_init;
	BYTE* param;
	BYTE paramsContainer[1024];
	cmd actionCmd;
	int offset=0;
	int size=0;
    
	printf("\tЗапуск на исполнение функции \"%s\"\n\n",itemName );
	
	
	for (int i=0; i<paramsQnty; i++)
	{
	    paramStrings[i]->getParamValue(&param);
	    
	    if (paramStrings[i]->isVector()) size=*(WORD*)param+sizeof(WORD);
	    else size=paramStrings[i]->getParamSize();
	    
	    memcpy(paramsContainer+offset,param,size);
	    offset+=size;
	}
    
	
	actionCmd.encode(itemId,offset,paramsContainer);
	actionCmd.makeSign();
	printf("\t");
	actionCmd.dbgPrint();
    
	SendAction->writeDataAsCmd(&actionCmd);
    
	printf("\t");
	result=SendAction->processAction();
	
        return result;
}

errType menuString::convertAnswerToStrings(char** strings)
{
	errType result=err_not_init;
	MyType var_type;
	BYTE typeLen;
	WORD var_length;
	WORD offset=0;
	WORD resultsCount=0;
	for (int i=0; i<resultsQnty; i++) {
		
		// IMPORTANT: need to split on (var_length/sizeof(type)) scalar parameters
		    var_type=(MyType)(resultStrings[i]->getParamType()&0x0F); // Scalarize type!
		    typeLen=lenMyTypes[resultStrings[i]->getParamType()];
		    
		    
		    
		    
		if (!resultStrings[i]->isVector()) {
		    var_length=resultStrings[i]->getParamSize();
		    result=RecvEvent->paramToStringDecode(offset, var_type, &strings[resultsCount++]); // if comment this - programm crashes!
		    
		    //if result!=err_result_ok, next values - not true
		    if ((var_type==type_ERRTYPE) && (*(BYTE*)RecvEvent->getParamPtr(offset)!=(BYTE)err_result_ok)) resultsQnty=resultsCount;
		    
		    offset+=var_length;
		} else {
		    var_length=*(WORD*)RecvEvent->getParamPtr(offset); // getParamSize not working i-?
		    
		    // need to compare var_length and remain size for reading
		    offset+=2;
		    WORD var_qnty=var_length/typeLen;
		    strings[resultsCount]=new char[2];
		    *(WORD*)strings[resultsCount]=var_qnty;
		    resultsCount+=1;
		    //read one vector
		    for (int p=0; p<var_length; p+=typeLen) {
			if ((offset+typeLen) <= RecvEvent->getParamLength()) {
			    result=RecvEvent->paramToStringDecode(offset, var_type, &strings[resultsCount++]);
			    offset+=typeLen;
			} else {
			    result=err_params_decode;
			    break;
			}
			
		    }
		    //printf("read vector end\n");
		}
	    }
	    
	
	return result;
}

errType menuString::readAnswer()
{
	errType result=err_not_init;
	BYTE *data;
	DWORD length;
        cmd actionCmd;
	
	result=RecvEvent->processAction();
	
	if (RecvEvent->isCmdExists()) 
	{
	    
	    data=new BYTE[1024];
	    
	    RecvEvent->readData(&data, &length);
	    
	    actionCmd.encode(data);
	    actionCmd.checkSign();
	
	    printf("\tПринят ответ адресата: [");
	    for (int i=0; i<length; i++) {
		printf("%.2X ",data[i]);
	    }    
	    printf("]\n\n",length);
	
    	    delete data;
	}// if isCmdExists

	return result;
}

errType menuString::printAnswer (char** strings)
{
	errType result=err_not_init;
	BYTE maxStrLen=0;
	BYTE minStrLen=0;
        
	char *name;
	char *value;
	
	BYTE offset=0;
	
	WORD stringsOffset=0;
	WORD elQnty=0;
	
	MyType valType;
	
	printf("\tРасшифровка:\n");
	//printf("\tresultsQnty: %d\n",resultsQnty);
	for (int i=0; i<resultsQnty; i++){
	    valType=resultStrings[i]->getParamType();
	    name=resultStrings[i]->getParamName();
	    
	    if (valType & 0xF0)
	    {
		//vectortype	
		elQnty=*(WORD*)strings[stringsOffset];
		stringsOffset+=1;
		if (valType==type_CHARVECTOR) printf("\t%s: ", name);
		for (int k=0; k<elQnty; k++)
		{
		    value=strings[stringsOffset];
		    stringsOffset++;
		    
		    if (valType==type_CHARVECTOR) printf("%s", value);
		    else printf("\t%s #%d: %s\n",name, k+1, value);
		}
		
		if (valType==type_CHARVECTOR) printf("\n");
		
	    } else {
		value=strings[stringsOffset];
		stringsOffset++;
		printf("\t%s: %s\n", name, value);
	    }
	}
	return result;
}


errType menuString::mainLoop()
{
    errType result=err_result_ok;
    char *strings[1024];
    
    if (paramsQnty) result=execMenu();
    
    if (result==err_result_ok) result=execFunc();
    else printf("\tФункция не исполнена, причина: %s\n\n",strErrTypes[result]);
    
    if (result==err_result_ok) result=readAnswer(/*resultsQnty*/);
    else printf("\tРезультат не получен, причина: %s\n\n",strErrTypes[result]);
    
    if (result==err_result_ok) result=convertAnswerToStrings(strings);
    
    if (result==err_result_ok) result=printAnswer(strings);
    else printf("\tРезультат напечатан не будет, причина: %s\n\n",strErrTypes[result]);
    
    return result;
}
