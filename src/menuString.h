class menuString
{
  BYTE itemId;
  char* itemName;
  BYTE paramsQnty;
  BYTE resultsQnty;
  menuParam **paramStrings;
  menuParam **resultStrings;
  udpAction *SendAction;
  udpAction *RecvEvent;
  public:
    menuString(BYTE, const char*, BYTE, BYTE, udpAction*, udpAction*);
    ~menuString();
    errType printParams();
    errType printResults();
    errType printString();
    errType paramsConstruct(BYTE parNo, const char* parName, MyType parType, BYTE* defaultValue);
    errType resultsConstruct(BYTE resNo, const char* resName, MyType resType, BYTE* defaultValue);
    errType setParamValue(BYTE itemNo, BYTE* value);
    errType getParamValue(BYTE itemNo, BYTE** value);
    errType setResultValue(BYTE itemNo, BYTE* value);
    errType getResultValue(BYTE itemNo, BYTE** value);
    
    errType mainLoop();
    errType execMenu();
    errType execFunc();
    errType readAnswer();
    errType convertAnswerToStrings(char **strings);
    errType printAnswer(char **strings);
};
