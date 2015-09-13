/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#include "screen_draw.h"
#include "variables.h"
#include "sdl.h"

using namespace std;

void draw(){
    glClear(GL_COLOR_BUFFER_BIT);/**Clear the screen.*/

    ss.clear();ss.str("");ss<<score_2;msg=ss.str();
    font.show(SCREEN_WIDTH/(2*SCALE),50*SCALE,msg,WHITE);

    ss.clear();ss.str("");ss<<score_1;msg=ss.str();
    font.show(SCREEN_WIDTH/(2*SCALE),SCREEN_HEIGHT-100*SCALE,msg,WHITE);

    for(int i=0;i<paddles.size();i++){
        paddles.at(i).show();
    }
    for(int i=0;i<balls.size();i++){
        balls.at(i).show();
    }

    if(option_frame_rate==true){
        ss.clear();ss.str("");ss<<"FPS: ";ss<<frame_rate;msg=ss.str();
        font.show(0,SCREEN_HEIGHT-70*SCALE,msg,BLACK);
        ss.clear();ss.str("");ss<<"MS Per Frame: ";ss<<ms_per_frame;msg=ss.str();
        font.show(0,SCREEN_HEIGHT-40*SCALE,msg,BLACK);
        msg="Balls:";
        font.show(SCREEN_WIDTH-250*SCALE,SCREEN_HEIGHT-70*SCALE,msg,BLACK);
        ss.clear();ss.str("");ss<<balls.size();msg=ss.str();
        font.show(SCREEN_WIDTH-250*SCALE,SCREEN_HEIGHT-40*SCALE,msg,BLACK);
    }

    SDL_GL_SwapBuffers();/**Update the screen.*/
}
