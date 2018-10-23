#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "bullet.h"
#include "asteriod.h"
#include "player.h"

class collision: public Setting
{
private:
	sf::Texture t2;
	sf::Sprite explosion;

public:

	collision()
	{
		if (!t2.loadFromFile("materials/explosion.png"))
			std::cout << "Error loading file";

		explosion.setTexture(t2);
		explosion.setOrigin(128, 128);
		bool life = false;
		framecount = 20;

	}

	~collision(){}


	void explode(sf::RenderWindow &window)
	{

		frame += animation_speed;
		if (frame > framecount) frame -= framecount;
		explosion.setPosition(x, y);
		explosion.setTextureRect(sf::IntRect(int(frame) * 256, 0, 256, 256));
		window.draw(explosion);
		

	}

	bool isEnd()
	{
		return (frame + animation_speed >= 20);
	}
};
