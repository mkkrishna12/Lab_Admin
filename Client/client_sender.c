#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ifaddrs.h>
#include "message.h"

#define his_ip "127.0.0.1"
#define his_port "8090"
#define log_path "client_sender.log"


// For Message Queues
key_t key;
int msgid;

char *send_buf;
struct _core_msg message;
struct _message to_send;
FILE* log_file;

void log(char* log_data)
{
    fputs(log_file,log_data);
    fputs(log_file,"\n");
}

int send_to_server()
{

	struct addrinfo hints;
	struct addrinfo *result, *rp;

	int s, sock, j;

	size_t len;
	ssize_t nread;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	s = getaddrinfo(his_ip, his_port, &hints, &result);

	if (s != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sock == -1)
			continue;

		if (connect(sock, rp->ai_addr, rp->ai_addrlen) != -1)
			break;

		close(sock);
	}

	if (rp == NULL)
	{
		fprintf(stderr, "Could Not Connect\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);

	write(sock, send_buf, 1600);

}

void init_message_queue()
{
	key = ftok("Sender_Socket", 65);

	msgid = msgget(key, 0666 | IPC_CREAT);
	
	if(key==-1)
}

void get_message_queue()
{
	msgrcv(msgid, &message, sizeof(message), 0, 0);
}

void init_client()
{
    
    message.message_type=0;
    
    message.message_data.ip = ;
    
    message.message_data.port="8080";
    
    if(LINUX)
    {
        message.message_data.os_type=1;
    }
    else
    {
        message.message_data.os_type=0;
    }
    
    send_buf=(char*)message;
    
    send_to_server();
    
}

void process_buf()
{    
    to_send.message_type = message.msg_type;
    
    to_send.message_data.data = message;
    
    to_send.message_data.ip = ;
    
    to_send.message_data.port = ;
    
    to_send.message_data.os = LINUX;
    
    send_buf = &to_send;
    
}

int main()
{

    log_file = fopen(log_path,"w");
    
	init_message_queue();
	
	init_client();

	while (1)
	{
		get_message_queue();
		process_buf();
		send_to_server();
	}


	return 0;
}
