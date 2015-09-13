/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#include "paddle.h"
#include "sdl.h"
#include "variables.h"
#include "random_number_generator.h"

using namespace std;

Paddle::Paddle(float get_x,float get_y,bool get_human){
    x=get_x;
    y=get_y;
    w=PADDLE_WIDTH;
    h=PADDLE_HEIGHT;
    human=get_human;
}

void Paddle::handle_input(){
if(human==true){
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    /**Handle input.*/
    if(keystates[SDLK_LEFT]){
        move_state=PADDLE_LEFT;
    }
    if(keystates[SDLK_RIGHT]){
        move_state=PADDLE_RIGHT;
    }
    if(!keystates[SDLK_LEFT] && !keystates[SDLK_RIGHT]){
        move_state=0;
    }
}
if(human==false){
    if(!ai_check.is_started()){
        ai_check.start();
    }
    if(ai_check.get_ticks()>200){
        ai_check.start();
        for(int i=0;i<balls.size();i++){
            if(x+w<balls.at(i).x){
                move_state=PADDLE_RIGHT;
            }
            if(x>balls.at(i).x+balls.at(i).w){
                move_state=PADDLE_LEFT;
            }
            if(x<balls.at(i).x && x+w>balls.at(i).x+balls.at(i).w){
                move_state=0;
            }
            if(balls.at(i).y_vel<0 && y>0){
                move_state=0;
            }
            if(balls.at(i).y_vel>0 && y<=0){
                move_state=0;
            }
        }
    }
}
}

void Paddle::move(Uint32 delta_ticks){
    if(move_state==PADDLE_LEFT){
        x-=(PADDLE_SPEED * (delta_ticks/1000.0f));/**Move the paddle on the x axis.*/
    }
    if(move_state==PADDLE_RIGHT){
        x+=(PADDLE_SPEED * (delta_ticks/1000.0f));
    }
}

void Paddle::handle_events(){
    /**Keep the paddle in bounds:*/
    if(x<0){/**If the player is too far left.*/
        x=0;
    }
    else if(x+w>SCREEN_WIDTH){/**If the paddle is too far right.*/
        x=SCREEN_WIDTH-w;
    }
}

void Paddle::show(){
    render_texture(x,y,w,h,paddle,NULL,WHITE);
}
