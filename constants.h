#ifndef MYLIB_CONSTANTS_H
#define MYLIB_CONSTANTS_H

//  File Name : constants.h   Purpose : Global Constants

namespace Constants
{
  const float WINDOW_WIDTH = 1600.0f;
  const float WINDOW_HEIGHT = 1200.0f;

  const float GENERAL_MAX_VELOCITY = 5.0f;

  const float PLAYER_MOVE_SPEED = 2.0f;
  const float PLAYER_ACCELERATION = 0.03f;
  const float PLAYER_MAX_VELOCITY = 1.2f;
  const float PLAYER_MAX_FALL_SPEED = 4.0f;
  const float AIR_DODGE_TIME = 250.0f;
  const float AIR_DODGE_SPEED = 3.0f;
  const float JUMP_SPEED = 4.5f;
  const int NUM_JUMPS = 2;
  const float SPRITE_SCALE = 3.0f;

  const int NUM_SNAKES = 20;

  const int MAX_NUM_PLATFORMS = 400;
  const float PLATFORM_SEPERATION = 200.0f;
  const float PLATFORM_WIDTH = 200.0f;
  const float FRICTION = 0.02f;
  const float GRAVITY = 0.03f;

}
#endif
