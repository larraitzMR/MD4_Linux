#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>		// UDP and TCP socket
#include <netinet/in.h>		// in_addr struct
#include <fcntl.h>		// To configure socket
#include <arpa/inet.h>      	// inet_ntoa() for IP format
#include <errno.h>		// For error handling
#include "network.h"


// =======================================================================
//
//  GLOBAL VARIABLES
//
// =======================================================================
struct sockaddr_in local_socket; //Configuration for local socket


// =======================================================================
//
//  FUNCTIONS
//
// =======================================================================

/* Configure a local UDP listen socket in a given port.
 * Return socket descriptor or -1 in case of error
 */

int    server;
int    address_len;
int    sendrc;
int    bndrc;
char*  greeting;
struct sockaddr_in  local_Address;

int true = 1;

int create_tcp_conection(int portNum) {

	address_len = sizeof(local_Address);

	memset(&local_Address,0x00,sizeof(local_Address));
	local_Address.sin_family = AF_INET;
	local_Address.sin_port = htons(portNum);
	local_Address.sin_addr.s_addr = htonl(INADDR_ANY);

	/*  Asignar el socket.  */
	if((server = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
	  printf("anomalía en la asignación de socket\n");
	  perror(NULL);
	  exit(-1);
	}

	if (setsockopt(server,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1)
	{
	    perror("Setsockopt");
	    exit(1);
	}

	/* Realizar el enlace (bind). */
	if((bndrc=bind(server,(struct sockaddr*)&local_Address, address_len))<0)
	{
	 printf("Enlace fallido\n");
	 perror(NULL);
	 exit(-1);
	}

	/* Invocar el método listen. */
	listen(server, 1);

	return server;
}

void close_tcp_connection(int client){
	close(server);
	close(client);

}

void send_tcp_message(char *data, int client){

	/* Envía un saludo (greeting) al cliente. */
	//if((sendrc =  write(client, data, sizeof(data)))<0)
	if((sendrc = send(client, data, strlen(data),0))<0)
	{
	  printf("Envío fallido\n");
	  perror(NULL);
	  exit(-1);
	}
}

void read_tcp_message(char *buffer, int client) {
	int n = 0;
	//char buffer[256];

    n = read(client,buffer,255);
    if (n < 0) error("ERROR reading from socket");
  //  printf("%s\n",buffer);
}
