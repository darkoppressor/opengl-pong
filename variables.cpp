/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#include "variables.h"
#include "paddle.h"

using namespace std;

/**Screen dimensions and bpp:*/
const float SCALE=1;
int SCREEN_WIDTH=640*SCALE;
int SCREEN_HEIGHT=480*SCALE;
int SCREEN_BPP=0;/**We set the screen's bpp to 0 to make it set to the current screen bpp of the computer.*/

const int PADDLE_LEFT=1;
const int PADDLE_RIGHT=2;
const float PADDLE_SPEED=400.0f*SCALE;
const float PADDLE_HEIGHT=16*SCALE;
const float PADDLE_WIDTH=128*SCALE;
const float BALL_HEIGHT=16*SCALE;
const float BALL_WIDTH=16*SCALE;

const int WHITE=1;
const int BLACK=2;

vector<Paddle> paddles;
vector<Ball> balls;

int score_1=0;
int score_2=0;
int last_score=0;

int frame_count=0;
int frame_rate=0;
float ms_per_frame=0;

bool option_frame_rate=false;
int option_gamemode=1;

/**SDL Specific variables:*/
/**The surfaces that we will be using:*/
SDL_Surface *screen=NULL;/**The screen surface.*/
/**The textures that we will be using:*/
GLuint paddle=NULL;
GLuint ball=NULL;
/**Used to poll for events.*/
SDL_Event event;
/**Music and sound effects:*/
Mix_Music *music=NULL;
Mix_Chunk *beep_paddle=NULL;
Mix_Chunk *beep_wall=NULL;
Mix_Chunk *score=NULL;
/**Font:*/
BitmapFont font;

stringstream ss("");/**String stream used to easily render ints and stuff as strings.*/
string msg="";/**ss passes its information into this string for output with msg_write.*/
