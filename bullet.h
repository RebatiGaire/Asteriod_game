#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>


class Bullet: public Setting
{

private:
	sf::Texture t2;
	sf::Sprite bullet;

public:

	Bullet()
  {
  	if (!t2.loadFromFile("materials/redbullet.png"))
  		std::cout << "Error loading file";

  	bullet.setTexture(t2);
  	bullet.setTextureRect(sf::IntRect(0, 0, 32, 32));
  	bullet.setScale(0.6, 0.8);
  	bullet.setOrigin(20, 30);

  	bullet.setPosition(x, y);
		spriteradius = 25.0f;
		life = true;

  }

	~Bullet(){}

	void setposition(float sangle, int X, int Y)
  {
  	x = X; y = Y;
  	angle = sangle;

  }

	void update()
  {

  	dx = sin(angle*0.0174444) * bullet_speed;
  	dy = -cos(angle*0.0174444) * bullet_speed;

  	x += dx;
  	y += dy;

  	if (x > screen_width || x<0 || y > screen_height || y < 0)
  	{
  		life = false;

  	}
  	bullet.setPosition(x, y);

  }

	void drawbullet(sf::RenderWindow &window)
  {

  		bullet.setRotation(angle);
  		window.draw(bullet);

  }
};
