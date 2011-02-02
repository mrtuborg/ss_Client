#include <netinet/in.h>
#include <deque>
#include <extra/ortsTypes/ortsTypes.h>
#include <comm/udp_port/udp_port.h>
#include <rcsLib/rcsCmd/rcsCmd.h>
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
char tittle[255]={"Тонкий клиент управления службой контроля технологического процесса"};
errType menuInit(menuString **menu, udpAction *sndAct, udpAction *rcvAct)
{
    errType result=err_not_init;
                                
    
    for (int i=0; i<menuLen; i++) menu[i]=0;
    
    menu[1]=new menuString(1,"Добавить задание", 7, 2, sndAct, rcvAct);
    menu[2]=new menuString(2,"Задать аварийное технологическое расписание", 1, 1, sndAct, rcvAct);
    menu[3]=new menuString(3,"Прочитать основное технологическое расписание", 1, 2, sndAct, rcvAct);
    menu[4]=new menuString(4,"Прочитать аварийное технологическое расписание", 0, 2, sndAct, rcvAct);
    menu[5]=new menuString(5,"Прочитать курсор исполнения", 1, 2, sndAct, rcvAct);
    
    menu[32]=new menuString(32,"Аварийное завершение подсистемы", 0, 1, sndAct, rcvAct);
    menu[33]=new menuString(33,"Смена оперативного режима службы",1, 1, sndAct, rcvAct);
    menu[34]=new menuString(34,"Запрос вектора состояния службы",0, 2, sndAct, rcvAct);
    
    menu[1]->paramsConstruct(0, "Идентификатор расписания", type_BYTE, &coord_type);
    menu[1]->paramsConstruct(1, "Идентификатор операции", type_DWORD, &func_mode);
    menu[1]->paramsConstruct(2, "Идентификатор следующей операции", type_DWORD, &func_mode);
    menu[1]->paramsConstruct(3, "Время начала, сек", type_WORD, &func_mode);
    menu[1]->paramsConstruct(4, "Время завершения, сек", type_WORD, &func_mode);
    menu[1]->paramsConstruct(5, "Идентификатор службы", type_BYTE, &func_mode);
    menu[1]->paramsConstruct(6, "Идентификатор функции", type_BYTE, &func_mode);
    menu[1]->paramsConstruct(7, "Параметрическая часть", type_BYTE, &func_mode);


    menu[2]->paramsConstruct(0, "Список задач", type_BYTE, &zeroValue);
    menu[3]->paramsConstruct(0, "Время начала исполнения", type_DWORD, &zeroValue);
    menu[5]->paramsConstruct(0, "Идентификатор расписания", type_BYTE, &zeroValue);

    menu[33]->paramsConstruct(0, "Новый оперативный режим", type_BYTE, &zeroValue);
    
    menu[1]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[1]->resultsConstruct(1, "Расширенный результат", type_DWORD, &coord_type);
    
    menu[2]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);

    menu[3]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[3]->resultsConstruct(1, "Список задач", type_DWORD, &zeroValue);
    
    menu[4]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[4]->resultsConstruct(1, "Список задач", type_DWORD, &zeroValue);
    
    menu[5]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[5]->resultsConstruct(0, "Количество завершённых задач", type_BYTE, &resValue);
    
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

