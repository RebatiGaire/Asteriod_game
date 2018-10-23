#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "player.h"
#include "bullet.h"
#include "asteriod.h"
#include "collision.h"



void create_bullet(player *myplayer, std::list<Bullet*> &bulletarray, sf::Sound &sound)
{
  sound.play();
  Bullet *b = new Bullet();
  b->setposition(myplayer->angle, myplayer->x, myplayer->y);
  bulletarray.push_back(b);

}


void check_keydown(sf::Event evnt, player *myplayer)
{

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      myplayer->left_rotation = true;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    myplayer->right_rotation = true;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    myplayer->thrust = true;
}


void check_keyup(sf::Event evnt, player *myplayer, std::list<Bullet*> &bulletarray, sf::Sound &sound)
{
  if (evnt.key.code == sf::Keyboard::Space)
  {

      create_bullet(myplayer, bulletarray, sound);
}
  if (evnt.key.code == sf::Keyboard::Left)
      myplayer->left_rotation = false;
  if (evnt.key.code == sf::Keyboard::Right)
    myplayer->right_rotation = false;
  if (evnt.key.code == sf::Keyboard::Up)
      myplayer->thrust = false;
}


void check_event(sf::RenderWindow &window, player *myplayer, std::list<Bullet*> &bulletarray,  sf::Sound &sound)
{
  sf::Event evnt;
	while (window.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
    {
			window.close();
      break;
    }
		case sf::Event::KeyPressed:
		{
      check_keydown(evnt, myplayer);
			break;
		}

    case sf::Event::KeyReleased:
    {
      check_keyup(evnt, myplayer, bulletarray, sound);
      break;
    }

		}
	}
}


void update_bullets(sf::RenderWindow &window, std::list<Bullet*> &bulletarray)
{

  for (auto i = bulletarray.begin(); i != bulletarray.end();)
  {

    Bullet *b = *i;
    b->update();

    if (b->life == false)
    {
      i = bulletarray.erase(i);
      delete b;
    }
    else
    {
      b->drawbullet(window);
      i++;
    }

  }

}

void update_player(sf::RenderWindow &window, player *myplayer, std::list<Bullet*> &bulletarray, std::list<asteriod*> &rocks)
{
  myplayer->update();
  if (myplayer->life == 0)
  {

      delete myplayer;
      player *myplayer = new player();
    }
  else
    myplayer->drawplayer(window);

}


void create_asteriod(std::list<asteriod*> &rocks)
{
  asteriod *a = new asteriod();
  a->setposition();
  rocks.push_back(a);
}


void update_asteriods(sf::RenderWindow &window, std::list<asteriod*> &rocks)
{

  if (rocks.size() < 12)
  {
    create_asteriod(rocks);
  }

  for (auto i = rocks.begin(); i != rocks.end();)
  {
    asteriod *a = *i;
		a->update();
    if (a->life == false)
		{
			i = rocks.erase(i);
			delete a;

		}
		else
		{
			a->drawasteriod(window);
			i++;
		}
  }

}


bool iscollide(Bullet *b, asteriod *a)
{
  if ((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y) <
    (b->spriteradius + a->spriteradius) *(b->spriteradius + a->spriteradius))
 {
    a->life = 0;
    b->life = 0;
    return true;
  }
  else
    return false;

}


bool iscollide1(player *p, asteriod *a)
{
  if ((a->x - p->x) * (a->x - p->x) + (a->y - p->y) * (a->y - p->y) <
    (p->spriteradius + a->spriteradius) *(p->spriteradius + a->spriteradius))
    {
      p->life = 0;
      a->life = 0;
      return true;
    }
  else
    return false;

}


void check_collision(sf::RenderWindow &window, player *myplayer, std::list<Bullet*> &bulletarray, std::list<asteriod*> &rocks, std::list<collision*> &explosion, sf::Sound &sound)
{
  for (auto a : rocks)
  {
		for (auto b : bulletarray)
		{

			if (iscollide(b, a))
			{
				collision *c = new collision();
				a->life = 0;
				b->life = 0;
				c->life = true;
				c->x = a->x;
				c->y = a->y;
        explosion.push_back(c);
        sound.play();
			}
		}

    if (iscollide1(myplayer, a))
    {
      collision *d = new collision();
      d->life = true;
      d->x = myplayer->x;
      d->y = myplayer->y;

      explosion.push_back(d);
      sound.play();

    }
  }

}


void check_explosion(sf::RenderWindow &window, std::list<collision*> &explosion)
{
  for (auto i = explosion.begin(); i != explosion.end();)
  {
    collision *c = *i;
    if (c->isEnd())
      c->life = false;
    if (c->life == false)
    {
      i = explosion.erase(i);
      delete c;

    }
    if (c->life == true)
    {
        c->explode(window);
        i++;
    }
  }
}
