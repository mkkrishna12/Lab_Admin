#include<stdio.h>
#include<string.h>
int type=0;
char year[8],collegeyear[4],branch[6],prn[20],name[40];
void selectcall(int argc,char **argv)
{
    char ch;
    strcpy(collegeyear,argv[1]);
    strcpy(branch,argv[2]);
    strcpy(year,argv[3]);
    strcpy(prn,argv[4]);
    int i=5;
    while(i<argc-1)
    {
        strcat(name,argv[i]);
        strcat(name," ");
        i++;
    }
    ch=argv[argc-1][0];
    if(ch==49)
        type=1;
    if(type==1)
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
    printf("college year:%s\n branch:%s\n year: %s\nprn:%s\nname:%s\ntype%d ",collegeyear,branch,year,prn,name,type);
}

