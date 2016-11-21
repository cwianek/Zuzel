#include "headers.h"

int createSocket(){

	int sock;
	if( (sock = socket(AF_INET,SOCK_STREAM,0)) < 0 ){
			perror("Could not create socket");
			exit(1);
	}

	return sock;

}

void bindSocketServer(int &sock, int port){

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if( bind(sock,(struct sockaddr*)&server ,sizeof(struct sockaddr)) < 0){
			perror("Could not bind socket!");
			exit(1);
	}

}

void connectServer(int &sock, int port, char * address){
	
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(address);
	
	int odp = connect(sock, (struct sockaddr *) &server, sizeof(server));  
 	if (odp < 0) {  
  		perror("Error connecting to the server!\n");  
  		exit(1);  
 	}  

}

int handleConnection(int &sock,void* (* func)(void*)){
	int clientSocket = acceptConnection(sock);
	createThreadForCommunication(clientSocket,func);
	return clientSocket;
}



void createThreadForCommunication(int &clientSocket,void* (* func)(void*)){
	
	pthread_t rThread;
	int pid = pthread_create(&rThread, NULL,func, (void *) clientSocket);
	if (pid) {
		perror("Cannot create thread");
		exit(1);
	}
}

int acceptConnection(int & sock){
	
	struct sockaddr client;
	int clientSocket;
	int sockaddrSize = sizeof(struct sockaddr);
	
	if((clientSocket = accept(sock,(struct sockaddr*)& client,(socklen_t*) &sockaddrSize))<0){
		perror("Could not accept connection!");
		}
		
	char message[40] = "You are connected with server\n";
	write(clientSocket, message, strlen(message));
	
	return clientSocket;
}
