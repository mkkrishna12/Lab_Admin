#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("Script@Windows Operation Failed!!!\n")
        return 0;
    }
    
    struct _message* message;
    
    message=(struct _message*)agrv[1];
    
    char command[1024]={0};
    
    strcpy(command,message->message_data.data.script.command);
    
    system(command);
    
    return 0;
}
