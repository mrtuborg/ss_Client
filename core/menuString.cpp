#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <deque>
#include <string.h>

#include <extra/ortsTypes/ortsTypes.h>
#include <rcsLib/rcsCmd/rcsCmd.h>
#include <peripheral/udp_port/udp_port.h>
#include <rcsLib/udpAction/udpAction.h>

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

errType menuString::paramsConstruct(BYTE parNo, const char* parName, OrtsType parType, BYTE* defaultValue)
{
    errType result=err_not_init;
    if (parNo<paramsQnty) paramStrings[parNo]->paramConstruct(parName, parType, defaultValue);
    return result;
}

errType menuString::resultsConstruct(BYTE resNo, const char* resName, OrtsType resType, BYTE* defaultValue)
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
    QWORD qwdVal=0;
    float fltVal=0;
    double dblVal=0;
    
    BYTE *value=0;

    printf("\tx. Запуск на исполнение \"%s\"\n",itemName );
    printf("\ta. Отказ запуска на исполнение \"%s\"\n",itemName );
    
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
		    case type_CHAR: scanf("%c", (char*)strVal);
			    value=(BYTE*)strVal;
			    break;
		    case type_DWORD: scanf("%u", &dwdVal);
			    value=(BYTE*)&dwdVal;
			    break;
		    case type_QWORD: scanf("%llu", &qwdVal);
			    value=(BYTE*)&qwdVal;
			    break;
		    case type_FLOAT: scanf("%f", &fltVal);
			    value=(BYTE*)&fltVal;
			    break;
		    case type_DOUBLE: scanf("%lf", &dblVal);
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
		    case type_BYTEVECTOR:
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

	rcsCmd actionCmd(0,itemId); // i don't know number of service

	int size=0;
	OrtsType type;
    
	printf("\tЗапуск на исполнение функции \"%s\"\n\n",itemName );
	
	actionCmd.eraseParams();

	for (int i=0; i<paramsQnty; i++)
	{
	    paramStrings[i]->getParamValue(&param);
	    type=paramStrings[i]->getParamType();
	    if (paramStrings[i]->isVector()) {
		size=*(WORD*)param+sizeof(WORD);
		
	    }
	    else{ 
		size=paramStrings[i]->getParamSize();
	    }
	    actionCmd.pushParam(type, param);
	}
	
	
    
	actionCmd.makeSign();
	printf("\t");
	actionCmd.dbgPrint();
    
	SendAction->writeDataAsCmd(&actionCmd);
    
	printf("\t");
	result=SendAction->processAction();
	
        return result;
}

errType menuString::readAnswer(char** strings)
{
	errType result=err_not_init;
	BYTE *data;
	DWORD length;
        rcsCmd *actionCmd;
        WORD size;
        OrtsType type;
	result=RecvEvent->processAction();
	if (RecvEvent->isCmdExists()) 
	{
	    
	    if (RecvEvent->readDataAsCmd(&actionCmd)==err_result_ok)
	    {
	    		data=new BYTE[1024];
	    		//actionCmd->dbgPrint();
	    		actionCmd->decode(data);
	    		actionCmd->checkSign();
	    		length=actionCmd->getCmdLength();
	    		printf("\tПринят ответ адресата: [");
	    		for (DWORD i=0; i<length; i++) {
	    			printf("%.2X ",data[i]);
	    		}
	    		printf("], Длина ответа: %d\n\n",length);
	    		delete []data;
	    
		
	    		for (int i=0; i< resultsQnty; i++)
	    		{
	    			type=resultStrings[i]->getParamType();
	    			data=(BYTE*)actionCmd->popParam(type);
		    
	    			paramToStringDecode(data, type, &strings[i]);
		    
	    			if ((type&0xF0)!=0) // is vector
	    			{
	    				size=*(WORD*)data;
	    				data+=2;
	    			} else { //is scalar
	    				size=lenOrtsTypes[type];
	    			}
		    //printf("size=%d\n",size);
		    //printf("Result #%d :\n[",i);
		    //for (int k=0; k<size; k++) printf(" %.2X", data[k]);
		    //printf("]\n");
                      
	    		}
	    }
	    
	    

	}// if isCmdExists

	return result;
}

errType menuString::printAnswer (char** strings)
{
	errType result=err_not_init;

	char *name;
	char *value;

	
	WORD stringsOffset=0;
	WORD elQnty=0;
	
	OrtsType valType;
	
	printf("\tРасшифровка:\n");
	//printf("\tresultsQnty: %d\n",resultsQnty);
	for (int i=0; i<resultsQnty; i++){
	    //printf("i=%d\n",i);
	    valType=resultStrings[i]->getParamType();
	    name=resultStrings[i]->getParamName();
	    
	    if (valType & 0xF0)
	    {
		//printf("vectortype\n");
		
		elQnty=*(WORD*)strings[stringsOffset];
		printf("elQnty=%d\n", elQnty);
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


errType menuString::paramToStringDecode(const void* ptr, OrtsType paramType, char** string)
{
	// length=0 for scalars and WORD for vector types
	

	errType result=err_not_init;

	if (ptr==0) return result;

	switch (paramType)
	{
	    case type_ERRTYPE: //errType
	        *string=new char[strlen(strErrTypes[*(BYTE*)ptr])+6];
			sprintf(*string, "%s (0x%.2X)", strErrTypes[*(BYTE*)ptr], *(BYTE*)ptr);
			result=err_result_ok;
			break;
	    case type_BYTE:
			*string=new char[11];
			sprintf(*string, "%d (0x%.2X)", *(BYTE*)ptr, *(BYTE*)ptr);
			result=err_result_ok;
			break;
	    case type_WORD:
			*string=new char[15];
			sprintf(*string, "%.5d (0x%.4X)", *(WORD*)ptr, *(WORD*)ptr);
			result=err_result_ok;
			break;
	    case type_DWORD:

			*string=new char[26];
			sprintf(*string, "%u (0x%.8X)", *(DWORD*)ptr, *(DWORD*)ptr);

			result=err_result_ok;
			break;
	    case type_QWORD:
			*string=new char[44];
			sprintf(*string, "%llu ", *(QWORD*)ptr);
			result=err_result_ok;
			break;
	    case type_FLOAT:
			*string=new char[26];
			sprintf(*string, "%f ", *(float*)ptr);
			result=err_result_ok;
			break;
			
	    case type_DOUBLE:
			*string=new char[44];
			sprintf(*string, "%lf ", *(double*)ptr);
			result=err_result_ok;
			break;
			
	    case type_CHAR:
			*string=new char[10];
			sprintf(*string, "%c", *(char*)ptr);
			result=err_result_ok;
			break;
			
	    default:
			printf("unrecognized type\n");
			break;
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
    
    if (result==err_result_ok) result=readAnswer(strings);
    else printf("\tРезультат не получен, причина: %s\n\n",strErrTypes[result]);
    
    //if (result==err_result_ok) result=convertAnswerToStrings(strings);
    
    if (result==err_result_ok) result=printAnswer(strings);
    else printf("\tРезультат напечатан не будет, причина: %s\n\n",strErrTypes[result]);
    
    return result;
}


