#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cmath>
#include "player.h"
#include "bullet.h"
#include "asteriod.h"
#include "collision.h"
#include "game_function.h"

int main()
{

	sf::SoundBuffer buffer, buffer1;
	sf::Sound sound, sound1;

	player *myplayer = new player();
	sf::RenderWindow wn(sf::VideoMode(myplayer->screen_width, myplayer->screen_height), "Asteriod", sf::Style::Default);

	sf::Texture t1, t2;
	sf::Sprite background, explosion;
	
	if (!t1.loadFromFile("materials/background.jpg"))
		std::cout << "Error loading file";
	background.setTexture(t1);

	if (!buffer.loadFromFile("materials/bulletsound.ogg"))
		std::cout << "Error loading file";
	sound.setBuffer(buffer);
	sound.setVolume(20.0f);

	if (!buffer1.loadFromFile("materials/Explosion.ogg"))
		std::cout << "Error loading file";
	sound1.setBuffer(buffer1);

	std::list<Bullet*> bulletarray;
	std::list<asteriod*> rocks;
	std::list<collision*> explosions;


	while (wn.isOpen())
	{

			wn.clear();
			wn.draw(background);
			check_event(wn, myplayer, bulletarray, sound);
			update_player(wn, myplayer, bulletarray, rocks);
			update_bullets(wn, bulletarray);
			check_explosion(wn, explosions);
			update_asteriods(wn, rocks);
			check_collision(wn, myplayer, bulletarray, rocks, explosions, sound1);
			wn.display();


	}

	return 0;
}
