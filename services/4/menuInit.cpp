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
char tittle[255]={"Тонкий клиент управления службой системы обеспечения СКСЮ"};
errType menuInit(menuString **menu, udpAction *sndAct, udpAction *rcvAct)
{
    errType result=err_not_init;
                                
    
    for (int i=0; i<menuLen; i++) menu[i]=0;
    
    menu[1]=new menuString(1,"Включить СКСЮ", 0, 1, sndAct, rcvAct);
    menu[2]=new menuString(2,"Выключить СКСЮ", 0, 1, sndAct, rcvAct);
    menu[3]=new menuString(3,"Начать измерение", 7, 1, sndAct, rcvAct);
    menu[4]=new menuString(4,"Измерить нуль", 6, 1, sndAct, rcvAct);
    menu[5]=new menuString(5,"Проверка связи между сервером и АРМ СКСЮ", 0, 1, sndAct, rcvAct);
    menu[6]=new menuString(6,"Подготовить результат измерений", 0, 1, sndAct, rcvAct);
    menu[7]=new menuString(7,"Обнулить базу измерений", 0, 1, sndAct, rcvAct);
    menu[8]=new menuString(8,"Начать тарировку", 5, 1, sndAct, rcvAct);
    menu[9]=new menuString(9,"Получить тарировочную точку", 12, 1, sndAct, rcvAct);
    menu[10]=new menuString(10,"Остановить тарировку", 5, 1, sndAct, rcvAct);
    menu[11]=new menuString(11,"Получить результаты измерений", 0, 1, sndAct, rcvAct);
    
    menu[32]=new menuString(32,"Аварийное завершение работы подсистемы", 0, 1, sndAct, rcvAct);
    menu[33]=new menuString(33,"Смена оперативного режима службы",1, 1, sndAct, rcvAct);
    menu[34]=new menuString(34,"Запрос вектора состояния службы",0, 2, sndAct, rcvAct);
    
    menu[3]->paramsConstruct(0, "binning", type_DWORD, &zeroValue);
    menu[3]->paramsConstruct(1, "Niter", type_DWORD, &zeroValue);
    menu[3]->paramsConstruct(2, "FiH", type_FLOAT, &zeroValue);
    menu[3]->paramsConstruct(3, "FiA", type_FLOAT, &zeroValue);
    menu[3]->paramsConstruct(4, "TC", type_FLOAT, &zeroValue);
    menu[3]->paramsConstruct(5, "Wm_c", type_FLOAT, &zeroValue);
    menu[3]->paramsConstruct(6, "Wa", type_FLOAT, &zeroValue);
    
    menu[4]->paramsConstruct(0, "binning", type_DWORD, &zeroValue);
    menu[4]->paramsConstruct(1, "FiH", type_FLOAT, &zeroValue);
    menu[4]->paramsConstruct(2, "FiA", type_FLOAT, &zeroValue);
    menu[4]->paramsConstruct(3, "TC", type_FLOAT, &zeroValue);
    menu[4]->paramsConstruct(4, "Wm_c", type_FLOAT, &zeroValue);
    menu[4]->paramsConstruct(5, "Wa", type_FLOAT, &zeroValue);
    
    menu[8]->paramsConstruct(0, "FiH", type_FLOAT, &zeroValue);
    menu[8]->paramsConstruct(1, "FiA", type_FLOAT, &zeroValue);
    menu[8]->paramsConstruct(2, "TC", type_FLOAT, &zeroValue);
    menu[8]->paramsConstruct(3, "Wm_c", type_FLOAT, &zeroValue);
    menu[8]->paramsConstruct(4, "Wa", type_FLOAT, &zeroValue);
    
    menu[9]->paramsConstruct(0, "binning", type_DWORD, &zeroValue);
    menu[9]->paramsConstruct(1, "Niter", type_DWORD, &zeroValue);
    menu[9]->paramsConstruct(2, "FiH", type_FLOAT, &zeroValue);
    menu[9]->paramsConstruct(3, "FiA", type_FLOAT, &zeroValue);
    menu[9]->paramsConstruct(4, "TC", type_FLOAT, &zeroValue);
    menu[9]->paramsConstruct(5, "Wm_c", type_FLOAT, &zeroValue);
    menu[9]->paramsConstruct(6, "Wa", type_FLOAT, &zeroValue);
    menu[9]->paramsConstruct(7, "X", type_FLOAT, &zeroValue);
    menu[9]->paramsConstruct(8, "Y", type_FLOAT, &zeroValue);
    menu[9]->paramsConstruct(9, "Z", type_FLOAT, &zeroValue);
    menu[9]->paramsConstruct(10, "Fix", type_FLOAT, &zeroValue);
    menu[9]->paramsConstruct(11, "Fiy", type_FLOAT, &zeroValue);
    
    
    menu[10]->paramsConstruct(0, "FiH", type_FLOAT, &zeroValue);
    menu[10]->paramsConstruct(1, "FiA", type_FLOAT, &zeroValue);
    menu[10]->paramsConstruct(2, "TC", type_FLOAT, &zeroValue);
    menu[10]->paramsConstruct(3, "Wm_c", type_FLOAT, &zeroValue);
    menu[10]->paramsConstruct(4, "Wa", type_FLOAT, &zeroValue);
    
    menu[33]->paramsConstruct(0, "Новый оперативный режим", type_BYTE, &zeroValue);
    
    menu[1]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[2]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[3]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[4]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    
    menu[5]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    
    menu[6]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    
    menu[7]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[8]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    
    menu[9]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &zeroValue);
    
    menu[10]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);


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

