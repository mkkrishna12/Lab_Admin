#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

key_t key;
int msgid;

char year[10];
char branch[50];
char prn[30];
char name[200];
int type;
char date[50];
char time[50];
struct _message message;

void init_message_queue()
{
	key = ftok("Socket_Sender", 65);

	msgid = msgget(key, 0666 | IPC_CREAT);
}

void post_message_queue(struct _message* message)
{
	msgsnd(msgid, message, sizeof(*message), 0);
}

void user_auth_start()
{
	
	init_message_queue();
	
	message.message_data.data.user_info.YEAR=year;
	message.message_data.data.user_info.BRANCH=branch;
	message.message_data.data.user_info.PRN=prn;
	message.message_data.data.user_info.NAME=name;
	message.message_data.data.user_info.TYPE=type;
	message.message_data.data.user_info.DATE=date;
	message.message_data.data.user_info.TIME=time;
	
	post_message_queue(&message);
	/*
		Pick PRN and Name from user.txt and create message to send server...
		1. Message Create of type User Info
		2. Send to Client_Sender
	*/
}

void user_auth_end()	
{
	post_message_queue(&message);
	exit(0);
	/*
		Pick PRN and Name from user.txt and create message to send server...
		1. Message Create of type User Info
		2. Send to Client_Sender
	*/
}

void select_call()
{
	/*
		File Handeling to extract TYPE,PRN,NAME;
	*/
}

int main()
{
	select_call();
}
