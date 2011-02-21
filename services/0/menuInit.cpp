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
char tittle[255]={"Тонкий клиент управления службой самодиагностики"};

errType menuInit(menuString **menu, udpAction *sndAct, udpAction *rcvAct)
{
    errType result=err_not_init;
                                
    
    for (int i=0; i<menuLen; i++) menu[i]=0;
    
    menu[1]=new menuString(1,"Запрос списка подконтрольных идентификаторов", 0, 2, sndAct, rcvAct);
    menu[2]=new menuString(2,"Запрос информации по подконтрольному процессу", 1, 10, sndAct, rcvAct);
    
    
    menu[3]=new menuString(3,"Перезагрузить сервер", 0, 1, sndAct, rcvAct);
    menu[4]=new menuString(4,"Поиск идентификатора", 1, 2, sndAct, rcvAct);
    menu[5]=new menuString(5,"Завершить процесс", 1, 1, sndAct, rcvAct);
    menu[6]=new menuString(6,"Перезапустить процесс", 1, 1, sndAct, rcvAct);
    menu[7]=new menuString(7,"Установить фильтр", 4, 1, sndAct, rcvAct);
    
    menu[32]=new menuString(32,"Аварийное завершение подсистемы", 0, 1, sndAct, rcvAct);
    menu[33]=new menuString(33,"Смена оперативного режима службы",1, 1, sndAct, rcvAct);
    menu[34]=new menuString(34,"Запрос вектора состояния службы",0, 2, sndAct, rcvAct);
    
    menu[2]->paramsConstruct(0, "Идентификатор процесса", type_WORD, &zeroValue);

    menu[4]->paramsConstruct(0, "Часть имени процесса", type_CHARVECTOR, &zeroValue);
    
    menu[5]->paramsConstruct(0, "Идентификатор процесса", type_WORD, &zeroValue);
    menu[6]->paramsConstruct(0, "Идентификатор процесса", type_WORD, &zeroValue);
    
    menu[7]->paramsConstruct(0, "Имя процесса (строка запуска)", type_CHARVECTOR, &func_mode);
    menu[7]->paramsConstruct(1, "Максимальная нагрузка на ЦП(%) ", type_BYTE, &func_mode);
    menu[7]->paramsConstruct(2, "Максимальный объём используемой памяти(Кб) ", type_DWORD, &func_mode);
    menu[7]->paramsConstruct(3, "Реакция на превышение значения(0/1) ", type_BYTE, &func_mode);

    
    menu[33]->paramsConstruct(0, "Новый оперативный режим", type_BYTE, &func_mode);


    
    menu[1]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[1]->resultsConstruct(1, "Идентификатор", type_WORDVECTOR, &coord_type);
    
    menu[2]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[2]->resultsConstruct(1, "Идентификатор родительского процесса", type_WORD, &coord_type);
    menu[2]->resultsConstruct(2, "Идентификатор пользователя запустившего процесс", type_WORD, &coord_type);
    menu[2]->resultsConstruct(3, "Используемое вычислительное время центрального процессора", type_BYTE, &coord_type);
    menu[2]->resultsConstruct(4, "Маркеры состояния процесса", type_CHARVECTOR, &coord_type);
    menu[2]->resultsConstruct(5, "Время работы процесса", type_QWORD, &coord_type);
    menu[2]->resultsConstruct(6, "Всего задействовано памяти", type_DWORD, &coord_type);    
    menu[2]->resultsConstruct(7, "Задействовано памяти под резидентную часть", type_DWORD, &coord_type);    
    menu[2]->resultsConstruct(8, "Строка запуска", type_CHARVECTOR, &coord_type);    
    menu[2]->resultsConstruct(9, "Переменные среды окружения", type_CHARVECTOR, &coord_type);
    
    
    menu[3]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    
    menu[4]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &resValue);
    menu[4]->resultsConstruct(1, "Идентификатор процесса", type_WORD, &zeroValue);
    
    
    menu[5]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[6]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[7]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    
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

