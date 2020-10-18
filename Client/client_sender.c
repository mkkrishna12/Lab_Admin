#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <errno.h>
// Socket Libraries
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// IPC Message Queue Libraries
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ifaddrs.h>
#include <signal.h>

// User Defined Libraries
#include "message.h"
#include "macros.h"

#define log_path "Logs/client_sender.log"
#define server_data_path "Settings/server.txt"

// For Message Queues
key_t key;
int msgid;

char *send_buf;
struct core_msg message;
struct _message to_send;
FILE* log_file;

char hostbuffer[256];
char *IPbuffer;
struct hostent *host_entry;
int hostname;

char his_ip[20];
char his_port[6];

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


void checkHostName(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}

void checkHostEntry(struct hostent * hostentry)
{
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}

void checkIPbuffer(char *IPbuffer)
{
    if (NULL == IPbuffer)
    {
        perror("inet_ntoa");
        exit(1);
    }
}

void init_client()
{
     // To retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);

    // To retrieve host information
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);

    // To convert an Internet network address into ASCII string

    IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));

    to_send.message_type = message.msg_type;

    strcpy(to_send.message_data.ip ,IPbuffer);

    strcpy(to_send.message_data.port ,"8080");

    if(LINUX)
    {
        to_send.message_data.os_type=1;
    }
    else
    {
        to_send.message_data.os_type=0;
    }

    send_buf=(char*)&message;

    send_to_server();

}


void process_buf()
{

    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);
    IPbuffer = inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0]));

    to_send.message_type = message.msg_type;

    to_send.message_data.data = message;

    strcpy(to_send.message_data.ip ,IPbuffer);

    strcpy(to_send.message_data.port ,"8080");

    if(LINUX)
    {
        to_send.message_data.os_type=1;
    }
    else
    {
        to_send.message_data.os_type=0;
    }
    
    send_buf = (char*)&to_send;

}

void process_control_message()
{
    strcpy(his_ip,message.msg.control_message.server_data.ip);
    
    strcpy(his_port,message.msg.control_message.server_data.port);

}

void report_log(char* log_data)
{
    fputs(log_data,log_file);
    fputs("\n",log_file);
    fclose(log_file);
}

void handle_signal()
{
    report_log("Termination Signal is Recived");
    exit(1);
}

void parser_server_data()
{
    // Parser server_data_path variables
}

int main()
{
    log_file = fopen(log_path,"w");
    
    if(signal(SIGINT,handle_signal) == SIG_ERR)
        report_log("Unable to Catch SIGINT Signal");
        
    if(signal(SIGKILL,handle_signal) == SIG_ERR)
        report_log("Unable to Catch SIGKILL Signal");
        
    if(signal(SIGTERM,handle_signal) == SIG_ERR)
        report_log("Unable to Catch SIGTERM Signal");

	init_message_queue();
	
	parse_server_data();

	init_client();

	while (1)
	{
		get_message_queue();
		
		if(message.msg_type != Control_Server_Data)
		{
		    process_buf();
		    send_to_server();
		}	
		else
		{
		    process_control_message();
		}
	}


	return 0;
}
