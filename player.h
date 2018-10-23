#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "setting.h"

class player: public Setting
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape rect;

public:
	bool left_rotation = false, right_rotation = false, thrust = false, forward_direction = false;



	player()
	{
		if (!texture.loadFromFile("materials/spaceship.png"))
		{
			std::cout << "Error loading file";
		}

		x = screen_width/2;
		y = screen_height/2;
		life = true;
		spriteradius = 50;

		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(40, 0, 40, 40));

		texture.setSmooth(true);
		sprite.setOrigin(20,20);


	}
	void drawplayer(sf::RenderWindow &window)
	{
		sprite.setPosition(x, y);
		window.draw(sprite);
	}


	void update()
	{
		if (left_rotation)
		{
			angle -= 0.8;
			sprite.setRotation(angle);
		}
		if (right_rotation)
		{
			angle += 0.8;
			sprite.setRotation(angle );
		}

		if (thrust)
		{
				sprite.setTextureRect(sf::IntRect(40, 40, 40, 40));
				dx += sin(angle*0.0174444)*0.01;
			  dy -= cos(angle*0.0174444)*0.01;
		}
		else
		{
			sprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
			dx *= 0.99;
			dy *= 0.99;
		}

		player_speed = sqrt(dx*dx + dy * dy);
		if (player_speed>player_maxspeed)
		{
			dx *= player_maxspeed / player_speed;
			dy *= player_maxspeed / player_speed;
		}

		x += dx;
		y += dy;

		if (x>screen_width) x = 0; if (x<0) x = screen_width;
		if (y>screen_height) y = 0; if (y<0) y = screen_height;



	}
	~player(){}
};
