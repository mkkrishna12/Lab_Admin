#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include "macros.h"
#include "message.h"

void file_transfer(struct _message message){

    char file_trans[200];
    strcpy(file_trans,File_Transfer);

    char file_name[100];

    strcpy(file_name, message.message_data.file_transfer.file_name);


    int k=strlen(File_Transfer);
    int m=strlen(file_name);

    file_name[m]='\0';

    int i=0;
    while(file_name[i]!='\0'){

        while(file_name[i]!='/' && file_name[i]!='\0'){
            file_trans[k]=file_name[i];
            k++;
            i++;
        }

        file_trans[k]='\0';
        if(file_name[i]!='\0'){
            struct stat st = {0};
            if (stat(file_trans, &st) == -1) {
                if(WINDOWS==1){
                    if(mkdir(file_trans) == -1){
                        printf("\nFolder Not created");
                        return 0;
                    }
                }
                /*if(LINUX==1){
                    if(mkdir(file_trans,0777) == -1){
                        printf("\nFolder Not created");
                        return;
                    }
                }*/
            }
            file_trans[k]=file_name[i];
            k++;
            i++;
        }

    }
    file_trans[k]=file_name[i];

    char libPath[PATH_MAX+1];
    snprintf(libPath, PATH_MAX + 1, file_trans);

    FILE *fLib = fopen(libPath , "w+");
    int j=0;
    while(message.message_data.file_transfer.file_buffer[j]){
        char ch = message.message_data.file_transfer.file_buffer[j];
        fprintf(fLib,"%c",ch);
        j++;
    }
    fclose(fLib);

}

int main(){
    struct _message message;
    strcpy(message.message_data.file_transfer.file_name ,"kajal/komal/pranav/d.txt");
    strcpy(message.message_data.file_transfer.file_buffer , "kajal_Pawar Komal_pawar Pranav_pawar");
    file_transfer(message);

}

