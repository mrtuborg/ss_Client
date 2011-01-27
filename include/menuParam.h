class menuParam
{
  char *paramName;
  OrtsType type;
  BYTE value[255];
  public:
    menuParam();
    ~menuParam();
    errType printParamName();
      char* getParamName();
    

    errType printString();
    errType paramConstruct(const char* parString, OrtsType parType, BYTE* defaultValue);
    OrtsType getParamType();
    bool isVector();
    int getParamSize();
    

    errType setParamValue(BYTE* value);
    errType getParamValue(BYTE** value);

};
