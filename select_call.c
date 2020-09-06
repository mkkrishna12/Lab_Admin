#include<stdio.h>
#include<string.h>
enum _signal_type{LOGOUT,LOGIN} signal_type;
char year[8],collegeyear[4],branch[6],prn[20],name[40],date[12],time[10];
void selectcall(int argc,char **argv)
{
    signal_type=LOGOUT;
    char ch[]="LOGIN";
    strcpy(date,argv[1]);
    strcpy(time,argv[2]);
    strcpy(collegeyear,argv[3]);
    strcpy(branch,argv[4]);
    strcpy(year,argv[5]);
    strcpy(prn,argv[6]);
    int i=7;
    while(i<argc-1)
    {
        strcat(name,argv[i]);
        strcat(name," ");
        i++;
    }
    if(strcmp(ch,argv[argc-1])==0)
        signal_type=LOGIN;
    if(signal_type==1)
    {
        //fun1
    }
    else
    {
        //fun2
    }
}
int main(int argc,char* argv[])
{
    selectcall(argc,argv);
}
