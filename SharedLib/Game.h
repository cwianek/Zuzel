#include "headers.h"

class Game{

public:
      Player * enemy;
      Player * player;
      bool checkPoints[2];
      bool enemyCheckPoints[2];
      bool focus;
      int * socket;
      void run();
      void checkCollision(Player &player,sf::Image &image);
      void setEnemy(Player & enemy);
      void setPlayer(Player & player);
      void setSocket(int & socket);
      void sendPosition(sf::RectangleShape &shape,int &sock);
      void getTextFromInt(int i, sf::Text &text, sf::Vector2f pos, int size);
      void handleStart(sf::RenderWindow & window, sf::Clock & clock,sf::Sprite & background);
 void trackPositions(sf::RectangleShape & shape, bool checkPoints[]);
 void displayLaps(sf::Text &enemyLaps, sf::Text &playerLaps, int playerLap, int enemyLap);
 int checkIfLapDone(sf::RectangleShape body, int lap, bool checkPoints[]);
void handleEndOfGame(sf::RenderWindow & window,int laps1, int laps2,sf::Font & font);
void endGame(sf::RenderWindow & window, sf::Text & text);
};
