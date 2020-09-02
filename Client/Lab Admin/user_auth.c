#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

key_t key;
int msgid;

char PRN[30];
char NAME[200];
int TYPE;

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
	/*
		Pick PRN and Name from user.txt and create message to send server...
		1. Message Create of type User Info
		2. Send to Client_Sender
	*/
}

void user_auth_end()	
{
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