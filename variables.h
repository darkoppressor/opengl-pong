/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#ifndef variables_h
#define variables_h

#include "paddle.h"
#include "ball.h"
#include "font.h"

#include <string>/**We are declaring a string variable.*/
#include <sstream>/**We are declaring a string stream.*/
#include <vector>

#include <SDL_mixer.h>
#include <SDL_opengl.h>

/**Screen dimensions and bpp:*/
extern const float SCALE;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_BPP;

extern const int PADDLE_LEFT;
extern const int PADDLE_RIGHT;
extern const float PADDLE_SPEED;
extern const float PADDLE_HEIGHT;
extern const float PADDLE_WIDTH;
extern const float BALL_HEIGHT;
extern const float BALL_WIDTH;

extern const int WHITE;
extern const int BLACK;

extern std::vector<Paddle> paddles;
extern std::vector<Ball> balls;

extern int score_1;
extern int score_2;
extern int last_score;

extern int frame_count;
extern int frame_rate;
extern float ms_per_frame;

extern bool option_frame_rate;
extern int option_gamemode;

/**SDL Specific variables:*/
/**The surfaces that we will be using:*/
extern SDL_Surface *screen;
/**The textures that we will be using:*/
extern GLuint paddle;
extern GLuint ball;
/**Used to poll for events.*/
extern SDL_Event event;
/**Music and sound effects:*/
extern Mix_Music *music;
extern Mix_Chunk *beep_paddle;
extern Mix_Chunk *beep_wall;
extern Mix_Chunk *score;
/**Font:*/
extern BitmapFont font;

extern std::stringstream ss;
extern std::string msg;

#endif
