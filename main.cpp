/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#include <vector>
#include <ctime>

#include <SDL.h>/**Standard SDL stuff.*/
#include <SDL_mixer.h>/**SDL audio stuff.*/
#include <SDL_image.h>/**SDL graphics stuff.*/

#include "main.h"
#include "timer.h"
#include "variables.h"
#include "input.h"
#include "screen_draw.h"
#include "sdl.h"
#include "logic.h"
#include "quit.h"

using namespace std;

void game_loop(){
    SDL_EnableKeyRepeat(1,0);
    bool loop=true;

    Timer delta;
    delta.start();/**Start the delta timer.*/

    Timer timer_frame_rate;
    timer_frame_rate.start();

    /**Create the paddles:*/
    paddles.clear();
    paddles.push_back(Paddle(0,SCREEN_HEIGHT-PADDLE_HEIGHT,true));
    paddles.push_back(Paddle(0,0,false));
    balls.clear();
    balls.push_back(Ball());

    Mix_PlayMusic(music,-1);

    while(true){
        if(timer_frame_rate.get_ticks()>=1000){
            frame_rate=frame_count;
            frame_count=0;
            ms_per_frame=1000.0f/frame_rate;
            timer_frame_rate.start();
        }
        frame_count++;
        input_game();/**Handle input.*/
        movement(delta.get_ticks());
        hit_detection();
        delta.start();/**Restart delta timer.*/
        draw();/**Render the screen.*/
    }
}

int main(int argc, char* args[]){/**We want to use main this way because SDL doesn't like other ways of using main.*/
    /**The following two lines seed the random number generator.*/
    time_t seconds;
    srand((unsigned int)time(&seconds));

    /**Initiation of SDL stuff.*/
    if(init()==false){
        return 1;
    }
    if(load_files()==false){
        return 1;
    }
    game_loop();
    quit_game();
    return 0;
}
