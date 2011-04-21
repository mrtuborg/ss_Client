#include <netinet/in.h>
#include <deque>
#include <extra/ortsTypes/ortsTypes.h>
#include <peripheral/udp_port/udp_port.h>
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

    
    menu[1]=new menuString(1,"Добавить задание", 10, 2, sndAct, rcvAct);
    menu[2]=new menuString(2,"Запустить пакетное задание на исполнение", 1, 1, sndAct, rcvAct);
    menu[3]=new menuString(3,"Остановить выполнение пакетного задания", 1, 1, sndAct, rcvAct);
    menu[4]=new menuString(4,"Запрос статуса операции", 2, 3, sndAct, rcvAct);
    menu[5]=new menuString(5,"Запрос идентификаторов выполняющегося задания", 1, 2, sndAct, rcvAct);
    menu[6]=new menuString(6,"Запрос содержимого операции", 2, 8, sndAct, rcvAct);
    menu[7]=new menuString(7,"Запрос списка идентификаторов операций", 1, 2, sndAct, rcvAct);
    menu[8]=new menuString(8,"Запустить задание на исполнение", 2, 1, sndAct, rcvAct);
    
    menu[32]=new menuString(32,"Аварийное завершение подсистемы", 0, 1, sndAct, rcvAct);
    menu[33]=new menuString(33,"Смена оперативного режима службы",1, 1, sndAct, rcvAct);
    menu[34]=new menuString(34,"Запрос вектора состояния службы",0, 2, sndAct, rcvAct);
    
    menu[1]->paramsConstruct(0, "Идентификатор расписания", type_BYTE, &coord_type);
    menu[1]->paramsConstruct(1, "Идентификатор операции", type_DWORD, &func_mode);
    menu[1]->paramsConstruct(2, "Идентификатор следующей операции", type_DWORD, &func_mode);
    menu[1]->paramsConstruct(3, "Время начала, сек", type_DWORD, &func_mode);
    menu[1]->paramsConstruct(4, "Время завершения, сек", type_DWORD, &func_mode);
    menu[1]->paramsConstruct(5, "IPv4-адресс службы исполнения", type_DWORD, &func_mode);
    menu[1]->paramsConstruct(6, "UDP порт службы исполнения", type_WORD, &func_mode);
    menu[1]->paramsConstruct(7, "Идентификатор службы", type_BYTE, &func_mode);
    menu[1]->paramsConstruct(8, "Идентификатор функции", type_BYTE, &func_mode);
    menu[1]->paramsConstruct(9, "Параметрическая часть", type_BYTEVECTOR, &func_mode);

    menu[2]->paramsConstruct(0, "Идентификатор пакетного задания", type_BYTE, &coord_type);

    menu[3]->paramsConstruct(0, "Идентификатор пакетного задания", type_BYTE, &coord_type);

    menu[4]->paramsConstruct(0, "Идентификатор пакетного задания", type_BYTE, &coord_type);
    menu[4]->paramsConstruct(1, "Идентификатор операции", type_DWORD, &coord_type);

    menu[5]->paramsConstruct(0, "Идентификатор пакетного задания", type_BYTE, &coord_type);

    menu[6]->paramsConstruct(0, "Идентификатор пакетного задания", type_BYTE, &coord_type);
    menu[6]->paramsConstruct(1, "Идентификатор операции", type_DWORD, &coord_type);

    menu[7]->paramsConstruct(0, "Идентификатор пакетного задания", type_BYTE, &coord_type);

    menu[8]->paramsConstruct(0, "Идентификатор пакетного задания", type_BYTE, &coord_type);
    menu[8]->paramsConstruct(1, "Идентификатор операции", type_DWORD, &coord_type);

    menu[33]->paramsConstruct(0, "Новый оперативный режим", type_BYTE, &zeroValue);
    
    menu[1]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[1]->resultsConstruct(1, "Расширенный результат", type_DWORD, &coord_type);
    
    menu[2]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);

    menu[3]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    
    menu[4]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[4]->resultsConstruct(1, "Статус операции", type_BYTE, &zeroValue);
    menu[4]->resultsConstruct(2, "Ответ исполнителя", type_BYTEVECTOR, &zeroValue);
    
    menu[5]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[5]->resultsConstruct(1, "Идентификаторы исполняющихся операций", type_DWORDVECTOR, &resValue);
    
    menu[6]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[6]->resultsConstruct(1, "Идентификатор следующей операции", type_DWORD, &func_mode);
    menu[6]->resultsConstruct(2, "Время начала, сек", type_DWORD, &func_mode);
    menu[6]->resultsConstruct(3, "Время завершения, сек", type_DWORD, &func_mode);
    menu[6]->resultsConstruct(4, "IPv4-адресс службы исполнения", type_DWORD, &func_mode);
    menu[6]->resultsConstruct(5, "UDP порт службы исполнения", type_WORD, &func_mode);
    menu[6]->resultsConstruct(6, "Идентификатор службы", type_BYTE, &func_mode);
    menu[6]->resultsConstruct(7, "Идентификатор функции", type_BYTE, &func_mode);
    menu[6]->resultsConstruct(8, "Параметрическая часть", type_BYTEVECTOR, &func_mode);

    menu[7]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[7]->resultsConstruct(1, "Массив идентификаторов операций", type_DWORDVECTOR, &resValue);

    menu[8]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);

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

