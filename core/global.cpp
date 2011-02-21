#include <extra/ortsTypes/ortsTypes.h>

/// Debug info detailed level.
int verbose_level=0;


/// Global programm terminating signal.
/// Flag variable to signal to all processes about program terminating.
bool AppTerminated=false;

char ip[255]={0};
char if_name[255]={0};

/// Udp port number. Uses as argument from command line which
/// selects udp socket to communicate with a server side.
WORD wUdp=0;
