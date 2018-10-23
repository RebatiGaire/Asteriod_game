#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Setting
{
public:
  float screen_width, screen_height;
  float x, y, dx, dy, angle;
  float spriteradius;
  float player_speed =0, player_maxspeed, bullet_speed;
  bool life;
  float frame, animation_speed;
  int framecount;

  Setting()
  {
    screen_width = 1360;
    screen_height = 760;
    player_maxspeed = 1.0f;
    bullet_speed = 2.0f;
    angle = 0;
    frame = 0;
    animation_speed = 0.08;


  }
  ~Setting()
  {}

};
