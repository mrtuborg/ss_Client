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
char tittle[255]={"Тонкий клиент управления службой контроля САУ укрытия"};
errType menuInit(menuString **menu, udpAction *sndAct, udpAction *rcvAct)
{
    errType result=err_not_init;
                                
    
    for (int i=0; i<menuLen; i++) menu[i]=0;
    
    menu[1]=new menuString(1,"Включить питание укрытия", 1, 2, sndAct, rcvAct);
    menu[2]=new menuString(2,"Выключить питание укрытия", 0, 1, sndAct, rcvAct);
    menu[3]=new menuString(3,"Включить гидросистему", 0, 1, sndAct, rcvAct);
    menu[4]=new menuString(4,"Выключить гидросистему", 0, 1, sndAct, rcvAct);
    menu[5]=new menuString(5,"Получить параметры гидросистемы", 0, 5, sndAct, rcvAct);
    menu[6]=new menuString(6,"Открыть створку", 1, 1, sndAct, rcvAct);
    menu[7]=new menuString(7,"Закрыть створку", 1, 1, sndAct, rcvAct);
    menu[8]=new menuString(8,"Остановить створку", 1, 1, sndAct, rcvAct);
    menu[9]=new menuString(9,"Открыть укрытие", 0, 1, sndAct, rcvAct);
    menu[10]=new menuString(10,"Закрыть укрытие", 0, 1, sndAct, rcvAct);
    menu[11]=new menuString(11,"Остановить укрытие", 0, 1, sndAct, rcvAct);
    menu[12]=new menuString(12,"Получить параметры створки", 1, 3, sndAct, rcvAct);
    menu[13]=new menuString(13,"Получить параметры полуосей", 1, 2, sndAct, rcvAct);
    menu[14]=new menuString(14,"Режим удалённого управления", 0, 1, sndAct, rcvAct);
    menu[15]=new menuString(15,"Режим местного управления", 0, 1, sndAct, rcvAct);
    menu[16]=new menuString(16,"Запуск процесса контроля функционирования САУ",0,1, sndAct, rcvAct);
    menu[17]=new menuString(17,"Произвести коррекцию гидроцилиндров",0,1, sndAct, rcvAct);


    menu[32]=new menuString(32,"Аварийное завершение подсистемы", 0, 1, sndAct, rcvAct);
    menu[33]=new menuString(33,"Смена оперативного режима службы",1, 1, sndAct, rcvAct);
    menu[34]=new menuString(34,"Запрос вектора состояния службы",0, 2, sndAct, rcvAct);
    
    menu[1]->paramsConstruct(0, "Время на раскрытие", type_WORD, &coord_type);
    
    menu[6]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);
    menu[7]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);
    menu[8]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);
    menu[12]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);    
    menu[13]->paramsConstruct(0, "Номер полуоси", type_BYTE, &zeroValue);
    
    menu[33]->paramsConstruct(0, "Новый оперативный режим", type_BYTE, &zeroValue);
    
    menu[1]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[1]->resultsConstruct(1, "Состояние гидросистемы", type_WORD, &coord_type);
    
    menu[2]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[3]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[4]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    
    menu[5]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[5]->resultsConstruct(1, "Уровень жидкости", type_BYTE, &coord_type);
    menu[5]->resultsConstruct(2, "Температура жидкости", type_BYTE, &coord_type);
    menu[5]->resultsConstruct(3, "Процент загрязнения фильтров", type_BYTE, &coord_type);
    menu[5]->resultsConstruct(4, "Давление  в системе", type_BYTE, &coord_type);

    
    menu[6]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[7]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[8]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[9]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[10]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[11]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    
    menu[12]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[12]->resultsConstruct(1, "Код состояния", type_BYTE, &coord_type);
    menu[12]->resultsConstruct(2, "Угол положения", type_WORD, &coord_type);
    
    menu[13]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[13]->resultsConstruct(1, "Код состояния", type_BYTE, &coord_type);
    
    
    menu[14]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[15]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[16]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[17]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    
    
    
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

