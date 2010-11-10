#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <deque>
#include "myTypes.h"
#include "buffer/ssBuffer.h"
#include "udp/udp_port.h"
#include "ssCmd/cmd.h"
#include "udpAction.h"
#include "global.h"

void* udpListenerThread (void* user)
{
    errType result=err_not_init;
    bool terminate=false;
    udpAction *app=(udpAction*)user;
    
    if (verbose_level) printf("recvEvent: udpListenerThread started\n");
    
    while (!terminate)
    {
        result=app->receiveEvent();
        if ((result==err_timeout) || (result==err_result_ok)) terminate=true;
        sched_yield();
    }
    
    if (verbose_level){
	if (result==err_timeout) printf("udpListenerThread exited by timeout\n");
	else printf("udpListenerThread exited by received data event\n");
    }
}


udpAction::udpAction(BYTE type, WORD port, char* ip)
{
    actionType=type;
    udpPort=new udp_port(port);
    remote_ip.s_addr=inet_addr(ip);
    Command=new cmd;
    //dataLen=0;
}

udpAction::~udpAction()
{
    delete udpPort;
    delete Command;
}

errType udpAction::waitRecvEvent()
{
	errType result=err_not_init;

	if (verbose_level) printf("Wait for receiving answer\n");
	errType ret=(errType)pthread_join(listenerThread, NULL);
	//printf("ret=%d\n",ret);
	return result;
}

errType udpAction::writeDataAsCmd(cmd *data)
{
    errType result=err_not_init;
    BYTE tmp[255];
    Command=data;
    Command->decode(tmp);
/*    printf("Action: ");
    for (int i=0; i<Command->getCmdLength(); i++) printf("%.2X ",tmp[i]);
    printf(", Length=%d\n",Command->getCmdLength());
*/    return result;
}


errType udpAction::writeData(BYTE *data_in, DWORD length)
{
    errType result=err_not_init;
    if (Command==0) Command = new cmd;
    
    Command->encode(data_in[0],length,data_in+1);

/*    printf("Action: ");
    for (int i=0; i<Command->getCmdLength(); i++) printf("%.2X ",Command->get_func_paramsPtr()[i]);
    printf(", Length=%d\n",Command->getCmdLength());
*/
    return result;
}

errType udpAction::readData(BYTE **data_out, DWORD *length)
{
    errType result=err_not_init;
    if (Command == 0 ) result=err_result_error;
    else {
	Command->decode(*data_out);
	*length=Command->getCmdLength();
	result=err_result_ok;
    }
    
    return result;
}

errType udpAction::sendAction()
{
    errType result=err_not_init;
    
    BYTE* data;
    
    if (Command==0) result=err_result_error;
    else {	
	
	udpPort->open_port(actionType); 	//-bool listen_mode=actionType;
	data=new BYTE[Command->getCmdLength()];
	Command->decode(data);
	//---- crc error
	// data[Command->getCmdLength()-2]+=1;
	//---
	result=udpPort->sendData(remote_ip, data, Command->getCmdLength());
	delete data;
	udpPort->close_port();
    }        
    
    return result;
}

errType udpAction::receiveEvent()
{
    errType result=err_not_init;
    BYTE event=0;
    size_t sz[1];
    *sz=1024; // what if greater?
    bool listen_mode=actionType;
    
    BYTE* data;
    
    result=udpPort->udp_async_process(&event,10,0);
    
    if ((result==err_result_ok) & ((event&0x01)==0x01)){
	//printf("Have new data!\n");
	data=new BYTE[*sz];
	result=udpPort->readData(data, sz);
	if (Command==0) Command=new cmd;
	Command->encode(data);
	delete data;
    }
    
    //if (result==err_timeout) printf("timeout\n");
    return result;
}
      
void *udpAction::getParamPtr(WORD offset)
{
    return Command->get_func_paramsPtr(offset);
}

errType udpAction::paramToStringDecode(BYTE paramOffset, MyType paramType, char** string,  WORD length)
{
	// length=0 for scalars and WORD for vector types
	
	int len=0;
	void *ptr=Command->get_func_paramsPtr(paramOffset);
	errType result=err_not_init;
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
		sprintf(*string, "%lu (0x%.8X)", *(DWORD*)ptr, *(DWORD*)ptr);
		result=err_result_ok;
		break;
	    case type_QWORD:
		*string=new char[44];
		sprintf(*string, "%lu (0x%.16X)", *(QWORD*)ptr, *(QWORD*)ptr);
		result=err_result_ok;
		break;
	    case type_FLOAT:
		*string=new char[26];
		sprintf(*string, "%f (0x%.8X)", *(float*)ptr, *(float*)ptr);
		result=err_result_ok;
		break;
	    
	    case type_DOUBLE:
		*string=new char[44];
		sprintf(*string, "%f (0x%.16X)", *(double*)ptr, *(double*)ptr);
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

bool udpAction::isCmdExists()
{
    if (Command==0) return false;
    else return true;
}

errType udpAction::processAction()
{
    errType result=err_not_init;
    switch (actionType)
    {
    case 0: 
	    result=sendAction();
	    break;
    case 1: 
	    delete Command;
	    Command=0;
	    
	    udpPort->open_port(true);
	    int ret=pthread_create(&listenerThread, NULL, udpListenerThread, (void*) this);
	    waitRecvEvent();
	    
	    udpPort->close_port();
	    if (Command==0) result=err_timeout;
	    else result=err_result_ok;
	    break;
    }
    return result;
    
}

DWORD udpAction::getParamLength()
{
    return Command->get_func_paramsLength();
}