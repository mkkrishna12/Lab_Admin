enum messageType{Client_Initiation,User_Information,Script,File_Transfer,Loopback,Control_Server_Data};

#if defined (__unix__)
 #define LINUX 1
#else
 #define LINUX 0
#endif
