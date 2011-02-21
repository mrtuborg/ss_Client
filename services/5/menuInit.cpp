#include <netinet/in.h>
#include <deque>
#include <extra/ortsTypes/ortsTypes.h>                                          
#include <rcsLib/rcsCmd/rcsCmd.h>                                               
#include <peripheral/udp_port/udp_port.h>                                             
#include <rcsLib/udpAction/udpAction.h>
#include <menuParam.h>
#include <menuString.h>
BYTE menuLen=40;

BYTE resValue=3;
BYTE coord_type=1;
BYTE func_mode=1;
char mode_params[255]={"test"};
WORD Az_adj[1]={0};
WORD Elev_adj[1]={0};
WORD Time_adj[1]={0};
BYTE zeroValue=0;
char tittle[255]={"Тонкий клиент управления службой контроля АРМ \"Система наведения\""};
errType menuInit(menuString **menu, udpAction *sndAct, udpAction *rcvAct)
{
    errType result=err_not_init;
                                
    
    for (int i=0; i<menuLen; i++) menu[i]=0;
    
    menu[1]=new menuString(1,"Запрос текущего функционального режима АРМ", 0, 2, sndAct, rcvAct);
    menu[2]=new menuString(2,"Запрос текущих координат АРМ", 0, 7, sndAct, rcvAct);
    menu[3]=new menuString(3,"Запрос расширенных параметров системы АРМ", 0, 14, sndAct, rcvAct);
    menu[4]=new menuString(4,"Задать поправки АРМ", 3, 1, sndAct, rcvAct);
    menu[5]=new menuString(5,"Режим программного наведения", 1, 1, sndAct, rcvAct);
    menu[6]=new menuString(6,"Режим КН наведения", 0, 1, sndAct, rcvAct);
    menu[7]=new menuString(7,"Режим ЗВВ наведения", 0, 1, sndAct, rcvAct);
    menu[8]=new menuString(8,"Режим Поиск, старт", 3, 1, sndAct, rcvAct);
    menu[9]=new menuString(9,"Режим Поиск, стоп", 0, 1, sndAct, rcvAct);
    
    
    menu[32]=new menuString(32,"Аварийное завершение подсистемы", 0, 1, sndAct, rcvAct);
    menu[33]=new menuString(33,"Смена оперативного режима службы",1, 1, sndAct, rcvAct);
    menu[34]=new menuString(34,"Запрос вектора состояния службы",0, 2, sndAct, rcvAct);
    
    menu[4]->paramsConstruct(0, "Поправка по азимуту", type_DOUBLE, ((BYTE*)Az_adj));
    menu[4]->paramsConstruct(1, "Поправка по углу места", type_DOUBLE, ((BYTE*)Elev_adj));
    menu[4]->paramsConstruct(2, "Поправка времени", type_QWORD, ((BYTE*)Time_adj));
    
    menu[5]->paramsConstruct(0, "Имя файла исходных данных", type_CHARVECTOR, (BYTE*)mode_params);
    menu[8]->paramsConstruct(0, "Число витков", type_BYTE, &zeroValue);
    menu[8]->paramsConstruct(1, "Шаг", type_BYTE, &zeroValue);
    menu[8]->paramsConstruct(2, "Время стояния", type_BYTE, &zeroValue);
    
    menu[33]->paramsConstruct(0, "Новый оперативный режим", type_BYTE, &zeroValue);
    
    menu[1]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[1]->resultsConstruct(1, "Режим функционирования", type_BYTE, &coord_type);
    
    menu[2]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[2]->resultsConstruct(1, "Текущее календарное время", type_QWORD, &coord_type);
    menu[2]->resultsConstruct(2, "Текущее звёздное время", type_QWORD, &coord_type);
    menu[2]->resultsConstruct(3, "Азимут ДОС", type_DOUBLE, &coord_type);
    menu[2]->resultsConstruct(4, "Угол места ДОС", type_DOUBLE, &coord_type);
    menu[2]->resultsConstruct(5, "Программный азимут", type_DOUBLE, &coord_type);
    menu[2]->resultsConstruct(6, "Программный угол места", type_DOUBLE, &coord_type);
    
    menu[3]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[3]->resultsConstruct(1, "Поправка по азимуту", type_DOUBLE, &zeroValue);
    menu[3]->resultsConstruct(2, "Поправка по углу места", type_DOUBLE, &zeroValue);
    menu[3]->resultsConstruct(3, "Пеленг по азимуту", type_DOUBLE, &zeroValue);
    menu[3]->resultsConstruct(4, "Пеленг по углу места", type_DOUBLE, &zeroValue);
    menu[3]->resultsConstruct(5, "Программная скорость по азимуту", type_DOUBLE, &zeroValue);
    menu[3]->resultsConstruct(6, "Программная скорость по углу места", type_DOUBLE, &zeroValue);    
    menu[3]->resultsConstruct(7, "Фактическая скорость по азимуту", type_DOUBLE, &zeroValue);    
    menu[3]->resultsConstruct(8, "Фактическая скорость по углу места", type_DOUBLE, &zeroValue);        
    menu[3]->resultsConstruct(9, "Привязка по азимуту", type_DOUBLE, &zeroValue);
    menu[3]->resultsConstruct(10, "Привязка по углу места", type_DOUBLE, &zeroValue);    
    menu[3]->resultsConstruct(11, "Поправка по времени", type_QWORD, &zeroValue);    
    menu[3]->resultsConstruct(12, "Состояние аппаратуры", type_BYTE, &zeroValue);
    menu[3]->resultsConstruct(13, "Используемое поле камеры", type_BYTE, &zeroValue);
    menu[3]->resultsConstruct(14, "Дискрет", type_BYTE, &zeroValue);
    
    menu[4]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[5]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[6]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[7]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[8]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[9]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);

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

