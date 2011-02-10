#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <extra/ortsTypes/ortsTypes.h>
#include "menuParam.h"

menuParam::menuParam()
{
    
}

menuParam::~menuParam()
{
    delete paramName;
}

errType menuParam::paramConstruct(const char* parName, OrtsType parType, BYTE* defaultValue)
{
    errType result=err_not_init;
    paramName=new char[strlen(parName)+1];
    strcpy(paramName,parName);
    type=parType;
    setParamValue(defaultValue);
    return result;
}

errType menuParam::setParamValue(BYTE* newValue)
{
    errType result=err_not_init;
    WORD str_len=0;
	int len=0;
	int m=0,n=0;

    switch((OrtsType)type)
    {
	case type_CHAR: // char
	    str_len=strlen((char*)newValue);
	    *value=*newValue;
	    break;
	case type_DWORD: // DWORD
	    memcpy(value,newValue,4);
	    break;
	case type_FLOAT: // float
	    memcpy(value,newValue,sizeof(float));
	    break;
	case type_DOUBLE: // double
	    memcpy(value,newValue,sizeof(double));
	    break;
	case type_CHARVECTOR:
	    *((WORD*)value)=strlen((char*)newValue); // WORD value[0] - vector size
	    strcpy((char*)(value+2), (char*)newValue);
	    break;
	case type_BYTEVECTOR:
		len=strlen((char*)newValue)+1;
		char container[len][len];

		for (int i=0; i<len; i++){
			if (isdigit(newValue[i])){
				    	container[m][n++]=newValue[i];
				    	container[m][n]=0;
			} else {
				    	if (n>0) {
				    		n=0;
				    		m++;
				    	}
			}
		}

		if (n>0) {
			n=0;
			m++;
		}

		for (int i=0; i<m; i++){
			value[i+2]=(BYTE)atoi(container[i]);
		}
		*((WORD*)value)=m;
		break;
	default: // BYTE(1), WORD(2)
	    memcpy(value,newValue,lenOrtsTypes[type]);
	    break;
    }
    return result;
}

errType menuParam::getParamValue(BYTE** parValue)
{
    errType result=err_not_init;
    *parValue=value;
    return result;
}


errType menuParam::printParamName()
{
    if (!paramName) return err_result_error;
    printf("[ %s ]", paramName);
    return err_result_ok;
}


char* menuParam::getParamName()
{
    if (!paramName) return 0;
    return paramName;
}



errType menuParam::printString()
{
    errType result=err_not_init;
    if (!paramName) return err_result_error;

    int vector_length;

    switch((OrtsType)type)
    {
	
	case type_ERRTYPE: // char
	    printf("[ %s: 0x%.2X ]", paramName, *(BYTE*)value);
	break;
	
	case type_CHAR: // char
	    printf("[ %s: %c ]", paramName, *(char*)value);
	break;
	
	case type_DWORD: // DWORD
	    printf("[ %s=%d ]",  paramName, *((DWORD*)value));
	break;
	
	case type_QWORD: // QWORD
	    printf("[ %s=%llu ]",  paramName, *((QWORD*)value));
	break;
	
	case type_FLOAT: // float
	    printf("[ %s=%f ]",  paramName, *((float*)value));
	break;
	
	case type_DOUBLE: // double
	    printf("[ %s=%f ]",  paramName, *((double*)value));
	    break;
	
	case type_BYTE: // BYTE(1), WORD(2)
	    printf("[ %s=", paramName);
	    printf("0x%.2X ]", *value);
	break;
	    
	case type_WORD: // BYTE(1), WORD(2)
	    printf("[ %s=", paramName);
	    printf("0x%.4X ]", *(WORD*)value);
	break;
	
	case type_CHARVECTOR:
	     printf("[ %s: \"", paramName);
	     for (int i=2; i<*(WORD*)value; i++) printf("%c", value[i]);
	     printf("\"]");
	break;
	
	case type_BYTEVECTOR:
		 vector_length=*(WORD*)value;
		 printf("[ %s: \"", paramName);
		 for (int i=0; i<vector_length; i++) printf("%.2X ", value[i+2]);
		 printf("\"]");
	break;

	case type_WORDVECTOR:
		     printf("[ %s: \"", paramName);
		     for (int i=2; i<*(WORD*)value; i+=2) printf("%.4X ", value[i]);
		     printf("\"]");
	break;

    }
    return result;
}

OrtsType menuParam::getParamType()
{
    return type;
}

int menuParam::getParamSize()
{
    int result=0;
    if (!paramName) return err_result_error;
    if (!isVector()) result=lenOrtsTypes[type];
    else result=*(WORD*)value; // [0] - size
    return result;
}

bool menuParam::isVector()
{
    return (type&0xF0)!=0;
}
