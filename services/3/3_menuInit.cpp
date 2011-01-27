#include <netinet/in.h>
#include <deque>
#include "../../rcsLib/rcsLib.h"
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
    menu[5]=new menuString(5,"Получить параметры гидросистемы", 0, 6, sndAct, rcvAct);
    menu[6]=new menuString(6,"Открыть створку", 1, 2, sndAct, rcvAct);
    menu[7]=new menuString(7,"Закрыть створку", 1, 2, sndAct, rcvAct);
    menu[8]=new menuString(8,"Остановить створку", 1, 2, sndAct, rcvAct);
    menu[9]=new menuString(9,"Открыть укрытие", 0, 1, sndAct, rcvAct);
    menu[10]=new menuString(10,"Закрыть укрытие", 0, 1, sndAct, rcvAct);
    menu[11]=new menuString(11,"Остановить укрытие", 0, 1, sndAct, rcvAct);
    menu[12]=new menuString(12,"Получить параметры створки", 1, 4, sndAct, rcvAct);
    menu[13]=new menuString(13,"Получить значения датчиков полуосей", 3, 5, sndAct, rcvAct);
    menu[14]=new menuString(14,"Получить вектор состояния УЗ", 1, 3, sndAct, rcvAct);
    menu[15]=new menuString(15,"Сменить режим управления", 1, 1, sndAct, rcvAct);
    menu[16]=new menuString(16,"Запросить режим управления", 0, 2, sndAct, rcvAct);
    menu[17]=new menuString(17,"Запуск процесса контроля функционирования САУ",0,1, sndAct, rcvAct);
    menu[18]=new menuString(18,"Произвести коррекцию гидроцилиндров",0,1, sndAct, rcvAct);
    menu[19]=new menuString(19,"Получить параметры всех створок", 0, 7, sndAct, rcvAct);
    menu[20]=new menuString(20,"Получить значения датчиков всех полуосей", 0, 2, sndAct, rcvAct);
    menu[21]=new menuString(21,"Получить вектор состояния всех УЗ", 0, 4, sndAct, rcvAct);
    menu[25]=new menuString(25,"Тест: Несуществующая функция", 0, 1, sndAct, rcvAct);
    menu[26]=new menuString(12,"Тест (6): Меньше параметров", 0, 2, sndAct, rcvAct);
    menu[27]=new menuString(12,"Тест (6): Меньше результатов", 1, 0, sndAct, rcvAct);
    menu[28]=new menuString(12,"Тест (6): Больше параметров", 2, 2, sndAct, rcvAct);
    menu[29]=new menuString(12,"Тест (6): Больше результатов", 1, 4, sndAct, rcvAct);
    



    menu[32]=new menuString(32,"Аварийное завершение подсистемы", 0, 1, sndAct, rcvAct);
    menu[33]=new menuString(33,"Смена оперативного режима службы",1, 1, sndAct, rcvAct);
    menu[34]=new menuString(34,"Запрос вектора состояния службы",0, 2, sndAct, rcvAct);
    
    menu[1]->paramsConstruct(0, "Время на раскрытие", type_WORD, &coord_type);
    
    menu[6]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);
    menu[7]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);
    menu[8]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);
    menu[12]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);    
    
    menu[13]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);
    menu[13]->paramsConstruct(1, "Номер полуоси", type_BYTE, &zeroValue);
    menu[13]->paramsConstruct(2, "Номер датчика", type_BYTE, &zeroValue);
    
    menu[14]->paramsConstruct(0, "Номер УЗ", type_BYTE, &zeroValue);
    menu[15]->paramsConstruct(0, "Режим (0-ЦПУ, 1-ПДУ, 2-ПМУ)", type_BYTE, &zeroValue);
    
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
    menu[5]->resultsConstruct(5, "Состояние гидросистемы", type_BYTE, &coord_type);

    
    menu[6]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[6]->resultsConstruct(1, "Номер створки", type_BYTE, &coord_type);
    
    menu[7]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[7]->resultsConstruct(1, "Номер створки", type_BYTE, &coord_type);
    
    menu[8]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[8]->resultsConstruct(1, "Номер створки", type_BYTE, &coord_type);
    
    menu[9]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[10]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[11]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    
    menu[12]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[12]->resultsConstruct(1, "Номер створки", type_BYTE, &coord_type);
    menu[12]->resultsConstruct(2, "Код состояния", type_BYTE, &coord_type);
    menu[12]->resultsConstruct(3, "Угол положения", type_WORD, &coord_type);

    menu[13]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[13]->resultsConstruct(1, "Номер створки", type_BYTE, &zeroValue);
    menu[13]->resultsConstruct(2, "Номер полуоси", type_BYTE, &zeroValue);
    menu[13]->resultsConstruct(3, "Номер датчика", type_BYTE, &zeroValue);
    menu[13]->resultsConstruct(4, "Код состояния", type_BYTE, &coord_type);
    
    
    menu[14]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[14]->resultsConstruct(1, "Номер УЗ", type_BYTE, &coord_type);
    menu[14]->resultsConstruct(2, "Вектор состояния УЗ", type_BYTE, &coord_type);
    
    menu[15]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    
    menu[16]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[16]->resultsConstruct(1, "Пульт управления", type_BYTE, &coord_type);
    
    menu[17]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[18]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);

    menu[19]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[19]->resultsConstruct(1, "Код состояния створки 0", type_BYTE, &coord_type);
    menu[19]->resultsConstruct(2, "Угол положения створки 0", type_WORD, &coord_type);
    menu[19]->resultsConstruct(3, "Код состояния створки 1", type_BYTE, &coord_type);
    menu[19]->resultsConstruct(4, "Угол положения створки 1", type_WORD, &coord_type);
    menu[19]->resultsConstruct(5, "Код состояния створки 2", type_BYTE, &coord_type);
    menu[19]->resultsConstruct(6, "Угол положения створки 2", type_WORD, &coord_type);

    menu[20]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[20]->resultsConstruct(1, "Вектор состояния датчиков полуосей", type_WORD, &coord_type);
    
    
    menu[21]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[21]->resultsConstruct(1, "Вектор состояния УЗ 0", type_BYTE, &coord_type);
    menu[21]->resultsConstruct(2, "Вектор состояния УЗ 1", type_BYTE, &coord_type);
    menu[21]->resultsConstruct(3, "Вектор состояния УЗ 2", type_BYTE, &coord_type);
    
    menu[25]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    
    //menuString(12,"Тест (6): Меньше параметров", 0, 2, sndAct, rcvAct);
    
    menu[26]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[26]->resultsConstruct(1, "Номер створки", type_BYTE, &coord_type);
    
    
    //menuString(12,"Тест (6): Меньше результатов", 1, 0, sndAct, rcvAct);
    menu[27]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);
    
    
    //menuString(12,"Тест (6): Больше параметров", 2, 2, sndAct, rcvAct);
    menu[28]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);
    menu[28]->paramsConstruct(1, "Номер створки", type_BYTE, &zeroValue);
    
    menu[28]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[28]->resultsConstruct(1, "Номер створки", type_BYTE, &coord_type);
    
    //menuString(12,"Тест (6): Больше результатов", 1, 4, sndAct, rcvAct);
    
    menu[29]->paramsConstruct(0, "Номер створки", type_BYTE, &zeroValue);
    
    menu[29]->resultsConstruct(0, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[29]->resultsConstruct(1, "Номер створки", type_BYTE, &coord_type);
    menu[29]->resultsConstruct(2, "Квитанция исполнения", type_ERRTYPE, &coord_type);
    menu[29]->resultsConstruct(3, "Номер створки", type_BYTE, &coord_type);
    
    
    
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

