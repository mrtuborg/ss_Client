#include "../../ortsTypes/ortsTypes.h"

int verbose_level=0;
bool listen_mode=false;
bool AppTerminated=false;
bool awaitingPattern_mode=false;
bool pattern_found=false;

char ip[255]={0};
char dataFile[255]={0};
char if_name[255]={0};
char patternFile[255]={0};
char reactionFile[255]={0};

WORD wUdp=0;