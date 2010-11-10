#include <netinet/in.h>
#include <deque>
#include "myTypes.h"
#include "buffer/ssBuffer.h"
#include "udp/udp_port.h"
#include "ssCmd/cmd.h"
#include "udpAction.h"
#include "menuParam.h"
#include "menuString.h"
BYTE menuLen=40;

BYTE resValue=3;
BYTE coord_type=1;
BYTE func_mode=1;
char mode_params[255]={"test"};
WORD Az_adj[1]={0};
WORD Elev_adj[1]={0};
WORD Time_adj[1]={0};
BYTE zeroValue=0;
char tittle[255]={"Тонкий клиент управления службой контроля ТВР подкупольного пространства"};
errType menuInit(menuString **menu, udpAction *sndAct, udpAction *rcvAct)
{
    errType result=err_not_init;
                                
    
    for (int i=0; i<menuLen; i++) menu[i]=0;
    
    menu[1]=new menuString(1,"Запрос текущего функционального режима АРМ", 0, 2, sndAct, rcvAct);
    menu[2]=new menuString(2,"Запрос текущих координат АРМ", 1, 5, sndAct, rcvAct);
    menu[3]=new menuString(3,"Запрос расширенных параметров системы АРМ", 0, 14, sndAct, rcvAct);
    menu[4]=new menuString(4,"Установить функциональный режим АРМ", 2, 1, sndAct, rcvAct);
    menu[5]=new menuString(5,"Задать поправки АРМ", 3, 1, sndAct, rcvAct);
    menu[32]=new menuString(32,"Аварийное завершение подсистемы", 0, 1, sndAct, rcvAct);
    menu[33]=new menuString(33,"Смена оперативного режима службы",1, 1, sndAct, rcvAct);
    menu[34]=new menuString(34,"Запрос вектора состояния службы",0, 2, sndAct, rcvAct);
    
    menu[2]->paramsConstruct(0, "Тип координат", type_BYTE, &coord_type);
    menu[4]->paramsConstruct(0, "Режим функционирования", type_BYTE, &func_mode);
    menu[4]->paramsConstruct(1, "Параметры режима", type_ASCIIZ, (BYTE*)mode_params);
    menu[5]->paramsConstruct(0, "Поправка по азимуту", type_DWORD, ((BYTE*)Az_adj));
    menu[5]->paramsConstruct(1, "Поправка по углу места", type_DWORD, ((BYTE*)Elev_adj));
    menu[5]->paramsConstruct(2, "Поправка времени", type_DWORD, ((BYTE*)Time_adj));
    menu[33]->paramsConstruct(0, "Новый оперативный режим", type_BYTE, &zeroValue);
    
    menu[1]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[1]->resultsConstruct(1, "Режим функционирования", type_BYTE, &coord_type);
    
    menu[2]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[2]->resultsConstruct(1, "Текущее календарное время", type_DWORD, &coord_type);
    menu[2]->resultsConstruct(2, "Текущее звёздное время", type_DWORD, &coord_type);
    menu[2]->resultsConstruct(3, "Текущий азимут", type_DWORD, &coord_type);
    menu[2]->resultsConstruct(4, "Текущий угол места", type_DWORD, &coord_type);
    
    menu[3]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[3]->resultsConstruct(1, "Поправка по азимуту", type_DWORD, &zeroValue);
    menu[3]->resultsConstruct(2, "Поправка по углу места", type_DWORD, &zeroValue);
    menu[3]->resultsConstruct(3, "Поправка по времени", type_DWORD, &zeroValue);
    menu[3]->resultsConstruct(4, "Программная скорость по азимуту", type_DWORD, &zeroValue);
    menu[3]->resultsConstruct(5, "Фактическая скорость по азимуту", type_DWORD, &zeroValue);    
    menu[3]->resultsConstruct(6, "Программная скорость по углу места", type_DWORD, &zeroValue);
    menu[3]->resultsConstruct(7, "Фактическая скорость по углу места", type_DWORD, &zeroValue);    
    menu[3]->resultsConstruct(8, "Пеленг по азимуту", type_DWORD, &zeroValue);
    menu[3]->resultsConstruct(9, "Пеленг по углу места", type_DWORD, &zeroValue);
    menu[3]->resultsConstruct(10, "Привязка по азимуту", type_DWORD, &zeroValue);
    menu[3]->resultsConstruct(11, "Привязка по углу места", type_DWORD, &zeroValue);
    menu[3]->resultsConstruct(12, "Состояние аппаратуры", type_WORD, &zeroValue);
    menu[3]->resultsConstruct(13, "Используемое поле", type_BYTE, &zeroValue);
    
    menu[4]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[5]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);

    menu[32]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[33]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[34]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[34]->resultsConstruct(1, "Вектор состояния службы", type_DWORD, &zeroValue);
    
    return result;
}

errType menuDeinit(menuString **menu)
{
    errType result=err_not_init;
    for (BYTE i=0; i<menuLen; i++) if (menu[i]) delete menu[i];
    return result;
}

