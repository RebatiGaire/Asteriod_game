#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

class asteriod: public Setting
{

private:
	sf::Texture t2;
	sf::Sprite asteriods;

public:

	asteriod()
	{

		if (!t2.loadFromFile("materials/asteriod.png"))
		{
			std::cout << "Error loading file";
		}
		asteriods.setTexture(t2);
		asteriods.setOrigin(32, 32);
		asteriods.setScale(1.1, 1.1);
		spriteradius = 25;
		life = true;
		animation_speed = 0.08;

	}



	void setposition()
	{
		float g;
		g = rand() % 2;
		if (g == 0)
		{
			x = rand() % 1300;
			y = 0;
			dx = rand() % 2 ? 1 : 0.5;
			dy = rand() % 2 ? 1 : 0.5;

		}
		else
		{
			x = 0;
			y = rand() % 800;
			dx = rand() % 4 ? 1 : 0.5;
			dy = rand() % 2 ? 0.5 : 0.2;

		}

	}


	void update()
	{

			x += dx;
			y += dy;

			if (x > screen_width || x<0 || y>screen_height || y < 0)
				life = false;


				asteriods.setPosition(x, y);
				asteriods.setTextureRect(sf::IntRect(int(frame) * 64, 0, 64, 64));
				(frame>16) ? frame = 0 : frame += animation_speed;

	}

	void drawasteriod(sf::RenderWindow &window)
	{
		window.draw(asteriods);
	}

		~asteriod(){}

};
