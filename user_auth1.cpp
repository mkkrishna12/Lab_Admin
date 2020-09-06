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
char date[50];
char time[50];
struct _message message;
enum _signal_type{LOGOUT,LOGIN} signal_type;
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
	
	strcpy(message.message_data.data.user_info.YEAR , year);
	strcpy(message.message_data.data.user_info.BRANCH , branch);
	strcpy(message.message_data.data.user_info.PRN , prn);
	strcpy(message.message_data.data.user_info.NAME , name);
	strcpy(message.message_data.data.user_info.DATE , date);
	strcpy(message.message_data.data.user_info.TIME , time);
	message.message_data.data.user_info.TYPE = signal_type;
	
	post_message_queue(&message);
	/*
		Pick PRN and Name from user.txt and create message to send server...
		1. Message Create of type User Info
		2. Send to Client_Sender
	*/
}

void user_auth_end()	
{
	strcpy(message.message_data.data.user_info.YEAR , year);
	strcpy(message.message_data.data.user_info.BRANCH , branch);
	strcpy(message.message_data.data.user_info.PRN , prn);
	strcpy(message.message_data.data.user_info.NAME , name);
	strcpy(message.message_data.data.user_info.DATE , date);
	strcpy(message.message_data.data.user_info.TIME , time);
	message.message_data.data.user_info.TYPE = type;
	
	post_message_queue(&message);
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
