#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <deque>
#include <extra/ortsTypes/ortsTypes.h>
#include <rcsLib/rcsCmd/rcsCmd.h>
#include <peripheral/udp_port/udp_port.h>
#include <rcsLib/udpAction/udpAction.h>

#include <system/arg_parser/carg_parser.h>
#include "console_out.h"
#include "global.h"
#include "menuParam.h"
#include "menuString.h"
#include "menuInit.h"




errType process_cmdLine(int argc, char *argv[])
{
  errType result=err_result_ok;

  const ap_Option options[] =
    {
    { 'V', "version",         ap_no },
    { 'h', "help",            ap_no },
    { 'v', "verbose",         ap_no },
    { 'u', "udp_port",        ap_yes},
    { 'i', "ip_addr",         ap_yes},
    { 'e', "interface",       ap_yes},
    {   0, 0,                 ap_no }};

  Arg_parser parser;
  int argind;

  if( !ap_init( &parser, argc, argv, options, 0 ) )
    { show_error( "Необходимо задать опции запуска", 0, 0 ); return err_result_error; }
  if( ap_error( &parser ) )                             /* bad option */
    { show_error( ap_error( &parser ), 0, 1 ); return err_result_error; }

 for( argind = 0; argind < ap_arguments( &parser ); ++argind )
 {
    const int code = ap_code( &parser, argind );
    if( !code ) break;                                  // no more options
    switch( code )
      {
      case 'V': show_version(); return err_extra;
      case 'h': show_help( verbose_level ); return err_extra;
      case 'v': verbose_level = 1; break;
      case 'u': break;
      case 'e': break;
      case 'i': break;
      default : internal_error( "опция не поддерживается" );
      }
    } // end process options

  for( argind = 0; argind < ap_arguments( &parser ); ++argind )
  {
    const int code = ap_code( &parser, argind );
    const char * arg = ap_argument( &parser, argind );

    switch(code){
        case 'i': //ipaddress
         strcpy(ip,arg);
        break;
        
        case 'u':
	    wUdp=atol(arg);
        break;
        
        case 'e':
         strcpy(if_name, arg);
        break;
        

        default:
        break;
   }

    if( !code ) { // option
       // non-option
      printf( "аргумент `%s' не является опцией ", arg );
      printf( "\n" );
      result=err_result_error;
    }
}
    if (!ap_arguments( &parser )) result=err_result_ok;
    return result;
}

errType fileRead (char* fname, BYTE** buffer, size_t *sz){
    errType result=err_not_init;
    FILE *pFile;
    BYTE *buf;
    int ret;
    //size_t lSize=0;
    
    printf("Open file %s for reading\n",fname);
    pFile=fopen(fname,"rb");
    if (pFile==NULL) {
	printf ("File %s access error. Exiting.\n",fname);
	result=err_result_error;
	return err_result_error;
    }
                           
    fseek (pFile , 0 , SEEK_END);
    *sz = ftell (pFile);
    rewind (pFile);

    buf=new BYTE[*sz];
    ret=fread(buf,*sz,1,pFile);
    
//    printf("File size %lu readed %lu:\n=",ret, *sz);
//    for (int i=0; i<*sz; i++) printf(" %.2X ", buf[i]);
//    printf("=\n");

    fclose(pFile);
    
    *buffer=buf;
    
    if (*sz>0) result=err_result_ok;
    else result=err_result_error;
    
    return result;
}

void dbg_hex_print(BYTE* buffer, size_t len){
    printf("[");
    for (size_t i=0; i<len; i++) printf("%.2X ",buffer[i]);
    printf("]\n");
}

void printTittle()
{
    printf("\n\n\n\n\n");
    printf("------------------------------------------------------------------\n");
    printf("%s\n",tittle);
}

void printMenu(menuString **menu)
{
 printf("------------------------------------------------------------------\n");
 for (BYTE i=0; i<menuLen; i++) 
 {
    if (menu[i])
    {
	printf("\t%d. ",i);
	menu[i]->printString();
    }
    //else printf("%d.\n",i);
 }
 printf("-------------------------------------------------------------------\n");
}

int main(char argc, char *argv[]) {
	errType result=err_result_ok;
	errType ret=process_cmdLine(argc, argv);
	udp_port *uPort;
	udp_port *rcvPort;

	BYTE *buffer;

	size_t sz[1]={0};

	if (ret!=err_result_ok) exit(1);

	uPort=new udp_port(wUdp);
    rcvPort=new udp_port(wUdp+1);
        
    if (uPort->open_port(listen_mode)!=err_result_ok) {
	    printf("Коммуникационный порт не может быть открыт. Выполнение программы остановлено!\n");
	    delete uPort;
	    return -1;
    }
	
	
    	buffer=new BYTE[255];
    	*sz=1024;
    	int choosen=0;
    	char choose[15];
    	    
    	menuString **menu;
    	menu=new menuString*[menuLen];
    	    
    	udpAction *SendAction=new udpAction(0,wUdp,ip);
    	udpAction *RecvEvent=new udpAction(1,wUdp+1,(char*)"127.0.0.1", 5, 0);
    	    
    	menuInit(menu, SendAction, RecvEvent);
    	printTittle();
    	printMenu(menu);
    	do {
    		printf("выбор > ");
    		scanf("%s",choose);
    		//printf("\n--%s\n",choose);
    		//choosen=getchar();
    		if (choose[0]=='c') {
    		    printTittle();
    		    printMenu(menu);
    		}
    		else {
    		    choosen=atoi(choose);
    		    //printf("\n%.2X\n",choosen);
    		    if ((choosen>0) && (choosen<=menuLen)&&(menu[choosen])) {
    			    result=menu[choosen]->mainLoop();
    			    choosen=0;
    		    } else {
    		    		printf ("\tКомманда не поддерживается, либо введена неверная комманда\n");
    		    		printf ("\tВведите 'c' для повторной печати меню комманд\n");
    		    }
    		}
    		
    	    } while(!AppTerminated);
    	    delete []buffer;
        
        
	uPort->close_port();
	delete uPort;
	delete menu;
	
	return 0;
}
