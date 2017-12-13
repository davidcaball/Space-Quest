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
  const float AIR_DODGE_SPEED = 3.0f;
  const float JUMP_SPEED = 4.5f;
  const int NUM_JUMPS = 2;
  const float SPRITE_SCALE = 3.0f;

  const int NUM_SNAKES = 40;
  const float SNAKE_SCALE = 3.0f;
  const float SNAKE_SPEED = 0.2f;
  const float COLLISION_BUFFER = 25.0f; //disance between center of snake and sprite to signify collision

  const int FIREBALL_DIST_MOD = 250;
  const int NUM_FIREBALLS = 100;
  const float FIREBALL_SCALE = 2.5f;
  const float FIREBALL_SPEED = 1.0f;
  const int FIREBALL_RATE = 500; //time between checks to see if fireball spawns
  const int FIREBALL_ANIM = 1000; //length of animation cycle

  const float AIR_DODGE_TIME = 250.0f;
  const float HIT_ANIM_TIME = 1000.0f; //length of red/white blink and invinc

  const int MAX_NUM_PLATFORMS = 400;
  const float PLATFORM_SEPERATION = 200.0f;
  const float PLATFORM_WIDTH = 200.0f;
  const float PLATFORM_W_SCALE = 2.2f;
  const float PLATFORM_H_SCALE = 2.0f;
  const float FRICTION = 0.02f;
  const float GRAVITY = 0.03f;

}
#endif
