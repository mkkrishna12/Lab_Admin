#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message.h"

#define his_ip "127.0.0.1"
#define his_port "8090"


// For Message Queues
key_t key;
int msgid;

char *send_buf;
struct _message message;

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
}

void get_message_queue()
{
	msgrcv(msgid, &message, sizeof(message), 0, 0);
}

void init_client()
{
    struct _message message;
    
    message.message_type=0;
    
    message.message_data.ip="";
    
    message.message_data.port="";
    
    if(WINDOWS)
    {
        message.message_data.os_type=WINDOWS;
    }
    else if(LINUX)
    {
        message.message_data.os_type=LINUX;
    }
    else
    {
        message.message_data.os_type=NONE;
    }
    
    message.message_data.data.client_info.ip="";
    
    message.message_data.data.client_info.port="";
    
    send_buf=(char*)message;
    
    send_to_server();
    
}

int main()
{
	init_message_queue();
	
	init_client();

	// System Call for opening Lab Admin

	while (1)
	{
		get_message_queue();
		send_buf = (char*)&message;
		send_to_server();
	}


	return 0;
}
