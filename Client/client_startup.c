#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <windows.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "message.h"


// For Message Queues
key_t key;
int msgid;

// For Socket Interface
unsigned int PORT = 8080;
struct addrinfo hints;
struct addrinfo *result, *rp;
int sfd, s;
struct sockaddr_storage peer_addr;
socklen_t peer_addr_len;
ssize_t nread;

int init_socket()
{
	char port[5];
	itoa(PORT,port,10);

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	s = getaddrinfo(NULL, argv[1], &hints, &result);
	if (s != 0) {
		return 0;
	}

	/* getaddrinfo() returns a list of address structures.
	   Try each address until we successfully bind(2).
	   If socket(2) (or bind(2)) fails, we (close the socket
	   and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;                  /* Success */

		close(sfd);
	}

	if (rp == NULL) {               /* No address succeeded */
		return 0;
	}

	freeaddrinfo(result);           /* No longer needed */

	return 1;
}

void receive_socket()
{
	
}

void init_message_queue()
{
	key = ftok("Lab_Admin", 65);

	msgid = msgget(key, 0666 | IPC_CREAT);
}

void post_message_queue(struct _message* message)
{
	msgsnd(msgid, message, sizeof(*message), 0);
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdParam, int iCmdShow)
{
	init_message_queue();

	while(!init_socket())
		PORT++;




	return 0;
}