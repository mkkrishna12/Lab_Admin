#if defined (_WIN32) || defined (_WIN64)
 #define Local_Database ""
 #define Bridge_File ""
 #define File_Transfer ""
 #define WINDOWS 1
 #define LINUX 0
#elif defined (__unix__)
 #define Local_Database ""
 #define Bridge_File ""
 #define File_Transfer ""
 #define WINDOWS 0
 #define LINUX 1
#endif
