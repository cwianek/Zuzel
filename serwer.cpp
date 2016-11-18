#include "headers.h"

const int PORT = 1234;

Player * enemy;
void * receiveMessage(void * socket);

int main(){
	
	Game game;
	enemy = new Player(400,300,20,5);
    Player * player = new Player(300,300,20,5);
    
    game.setEnemy(*enemy);
    game.setPlayer(*player);
	
	int sock = createSocket();
	bindSocketServer(sock,PORT);
	listen(sock,QUEUE_SIZE);
	int clientSock = handleConnection(sock,receiveMessage); //thread will die when program ends
	
	game.setSocket(clientSock);
	game.run();

	
	return 0;
}


void * receiveMessage(void * socket) {
 int sockfd = (intptr_t) socket;
 char buffer[BUFSIZE];  
  
while(1) {
  int x, y, rotation;
  
  read(sockfd,buffer,10);
  if(buffer[9] == 1)
    x = atof(buffer);
  else if(buffer[9] == 2)
    y = atof(buffer);
  else if(buffer[9] == 3)
    rotation = atof(buffer);
    
  read(sockfd,buffer,10);
  if(buffer[9] == 1)
    x = atof(buffer);
  else if(buffer[9] == 2)
    y = atof(buffer);
  else if(buffer[9] == 3)
    rotation = atof(buffer);
    
    read(sockfd,buffer,10);
  if(buffer[9] == 1)
    x = atof(buffer);
  else if(buffer[9] == 2)
    y = atof(buffer);
  else if(buffer[9] == 3)
    rotation = atof(buffer);
  
  enemy->body.setPosition(x,y);
  enemy->body.setRotation(rotation);
}
}



