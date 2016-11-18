#pragma once

#include "headers.h"

class Player{

    
public:
    
    sf::RectangleShape body;
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    float elapsedTime;
    float angle;
    float rotation;
    bool slowDown;
    
    Player(float x, float y, float width, float height);
    void checkInput(float elapsed);
    void draw(sf::RenderWindow & window);
    void setElapsedTime(float elapsedTime);
    void setTexture(sf::Texture & texture);
    void move(float elapsed);
    float tellMeBitchHowMuchSpeedIs();
  
};
