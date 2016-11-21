#pragma once

#include "headers.h"

const int QUEUE_SIZE = 3;
const int BUFSIZE = 1000;

int createSocket();
int acceptConnection(int &sock);
void createThreadForCommunication(int &clientSocket,void* (* func)(void *));
void bindSocketServer(int &sock,int port);
void connectServer(int &sock, int port, char * address);
int handleConnection(int &sock,void* (* func)(void*));
void * receiveMessage(void * socket);


