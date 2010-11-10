class udpAction
{
    BYTE actionType; // 1-listening, 0-sending
    struct in_addr remote_ip;
    
    pthread_t listenerThread;
    
    
    udp_port *udpPort;
    cmd *Command;
    
    
    public:
	udpAction(BYTE type, WORD port, char* ip="127.0.0.1");
	~udpAction();
	
	errType writeData(BYTE *data_in, DWORD length);
	errType writeDataAsCmd (cmd *data);
	errType  readData(BYTE **data_out, DWORD *length);
	
	errType receiveEvent();
	errType waitRecvEvent();
	errType sendAction();
	
	errType processAction();
	bool isCmdExists();
	errType paramToStringDecode(BYTE, MyType, char**, WORD length=0);
	void* getParamPtr(WORD offset=0);
	DWORD getParamLength();
};
