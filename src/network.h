#pragma once

#ifndef NETWORK_H_

#define NETWORK_H_


#define IP_ADDRESS		"192.168.1.52"


int create_tcp_conection(int portNum);
void close_tcp_connection();
void send_tcp_message(char *data);
void read_tcp_message(char *buffer);


#endif /* NETWORK_H_ */
