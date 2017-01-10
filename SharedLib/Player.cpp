#include "headers.h"

Player::Player(float x, float y, float width, float height){
     body.setPosition(x,y);
     body.setSize(sf::Vector2f(width,height));
     body.setFillColor(sf::Color::Blue);
     body.setOrigin(width/2,height/2);
     
     angle = 0;
     speed = 0.1;
     rotation = 0.1;
   }

void Player::checkInput(float elapsed){
    
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
      angle -= rotation;
      body.setRotation(angle*180/3.14);
   }
    
}

void Player::move(float elapsedTime){
    
    float xoff = cos(angle) * tellMeBitchHowMuchSpeedIs() * elapsedTime;
    float yoff = sin(angle) * tellMeBitchHowMuchSpeedIs() * elapsedTime;
    if(body.getPosition().x < WIDTH && body.getPosition().x > 0 
	&& body.getPosition().y < HEIGHT && body.getPosition().y > 0)
	{
	    	body.move(xoff,yoff);
	}else{
		body.setPosition(sf::Vector2f(300,300));
	}
}

void Player::setElapsedTime(float elapsedTime){
    this->elapsedTime = elapsedTime;
}

void Player::draw(sf::RenderWindow &window){
    window.draw(body);
}

float Player::tellMeBitchHowMuchSpeedIs(){
    if(slowDown){
        speed = 0.03;
    }else{
        speed = 0.1;
    }
    return speed;
}

