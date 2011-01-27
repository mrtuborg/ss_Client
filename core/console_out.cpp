#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "auto_config.h"

#include "./arg_parser/carg_parser.h"

char PROGVERSION[255] = "0.1";
char Program_name[255]    = "Клиент консоли серверов СУК НОЛС ТИ";
char program_name[255]    = "sc_Client";
char program_year[255]    = "2010";

#ifndef REVISION
    #define REVISION "0"
#endif

void show_help( const char verbose )
{
  printf( "%s - Консольный клиент управления службами сервера СУК НОЛС ТИ\n", Program_name );
  printf( "\nИспользование: %s [опции]\n",program_name);
  printf( "где опции, задаются следующими кдючами:\n" );
  printf( "  -h, --help		справка по опциям программного средства\n" );
  printf( "  -V, --version		печать версии программного средства\n" );
  printf( "  -u<arg>,		задать порт коммуникации с управляемой службой\n"); 
  printf( "  -i<arg>,		задать ip-адрес размещения управляемой службы\n" );
//  printf( "  -v, --verbose		включить режим отладочных сообщений (используется только разработчиком данного средства)\n" );

  if( verbose )
    {
    printf( "  -H, --hidden              example of hidden option (shown with -v -h)\n" );
    }
  printf( "\nОбо всех найденных ошибках просьба сообщать по адресу: nosenko@nicetu.ru\n");
}

void show_version()
{
  printf( "%s версия %s (ревизия №%s)\n", Program_name, PROGVERSION, REVISION);
  /*printf( "Copyright (C) %s Vladimir A. Nosenko.\n", program_year );
  printf( "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n" );
  printf( "This is free software: you are free to change and redistribute it.\n" );
  printf( "There is NO WARRANTY, to the extent permitted by law.\n" );
  */
}

void show_error( const char * msg, const int errcode, const char help )
{
  if( msg && msg[0] != 0 )
    {
    fprintf( stderr, "%s: %s", program_name, msg );
    if( errcode > 0 ) fprintf( stderr, ": %s", strerror( errcode ) );
    fprintf( stderr, "\n" );
    }
    fprintf( stderr, "Используйте ключ `%s --help' для вывода краткой справки по опциям запуска\n",program_name);
}


void internal_error( const char * msg )
{
  char buf[80];
  snprintf( buf, sizeof( buf ), "Внутренняя ошибка: %s.\n", msg );
  show_error( buf, 0, 0 );
  exit( 3 );
}

const char * optname( const int code, const ap_Option options[] )
{
  static char buf[2] = "?";
  int i;

  if( code != 0 )
    for( i = 0; options[i].code; ++i )
      if( code == options[i].code )
        { if( options[i].name ) return options[i].name; else break; }
  if( code > 0 && code < 256 ) buf[0] = code; else buf[0] = '?';
  return buf;
}
