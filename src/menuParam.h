class menuParam
{
  char *paramName;
  MyType type;
  BYTE value[255];
  public:
    menuParam();
    ~menuParam();
    errType printParamName();
      char* getParamName();
    

    errType printString();
    errType paramConstruct(const char* parString, MyType parType, BYTE* defaultValue);
    MyType getParamType();
    bool isVector();
    int getParamSize();
    

    errType setParamValue(BYTE* value);
    errType getParamValue(BYTE** value);

};
