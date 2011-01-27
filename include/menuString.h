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
    errType paramsConstruct(BYTE parNo, const char* parName, OrtsType parType, BYTE* defaultValue);
    errType resultsConstruct(BYTE resNo, const char* resName, OrtsType resType, BYTE* defaultValue);
    errType setParamValue(BYTE itemNo, BYTE* value);
    errType getParamValue(BYTE itemNo, BYTE** value);
    errType setResultValue(BYTE itemNo, BYTE* value);
    errType getResultValue(BYTE itemNo, BYTE** value);
    
    errType mainLoop();
    errType execMenu();
    errType execFunc();
    errType readAnswer(char** strings);
    errType convertAnswerToStrings(char** strings);
    errType printAnswer(char** strings);
    errType paramToStringDecode(const void* ptr, OrtsType paramType, char** string);
};
