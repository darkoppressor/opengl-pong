/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#include "input.h"
#include "variables.h"
#include "quit.h"
#include "sdl.h"
#include "screen_draw.h"

using namespace std;

void input_game(){
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    /**Handle input.*/
    if(keystates[SDLK_PAUSE]){
        keystates[SDLK_PAUSE]=NULL;
        //pause();
    }
    if(keystates[SDLK_f]){
        keystates[SDLK_f]=NULL;
        option_frame_rate=!option_frame_rate;
    }
    if(keystates[SDLK_m]){
        keystates[SDLK_m]=NULL;
        option_gamemode++;
        if(option_gamemode>2){
            option_gamemode=0;
        }
    }
    if(keystates[SDLK_KP_PLUS]){
        keystates[SDLK_KP_PLUS]=NULL;
        for(int i=0;i<1;i++){
            balls.push_back(Ball());
        }
        //if(balls.size()<1000000){
        //    balls.push_back(Ball());
        //}
    }
    if(keystates[SDLK_KP_MINUS]){
        keystates[SDLK_KP_MINUS]=NULL;
        if(balls.size()>1){
            balls.pop_back();
        }
    }
    if(option_gamemode==0){/**If we are in demo mode.*/
        for(int i=0;i<paddles.size();i++){
            paddles.at(i).human=false;
        }
    }
    if(option_gamemode==1){/**If we are in singleplayer mode.*/
        paddles.at(0).human=true;
        paddles.at(1).human=false;
    }
    if(option_gamemode==2){/**If we are in humans only mode.*/
        for(int i=0;i<paddles.size();i++){
            paddles.at(i).human=true;
        }
    }
    for(int i=0;i<paddles.size();i++){
        paddles.at(i).handle_input();
    }
}
