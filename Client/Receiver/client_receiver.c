#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../Messages/message.h"

#define Script_Linux_Path "../Scripts/linux_script_handler"
#define File_Transfer_Script "../File_Transfer/file_transfer"

// For Message Queues
key_t key;
int msgid;

char receive_buf[1600];
char my_port[6];

struct addrinfo hints;
struct addrinfo *result, *rp;
int sfd, s;
struct sockaddr_storage peer_addr;
socklen_t peer_addr_len;
ssize_t nread;

int receive_init()
{

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	s = getaddrinfo(NULL, my_port, &hints, &result);

	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return 0;
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype,
		             rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;

		close(sfd);
	}

	if (rp == NULL) {
		fprintf(stderr, "Could not bind\n");
		return 0;
	}

	freeaddrinfo(result);

	return 1;
}


void receive()
{
	peer_addr_len = sizeof(struct sockaddr_storage);
	nread = recvfrom(sfd, receive_buf, 1600, 0,
	                 (struct sockaddr *) &peer_addr, &peer_addr_len);
	if (nread == -1)
		return ;            /* Ignore failed request */

	char host[NI_MAXHOST], service[NI_MAXSERV];

	s = getnameinfo((struct sockaddr *) &peer_addr,
	                peer_addr_len, host, NI_MAXHOST,
	                service, NI_MAXSERV, NI_NUMERICSERV);

	if (s != 0)
	{
		fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

}

void init_message_queue()
{
	key = ftok("Sender_Socket", 65);

	msgid = msgget(key, 0666 | IPC_CREAT);
}

void post_message_queue(struct _message message)
{
	msgsnd(msgid, &message, sizeof(message), 0);
}


void script_handler(struct _message message)
{
    if(LINUX)
    {
        system("");
    }
    else
    {
        printf("Operating System Error!!!\n");
    }
}

void loopback_handler(struct _message message)
{
    struct core_msg loopback;
    
    /*
        Extract User Info from Shared Memory
    */
    
    // Send it to Client_Sender
}

void file_transfer_handler(struct _message message)
{
    if(LINUX)
    {
        system(File_Transfer_Script+" "+(char*) message);
    }
    else
    {
        printf("Operating System Error!!!\n");
    }
}

void parse_local_data()
{

}

int main()
{
    parser_local_data();
    
	init_message_queue();

	if(!receive_init())
	{
		printf("Some Error Took Place.\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		receive();

		struct _message* message;

		message=(struct _message*)receive_buf;
		
		switch(message.message_type)
		{
		    case 2:
		        script_handler(message);
		        break;
		        
		    case 4:
		        loopback_handler(message);
		        break;
		        
		    case 3:
		        file_transfer_handler(message);
		        break;
		        
		    default:
		        printf("Wrong Type of Message Received!!!!\n");
		}
	}


	return 0;
}
